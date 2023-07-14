#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->stackedWidget->setStyleSheet("background-color: transparent;");
  Init();

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

  // 玩家初始化（目前不正规）
  Player *p = new Player(1, Point(MAP_WIDTH * BLOCK_SIZE / 2 - 32, MAP_HEIGHT * BLOCK_SIZE / 2 - 32));
  this->SetPlayer(p);
  p->SetTimerID(startTimer(150));
  p->AddState("idle", "./res/game/c1/c1_idel/c1_idel (%%).png", 1, 8);
  p->AddState("walk", "./res/game/c1/c1_walk/c1_walk (%%).png", 1, 8);
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
  for (auto it = playerList.begin(); it != playerList.end(); it++)
  {
    if (event->timerId() == (*it)->GetTimerID())
    {
      (*it)->NextFrame();
    }
  }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  Player player = *(this->me);
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
  std::map<Point, int> decorates = this->GetDecorate(Point(left_top_x, left_top_y), Point(left_top_x + DEFUALT_WIDTH, left_top_y + DEFUALT_HEIGHT));
  for (auto i = decorates.begin(); i != decorates.end(); i++)
  {
    painter.drawPixmap((*i).first.GetX() - left_top_x, (*i).first.GetY() - left_top_y, DECORATE_SIZE * 2, DECORATE_SIZE * 2, *pix_decorate[(*i).second]);
  }

  // 画建筑选框
  int cursor_block_location_x = (mousePosition.rx() + left_top_x) / BLOCK_SIZE;
  int cursor_block_location_y = (mousePosition.ry() + left_top_y) / BLOCK_SIZE;
  if (isbuilding && abs(player_block_location_x - cursor_block_location_x) < 5 && abs(player_block_location_y - cursor_block_location_y) < 5)
  {
    int b_x = cursor_block_location_x - block_x;
    int b_y = cursor_block_location_y - block_y;
    QPixmap *pix_building_cursor = new QPixmap(QString::fromStdString(building_cursor.GetNowFrame()));
    painter.drawPixmap(b_x * BLOCK_SIZE + start_x, b_y * BLOCK_SIZE + start_y, BLOCK_SIZE, BLOCK_SIZE, *pix_building_cursor);
  }

  // 画玩家(本机)
  QImage *image_this_player = new QImage(QString::fromStdString(player.GetNowFrame()));
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
    this->me->SetState("walk");
    PlayerMove(this->me->GetID(), UP);
  }
  else if (event->key() == Qt::Key_S)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->me->SetState("walk");
    PlayerMove(this->me->GetID(), DOWN);
  }
  else if (event->key() == Qt::Key_A)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->me->SetState("walk");
    PlayerMove(this->me->GetID(), LEFT);
  }
  else if (event->key() == Qt::Key_D)
  {
    if (pressTimer->isActive())
    {
      pressTimer->stop();
    }
    this->me->SetState("walk");
    PlayerMove(this->me->GetID(), RIGHT);
  }
  else if (event->key() == Qt::Key_B)
  {
    this->isbuilding = !this->isbuilding;
  }
  else
  {
    // 处理其他按键事件
  }
}

void MainWindow::handleDelayedKeyRelease()
{
  this->me->SetState("idle");
}

void MainWindow::Init()
{
  // 地图初始化

  // 坐标范围初始化
  map_x_max = MAP_WIDTH * BLOCK_SIZE;
  map_y_max = MAP_HEIGHT * BLOCK_SIZE;

  // 装饰品初始化
  srand(time(0));
  this->decorates.insert(std::pair<Point, int>(Point(MAP_WIDTH * BLOCK_SIZE / 2, MAP_HEIGHT * BLOCK_SIZE / 2), rand() % 7));
  int size = rand() % (MAP_WIDTH * MAP_HEIGHT / 4) + MAP_WIDTH;
  for (int i = 0; i < size; i++)
  {
    int x = BLOCK_SIZE + rand() % (BLOCK_SIZE * MAP_WIDTH - 2 * BLOCK_SIZE);
    int y = BLOCK_SIZE + rand() % (BLOCK_SIZE * MAP_HEIGHT - 2 * BLOCK_SIZE);
    this->decorates.insert(std::pair<Point, int>(Point(x, y), rand() % 7));
  }
}

void MainWindow::SetPlayer(Player *p)
{
  if (this->myID == NO_PLAYER)
  {
    this->me = p;
    this->myID = p->GetID();
    playerList.push_back(p);
  }
}

Construct *MainWindow::GetConstruct(int x, int y)
{
  if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
  {
    return this->gameMap[x][y];
  }
  else
  {
    return NULL;
  }
}

bool MainWindow::AddPlayer(Player *p)
{
  // TODO:判断重复
  this->playerList.push_back(p);
  return true;
}

void MainWindow::PlayerMove(int playerID, int direction)
{
  for (auto it = playerList.begin(); it != playerList.end(); it++)
  {
    if ((*it)->GetID() == playerID)
    {
      double speed = (*it)->GetSpeed();
      if (direction == UP)
      {
        Point new_p((*it)->GetLocation().GetX(), (*it)->GetLocation().GetY() - speed);
        if (new_p.GetY() >= map_y_min && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else if (direction == DOWN)
      {
        Point new_p((*it)->GetLocation().GetX(), (*it)->GetLocation().GetY() + speed);
        if (new_p.GetY() < map_y_max && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
        }
      }
      else if (direction == LEFT)
      {
        Point new_p((*it)->GetLocation().GetX() - speed, (*it)->GetLocation().GetY());
        if (new_p.GetX() >= map_x_min && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
          (*it)->SetTowardsHorizontal(true);
        }
      }
      else if (direction == RIGHT)
      {
        Point new_p((*it)->GetLocation().GetX() + speed, (*it)->GetLocation().GetY());
        if (new_p.GetX() < map_x_max && !Block((*it)->GetLocation(), new_p))
        {
          (*it)->Move(new_p);
          (*it)->SetTowardsHorizontal(false);
        }
      }
      else
      {
      }
    }
  }
}

bool MainWindow::Block(Point p1, Point p2)
{
  // 目前不能斜向移动 可以先不判定 后续有需求改这
  if (p1.GetX() != p2.GetX() && p1.GetY() != p2.GetY())
  {
    return false;
  }
  else if (p1.GetX() != p2.GetX())
  {
    int min_b = std::min(p1.GetX(), p2.GetX()) / BLOCK_SIZE;
    int max_b = std::max(p1.GetX(), p2.GetX()) / BLOCK_SIZE;
    int y = p1.GetY() / BLOCK_SIZE;
    for (int i = min_b; i <= max_b; i++)
    {
      if (gameMap[i][y] != NULL && gameMap[i][y]->IsBlock())
      {
        return true;
      }
    }
    return false;
  }
  else if (p1.GetY() != p2.GetY())
  {
    int min_b = std::min(p1.GetY(), p2.GetY()) / BLOCK_SIZE;
    int max_b = std::max(p1.GetY(), p2.GetY()) / BLOCK_SIZE;
    int x = p1.GetX() / BLOCK_SIZE;
    for (int i = min_b; i <= max_b; i++)
    {
      if (gameMap[x][i] != NULL && gameMap[x][i]->IsBlock())
      {
        return true;
      }
    }
    return false;
  }
  return true;
}

std::map<Point, int> MainWindow::GetDecorate(Point left_top, Point right_down)
{
  std::map<Point, int> res;
  for (auto i = this->decorates.begin(); i != this->decorates.end(); i++)
  {
    if ((*i).first > left_top && (*i).first < right_down)
    {
      res.insert(*i);
    }
  }
  return res;
}