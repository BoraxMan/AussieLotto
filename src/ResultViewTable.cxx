#include "ResultViewTable.h"

const int MAX_COLS = 8;
const int MAX_ROWS = 50;

const char *powerballHeaders[] = {
  "Date",
  "Ball 1",
  "Ball 2",
  "Ball 3",
  "Ball 4",
  "Ball 5",
  "Ball 6",
  "Powerball"
};

const char *tattslottoHeaders[] = {
  "Date",
  "Ball 1",
  "Ball 2",
  "Ball 3",
  "Ball 4",
  "Ball 5",
  "Ball 6",
  "Supp 1",
  "Supp 2"
};

const char *ozlottoHeaders[] = {
  "Date",
  "Ball 1",
  "Ball 2",
  "Ball 3",
  "Ball 4",
  "Ball 5",
  "Ball 6",
  "Ball 7",
  "Supp 1",
  "Supp 2"
};

const char *sflHeaders[] = {
  "Date",
  "Ball 1",
  "Ball 2",
  "Ball 3",
  "Ball 4",
  "Ball 5",
  "Ball 6",
  "Ball 7",
  "Ball 8",
  "Bonus 1",
  "Bonus 2"
};

void ResultViewTable::DrawHeader(const char *s, int X, int Y, int W, int H) {
    fl_push_clip(X,Y,W,H);
      fl_draw_box(FL_THIN_UP_BOX, X,Y,W,H, row_header_color());
      fl_color(FL_BLACK);
      fl_draw(s, X,Y,W,H, FL_ALIGN_CENTER);
    fl_pop_clip();
  } 
  
void ResultViewTable::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H)
{
  int x = viewdata->rowToDraw(type, ROW);
  const std::vector<int> &balls = viewdata->getResults(type, x);
  const std::vector<int> &supps = viewdata->getSupps(type, x);
  std::string date;
  static char s[40];
  switch ( context ) {
    case CONTEXT_STARTPAGE:
      fl_font(FL_HELVETICA, 16);
      return; 
    case CONTEXT_COL_HEADER:
      if (type == R_TATTSLOTTO)
      {
	sprintf(s, "%s", tattslottoHeaders[COL]);
      } else if (type == R_OZLOTTO) {
	sprintf(s, "%s", ozlottoHeaders[COL]);
      } else if (type == R_POWERBALL) {
	sprintf(s, "%s", powerballHeaders[COL]);
      } else if (type == R_SET_FOR_LIFE) {
	sprintf(s, "%s", sflHeaders[COL]);
      } else if (type == R_WEEKDAY_TATTSLOTTO) {
        sprintf(s, "%s", tattslottoHeaders[COL]);
      }
      
      draw_col_header(s,X,Y,W,H);
      return; 
    case CONTEXT_ROW_HEADER:  
      sprintf(s ,"%u", x);
      DrawHeader(s,X,Y,W,H);
      return; 
    case CONTEXT_CELL: {
     if (COL == 0)
      {
	date = viewdata->getDate(type, x);
	sprintf(s,"%s",date.c_str());     
      } else if (( COL <= balls.size() ) && (COL >= 1)) {
	sprintf(s, "%u", balls[COL-1]);
      } else if (( COL > balls.size()) && (COL <= (balls.size() + supps.size()))) {
	sprintf(s, "%u", supps[COL - (balls.size() + 1)]);
      } else {
	sprintf(s, "%u", 0);
      }
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
    cols(viewdata->cols(type)-1);             // how many columns
    col_header(1);              // enable column headers (along top)
    col_width_all(70);          // default width of columns
    col_width(0,128);
    col_resize(1);              // enable column resizing
    end();                      // end the Fl_Table group
}
  
ResultViewTable::ResultViewTable(int X, int Y, int W, int H, const char *L) : Fl_Table(X,Y,W,H,L) {
    // Init secondary selection off
     // Rows
   
  }
  
  
void getColumnHeader(const int col, char *s, const gameType type)
{
  if (col == 0) {
    sprintf(s, "%s", "Date");
    return;
  } else if (col >=1 && col <= 5) {
    sprintf(s, "%s %u", "Ball", col);
  }
}
  