#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  REFRESH = startTimer(16);
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
  //引擎初始化
  g.DecorateInit(BLOCK_SIZE);
  // 玩家初始化（目前不正规）
  Player *p = new Player(1, Point(MAP_WIDTH * BLOCK_SIZE / 2, MAP_HEIGHT * BLOCK_SIZE / 2));
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
    repaint();
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
  QPainter painter(this);
  for (int i = 0; i <= DEFUALT_WIDTH / BLOCK_SIZE; i++)
  {
    for (int j = 0; j <= DEFUALT_HEIGHT / BLOCK_SIZE; j++)
    {
      QPixmap p_ground("./res/game/ground.png");
      painter.drawPixmap(start_x + i * BLOCK_SIZE, start_y + j * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, p_ground);
    }
  }
  QPixmap *pix_decorate[7];
  for (int i = 0; i < 7; ++i)
  {
    QString fileName = QString("./res/game/decorate%1.png").arg(i);
    pix_decorate[i] = new QPixmap(fileName); // 从文件中加载图像
  }
  std::map<Point, int> decorates = this->g.GetDecorate(Point(left_top_x, left_top_y), Point(left_top_x + DEFUALT_WIDTH, left_top_y + DEFUALT_HEIGHT));
  for (auto i = decorates.begin(); i != decorates.end(); i++)
  {
    painter.drawPixmap((*i).first.GetX() - left_top_x, (*i).first.GetY() - left_top_y, *pix_decorate[(*i).second]);
  }
  //painter.drawPixmap(player_location.GetX() - left_top_x, player_location.GetY() - left_top_y, *pix_decorate[3]);
}

void MainWindow::on_B_set_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_B_start_clicked()
{
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