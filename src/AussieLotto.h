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

#ifndef AUSSIELOTTO_H
#define AUSSIELOTTO_H

#include "AussieLottoGUI.h"
#include "LottoGame.h"
#include <string>
#include <bitset>


class AusLotto : public UserInterface
{
private:
  Fl_Input *tew[16][6];		// widget pointers for Lotto
  Fl_Input *oew[16][7];		// widget pointers for ozlotto
  Fl_Input *pew[16][7];		// widget pointers for powerball
  Fl_Input *lew[16][4];		// widget pointers for lottostrike
  std::bitset<46> NumberSelectorArray; // We're not using bit 0, just 1 - 45.  So need an extra spot.
  tattslottoGame *tatts;
  ozlottoGame *ozlotto;
  powerballGame *powerball;
  lottostrikeGame *lottostrike;
  void setGameTab(gameType);
  gameType getGameTab(void);
  void changeTab(void);
  void NumberSelectorUpdate(int x);
  void submitButtonNums();
  void clearNumberSelector();
  void show_tatts_entry_window();
  void show_ozlotto_entry_window();
  void show_powerball_entry_window();
  void show_lottostrike_entry_window();
  void clear_lotto(void);
  void clear_results(void);
  void show_license_window(void);
  
public:
  void tattsEntry(void);
  void ozlottoEntry(void);
  void powerballEntry(void);
  int generate();
  int open_file(void);
  void loadHelp(void);
  int save_file(void);
  void saveResults(void);
  void check_lotto(void);
  void lottostrikeEntry(void);
  void createTattsEntryWindows(void);
  void createOzlottoEntryWindows(void);
  void createPowerballEntryWindows(void);
  void createLottostrikeEntryWindows(void);
  AusLotto();
protected:

};

#endif
