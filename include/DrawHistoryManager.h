#ifndef DRAWHISTORYMANAGER_H
#define DRAWHISTORYMANAGER_H
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_File_Chooser.H>
#include <string>


#include "DrawHistoryManagerGUI.h"
#include "ResultManager.h"
#include "date.h"


class DrawHistoryManager: public DrawHistoryManagerGUI
{
public:
  DrawHistoryManager(ResultManager *resultmanager, const std::string &configdir);
  void updateDashboard(void);
  void update_results_callback(Fl_Widget* w, void* userdata);
private:
  ResultManager *rm;
  std::string homedir;
  void init_result_view(resultType type);
};

#endif
