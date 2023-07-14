#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  g.SetMapRange(BLOCK_SIZE);

  pressTimer = new QTimer(this);
  pressTimer->setSingleShot(true);
  connect(pressTimer, &QTimer::timeout, this, &handleDelayedKeyRelease);

  REFRESH = startTimer(16);
  building_cursor.SetTimerID(startTimer(200));
  building_cursor.AddState("show", "./res/game/build_cursor/build_cursor_%%.png", 0, 3);

  QPixmap cursorPixmap("./res/cursor.png");
  QCursor customCursor(cursorPixmap);
  setCursor(customCursor);

  mediaPlayer = new QMediaPlayer(this);
  playlist = new QMediaPlaylist(this);
  playlist->addMedia(QUrl::fromLocalFile("./res/music/bgm.mp3"));
  playlist->setPlaybackMode(QMediaPlaylist::Loop); // 设置循环播放模式
  mediaPlayer->setPlaylist(playlist);
  mediaPlayer->setVolume(50);
  mediaPlayer->play();

  // 封面动画载入
  QMovie *movie = new QMovie("./res/start/start.gif");
  ui->start_movie->setMovie(movie);
  ui->setting_movie->setMovie(movie);
  movie->start();

  // 引擎初始化
  std::map<Point, int> a = this->g.DecorateInit(BLOCK_SIZE);

  // 玩家初始化（目前不正规）
  Player *p = new Player(1, Point(MAP_WIDTH * BLOCK_SIZE / 2 - 32, MAP_HEIGHT * BLOCK_SIZE / 2 - 32));
  this->g.SetPlayer(p);
  Animation this_player;
  this_player.SetTimerID(startTimer(150));
  this_player.AddState("idle", "./res/game/c1/c1_idel/c1_idel (%%).png", 1, 8);
  this_player.AddState("walk", "./res/game/c1/c1_walk/c1_walk (%%).png", 1, 8);
  this->player_animation_list.push_back(this_player);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
  if (event->timerId() == REFRESH)
  {
    QPoint globalPos = QCursor::pos();
    mousePosition = mapFromGlobal(globalPos);
    repaint();
  }
  else if (event->timerId() == building_cursor.GetTimerID())
  {
    if (isbuilding)
    {
      building_cursor.NextFrame();
    }
  }
  for (int i = 0; i < this->player_animation_list.size(); i++)
  {
    if (event->timerId() == player_animation_list[i].GetTimerID())
    {
      player_animation_list[i].NextFrame();
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  Player player = this->g.GetPlayer();
  Point player_location = player.GetLocation();
  int left_top_x = player_location.GetX() - DEFUALT_WIDTH / 2;
  int left_top_y = player_location.GetY() - DEFUALT_HEIGHT / 2;
  int block_x = left_top_x / BLOCK_SIZE;
  int block_y = left_top_y / BLOCK_SIZE;
  int start_x = -(left_top_x % BLOCK_SIZE);
  int start_y = -(left_top_y % BLOCK_SIZE);
  int player_block_location_x = player_location.GetX() / BLOCK_SIZE;
  int player_block_location_y = player_location.GetY() / BLOCK_SIZE;
  QPainter painter(this);
  // 画地板
  for (int i = 0; i <= DEFUALT_WIDTH / BLOCK_SIZE; i++)
  {
    for (int j = 0; j <= DEFUALT_HEIGHT / BLOCK_SIZE; j++)
    {
      QPixmap p_ground("./res/game/ground.png");
      painter.drawPixmap(start_x + i * BLOCK_SIZE, start_y + j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, p_ground);
    }
  }

  // 画装饰
  QPixmap *pix_decorate[7];
  for (int i = 0; i < 7; ++i)
  {
    QString fileName = QString("./res/game/decorate%1.png").arg(i);
    pix_decorate[i] = new QPixmap(fileName); // 从文件中加载图像
  }
  std::map<Point, int> decorates = this->g.GetDecorate(Point(left_top_x, left_top_y), Point(left_top_x + DEFUALT_WIDTH, left_top_y + DEFUALT_HEIGHT));
  for (auto i = decorates.begin(); i != decorates.end(); i++)
  {
    painter.drawPixmap((*i).first.GetX() - left_top_x, (*i).first.GetY() - left_top_y, DECORATE_SIZE * 2, DECORATE_SIZE * 2, *pix_decorate[(*i).second]);
  }

  // 画建筑选框
  int cursor_block_location_x = (mousePosition.rx() + left_top_x) / BLOCK_SIZE;
  int cursor_block_location_y = (mousePosition.ry() + left_top_y) / BLOCK_SIZE;
  // QMessageBox::information(this, "", QString("%1,%2  %3,%4").arg(player_block_location_x).arg(player_block_location_y).arg(cursor_block_location_x).arg(cursor_block_location_y));
  if (isbuilding && abs(player_block_location_x - cursor_block_location_x) < 5 && abs(player_block_location_y - cursor_block_location_y) < 5)
  {
    int b_x = cursor_block_location_x - block_x;
    int b_y = cursor_block_location_y - block_y;
    QPixmap *pix_building_cursor = new QPixmap(QString::fromStdString(building_cursor.GetNowFrame()));
    painter.drawPixmap(b_x * BLOCK_SIZE + start_x, b_y * BLOCK_SIZE + start_y, BLOCK_SIZE, BLOCK_SIZE, *pix_building_cursor);
  }

  // 画玩家(本机)
  QImage *image_this_player = new QImage(QString::fromStdString(player_animation_list[0].GetNowFrame()));
  painter.drawPixmap(player.GetLocation().GetX() - left_top_x - BLOCK_SIZE / 2, player.GetLocation().GetY() - left_top_y - BLOCK_SIZE / 2, BLOCK_SIZE, BLOCK_SIZE, QPixmap::fromImage(image_this_player->mirrored(player.GetTowardsHorizontal(), false)));
}

void MainWindow::on_B_set_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_B_start_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  // ui->stackedWidget->setVisible(0);
  this->is_playing = true;
}

