#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <random>
#include <list>
#include <map>
#include <ctime>
#include <algorithm>

#include <QMainWindow>
#include <QPainter>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QTimer>

#include "../core/construct.h"
#include "../core/player.h"
#include "../core/animation.h"

#define DEFUALT_WIDTH 960
#define DEFUALT_HEIGHT 640
#define BLOCK_SIZE 64
#define START_PAGE_BUTTON_WIDTH DEFUALT_WIDTH / 6
#define DECORATE_SIZE 32
#define MAP_WIDTH 256
#define MAP_HEIGHT 256
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

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
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  void handleDelayedKeyRelease();

  void Init();
  std::map<Point, int> GetDecorate(Point left_top, Point right_down);
  void SetPlayer(Player *p);
  bool AddPlayer(Player *p);
  Construct *GetConstruct(int x, int y);
  void PlayerMove(int playerID, int direction);
  bool Block(Point p1, Point p2);

private:
  Ui::MainWindow *ui;
  Construct *gameMap[MAP_WIDTH][MAP_HEIGHT];
  std::list<Player *> playerList;
  int myID = NO_PLAYER;
  Player *me = NULL;
  std::map<Point, int> decorates;
  int map_x_min = 0, map_y_min = 0, map_x_max = 0, map_y_max = 0;
  int REFRESH;
  bool is_playing = 0;
  QMediaPlayer *mediaPlayer;
  QMediaPlaylist *playlist;
  QPoint mousePosition;
  bool isbuilding = false;
  int current_build_cursor_frame = 0;
  int ANIMATION_TIME;
  Animation building_cursor;
  std::vector<Animation> player_animation_list;
  QTimer *pressTimer;

private slots:
  void on_B_set_clicked();
  void on_B_start_clicked();
  void on_B_setreturn_clicked();
  void on_B_quit_clicked();
  void on_voiceSlider_valueChanged(int value);
  void on_B_pause_clicked();
  void on_voice_check_stateChanged(int state);
};

#endif // MAINWINDOW_H
