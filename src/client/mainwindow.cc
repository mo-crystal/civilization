#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

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
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
  
}

void MainWindow::on_B_set_clicked()
{
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_B_start_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_B_setreturn_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_B_quit_clicked()
{
  this->close();
}