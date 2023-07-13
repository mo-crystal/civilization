#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  REFRESH = startTimer(16);
  building_cursor.SetTimerID(startTimer(200));
  building_cursor.AddState("show", "./res/game/build_cursor/build_cursor_%%.png",0,3);


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
  // 开始界面按钮初始化
  QPixmap *pix_button = new QPixmap("./res/start/button_background.png");
  ui->button_background->setPixmap(*pix_button);

  QPixmap *pix_setting_background = new QPixmap("./res/start/setting_background.png");
  ui->setting_background->setPixmap(*pix_setting_background);

  ui->B_start->setStyleSheet(
      "QPushButton{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/start.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}"
      "QPushButton:hover{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/start_selected.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}");

  ui->B_set->setStyleSheet(
      "QPushButton{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/set.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}"
      "QPushButton:hover{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/set_selected.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}");

  ui->B_quit->setStyleSheet(
      "QPushButton{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/quit.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}"
      "QPushButton:hover{"
      "background-color: rgb(255, 255, 255,0);"
      "background-image: url(./res/start/quit_selected.png);"
      "background-repeat: no-repeat;"
      "background-position: center center;"
      "}");
  // 引擎初始化
  std::map<Point, int> a = this->g.DecorateInit(BLOCK_SIZE);
  // 玩家初始化（目前不正规）
  Player *p = new Player(1, Point(MAP_WIDTH * BLOCK_SIZE / 2 - 32, MAP_HEIGHT * BLOCK_SIZE / 2 - 32));
  this->g.SetPlayer(p);
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
}

void MainWindow::on_B_set_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_B_start_clicked()
{
  this->is_playing = true;
  ui->stackedWidget->setVisible(0);
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
