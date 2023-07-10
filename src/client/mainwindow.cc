#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //封面动画载入
  QMovie*movie=new QMovie("./res/start/start.gif");
  ui->start_movie->setMovie(movie);
  movie->start();

  //开始界面按钮初始化
  QPixmap *p_button=new QPixmap("./res/start/button_background.png");
  ui->button_background->setPixmap(*p_button);

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
    "}"
  );

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
    "}"
  );

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
    "}"
  );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

}