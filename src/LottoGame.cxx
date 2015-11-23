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


const int highest_ball = 45;
const long long full32bit = 4294967296ULL;  // 2^32
const std::string tatts_id = "TATTS_GAME";
const std::string ozlotto_id = "OZLOTTO_GAME";
const std::string powerball_id = "POWERBALL_GAME";
const std::string lottostrike_id = "LOTTOSTRIKE_GAME";

gameType getFileGameType(char *fname)
{ 
  std::ifstream fin;
  std::string header;

  fin.open(fname);
  
  if (!fin.is_open())
    throw std::string("Could not open file");
  
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

LottoGame::LottoGame() : memoryAllocated(false), games(0), outputted(0), balls(0)
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

void LottoGame::printNoWinners(void)
{
  strout << "You haven't won anything!" << std::endl;
  strout << "Better luck next time..." << std::endl << std::ends;
}

std::string LottoGame::checkResults()
{
  std::ostringstream test;

  return test.str();
}

int LottoGame::setResults(std::vector<int> passedResults) throw (std::string)
{
  size_t c;

  for (c = 0; c < passedResults.size(); ++c)
  {

    if (passedResults[c] > highest_ball)
      throw std::string("Can not have a lotto number greater than 45");  
    if (passedResults[c] == 0)
      throw std::string("Can not have a lottery number of zero");
  }
  for (c = 0; c < (passedResults.size() - 1); ++c)
  {
    for(int x = (c + 1); x < balls; ++x)
      if(passedResults[c] == passedResults[x])
	throw std::string("Can not have duplicate draw numbers");
  }

  results = passedResults;
  return 0;
}


int LottoGame::loadGame(char *fname)
{
  std::ifstream fin;
  std::string header;
  int c;
  fin.open(fname);
  
  if (!fin.is_open())
    throw std::string("Could not open file");

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

int LottoGame::setResultsSupps(int x1, int x2) throw (std::string)
{
  results_supps[0] = x1;
  results_supps[1] = x2;
  for (int c = 0; c <= 1; ++c)
  {
    if (results_supps[c] > highest_ball)
      throw std::string("Can not have a supplementary number greater than 45");
    else if (results_supps[c] == 0)
      throw std::string("Can not have a supplementary number which is zero");
  }

  return 0;
}


void LottoGame::addGame(std::vector<int>& enteredValues) throw (std::string)
{
  
  for (size_t x = 0; x < enteredValues.size(); ++x)
  {
    if (enteredValues[x] == 0)
      throw std::string("Not enough numbers entered");
    else if (enteredValues[x] > highest_ball)
      throw std::string("Can not have a number greater than 45"); 
  }
  
  std::sort(enteredValues.begin(), enteredValues.end());
  for (size_t c = 0; c < (enteredValues.size() - 1); ++c)
  {
    if (enteredValues[c] == enteredValues[c + 1])
      throw std::string("Can not have duplicate numbers");
  }
  numbers.push_back(enteredValues);
  ++games;
  
  return;

} 




//***********************
// Tattsotto Game methods
//***********************

std::ostream &operator<<(std::ostream &outstream, tattslottoGame & p)
{
  int gamecounter;
  for (gamecounter = p.outputted; gamecounter < p.games; ++gamecounter)
  {
    outstream << "Game  " << gamecounter + 1 << "\n";
    outstream << p.numbers[gamecounter][0] << "\t" << p.numbers[gamecounter][1] << "\t" << p.numbers[gamecounter][2] << "\t";
    outstream << p.numbers[gamecounter][3] << "\t" << p.numbers[gamecounter][4] << "\t" << p.numbers[gamecounter][5] << "\t";
    outstream << "\n\n";
  }
  p.outputted = p.games;
  
  outstream << std::ends;
  return outstream;
}

int tattslottoGame::generateGames(int numGames)
{
  int i;  //  The number ball
  int gamecounter; // To count which game
  games = numGames;
  if (!memoryAllocated)
  {
    numbers.resize(games);
    //numbers = new int[games][6];
    for (gamecounter = 0; gamecounter < games; ++gamecounter)
      numbers[gamecounter].resize(balls);
    
    memoryAllocated = true;
  }

  for (gamecounter = 0; gamecounter < games ; ++gamecounter)
  {
    for (i = 0 ; i < balls; ++i)
    {
      numbers[gamecounter][i] = (static_cast<int>(mt.genrand_uint32()/(full32bit/highest_ball))+1);
      for (int c = 0; c < i; ++c)
      {
	if (numbers[gamecounter][i] == numbers[gamecounter][c])
	  i--;
      }// Redo if we have already chosen that number.
      // We don't want the same number twice.
    }
    sort(numbers[gamecounter].begin(), numbers[gamecounter].end());
  }
  
  return 0;
  }

int tattslottoGame::saveGame(std::string fname)
{
  std::ofstream file_out;
  int c;
  
  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw std::string("Could not open file");
  
  file_out << tatts_id << "\n";
  file_out << games << "\n";
  
  for (c = 0; c < games; ++c)
  {
    file_out << numbers[c][0] << "\t" << numbers[c][1] << "\t" << numbers[c][2] <<  "\t";
    file_out << numbers[c][3] << "\t" << numbers[c][4] << "\t" << numbers[c][5] << "\n";
    // For each game, write out the randomly generated numbers.
  }

  file_out.close();
  return 0;
}


tattslottoGame::~tattslottoGame()
{

}

tattslottoGame::tattslottoGame()
{
  balls = tattsBalls;
  results.resize(balls);
}

tattslottoGame::tattslottoGame(char *fname)
{
  balls = tattsBalls;
  loadGame(fname); 
  results.resize(balls);
}

tattslottoGame::tattslottoGame(int numgames)
{
  balls = tattsBalls;
  if (numgames)
    generateGames(numgames);
  results.resize(balls);
}


std::string tattslottoGame::checkResults()
{
  int tat;
  int sup;
  int c;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 
  
  std::ostringstream strout; // The stream that we will write the results to.
  
  if (!results[0] || !results[1] || !results[2] ||
      !results[3] || !results[4] || !results[5] ||
      !results_supps[0] || !results_supps[1])
      throw std::string("Can't have zero as a lottery number.");

  if (results[0] > highest_ball || results[1] > highest_ball || 
      results[2] > highest_ball || results[3] > highest_ball ||
      results[4] > highest_ball || results[5] > highest_ball ||
      results_supps[0] > highest_ball || results_supps[1] > highest_ball)
      throw std::string("You have entered a number greater than the maximum possible.");
  
  for (c = 0; c < games; ++c)
  {
    if (results_tally.size() == static_cast<size_t>(winners))
      results_tally.resize(results_tally.size() + 10);

    tat = 0;
    sup = 0;
    for (int i = 0; i < balls; ++i)
    {
    if (numbers[c][i] == results[0])
      ++tat;
    else if (numbers[c][i] == results[1])
      ++tat;
    else if (numbers[c][i] == results[2])
      ++tat;
    else if (numbers[c][i] == results[3])
      ++tat;
    else if (numbers[c][i] == results[4])
      ++tat;
    else if (numbers[c][i] == results[5])
      ++tat;
    if (numbers[c][i] == results_supps[0])
      ++sup;
    if (numbers[c][i] == results_supps[1])
      ++sup;
    // Because it sometimes makes no difference if there are one or two supps
    // in regard to which division you are in, we don't need to differentiate between
    // whether you got one or two.  Here we just test for the existance of a supplementary
    // number and not how many there were (except for division 6, which needs two supps).
    }
    if (tat == 6)
    {
      results_tally.at(winners).push_back(1);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && sup)
    {
      results_tally.at(winners).push_back(2);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && !sup)
    {
      results_tally.at(winners).push_back(3);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 4)
    {
      results_tally.at(winners).push_back(4);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 3 && sup)
    {
      results_tally.at(winners).push_back(5);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat <= 2 && (sup == 2))
    {
      results_tally.at(winners).push_back(6);
      results_tally.at(winners++).push_back(c);
    }
  } // end of (for c < games) loop
  results_tally.resize(winners); //Resize to truncate extra vector items we didn't use.
  
  std::sort(results_tally.begin(), results_tally.end());
  if (!winners)
  {
    printNoWinners();
    return strout.str();
  }
  
  for (c = 0; c < winners; ++c)
  {
    strout << "Division " << results_tally[c][0] << ":\n";
    strout << "  Game  " << (results_tally[c][1] + 1) << std::endl;
    strout << numbers[results_tally[c][1]][0] << "\t" << numbers[results_tally[c][1]][1] << "\t";
    strout << numbers[results_tally[c][1]][2] << "\t" << numbers[results_tally[c][1]][3] << "\t"; 
    strout << numbers[results_tally[c][1]][4] << "\t" << numbers[results_tally[c][1]][5] << "\t";
    strout << "\n\n";
  }
 

  if (winners == 1)
    strout << "You've won a single game." << std::endl;
  else
    strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
  
}

//**********************
// Ozlotto Game methods
//**********************
  
std::ostream &operator<<(std::ostream &outstream, ozlottoGame & p)
{
  int gamecounter;
  for (gamecounter = p.outputted; gamecounter < p.games; ++gamecounter)
  {
    outstream << "Game  " << gamecounter + 1 << "\n";
    outstream << p.numbers[gamecounter][0] << "\t" << p.numbers[gamecounter][1] << "\t" << p.numbers[gamecounter][2] << "\t";
    outstream << p.numbers[gamecounter][3] << "\t" << p.numbers[gamecounter][4] << "\t";
    outstream << p.numbers[gamecounter][5] << "\t" << p.numbers[gamecounter][6];
    outstream << "\n\n";
  }
  p.outputted = p.games;
  outstream << std::ends;
  return outstream;
}


int ozlottoGame::generateGames(int numGames)
{
  int gamecounter; // To count which game

  games = numGames;
  
  if (!memoryAllocated)
  {
    numbers.resize(games);

    for (int c = 0; c < games; ++c)
      numbers[c].resize(balls);
    
    memoryAllocated = true;
  }

  for (gamecounter = 0; gamecounter < games ; ++gamecounter)
  {
    for (int i = 0 ; i < balls; ++i)
    {
      numbers[gamecounter][i] = (static_cast<int>(mt.genrand_uint32()/(full32bit/highest_ball))+1);
      for (int c = 0; c < i; ++c)
      {
	if (numbers[gamecounter][i] == numbers[gamecounter][c])
	  --i;
      }// Redo if we have already chosen that number.
      // We don't want the same number twice. 
    }
// Sort the generated numbers.
    sort(numbers[gamecounter].begin(), numbers[gamecounter].end());
  }
  
  return 0;
  }

  
int ozlottoGame::saveGame(std::string fname)
{
  std::ofstream file_out;

  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw std::string("Could not open file");
 
  file_out << ozlotto_id << "\n";

  file_out << games << "\n";
  
  for (int c = 0; c < games; ++c)
  {
    file_out << numbers[c][0] << "\t" << numbers[c][1] << "\t" << numbers[c][2] << "\t";
    file_out << numbers[c][3] << "\t" << numbers[c][4] << "\t" << numbers[c][5] << "\t";
    file_out << numbers[c][6] << "\n";
    // For each game, write out the randomly generated numbers.
  }

  file_out.close();
  return 0;
}


ozlottoGame::~ozlottoGame()
{

}

std::string ozlottoGame::checkResults()
{
  int tat;
  int sup;
  int c;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 
  // results_tally is two column array.  The first is the division number, the second the game number.
  
  std::ostringstream strout; // The stream that we will write the results to.

    if (!results[0] || !results[1] || !results[2] ||
	!results[3] || !results[4] || !results[5] || !results[6] ||
	!results_supps[0] || !results_supps[1])
      throw std::string("Can't have zero as a lottery number.");

  if (results[0] > highest_ball || results[1] > highest_ball || 
  results[2] > highest_ball || results[3] > highest_ball ||
  results[4] > highest_ball || results[5] > highest_ball ||
  results[6] > highest_ball || results_supps[0] > highest_ball || results_supps[1] > highest_ball)
     //If any numbers are higher than the highest ball number, warn the user.
    throw std::string("You have entered a number greater than the maximum possible.");
 
  for (c = 0; c < games; ++c)
  {
    tat = 0;
    sup = 0;
    if (results_tally.size() == static_cast<size_t>(winners))
      results_tally.resize(results_tally.size() + 10);

    for (int i = 0; i < balls; ++i)
    {
      if (numbers[c][i] == results[0])
	++tat;
      else if (numbers[c][i] == results[1])
	++tat;
      else if (numbers[c][i] == results[2])
	++tat;
      else if (numbers[c][i] == results[3])
	++tat;
      else if (numbers[c][i] == results[4])
	++tat;
      else if (numbers[c][i] == results[5])
	++tat;
      else if (numbers[c][i] == results[6])
	++tat;
      if (numbers[c][i] == results_supps[0] || numbers[c][i] == results_supps[1])
	++sup;
      // Because it makes no difference if there are one or two supps
      // in regard to which division you are in, we don't need to differentiate between
      // whether you got one or two.  Here we just test for the enumbersistance of a supplementary
      // number and not how many there were.
    }
    if (tat == 7)
    {
      results_tally.at(winners).push_back(1);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 6 && sup)
    {
      results_tally.at(winners).push_back(2);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 6 && !sup)
    {
      results_tally.at(winners).push_back(3);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && sup)
    {
      results_tally.at(winners).push_back(4);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && !sup)
    {
      results_tally.at(winners).push_back(5);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 4 && !sup)
    { 
      results_tally.at(winners).push_back(6);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 3 && sup)
    {
      results_tally.at(winners).push_back(7);
      results_tally.at(winners++).push_back(c);
    }
  } // end of (for c < games) loop
  results_tally.resize(winners); //Resize to truncate extra vector items we didn't use.
  
  std::sort(results_tally.begin(), results_tally.end());
  if (!winners)
  {
    printNoWinners();
    return strout.str();
  }
   
  for (c = 0; c < winners; ++c)
  {
    strout << "Division " << results_tally[c][0] << ":"  << "\n";
    strout << "  Game  " << (results_tally[c][1] + 1) << "\n";
    strout << numbers[results_tally[c][1]][0] << "\t" << numbers[results_tally[c][1]][1] << "\t";
    strout << numbers[results_tally[c][1]][2] << "\t";
    strout << numbers[results_tally[c][1]][3] << "\t" << numbers[results_tally[c][1]][4] << "\t";
    strout << numbers[results_tally[c][1]][5] << "\t" << numbers[results_tally[c][1]][6] << "\t";
    strout << "\n\n";
  }
 
if (winners == 1)
  strout << "You've won a single game." << std::endl;
else
  strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
  
}

ozlottoGame::ozlottoGame()
{  
  balls = ozlottoBalls;
  results.resize(balls);
}

ozlottoGame::ozlottoGame(char *fname)
{
  balls = ozlottoBalls;
  results.resize(balls);
  loadGame(fname);
}

ozlottoGame::ozlottoGame(int numgames)
{
  balls = ozlottoBalls;
    results.resize(balls);
  if (numgames)
    generateGames(numgames);

}

//***********************
// Powerball Game methods
//***********************

std::ostream &operator<<(std::ostream &outstream, powerballGame & p)
{
  int gamecounter;
  for (gamecounter = p.outputted; gamecounter < p.games; ++gamecounter)
  {
    outstream << "Game  " << gamecounter + 1 << "\n";
    outstream << p.numbers[gamecounter][0] << "\t" << p.numbers[gamecounter][1] << "\t" << p.numbers[gamecounter][2] << "\t";
    outstream << p.numbers[gamecounter][3] << "\t" << p.numbers[gamecounter][4] << "\t" << p.numbers[gamecounter][5] << std::endl;
    outstream << "Powerball : " << p.pb[gamecounter];
    outstream << "\n\n";
  }
  p.outputted = p.games;
  outstream << std::ends;
  return outstream;
}


void powerballGame::resetPowerballRandomPool(void)
{
 
  for (int c = 0; c < highest_ball; ++c)
  {
    powerballPool[c] = (c + 1);
  }
  std::random_shuffle(powerballPool.begin(), powerballPool.end());
  
  return;
  
}
  
int powerballGame::generateGames(int numGames, bool ensurePowerball)
{
  int c;  // General counter
  int gamecounter; // To count which game
  games = numGames;
  powerballsRemaining = highest_ball;

  resetPowerballRandomPool();
  
  if (!memoryAllocated)
  {
    numbers.resize(games);
    //numbers = new int[games][6];
    for (c = 0; c < games; ++c)
      numbers[c].resize((balls - 1)); // Its -1 because we don't include powerball
    
    pb.resize(games);
    memoryAllocated = true;
  }

  for (gamecounter = 0; gamecounter < games ; ++gamecounter)
  {
    for (int i = 0 ; i < (balls - 1); ++i)
    {
      numbers[gamecounter][i] = (static_cast<int>(mt.genrand_uint32()/(full32bit/highest_ball))+1);
      for (c = 0; c < i; ++c)
      {
	if (numbers[gamecounter][i] == numbers[gamecounter][c])
	  i--;
      }// Redo if we have already chosen that number.
      // We don't want the same number twice. In a lottery each number
      // can only be drawn once, so all our 6 numbers must be unique.
      // Decrementing i is not the best way to do this, but its quick and dirty
      // and will work as long as the number of numbers we have to choose isn't
      // greater than the range of numbers.  Then the loop will not terminate.
    } // This sets the 5 numbers
// Sort the generated numbers.
    sort(numbers[gamecounter].begin(), numbers[gamecounter].end());
    
    
    if (ensurePowerball == false)
      pb[gamecounter] = (static_cast<int>(mt.genrand_uint32()/(full32bit/highest_ball))+1); //Any random number
    else // If we are ensuring the powerball, we use a different method.
    {
      if (powerballsRemaining <= 0)
      {
	powerballsRemaining = highest_ball;
	resetPowerballRandomPool();
      }
      else
      {
	pb[gamecounter] = powerballPool[(powerballsRemaining - 1)];
	--powerballsRemaining;
      }
    }
  }  
  return 0;
}


int powerballGame::setResults(int x1, int x2, int x3, int x4, int x5, int x6, int pb) throw (std::string)
{ 
  int c;
  results[0] = x1;
  results[1] = x2;
  results[2] = x3;
  results[3] = x4;
  results[4] = x5;
  results[5] = x6;
  for (c = 0; c < (balls - 1); ++c)
  {
    if (results[c] > highest_ball)
      throw std::string("Can not have a lotto number greater than 45");
    if (results[c] == 0)
      throw std::string("Can not have a lottery number of zero");
  }
  result_pb = pb; // This is the powerball
  if (result_pb > highest_ball)
    throw std::string("Powerball cannot be greater than 45");
  if (!result_pb)
    throw std::string("Cannot have a powerball number of zero");
  
  for (c = 0; c < (balls - 1); ++c)
  {
    for(int x = (c + 1); x < balls; ++x)
      if(results[c] == results[x])
	throw std::string("Can not have duplicate draw numbers");
  }
  return 0;
}


int powerballGame::saveGame(std::string fname)
{
  std::ofstream file_out;
  int c;
  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw std::string("Could not open file");

  file_out << powerball_id << "\n";
  file_out << games << "\n";
  
  for (c = 0; c < games; ++c)
  {
    file_out << numbers[c][0] << "\t" << numbers[c][1] << "\t" << numbers[c][2] << "\t";
    file_out << numbers[c][3] << "\t" << numbers[c][4] << "\t" << numbers[c][5] << "\t";
    file_out << pb[c] << "\n";
  }

  file_out.close();
  return 0;
}


int powerballGame::loadGame(char *fname)
{
  
  std::ifstream fin;
  std::string header;
  int c;
  
  fin.open(fname);

  if (!fin.is_open())
    throw std::string("Could not open file");
  
  fin >> header;
  fin >> games;
  
  numbers.resize(games);

  for (c = 0; c < games; ++c)
    numbers[c].resize((balls - 1));

  pb.resize(games);
  memoryAllocated = true;
  
  for (c = 0; c < games; ++c)
  {
    fin >> numbers[c][0];
    fin >> numbers[c][1];
    fin >> numbers[c][2];
    fin >> numbers[c][3];
    fin >> numbers[c][4];
    fin >> numbers[c][5];
    fin >> pb[c];
    strout.seekp(0, std::ios::beg);
    // Go to the beginning of the buffer, to overwrite the last game.
    // If we don't do this, it will try to add to the end of the last string we wrote.
    // We want a brand new string here.
    strout << "Game  " << c + 1 << "\n";
    strout << numbers[c][0] << "\t" << numbers[c][1] << "\t" << numbers[c][2] << "\t";
    strout << numbers[c][3] << "\t" << numbers[c][4] << "\t" << numbers[c][5] << "\t" << "\n";
    strout << "Powerball :" << pb[c] << "\n\n";
  }

  strout << std::ends;
  return 0;
}

powerballGame::~powerballGame()
{
  
}

std::string powerballGame::checkResults()
{

  int tat;
  int sup;
  int c;
  int pow;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 

  std::ostringstream strout; // The stream that we will write the results to.

  if (!results[0] || !results[1] || !results[2] ||
    !results[3] || !results[4] || !results[5] || !result_pb)
      throw std::string("Can't have zero as a number.");

  if (results[0] > highest_ball || results[1] > highest_ball || 
  results[2] > highest_ball || results[3] > highest_ball ||
  results[4] > highest_ball || result_pb > highest_ball)
      throw std::string("Cannot have a ball higher than the maximum allowed");
      
  for (c = 0; c < games; ++c)
  {
    if (results_tally.size() == static_cast<size_t>(winners))
    {
      results_tally.resize(results_tally.size() + 10);
    }
    tat = 0;
    sup = 0;
    pow = 0;
    for (int i = 0; i < balls; ++i)
    {
    if (numbers[c][i] == results[0])
      ++tat;
    else if (numbers[c][i] == results[1])
      ++tat;
    else if (numbers[c][i] == results[2])
      ++tat;
    else if (numbers[c][i] == results[3])
      ++tat;
    else if (numbers[c][i] == results[4])
      ++tat;
    else if (numbers[c][i] == results[5])
      ++tat;
    if (pb[c] == result_pb)
      ++pow; // Check for powerball
    }
    
    if (tat == 6 && pow)
    {
      results_tally.at(winners).push_back(1);
      results_tally.at(winners++).push_back(c);;
    }
    else if (tat == 6 && !sup)
    {
      results_tally.at(winners).push_back(2);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && pow)
    {
      results_tally.at(winners).push_back(3);
      results_tally.at(winners++).push_back(c);;
    }
    else if (tat == 5 && !pow)
    {
      results_tally.at(winners).push_back(4);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 4 && pow)
    {
      results_tally.at(winners).push_back(5);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 3 && pow)
    {
      results_tally.at(winners).push_back(6);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 4 && !pow)
    {
      results_tally.at(winners).push_back(7);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 2 && pow)
    {
      results_tally.at(winners).push_back(8);
      results_tally.at(winners++).push_back(c);
    }

 } // end of (for c < games) loop
  results_tally.resize(winners); //Resize to truncate extra vector items we didn't use.
  
  std::sort(results_tally.begin(), results_tally.end());
  if (!winners)
  {
    printNoWinners();
    return strout.str();
  }
  
  for (c = 0; c < winners; ++c)
  {
    strout << "Division : " << results_tally[c][0] << "\n";
    strout << "  Game  " << (results_tally[c][1] + 1) << "\n";
    strout << numbers[results_tally[c][1]][0] << "\t" << numbers[results_tally[c][1]][1] << "\t";
    strout << numbers[results_tally[c][1]][2] << "\t";
    strout << numbers[results_tally[c][1]][3] << "\t" << numbers[results_tally[c][1]][4] << "\t";
    strout << numbers[results_tally[c][1]][5] << "\n";
    strout << "Powerball :" << pb[results_tally[c][1]];
    strout << "\n\n";
  }
 
  if (winners == 1)
    strout << "You've won a single game." << std::endl;
  else
    strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
}


powerballGame::powerballGame()
{
  balls = powerballBalls;
  results.resize((balls - 1));
  powerballPool.resize(highest_ball);
}

powerballGame::powerballGame(char *fname)
{
  balls = powerballBalls;
  results.resize((balls - 1));
  loadGame(fname);
  powerballPool.resize(highest_ball);
}

powerballGame::powerballGame(int numgames, bool ensurePowerball)
{
  balls = powerballBalls;
  results.resize((balls - 1));
  powerballPool.resize(highest_ball);
  if (numgames)
    generateGames(numgames, ensurePowerball);
}


void powerballGame::addGame(int x1, int x2, int x3, int x4, int x5, int x6, int x7) throw (std::string)
{
  std::vector<int> data;
  
  if (!x1 || !x2 || !x3 || !x4 || !x5 || !x6 || !x7)
    throw std::string("Not enough numbers entered");

  if((x1 > highest_ball) || (x2 > highest_ball) || (x3 > highest_ball) ||
	  (x4 > highest_ball) || (x5 > highest_ball) || (x6 > highest_ball) ||
	  (x7 > highest_ball))
    throw std::string("Can not have a number greater than 45");
    
  data.push_back(x1);
  data.push_back(x2);
  data.push_back(x3);
  data.push_back(x4);
  data.push_back(x5);
  data.push_back(x6);
  std::sort(data.begin(), data.end());
  for (size_t c = 0; c < data.size() - 1; ++c)
  {
    if (data[c] == data[c + 1])
      throw std::string("Can not have duplicate numbers");
  }
  
  numbers.push_back(data);

  pb.push_back(x7);
  ++games;
  
  return;  
} 

//***********************
// Lottostrike Game methods
//***********************

std::ostream &operator<<(std::ostream &outstream, lottostrikeGame & p)
{
  int gamecounter;
  for (gamecounter = p.outputted; gamecounter < p.games; ++gamecounter)
  {
    outstream << "Game  " << gamecounter + 1 << "\n";
    outstream << p.numbers[gamecounter][0] << "\t" << p.numbers[gamecounter][1] << "\t";
    outstream << p.numbers[gamecounter][2] << "\t" << p.numbers[gamecounter][3] << "\t";
    outstream << "\n\n";
  }
  p.outputted = p.games;
  
  outstream << std::ends;
  return outstream;
}

void lottostrikeGame::addGame(int x1, int x2, int x3, int x4) throw (std::string)
{
  std::vector<int> data;
  
  if (!x1 || !x2 || !x3 || !x4)
    throw std::string("Not enough numbers entered");
  else if((x1 > highest_ball) || (x2 > highest_ball) || (x3  > highest_ball) ||
	  (x4 > highest_ball))
    throw std::string("Can not have a number greater than 45");
    
  data.push_back(x1);
  data.push_back(x2);
  data.push_back(x3);
  data.push_back(x4);

  // We DON'T sort here, as order is important.
  for (size_t c = 0; c < (data.size() - 1); ++c)
  {
    for(size_t x = (c + 1); x < data.size(); ++x)
      if(data[c] == data [x])
	throw std::string("Can not have duplicate numbers");
  }
  
  numbers.push_back(data);
  ++games;
  
  return;
}  

int lottostrikeGame::generateGames(int numGames)
{
  int gamecounter; // To count which game
  games = numGames;
  if (!memoryAllocated)
  {
    numbers.resize(games);
    //numbers = new int[games][6];
    for (gamecounter = 0; gamecounter < games; ++gamecounter)
      numbers[gamecounter].resize(balls);
    
    memoryAllocated = true;
  }

  for (gamecounter = 0; gamecounter < games ; ++gamecounter)
  {
    for (int i = 0 ; i < balls; ++i)
    {
      numbers[gamecounter][i] = (static_cast<int>(mt.genrand_uint32()/(full32bit/45))+1);
      for (int c = 0; c < i; ++c)
      {
	if (numbers[gamecounter][i] == numbers[gamecounter][c])
	  i--;
      }// Redo if we have already chosen that number.
      // We don't want the same number twice.
    }
    // We DON'T sort here, because order is important in lotto strike.
  }
  
  return 0;
}


int lottostrikeGame::saveGame(std::string fname)
{
  std::ofstream file_out;
  int c;
  
  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw std::string("Could not open file");
  
  file_out << lottostrike_id << "\n";
  file_out << games << "\n";
  
  for (c = 0; c < games; ++c)
  {	
    file_out << numbers[c][0] << "\t" << numbers[c][1] << "\t";
    file_out << numbers[c][2] << "\t" << numbers[c][3] << "\n";
    // For each game, write out the randomly generated numbers.
  }

  file_out.close();
  return 0;
}


lottostrikeGame::~lottostrikeGame()
{

}

lottostrikeGame::lottostrikeGame()
{
  balls = lottostrikeBalls;
  results.resize(balls);
}

lottostrikeGame::lottostrikeGame(char *fname) 
{
  balls = lottostrikeBalls;
  results.resize(balls);
  loadGame(fname); 
}

lottostrikeGame::lottostrikeGame(int numgames) 
{
  balls = lottostrikeBalls;
  results.resize(balls);
  if (numgames)
    generateGames(numgames);
}


std::string lottostrikeGame::checkResults()
{
  int index, index2;
  int c;
  int oldmatches, matches = 0;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 
  
  std::ostringstream strout; // The stream that we will write the results to.
  
  if (!results[0] || !results[1] || !results[2] || !results[3])
      throw std::string("Can't have zero as a lottery number.");

  if (results[0] > highest_ball || results[1] > highest_ball || 
      results[2] > highest_ball || results[3] > highest_ball)
      throw std::string("You have entered a number greater than the maximum possible.");
  
  for (c = 0; c < games; ++c)
  {
    index2 = 0;
    oldmatches = 0;
    index = 0;
    matches = 0;
    
    if (results_tally.size() == static_cast<size_t>(winners))  
      results_tally.resize(results_tally.size() + 10);
      
    while(index < balls)
    {
      if((numbers[c][index] == results[index2]) && (index2 < balls))
      {
	++matches; 
	++index;
	++index2;
      }
      else if (matches == 0 && (index2 < balls))
      {
	++index2;
      }

      else if (index2 >= balls)
      {
	index2 = 0;
	++index;
	oldmatches = matches;
	matches = 0;
      }
      else
      {
	oldmatches = matches;
	matches = 0;
      }
    } // end while;

    if (oldmatches > matches)
      matches = oldmatches; // If we found two sequences we found, had
      // the original as thelarger sequence while continuing
      // our search, use the original.
    
    if (matches == 4)
    {
      results_tally.at(winners).push_back(1);
      results_tally.at(winners++).push_back(c);
    }
    else if (matches == 3)
    {
      results_tally.at(winners).push_back(2);
      results_tally.at(winners++).push_back(c);
    }
    else if (matches == 2)
    {
      results_tally.at(winners).push_back(3);
      results_tally.at(winners++).push_back(c);
    }
    else if (matches == 1)
    {
      results_tally.at(winners).push_back(4);
      results_tally.at(winners++).push_back(c);
    }
    
  } // end of (for c < games) loop
  results_tally.resize(winners); //Resize to truncate extra vector items we didn't use.
  
  std::sort(results_tally.begin(), results_tally.end());
  if (!winners)
  {
    printNoWinners();
    return strout.str();
  }
  
  for (c = 0; c < winners; ++c)
  {
    strout << "Division " << results_tally[c][0] << ":\n";
    strout << "  Game  " << (results_tally[c][1] + 1) << std::endl;
    strout << numbers[results_tally[c][1]][0] << "\t" << numbers[results_tally[c][1]][1] << "\t";
    strout << numbers[results_tally[c][1]][2] << "\t" << numbers[results_tally[c][1]][3] << "\t"; 
    strout << "\n\n";
  }
 
if (winners == 1)
  strout << "You've won a single game." << std::endl;
else
  strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
  
}

