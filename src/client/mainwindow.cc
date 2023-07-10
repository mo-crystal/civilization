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

  //按钮配置
  ui->verticalLayoutWidget->setGeometry((DEFUALT_WIDTH-START_PAGE_BUTTON_WIDTH)/2,DEFUALT_HEIGHT*3/4,START_PAGE_BUTTON_WIDTH,100);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

}