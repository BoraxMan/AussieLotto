/*
    AussieLotto: A tattslotto number generator and checker.
    Copyright (C) 2014 Dennis Katsonis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include "AussieLottoGUI.h"
#include "AussieLotto.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <bitset>
#include <Fl/fl_ask.h>
#include <FL/Fl_File_Chooser.H>

const int max_games = 1048576;
const int highest_ball = 45;

bool fexists(std::string filename)
{
  bool x;
  std::ifstream ifile(filename.c_str());
  x = ifile;
  ifile.close();
  return x;
}

/*
bool FileExist( const std::string& Name )
{
#ifdef OS_WINDOWS
    struct _stat buf;
    int Result = _stat( Name.c_str(), &buf );
#else
    struct stat buf;
    int Result = stat( Name.c_str(), &buf );
#endif
    return Result == 0;
}*/

void AusLotto::NumberSelectorUpdate(int x)
{
  NumberSelectorArray.flip(x);
}

void AusLotto::show_license_window(void)
{
  static int licenseLoaded = 0;
  std::string fname="/usr/share/doc/AussieLotto/LICENSE";
  
  if (!licenseLoaded)
  {   
    if (fexists(fname))
    {
      this->licenseTextBuffer->loadfile(fname.c_str());
      licenseLoaded = 1;
      this->LicenseWindow->show();
      return;
    }
    fname = "/usr/local/share/doc/AussieLotto/LICENSE";
    if (fexists(fname))
    {
      this->licenseTextBuffer->loadfile(fname.c_str());
      licenseLoaded = 1;
      this->LicenseWindow->show();
      return;
    }
    fname = "LICENSE";
    if (fexists(fname))
    {
      this->licenseTextBuffer->loadfile(fname.c_str());
      licenseLoaded = 1;
      this->LicenseWindow->show();
      return;
    }
    
  }
  this->LicenseWindow->show();
  return;
}
 
  
void AusLotto::submitButtonNums()
{
  gameType gt;
  std::stringstream strout;
  std::vector<int> values;
  std::string incorrectNumbers = "Incorrect number of numbers selected.";
  
  gt = this->getGameTab();  
 
  for (int c = 0; c < highest_ball; c++)
  {
    if (NumberSelectorArray.test(c))
      values.push_back(c);
  }
  
  try
  {
    switch (gt)
    {
      case TATTSLOTTO:
	if (values.size() != tattsBalls)
	  throw(incorrectNumbers);
	tatts->addGame(values[0], values[1], values[2],
	  values[3], values[4], values[5]);
	//tattslottoTextBuffer->text("");
	strout << *tatts;
	tattslottoTextBuffer->append(strout.str().c_str()); 
	this->num_games->value(tatts->getNumGames());
	break;
      case OZLOTTO:
	if (values.size() != ozlottoBalls)
	  throw(incorrectNumbers);
	ozlotto->addGame(values[0], values[1], values[2],
	  values[3], values[4], values[5], values[6]);
	strout << *ozlotto;
	ozlottoTextBuffer->append(strout.str().c_str());   
	this->num_games->value(tatts->getNumGames());
	break;
      case LOTTOSTRIKE:
	if (values.size() != lottostrikeBalls)
	  throw(incorrectNumbers);
	lottostrike->addGame(values[0], values[1], values[2],values[3]);
	strout << *lottostrike;
	lottostrikeTextBuffer->append(strout.str().c_str());   
	this->num_games->value(lottostrike->getNumGames());
	break;
      default:
	return;
    } // end of switch.
  } // end of "try" block.
  catch (std::string err)
  {
    fl_message(err.c_str());
    clearNumberSelector();
    return;
  }

  clearNumberSelector();
  hide_Numberentry_window();
  return;
}
      
