// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef DrawHistoryManagerGUI_h
#define DrawHistoryManagerGUI_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Output.H>

class DrawHistoryManagerGUI {
public:
  Fl_Double_Window* make_window();
  Fl_Double_Window *main_window;
  static Fl_Menu_Item menu_Update[];
  Fl_Output *tatts_last_draw;
  Fl_Output *ozlotto_last_draw;
  Fl_Output *powerball_last_draw;
  Fl_Output *sfl_last_draw;
  Fl_Output *ozlotto_last_date;
  Fl_Output *powerball_last_date;
  Fl_Output *sfl_last_date;
  Fl_Output *tatts_last_date;
  static void update_results(Fl_Widget* w, void* userdata);
  void update_results_callback(Fl_Widget* w, void* userdata);
};
#endif
