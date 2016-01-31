#ifndef RESULTVIEWTABLE_H
#define RESULTVIEWTABLE_H
#include <FL/Fl_Table.h>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include <FL/Fl_Check_Button.H>
#include "ResultManager.h"

void getColumnHeader(const int col, char *s, const gameType type);


class ResultViewTable : public Fl_Table
{
  public:
    void draw_cell(TableContext context, int ROW=0, int COL=0, int X=0, int Y=0, int W=0, int H=0);
    ResultViewTable(int X, int Y, int W, int H, const char *L=0);
    void DrawHeader(const char *s, int X, int Y, int W, int H);
    virtual void draw_col_header(char *s, int X, int Y, int W, int H);
    virtual void draw_context_cell(char *s, int ROW, int COL, int X, int Y, int W, int H);
    void setData(ResultManager *data, resultType rtype);
    void init(void);
  private:
  
    ResultManager *viewdata;
    resultType type;
};

#endif