void AusLotto::clearNumberSelector(void)
{ // I know this might be a terrible way to do it, an array of some sort would have
  // been much better.
  // But this works and it wasn't worth my time doing it a 'smarter' way.
  
  NumberSelectorArray.reset();
  this->button_1->clear();
  this->button_2->clear();
  this->button_3->clear();
  this->button_4->clear();
  this->button_5->clear();
  this->button_6->clear();
  this->button_7->clear();
  this->button_8->clear();
  this->button_9->clear();
  this->button_10->clear();
  this->button_11->clear();
  this->button_12->clear();
  this->button_13->clear();
  this->button_14->clear();
  this->button_15->clear();
  this->button_16->clear();
  this->button_17->clear();
  this->button_18->clear();
  this->button_19->clear();
  this->button_20->clear();
  this->button_21->clear();
  this->button_22->clear();
  this->button_23->clear();
  this->button_24->clear();
  this->button_25->clear();
  this->button_26->clear();
  this->button_27->clear();
  this->button_28->clear();
  this->button_29->clear();
  this->button_30->clear();
  this->button_31->clear();
  this->button_32->clear();
  this->button_33->clear();
  this->button_34->clear();
  this->button_35->clear();
  this->button_36->clear();
  this->button_37->clear();
  this->button_38->clear();
  this->button_39->clear();
  this->button_40->clear();
  this->button_41->clear();
  this->button_42->clear();
  this->button_43->clear();
  this->button_44->clear();
  this->button_45->clear();  
}

void AusLotto::createPowerballEntryWindows(void)
{
  this->PowerballEntryGroup->begin();

  static const char *header[7] = {
            "1","2","3","4","5","6","PB"};
  int X= 12;
  int Y = 24;
  int cellw = 40;
  int cellh = 25;
  int xx = X, yy = Y;

 // Create widgets
  for ( int r = 0; r < 17; r++ )
  {
    for ( int c = 0; c < 7; c++ )
    {
      if ( r == 0 )
      {
	Fl_Box *box = new Fl_Box(xx+c*5 ,yy+r*5,cellw,cellh,header[c]);
        box->box(FL_BORDER_BOX);
      }
      else
      {
	Fl_Input *in = new Fl_Input(xx + c*5,yy+r*5,cellw,cellh);
        in->box(FL_BORDER_BOX);
        in->value("");
        pew[r-1][c] = in;
      } 
      xx += cellw;
    }
    xx = X;
    yy += cellh;
  }
  this->PowerballEntryGroup->end();
}


void AusLotto::createOzlottoEntryWindows(void)
{
  this->OzlottoEntryGroup->begin();

          static const char *header[7] = {
            "1","2","3","4","5","6","7"};
	int X= 12;
	int Y = 24;
	int cellw = 40;
        int cellh = 25;
        int xx = X, yy = Y;

        // Create widgets
        for ( int r = 0; r < 17; r++ ) {
            for ( int c = 0; c < ozlottoBalls; c++ ) {
                if ( r == 0 ) {
                    Fl_Box *box = new Fl_Box(xx+c*5 ,yy+r*5,cellw,cellh,header[c]);
                    box->box(FL_BORDER_BOX);
                } else  {
                    Fl_Input *in = new Fl_Input(xx + c*5,yy+r*5,cellw,cellh);
                    in->box(FL_BORDER_BOX);
                    in->value("");
                    oew[r-1][c] = in;
                } 
                xx += cellw;
            }
            xx = X;
            yy += cellh;
  }
  this->OzlottoEntryGroup->end();
}

void AusLotto::createTattsEntryWindows(void)
{
    this->TattsEntryGroup->begin();

          static const char *header[6] = {
            "1","2","3","4","5","6"};
	int X= 12;
	int Y = 24;
	int cellw = 40;
        int cellh = 25;
        int xx = X, yy = Y;
	

        // Create widgets
        for ( int r = 0; r < 17; r++ ) {
            for ( int c = 0; c < tattsBalls; c++ ) {
                if ( r == 0 ) {
                    Fl_Box *box = new Fl_Box(xx+c*5 ,yy+r*5,cellw,cellh,header[c]);
                    box->box(FL_BORDER_BOX);
                } else  {
                    Fl_Input *in = new Fl_Input(xx + c*5,yy+r*5,cellw,cellh);
                    in->box(FL_BORDER_BOX);
                    in->value("");
                    tew[r-1][c] = in;
                } 
                xx += cellw;
            }
            xx = X;
            yy += cellh;
  }
  this->TattsEntryGroup->end(); 
}

