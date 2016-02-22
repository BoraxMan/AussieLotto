// generated by Fast Light User Interface Designer (fluid) version 1.0303

#ifndef AussieLottoGUI_h
#define AussieLottoGUI_h
#include <FL/Fl.H>
#include "types.h"
#include "DrawHistoryManager.h"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Light_Button.H>

class UserInterface {
public:
  DrawHistoryManager *dhm; 
  Fl_Text_Buffer *sflTextBuffer; 
  Fl_Text_Buffer *ozlottoTextBuffer; 
  Fl_Text_Buffer *lottostrikeTextBuffer; 
  Fl_Text_Buffer *licenseTextBuffer; 
  Fl_Text_Buffer *powerballTextBuffer; 
  Fl_Text_Buffer *tattslottoTextBuffer; 
  Fl_Text_Buffer *textbuf_results; 
  Fl_Text_Buffer *help_text; 
  Fl_Window* make_window();
  Fl_Window *lotto_gui;
private:
  inline void cb_Quit_i(Fl_Button*, void*);
  static void cb_Quit(Fl_Button*, void*);
  static Fl_Menu_Item menu_File[];
  inline void cb_Open_i(Fl_Menu_*, void*);
  static void cb_Open(Fl_Menu_*, void*);
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_Exit_i(Fl_Menu_*, void*);
  static void cb_Exit(Fl_Menu_*, void*);
  inline void cb_About_i(Fl_Button*, void*);
  static void cb_About(Fl_Button*, void*);
  inline void cb_Generate_i(Fl_Button*, void*);
  static void cb_Generate(Fl_Button*, void*);
  inline void cb_Check_i(Fl_Button*, void*);
  static void cb_Check(Fl_Button*, void*);
public:
  Fl_Value_Input *num_games;
  static Fl_Menu_Item menu_Options[];
private:
  inline void cb_Check1_i(Fl_Menu_*, void*);
  static void cb_Check1(Fl_Menu_*, void*);
  inline void cb_Generate1_i(Fl_Menu_*, void*);
  static void cb_Generate1(Fl_Menu_*, void*);
  inline void cb_Clear_i(Fl_Menu_*, void*);
  static void cb_Clear(Fl_Menu_*, void*);
  inline void cb_Clear1_i(Fl_Menu_*, void*);
  static void cb_Clear1(Fl_Menu_*, void*);
  inline void cb_Result_i(Fl_Menu_*, void*);
  static void cb_Result(Fl_Menu_*, void*);
  inline void cb_Help_i(Fl_Button*, void*);
  static void cb_Help(Fl_Button*, void*);
public:
  Fl_Tabs *tabular;
private:
  inline void cb_tabular_i(Fl_Tabs*, void*);
  static void cb_tabular(Fl_Tabs*, void*);
public:
  Fl_Group *tattslotto_tab;
  Fl_Value_Input *num1;
  Fl_Value_Input *num2;
  Fl_Value_Input *num3;
  Fl_Value_Input *num4;
  Fl_Value_Input *num5;
  Fl_Value_Input *num6;
  Fl_Value_Input *supp1;
  Fl_Value_Input *supp2;
  Fl_Text_Display *number_view;
  Fl_Button *ShowTattsEntryWidget;
private:
  inline void cb_Enter_i(Fl_Button*, void*);
  static void cb_Enter(Fl_Button*, void*);
public:
  Fl_Value_Input *t_draw;
  Fl_Group *radiobuttons;
  Fl_Round_Button *weekday_but;
  Fl_Round_Button *sat_but;
  Fl_Group *ozlotto_tab;
  Fl_Value_Input *oz_num1;
  Fl_Value_Input *oz_num2;
  Fl_Value_Input *oz_num3;
  Fl_Value_Input *oz_num4;
  Fl_Value_Input *oz_num5;
  Fl_Value_Input *oz_num6;
  Fl_Value_Input *oz_num7;
  Fl_Value_Input *oz_supp1;
  Fl_Value_Input *oz_supp2;
  Fl_Text_Display *oz_number_view;
  Fl_Button *ShowOzlottoEntryWidget;
private:
  inline void cb_Enter1_i(Fl_Button*, void*);
  static void cb_Enter1(Fl_Button*, void*);
public:
  Fl_Value_Input *o_draw;
  Fl_Group *powerball_tab;
  Fl_Value_Input *pb_num1;
  Fl_Value_Input *pb_num2;
  Fl_Value_Input *pb_num3;
  Fl_Value_Input *pb_num4;
  Fl_Value_Input *pb_num5;
  Fl_Value_Input *pb_num6;
  Fl_Value_Input *powerball_value;
  Fl_Text_Display *powerball_number_view;
  Fl_Button *ShowPowerballEntryWidget;
  Fl_Check_Button *ensurePowerball;
private:
  inline void cb_ensurePowerball_i(Fl_Check_Button*, void*);
  static void cb_ensurePowerball(Fl_Check_Button*, void*);
public:
  Fl_Value_Input *p_draw;
  Fl_Group *lottostrike_tab;
  Fl_Value_Input *lsnum1;
  Fl_Value_Input *lsnum2;
  Fl_Value_Input *lsnum3;
  Fl_Value_Input *lsnum4;
  Fl_Value_Input *lsnum5;
  Fl_Value_Input *lsnum6;
  Fl_Text_Display *lottostrike_number_view;
  Fl_Button *ShowLottostrikeEntryWidget;
  Fl_Group *setforlife_tab;
  Fl_Value_Input *sfl_num1;
  Fl_Value_Input *sfl_num2;
  Fl_Value_Input *sfl_num3;
  Fl_Value_Input *sfl_num4;
  Fl_Value_Input *sfl_num5;
  Fl_Value_Input *sfl_num6;
  Fl_Value_Input *sfl_num7;
  Fl_Value_Input *sfl_num8;
  Fl_Value_Input *sfl_bonus1;
  Fl_Value_Input *sfl_bonus2;
  Fl_Text_Display *sflnumber_view;
  Fl_Button *ShowSFLEntryWidget;
private:
  inline void cb_Enter2_i(Fl_Button*, void*);
  static void cb_Enter2(Fl_Button*, void*);
public:
  Fl_Value_Input *s_draw;
  static Fl_Menu_Item menu_Winning[];
private:
  inline void cb_License_i(Fl_Button*, void*);
  static void cb_License(Fl_Button*, void*);
public:
  Fl_Double_Window *results_window;
private:
  inline void cb_Save1_i(Fl_Button*, void*);
  static void cb_Save1(Fl_Button*, void*);
public:
  Fl_Double_Window *divisions_window;
  Fl_Double_Window *help_window;
  Fl_Help_View *helpView;
  Fl_Double_Window *oz_divisions_window;
  Fl_Double_Window *powerball_divisions_window;
  Fl_Double_Window *TattsNumberEntryWindow;
  Fl_Group *TattsEntryGroup;
private:
  inline void cb_OK_i(Fl_Button*, void*);
  static void cb_OK(Fl_Button*, void*);
public:
  Fl_Double_Window *OzlottoNumberEntryWindow;
  Fl_Group *OzlottoEntryGroup;
private:
  inline void cb_OK1_i(Fl_Button*, void*);
  static void cb_OK1(Fl_Button*, void*);
public:
  Fl_Double_Window *LottostrikeNumberEntryWindow;
  Fl_Group *LottostrikeEntryGroup;
private:
  inline void cb_OK2_i(Fl_Button*, void*);
  static void cb_OK2(Fl_Button*, void*);
public:
  Fl_Double_Window *SetForLifeNumberEntryWindow;
  Fl_Group *SetForLifeEntryGroup;
private:
  inline void cb_OK3_i(Fl_Button*, void*);
  static void cb_OK3(Fl_Button*, void*);
public:
  Fl_Double_Window *Numberentry;
  Fl_Light_Button *button_1;
  Fl_Light_Button *button_2;
  Fl_Light_Button *button_3;
  Fl_Light_Button *button_4;
  Fl_Light_Button *button_5;
  Fl_Light_Button *button_6;
  Fl_Light_Button *button_7;
  Fl_Light_Button *button_8;
  Fl_Light_Button *button_9;
  Fl_Light_Button *button_10;
  Fl_Light_Button *button_11;
  Fl_Light_Button *button_12;
  Fl_Light_Button *button_13;
  Fl_Light_Button *button_14;
  Fl_Light_Button *button_15;
  Fl_Light_Button *button_16;
  Fl_Light_Button *button_17;
  Fl_Light_Button *button_18;
  Fl_Light_Button *button_19;
  Fl_Light_Button *button_20;
  Fl_Light_Button *button_21;
  Fl_Light_Button *button_22;
  Fl_Light_Button *button_23;
  Fl_Light_Button *button_24;
  Fl_Light_Button *button_25;
  Fl_Light_Button *button_26;
  Fl_Light_Button *button_27;
  Fl_Light_Button *button_28;
  Fl_Light_Button *button_29;
  Fl_Light_Button *button_30;
  Fl_Light_Button *button_31;
  Fl_Light_Button *button_32;
  Fl_Light_Button *button_33;
  Fl_Light_Button *button_34;
  Fl_Light_Button *button_35;
  Fl_Light_Button *button_36;
  Fl_Light_Button *button_37;
  Fl_Light_Button *button_38;
  Fl_Light_Button *button_39;
  Fl_Light_Button *button_40;
  Fl_Light_Button *button_41;
  Fl_Light_Button *button_42;
  Fl_Light_Button *button_43;
  Fl_Light_Button *button_44;
  Fl_Light_Button *button_45;
private:
  inline void cb_OK4_i(Fl_Button*, void*);
  static void cb_OK4(Fl_Button*, void*);
public:
  Fl_Double_Window *PowerballNumberEntryWindow;
  Fl_Group *PowerballEntryGroup;
private:
  inline void cb_OK5_i(Fl_Button*, void*);
  static void cb_OK5(Fl_Button*, void*);
public:
  Fl_Double_Window *lottostrike_divisions_window;
  Fl_Double_Window *LicenseWindow;
  int quit();
  void show_help_window();
  virtual int open_file() = 0;
  virtual int save_file() = 0;
  virtual void clear_results() = 0;
  virtual void check_lotto() = 0;
  virtual int generate() = 0;
  virtual void clear_lotto() = 0;
  virtual void changeTab() = 0;
  virtual void tattsEntry() = 0;
  virtual void ozlottoEntry() = 0;
  virtual void powerballEntry() = 0;
  virtual void lottostrikeEntry() = 0;
  virtual void setForLifeEntry() = 0;
  virtual void saveResults() = 0;
  static void NumberSelectorUpdate_cb(Fl_Widget* w, void* userdata);
  virtual void show_Numberentry_window();
  virtual void submitButtonNums() = 0;
  virtual void clearNumberSelector() = 0;
  virtual void loadHelp() = 0;
  virtual void show_license_window();
  virtual void ensurePowerballButton() = 0;
  static void show_divisions(Fl_Widget* w, void* userdata);
  void show_div_callback(Fl_Widget* w, void* userdata);
  static void hide_parent(Fl_Widget *w, void* data);
  void show_entry_callback(Fl_Widget* w, void* userdata);
  static void show_entry_window(Fl_Widget* w, void* userdata);
  virtual void NumberSelectorUpdate(int x) = 0;;
  static void use_draw_results(Fl_Widget* w, void* userdata);
  virtual void use_draw_results_cb(Fl_Widget* w, void* userdata) = 0;
};
#endif
