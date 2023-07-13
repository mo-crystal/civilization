#include <map>
#include <vector>
#include <iostream>

class Animation
{
private:
  int timerID;
  std::map<std::string, std::vector<std::string>> state;
  int nowFrame = 0;
  std::string nowState = "";

public:
  Animation();
  ~Animation();
  void SetTimerID(int _timerID) { this->timerID = _timerID; }
  void AddState(std::string state_name, std::vector<std::string> paths);
  void AddState(std::string state_name, std::string path, int start, int end);
  void NextFrame();
  void SetState(std::string _state);
  int GetTimerID() { return this->timerID; }
  std::string GetNowFrame() { return this->state[this->nowState][nowFrame]; }
};