void AusLotto::createLottostrikeEntryWindows(void)
{
    this->LottostrikeEntryGroup->begin();

          static const char *header[4] = {
            "1","2","3","4"};
	int X= 12;
	int Y = 24;
	int cellw = 40;
        int cellh = 25;
        int xx = X, yy = Y;
	

        // Create widgets
        for ( int r = 0; r < 17; r++ ) {
            for ( int c = 0; c < lottostrikeBalls; c++ ) {
                if ( r == 0 ) {
                    Fl_Box *box = new Fl_Box(xx+c*5 ,yy+r*5,cellw,cellh,header[c]);
                    box->box(FL_BORDER_BOX);
                } else  {
                    Fl_Input *in = new Fl_Input(xx + c*5,yy+r*5,cellw,cellh);
                    in->box(FL_BORDER_BOX);
                    in->value("");
                    lew[r-1][c] = in;
                } 
                xx += cellw;
            }
            xx = X;
            yy += cellh;
  }
  this->LottostrikeEntryGroup->end(); 
}


void AusLotto::tattsEntry(void)
{
  int r;
  int c;
  int intValues[tattsBalls];
  std::string value;
  std::stringstream strout;
  
  
  for (r = 0; r < 16; r++)
  {

    for (c = 0; c < tattsBalls; c++)
    {
      if (tew[r][c]->size())
      {
	value = std::string(tew[r][c]->value());
	std::istringstream(value) >> intValues[c];
      }
      else
	intValues[c] = 0;
      
   }
    // If all values are 0, ignore the line.

    if (( intValues[0] || intValues[1] || intValues[2] ||
	  intValues[3] || intValues[4] || intValues[5]) != 0)
    {
      try
      {
	tatts->addGame(intValues[0], intValues[1], intValues[2],
         intValues[3], intValues[4], intValues[5]);
      }
      catch (std::string err)
      {
	fl_message(err.c_str());
	return;
      }
    }
  }
  this->TattsNumberEntryWindow->hide();
  this->num_games->value(tatts->getNumGames());
  //tattslottoTextBuffer->text("");
  strout << *tatts;
  tattslottoTextBuffer->append(strout.str().c_str()); 
}

void AusLotto::ozlottoEntry(void)
{
  int r;
  int c;
  int intValues[ozlottoBalls];
  std::string value;
  std::stringstream strout;
  
  for (r = 0; r < 16; r++)
  {
    for (c = 0; c < ozlottoBalls; c++)
    {
      if (oew[r][c]->size())
      {
	value = std::string(oew[r][c]->value());
	std::istringstream(value) >> intValues[c];
      }
      else
	intValues[c] = 0;
      
   }
    // If all values are 0, ignore the line.

    if (( intValues[0] || intValues[1] || intValues[2] ||
	  intValues[3] || intValues[4] || intValues[5] || intValues[6]) != 0)
    {
      try
      {
	ozlotto->addGame(intValues[0], intValues[1], intValues[2],
         intValues[3], intValues[4], intValues[5], intValues[6]);
      }
      catch (std::string err)
      {
	fl_message(err.c_str());
	return;
      }
    } 
  }
  this->OzlottoNumberEntryWindow->hide();
  this->num_games->value(ozlotto->getNumGames());
  //ozlottoTextBuffer->text("");
  strout << *ozlotto;
  ozlottoTextBuffer->append(strout.str().c_str());  
}


void AusLotto::powerballEntry(void)
{
  int r;
  int c;
  int intValues[powerballBalls];
  std::string value;
  std::stringstream strout;
  
  for (r = 0; r < 16; r++)
  {
    for (c = 0; c < powerballBalls; c++)
    {
      if (pew[r][c]->size())
      {
	value = std::string(pew[r][c]->value());
	std::istringstream(value) >> intValues[c];
      }
      else
	intValues[c] = 0;   
   }
    // If all values are 0, ignore the line.

    if (( intValues[0] || intValues[1] || intValues[2] ||
	  intValues[3] || intValues[4] || intValues[5] || intValues[6]) != 0)
    {
      try
      {
	powerball->addGame(intValues[0], intValues[1], intValues[2],
         intValues[3], intValues[4], intValues[5], intValues[6]);
      }
      catch (std::string err)
      {
	fl_message(err.c_str());
	return;
      } 
    }
  }
  this->PowerballNumberEntryWindow->hide();
  this->num_games->value(powerball->getNumGames());
  //powerballTextBuffer->text("");
  strout << *powerball;
  powerballTextBuffer->append(strout.str().c_str());  
}


