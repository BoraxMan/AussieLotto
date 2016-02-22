#include <sstream>
#include <curl/curl.h>
    
#include "DrawHistoryManager.h"

const char *resultTypeLabels[] = {
  "Tattslotto Results",
  "OzLotto Results",
  "Powerball Results",
  "Set For Life Results",
  "Monday, Wednesday Tattslotto Results"
};


int xferinfo(void *gui,
                    double dltotal, double dlnow,
                    double ultotal, double ulnow)
{
  ((DrawHistoryManager*)gui)->update_progress_bar->value(dlnow/dltotal);

    Fl::check();
  return 0;
}

DrawHistoryManager::DrawHistoryManager(ResultManager *resultmanager, const std::string &configdir)
{
  rm = resultmanager;
  rm->progress_callback = xferinfo;
  rm->ptr = this;
  homedir = configdir;

}

void DrawHistoryManager::init_result_view(resultType type)
{
  if (rm->active() == false) return;
  
  resultViewTable->setData(rm, type);
  resultViewTable->label("                                                                             ");
  resultViewTable->label(resultTypeLabels[static_cast<int>(type)]);
  resultViewTable->init();
}

void DrawHistoryManager::update_results_callback(Fl_Widget* w, void* userdata)
{
    this->update_progress_bar->label("Beginning transfer...");
  
    this->update_progress_bar->value(0.0f);
  
  if (tatts_c->value()) {
    this->update_progress_bar->value(0.0f);
    this->update_progress_bar->label("Downloading Tattslotto results");
    rm->downloadResults(R_TATTSLOTTO);
    
  }
  if (ozlotto_c->value()) {
    this->update_progress_bar->value(0.0f);
    this->update_progress_bar->label("Downloading OzLotto results");
    rm->downloadResults(R_OZLOTTO);
    
  }
  if (powerball_c->value()) {
    this->update_progress_bar->value(0.0f);
    this->update_progress_bar->label("Downloading Powerball results");
    rm->downloadResults(R_POWERBALL);
  }

  if (sfl_c->value()) {
    this->update_progress_bar->value(0.0f);
    this->update_progress_bar->label("Downloading Set For Life results");
    rm->downloadResults(R_SET_FOR_LIFE);
    
  }
  if (weekday_tatts_c->value()) {
    this->update_progress_bar->value(0.0f);
    this->update_progress_bar->label("Downloading Weekday Lottoresults");
    rm->downloadResults(R_WEEKDAY_TATTSLOTTO);
    
  }
  
  this->update_progress_bar->label("Finished.");  
  
  rm->reload();
  init_result_view(R_TATTSLOTTO);
  init_result_view(R_OZLOTTO);
  init_result_view(R_SET_FOR_LIFE);
  init_result_view(R_POWERBALL);
  init_result_view(R_WEEKDAY_TATTSLOTTO);
  updateDashboard();

}  

void DrawHistoryManager::updateDashboard(void)
{
  //rm->downloadResults(R_TATTSLOTTO);
  
  std::string s;
  std::stringstream out;
  if (rm->active() == false) return;

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
  
  x = rm->getLastDraw(R_WEEKDAY_TATTSLOTTO);
  out << x;
  s = out.str();
  this->weekday_last_draw->value(s.c_str());
  out.str("");
  
  s = rm->getDate(R_TATTSLOTTO);
  this->tatts_last_date->value(s.c_str());
  out.str("");
  s = rm->getDate(R_OZLOTTO);
  this->ozlotto_last_date->value(s.c_str());
  out.str("");
  s = rm->getDate(R_POWERBALL);
  this->powerball_last_date->value(s.c_str());
  out.str("");
  s = rm->getDate(R_SET_FOR_LIFE);
  this->sfl_last_date->value(s.c_str());
    out.str("");
  s = rm->getDate(R_WEEKDAY_TATTSLOTTO);
  this->weekday_last_date->value(s.c_str());

}