void MainWindow::on_B_setreturn_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_B_quit_clicked()
{
  this->close();
}

void MainWindow::on_voiceSlider_valueChanged(int value)
{
  mediaPlayer->setVolume(value);
}

void MainWindow::on_B_pause_clicked()
{
  // 后期可制作游戏内设置界面
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_voice_check_stateChanged(int state)
{
  if (state == Qt::Checked)
  {
    mediaPlayer->stop();
  }
  else if (state == Qt::Unchecked)
  {
    mediaPlayer->play();
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_W || event->key() == Qt::Key_A || event->key() == Qt::Key_D || event->key() == Qt::Key_S)
  {
    if (!pressTimer->isActive())
    {
      pressTimer->start(100);
    }
  }
  else
  {
  }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_W)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->player_animation_list[0].SetState("walk");
    g.PlayerMove(g.GetPlayer().GetID(), UP);
  }
  else if (event->key() == Qt::Key_S)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->player_animation_list[0].SetState("walk");
    g.PlayerMove(g.GetPlayer().GetID(), DOWN);
  }
  else if (event->key() == Qt::Key_A)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->player_animation_list[0].SetState("walk");
    g.PlayerMove(g.GetPlayer().GetID(), LEFT);
  }
  else if (event->key() == Qt::Key_D)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->player_animation_list[0].SetState("walk");
    g.PlayerMove(g.GetPlayer().GetID(), RIGHT);
  }
  else if (event->key() == Qt::Key_B){
    this->isbuilding=!this->isbuilding;
  }
  else
  {
    // 处理其他按键事件
  }
}

void MainWindow::handleDelayedKeyRelease()
{
  this->player_animation_list[0].SetState("idle");
}
