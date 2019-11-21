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

//#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"




gameType getFileGameType(char *fname)
{ 
  std::ifstream fin;
  std::string header;

  fin.open(fname);
  
  if (!fin.is_open())
    throw (AussieLottoException("Could not open file", fname));
  
  fin >> header;
  fin.close();
      
  if (header == tatts_id)
    return TATTSLOTTO;
  else if (header == ozlotto_id)
    return OZLOTTO;
  else if (header == powerball_id)
    return POWERBALL;
  else if (header == lottostrike_id)
    return LOTTOSTRIKE;
  else
    return UNDEFINED;
  
}
//*******************
// Lotto Game methods
//*******************

LottoGame::LottoGame() : memoryAllocated(false), games(0), outputted(0), balls(0), m_prizesAvailable(false)
{  

}


LottoGame::~LottoGame()
{

}


int LottoGame::getNumGames() const
{
  return games;
}

int LottoGame::saveGame(std::string fname)
{
  return 0;
}
int LottoGame::generateGames(int numgames)
{
  return 0;
}


std::string LottoGame::checkResults()
{
  std::ostringstream test;

  return test.str();
}

int LottoGame::setResults(std::vector<int> passedResults)/* throw (AussieLottoException)*/
{
  size_t c;

  for (c = 0; c < passedResults.size(); ++c)
  {

    if (passedResults[c] > highest_ball)
      throw (AussieLottoException("Can not have a lotto number greater than 45", " "));  
    if (passedResults[c] == 0)
      throw (AussieLottoException("Can not have a lottery number of zero", "Try again"));
  }
  for (c = 0; c < (passedResults.size() - 1); ++c)
  {
    for(int x = (c + 1); x < balls; ++x)
      if(passedResults[c] == passedResults[x])
	throw AussieLottoException("Can not have duplicate draw numbers", " ");
  }
  results = passedResults;
  return 0;
}

void LottoGame::setPrizes(std::vector<float> prizes)
{
  m_prizes = prizes;
  m_prizesAvailable = true;
}

int LottoGame::loadGame(char *fname)
{
  std::ifstream fin;
  std::string header;
  int c;
  fin.open(fname);
  
  if (!fin.is_open())
    throw AussieLottoException("Could not open file", fname);

  fin >> header;

  fin >> games;
  numbers.resize(games);

  for (c = 0; c < games; ++c)
  {
    int temp;
    for (int x = 0; x < balls; ++x)
    {
      fin >> temp;
      numbers[c].push_back(temp);
    }
    
    memoryAllocated = true;

    strout.seekp(0, std::ios::beg);
    // Go to the beginning of the buffer, to overwrite the last game.
    // If we don't do this, it will try to add to the end of the last string we wrote.
    // We want a brand new string here.
    strout << "Game  " << c + 1 << std::endl;

    for (int x = 0; x < balls ; ++x)
    {
      strout << numbers[c][x];
      
      if (x == (balls - 1))
	strout << "\n";
      else
	strout << "\t";
    }

    strout << "\n\n";
  }
  strout << std::ends;

  return 0;
}

int LottoGame::setResultsSupps(int x1, int x2)/* throw (AussieLottoException)*/
{
  results_supps[0] = x1;
  results_supps[1] = x2;
  for (int c = 0; c <= 1; ++c)
  {
    if (results_supps[c] > highest_ball) {
      std::string s;
      std::stringstream out;
      out << "You entered ";
      out << results_supps[c];
      s = out.str();
      throw (AussieLottoException("Can not have a supplementary number greater than 45.",
				  s.c_str()));      
    } else if (results_supps[c] == 0) {
      throw (AussieLottoException("Can not have a supplementary number which is zero", " "));
    }
  }
  return 0;
}


void LottoGame::addGame(std::vector<int>& enteredValues)/* throw (AussieLottoException)*/
{
  
  for (size_t x = 0; x < enteredValues.size(); ++x)
  {
    if (enteredValues[x] == 0)
      throw (AussieLottoException("Not enough numbers entered", " "));
    else if (enteredValues[x] > highest_ball) {
      std::string s;
      std::stringstream out;
      out << "You chose ";
      out << enteredValues[x];
      s = out.str();
      throw (AussieLottoException("Can not have a number greater than 45.", s.c_str())); 
    }
  } // end for
  
  std::sort(enteredValues.begin(), enteredValues.end());
  for (size_t c = 0; c < (enteredValues.size() - 1); ++c)
  {
    if (enteredValues[c] == enteredValues[c + 1]) {
      std::string s;
      std::stringstream out;
      out << "The duplicate is ";
      out << enteredValues[c];
      s = out.str();
      throw (AussieLottoException("Can not have duplicate numbers.",
				  s.c_str()));
    }
  } // end for
  numbers.push_back(enteredValues);
  ++games;
   
  return;

} 