void AusLotto::lottostrikeEntry(void)
{
  int r;
  int c;
  int intValues[lottostrikeBalls];
  std::string value;
  std::stringstream strout;
  
  for (r = 0; r < 16; r++)
  {
    for (c = 0; c < lottostrikeBalls; c++)
    {
      if (lew[r][c]->size())
      {
	value = std::string(lew[r][c]->value());
	std::istringstream(value) >> intValues[c];
      }
      else
	intValues[c] = 0;   
   }
    // If all values are 0, ignore the line.

    if (( intValues[0] || intValues[1] || intValues[2] || intValues[3]) != 0)
    {
      try
      {
	lottostrike->addGame(intValues[0], intValues[1], intValues[2],intValues[3]);
      }
      catch (std::string err)
      {
	fl_message(err.c_str());
	return;
      } 
    }
  }
  this->LottostrikeNumberEntryWindow->hide();
  this->num_games->value(lottostrike->getNumGames());
  //powerballTextBuffer->text("");
  strout << *lottostrike;
  lottostrikeTextBuffer->append(strout.str().c_str());  
}


void AusLotto::show_tatts_entry_window(void)
{

  for ( int r = 0; r < 16; r++ )
  {
    for ( int c = 0; c < tattsBalls; c++ )
    {
      tew[r][c]->value("");
    } 
  }
  this->TattsNumberEntryWindow->show();
}

void AusLotto::show_ozlotto_entry_window(void)
{

  for ( int r = 0; r < 16; r++ )
  {
    for ( int c = 0; c < ozlottoBalls; c++ )
    {
      oew[r][c]->value("");
    } 
  }
  this->OzlottoNumberEntryWindow->show();
}

void AusLotto::show_powerball_entry_window(void)
{
  for ( int r = 0; r < 16; r++ )
  {
    for ( int c = 0; c < powerballBalls; c++ )
    {
      pew[r][c]->value("");
    } 
  }
  this->PowerballNumberEntryWindow->show();
}

void AusLotto::show_lottostrike_entry_window(void)
{
  for ( int r = 0; r < 16; r++ )
  {
    for ( int c = 0; c < lottostrikeBalls; c++ )
    {
      lew[r][c]->value("");
    } 
  }
  this->LottostrikeNumberEntryWindow->show();
}


AusLotto::AusLotto()
{
  tattslottoTextBuffer = new Fl_Text_Buffer();
  ozlottoTextBuffer = new Fl_Text_Buffer();
  powerballTextBuffer = new Fl_Text_Buffer();
  lottostrikeTextBuffer = new Fl_Text_Buffer();
  licenseTextBuffer = new Fl_Text_Buffer();
  textbuf_results = new Fl_Text_Buffer();

  tatts = new tattslottoGame();
  ozlotto = new ozlottoGame();
  powerball = new powerballGame();
  lottostrike = new lottostrikeGame();

  NumberSelectorArray.reset();
  
}

void AusLotto::clear_lotto(void)
{
  gameType activeTab;
  
  activeTab = this->getGameTab();
  
  switch(activeTab)
  {
    case TATTSLOTTO:
      delete tatts;
      tatts = new tattslottoGame();
      tattslottoTextBuffer->text("");
      break;
    case OZLOTTO:
      delete ozlotto;
      ozlotto = new ozlottoGame();
      ozlottoTextBuffer->text("");
      break;
    case POWERBALL:
      delete powerball;
      powerball = new powerballGame();
      powerballTextBuffer->text("");
      break;
    case LOTTOSTRIKE:
      delete lottostrike;
      lottostrike = new lottostrikeGame();
      lottostrikeTextBuffer->text("");
      break;
    default:
      break;
  }
  
  this->num_games->value(0);
  return;
}

