#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include<QMovie>


#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH/6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
  void paintEvent(QPaintEvent *event);

 private:
  Ui::MainWindow* ui;

  private slots:
    void on_B_set_clicked();
    void on_B_start_clicked();
    void on_B_setreturn_clicked();
    void on_B_quit_clicked();
};

#endif  // MAINWINDOW_H
