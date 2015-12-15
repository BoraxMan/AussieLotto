#include "ResultViewTable.h"

const int MAX_COLS = 8;
const int MAX_ROWS = 50;

void ResultViewTable::DrawHeader(const char *s, int X, int Y, int W, int H) {
    fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
      fl_color(FL_BLACK);
      fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
    fl_pop_clip();
  } 
void ResultViewTable::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H)
{
  int x = viewdata->rowToDraw(R_TATTSLOTTO, ROW);
  std::string date;
  static char s[40];
  switch ( context ) {
    case CONTEXT_STARTPAGE:
      fl_font(FL_HELVETICA, 16);
      return; 
    case CONTEXT_COL_HEADER:
      sprintf(s ,"%u", x); 
      draw_col_header(s,X,Y,W,H);
      return; 
    case CONTEXT_ROW_HEADER:  
      sprintf(s ,"%u", x);
      DrawHeader(s,X,Y,W,H);
      return; 
    case CONTEXT_CELL: {
     if (COL == 0)
      {
	date = viewdata->getDate(R_TATTSLOTTO, x);
	sprintf(s,"%s",date.c_str());     
      } else sprintf(s, "%s", "test");
      // Handle coloring of cells
      draw_context_cell(s, ROW, COL, X, Y, W, H);
    }
    default:
      return;
  }
}

void ResultViewTable::draw_context_cell(char *s, int ROW, int COL, int X, int Y, int W, int H)
{


  int fgcol = FL_BLACK;
  int bgcol = FL_WHITE;
  fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, bgcol);
  fl_color(fgcol);
  fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
  return;
}

void ResultViewTable::draw_col_header(char *s,int X,int Y,int W,int H)
{
  DrawHeader(s,X,Y,W,H);
  return;
}

void ResultViewTable::setData(ResultManager *data, resultType rtype)
{
  viewdata = data;
  type = rtype;
}
  
void ResultViewTable::init()
{
   if (viewdata == NULL) {
      return;
    }
    rows(viewdata->size(type));             // how many rows
    row_header(1);              // enable row headers (along left)
    row_height_all(20);         // default height of rows
    row_resize(0);              // disable row resizing
    // Cols
    cols(viewdata->cols(type));             // how many columns
    col_header(1);              // enable column headers (along top)
    col_width_all(80);          // default width of columns
    col_resize(1);              // enable column resizing
    end();                      // end the Fl_Table group
}
  
ResultViewTable::ResultViewTable(int X, int Y, int W, int H, const char *L) : Fl_Table(X,Y,W,H,L) {
    // Init secondary selection off
     // Rows
   
  }