void AusLotto::changeTab(void)
{
  gameType gt;
  
  gt = this->getGameTab();

  if (gt == TATTSLOTTO && tatts->getNumGames())
    this->num_games->value(tatts->getNumGames());
  if (gt == OZLOTTO && ozlotto->getNumGames())
    this->num_games->value(ozlotto->getNumGames());
  if (gt == POWERBALL && powerball->getNumGames())
    this->num_games->value(powerball->getNumGames());
  if (gt == LOTTOSTRIKE && lottostrike->getNumGames())
    this->num_games->value(lottostrike->getNumGames());
}
  
void AusLotto::check_lotto(void)
{
  std::string s;
  std::string nogames = "No games to check.";
  gameType activeTab;
  textbuf_results->text("");
  activeTab = this->getGameTab();
  
  try
  {
    switch(activeTab)
    {
      case TATTSLOTTO:
	if (tatts->getNumGames() == 0)
	  throw (nogames);
	tatts->setResults(static_cast<int>(this->num1->value()), static_cast<int>(this->num2->value()), 
	static_cast<int>(this->num3->value()), static_cast<int>(this->num4->value()),
	static_cast<int>(this->num5->value()), static_cast<int>(this->num6->value()));
	tatts->setResultsSupps(static_cast<int>(this->supp1->value()),
	static_cast<int>(this->supp2->value()));
	s = tatts->checkResults();
	break;
      case OZLOTTO:
	if (ozlotto->getNumGames() == 0)
	  throw(nogames);
	ozlotto->setResults(static_cast<int>(this->oz_num1->value()), static_cast<int>(this->oz_num2->value()), 
	static_cast<int>(this->oz_num3->value()), static_cast<int>(this->oz_num4->value()),
	static_cast<int>(this->oz_num5->value()), static_cast<int>(this->oz_num6->value()),
	static_cast<int>(this->oz_num7->value())); 
	ozlotto->setResultsSupps(static_cast<int>(this->oz_supp1->value()),
	static_cast<int>(this->oz_supp2->value()));
	s = ozlotto->checkResults();
	break;
      case POWERBALL:
	if (powerball->getNumGames() == 0)
	  throw(nogames);
	powerball->setResults(static_cast<int>(this->pb_num1->value()), static_cast<int>(this->pb_num2->value()), 
	static_cast<int>(this->pb_num3->value()), static_cast<int>(this->pb_num4->value()),
	static_cast<int>(this->pb_num5->value()), static_cast<int>(this->pb_num6->value()),
	static_cast<int>(this->powerball_value->value()));
	s = powerball->checkResults();
	break;
      case LOTTOSTRIKE:
	if (lottostrike->getNumGames() == 0)
	  throw(nogames);
	lottostrike->setResults(static_cast<int>(this->lsnum1->value()), static_cast<int>(this->lsnum2->value()), 
	static_cast<int>(this->lsnum3->value()), static_cast<int>(this->lsnum4->value()),
	static_cast<int>(this->lsnum5->value()), static_cast<int>(this->lsnum6->value()));
	s = lottostrike->checkResults();
	break;
      default:
	throw("Unknown game type");
    }// end of switch
  } // end of try
  catch (std::string err)
  {
    fl_message(err.c_str());
    return;
  }
    
  textbuf_results->append(s.c_str());
  this->results_window->show();
  return;
}

