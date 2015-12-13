#include <sstream>

    
#include "DrawHistoryManager.h"

DrawHistoryManager::DrawHistoryManager(ResultManager *resultmanager, const std::string &configdir)
{
  rm = resultmanager;
  homedir = configdir;
}


void DrawHistoryManager::update_results_callback(Fl_Widget* w, resultType userdata)
{
  std::cout << userdata << std::endl;
  
}  

void DrawHistoryManager::updateDashboard(void)
{
  //rm->downloadResults(R_TATTSLOTTO);
  
  std::string s;
  std::stringstream out;
  std::cout << "&&&" << std::endl;
  int x = rm->getLastDraw(R_TATTSLOTTO);
  out << x;
  s = out.str();
  this->tatts_last_draw->value(s.c_str()); // FL_ouput makes a copy of the string, so this is OK.
  out.str("");
  x = rm->getLastDraw(R_OZLOTTO);
  out << x;
  s = out.str();
  this->ozlotto_last_draw->value(s.c_str());
  out.str("");
  x = rm->getLastDraw(R_POWERBALL);
  out << x;
  s = out.str();
  this->powerball_last_draw->value(s.c_str());
  out.str("");
  x = rm->getLastDraw(R_SET_FOR_LIFE);
  out << x;
  s = out.str();
  this->sfl_last_draw->value(s.c_str());
  out.str("");
  s = rm->getDate(R_TATTSLOTTO);
  this->tatts_last_date->value(s.c_str());
  out.str("");
  std::cout << "&&&" << std::endl;
  s = rm->getDate(R_OZLOTTO);
  this->ozlotto_last_date->value(s.c_str());
  out.str("");
  s = rm->getDate(R_POWERBALL);
  this->powerball_last_date->value(s.c_str());
  out.str("");
  s = rm->getDate(R_SET_FOR_LIFE);
  this->sfl_last_date->value(s.c_str());

}