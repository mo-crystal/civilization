#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>

#include <QMainWindow>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>

#include "game.h"

#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define BLOCK_SIZE 64
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH / 6
#define DECORATE_SIZE 32

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);

private:
  Ui::MainWindow *ui;
  Game g;
  int REFRESH;
  bool is_playing = 0;

private slots:
  void on_B_set_clicked();
  void on_B_start_clicked();
  void on_B_setreturn_clicked();
  void on_B_quit_clicked();
};

#endif // MAINWINDOW_H