void AusLotto::clear_results(void)
{
  gameType activeTab;
  
  activeTab = this->getGameTab();
  
  switch(activeTab)
  {
    case TATTSLOTTO:
      this->num1->value(0);
      this->num2->value(0);
      this->num3->value(0);
      this->num4->value(0);
      this->num5->value(0);
      this->num6->value(0);
      this->supp1->value(0);
      this->supp2->value(0);
      break;
    case OZLOTTO:
      this->oz_num1->value(0);
      this->oz_num2->value(0);
      this->oz_num3->value(0);
      this->oz_num4->value(0);
      this->oz_num5->value(0);
      this->oz_num6->value(0);
      this->oz_num7->value(0);
      this->oz_supp1->value(0);
      this->oz_supp2->value(0);
      break;
    case POWERBALL:
      this->pb_num1->value(0);
      this->pb_num2->value(0);
      this->pb_num3->value(0);
      this->pb_num4->value(0);
      this->pb_num5->value(0); 
      this->pb_num6->value(0); 
      this->powerball_value->value(0);
      break;
    case LOTTOSTRIKE:
      this->lsnum1->value(0);
      this->lsnum2->value(0);
      this->lsnum3->value(0);
      this->lsnum4->value(0);
      this->lsnum5->value(0);
      this->lsnum6->value(0);
      break;
    default:
      break;
} // end of switch

// Reset the GUI and the values if we want to enter new values.
// A redundant function because you can manually change them, but this gives
// the user an easier way to do it, select a menu option rather than
// entering '0' in all the 8 fields
  return;
}


void AusLotto::saveResults(void)
{
  char *fname;
  std::ofstream file_out;

  fname = fl_file_chooser("Save Results", NULL, NULL);

  if (fname == NULL)
    return;

  if (this->textbuf_results->savefile(fname))
    fl_message("Could not write file");
  return;
}
    
int AusLotto::save_file(void)
{

  char *fname;
  std::string extension;
  std::string nogames = "There are no games to save.";
  gameType activeTab;
  
  fname = fl_file_chooser("Save Tatts Game", NULL, NULL);

  if (fname == NULL)
    return 1;
    
  std::string filename(fname);
  
  if (filename.size() > 6)
    extension = filename.substr(filename.size() - 6);
  if (extension != ".tatts")
    filename.append(".tatts");
  
  activeTab = this->getGameTab();
  
  if(fexists(filename))
  {
    fl_message("Do you want to overwrite this file?");
  }

  
  try
  {
    switch(activeTab)
    {
      case TATTSLOTTO:
	if (!tatts->getNumGames())
	  throw(nogames);
	tatts->saveGame(filename);
	break;
      case OZLOTTO:
	if (!ozlotto->getNumGames())
	  throw(nogames);
	ozlotto->saveGame(filename);
	break;
      case POWERBALL:
	if (!powerball->getNumGames())
	  throw(nogames);
	powerball->saveGame(filename);
	break;
      case LOTTOSTRIKE:
	if (!lottostrike->getNumGames())
	  throw(nogames);
	lottostrike->saveGame(filename);
	break;
      default:
	throw("Unknown game type!");
	break;
    } // end of switch
  }// end of try
  catch (std::string err)
  {
    fl_message(err.c_str());
    return -1;
  }
  
  return 0;
}

void AusLotto::loadHelp(void)
{
  std::string fname="/usr/share/doc/AussieLotto/help.html";
  if (fexists(fname))
  {
    this->helpView->load(fname.c_str());
    return;
  }

  fname = "/usr/local/share/doc/AussieLotto/help.html";
  if (fexists(fname))
  {
    this->helpView->load(fname.c_str());
    return;
  }
 fname = "help.html";
 if (fexists(fname))
 {
   this->helpView->load(fname.c_str());
   return;
 }
 
 return;
}

int AusLotto::open_file(void)
{
  gameType gt;
  char *fname;
  std::stringstream strout;
    
  fname = fl_file_chooser("Load Tatts file", "*.tatts", NULL);

  if (fname == NULL)
    return -1;

  gt = getFileGameType(fname);
  
  try
  {
    switch(gt)
    {
      case TATTSLOTTO:
	delete tatts;
	tatts = new tattslottoGame(fname);
	this->num_games->value(tatts->getNumGames());
	strout << *tatts;
	tattslottoTextBuffer->text("");
	tattslottoTextBuffer->append(strout.str().c_str());  
	setGameTab(TATTSLOTTO);
	break;
      case OZLOTTO:
	delete ozlotto;
	ozlotto = new ozlottoGame(fname);
	this->num_games->value(ozlotto->getNumGames());
	strout << *ozlotto;
	ozlottoTextBuffer->text("");
	ozlottoTextBuffer->append(strout.str().c_str());
	setGameTab(OZLOTTO);
	break;
      case POWERBALL:
	delete powerball;
	powerball = new powerballGame(fname);
	this->num_games->value(powerball->getNumGames());
	strout << *powerball;
	powerballTextBuffer->text("");
	powerballTextBuffer->append(strout.str().c_str());
	setGameTab(POWERBALL);
	break;
      case LOTTOSTRIKE:
	delete lottostrike;
	lottostrike = new lottostrikeGame(fname);
	this->num_games->value(lottostrike->getNumGames());
	strout << *lottostrike;
	lottostrikeTextBuffer->text("");
	lottostrikeTextBuffer->append(strout.str().c_str());  
	setGameTab(LOTTOSTRIKE);
	break;
      default:
	throw std::string("This isn't a file created by this program.\nNot going to try to open it.");
	break;
    }// end of switch
  } // end of try
  catch (std::string err)
  {
    fl_message(err.c_str());
    return -1;
  }
  return 0;
} // end open_file()


void AusLotto::setGameTab(gameType gt)
{ 
  switch(gt)
  {
    case TATTSLOTTO:
      this->tabular->value(this->tattslotto_tab);
      break;
    case OZLOTTO:
      this->tabular->value(this->ozlotto_tab);
      break;
    case POWERBALL:
      this->tabular->value(this->powerball_tab);
      break;
    case LOTTOSTRIKE:
      this->tabular->value(this->lottostrike_tab);
      break;
    default:
      break;
      
  }
  return;
}

gameType AusLotto::getGameTab(void)
{ /* This returns the tab that is selected in the UI. */
  if (this->tabular->value() == this->tattslotto_tab)
    return TATTSLOTTO;
  if (this->tabular->value() == this->ozlotto_tab)
    return OZLOTTO;
  if (this->tabular->value() == this->powerball_tab)
    return POWERBALL;
  if (this->tabular->value() == this->lottostrike_tab)
    return LOTTOSTRIKE;
  return UNDEFINED;
}

int AusLotto::generate()
{
  gameType gt;
  int numgames;

  std::stringstream strout; // The stream that we will write the generated nubmers to.

  numgames = static_cast<int>(this->num_games->value());
  try
  {
    if (!numgames)
      throw std::string("How many games?");
    else if (numgames > max_games || numgames < 0)
    {
      this->num_games->value(0);
      throw std::string("Can't do more than a million or so games");
    }
  }
  catch(std::string err)
  {
   fl_message(err.c_str());
  return -1;
  }

  gt = this->getGameTab();
  
  switch(gt)
  {
    case TATTSLOTTO:
      delete tatts;
      tattslottoTextBuffer->text("");
      tatts = new tattslottoGame(numgames);
      strout << *tatts;
      tattslottoTextBuffer->append(strout.str().c_str());
      break;
    case OZLOTTO:
      delete ozlotto;
      ozlottoTextBuffer->text("");
      ozlotto = new ozlottoGame(numgames);
      strout << *ozlotto;
      ozlottoTextBuffer->append(strout.str().c_str());
      break;
    case POWERBALL:
      delete powerball;
      powerballTextBuffer->text("");
      powerball = new powerballGame(numgames);
      strout << *powerball;
      powerballTextBuffer->append(strout.str().c_str()); 
      break;
    case LOTTOSTRIKE:
      delete lottostrike;
      lottostrikeTextBuffer->text("");
      lottostrike = new lottostrikeGame(numgames);
      strout << *lottostrike;
      lottostrikeTextBuffer->append(strout.str().c_str()); 
      break;
    default:
      break;
    
  } // end of switch
  return 0;
}
 
 int main(void)
 { 
  randomizeSeed();
  AusLotto tattslotto;
  fl_register_images();

  tattslotto.make_window();
  tattslotto.lotto_gui->show();
  tattslotto.createOzlottoEntryWindows();
  tattslotto.createTattsEntryWindows();
  tattslotto.createPowerballEntryWindows();
  tattslotto.createLottostrikeEntryWindows();
  return Fl::run();
}
