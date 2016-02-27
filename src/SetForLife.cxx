#include "SetForLife.h"

#include <iostream>
//*******************
// Set For Life Games
//*******************

std::ostream &operator<<(std::ostream &outstream, setforlifeGame & p)
{
  int gamecounter;
  for (gamecounter = p.outputted; gamecounter < p.games; ++gamecounter)
  {
    outstream << "Game  " << gamecounter + 1 << "\n";
    outstream << p.numbers[gamecounter][0] << "\t" << p.numbers[gamecounter][1] << "\t" << p.numbers[gamecounter][2] << "\t";
    outstream << p.numbers[gamecounter][3] << "\t" << p.numbers[gamecounter][4] << "\t" << p.numbers[gamecounter][5] << "\t";
    outstream << p.numbers[gamecounter][6] << "\t" << p.numbers[gamecounter][7];
    outstream << "\n\n";
  }
  p.outputted = p.games;
  
  outstream << std::ends;
  return outstream;
}

int setforlifeGame::generateGames(int numGames)
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

int setforlifeGame::saveGame(std::string fname)
{
  std::ofstream file_out;
  int c;
  
  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw AussieLottoException("Could not open file", fname.c_str());
  
  file_out << tatts_id << "\n";
  file_out << games << "\n";
  
  for (c = 0; c < games; ++c)
  {
    file_out << numbers[c][0] << "\t" << numbers[c][1] << "\t" << numbers[c][2] <<  "\t";
    file_out << numbers[c][3] << "\t" << numbers[c][4] << "\t" << numbers[c][5] <<  "\t";
    file_out << numbers[c][6] << "\t" << numbers[c][7] << "\n";
    // For each game, write out the randomly generated numbers.
  }

  file_out.close();
  return 0;
}


setforlifeGame::~setforlifeGame()
{

}

setforlifeGame::setforlifeGame()
{
  balls = setforlifeBalls;
  results.resize(balls);
}

setforlifeGame::setforlifeGame(char *fname)
{
  balls = setforlifeBalls;
  loadGame(fname); 
  results.resize(balls);
}

setforlifeGame::setforlifeGame(int numgames)
{
  balls = setforlifeBalls;
  if (numgames)
    generateGames(numgames);
  results.resize(balls);
}


std::string setforlifeGame::checkResults()
{
  int tat;
  int sup;
  int c;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 
  
  std::ostringstream strout; // The stream that we will write the results to.

  if (results[0] > highest_ball || results[1] > highest_ball || 
      results[2] > highest_ball || results[3] > highest_ball ||
      results[4] > highest_ball || results[5] > highest_ball ||
      results[6] > highest_ball || results[7] > highest_ball ||
      results_supps[0] > highest_ball || results_supps[1] > highest_ball)
      throw AussieLottoException("You have entered a number greater than the maximum possible.", " ");
  
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
    else if (numbers[c][i] == results[6])
      ++tat;
    else if (numbers[c][i] == results[7])
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
    if (tat == 8)
    {
      results_tally.at(winners).push_back(1);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 7 && sup)
    {
      results_tally.at(winners).push_back(2);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 7 && !sup)
    {
      results_tally.at(winners).push_back(3);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 6 && sup)
    {
      results_tally.at(winners).push_back(4);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 6 && !sup)
    {
      results_tally.at(winners).push_back(5);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && sup)
    {
      results_tally.at(winners).push_back(6);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 5 && !sup)
    {
      results_tally.at(winners).push_back(7);
      results_tally.at(winners++).push_back(c);
    }
    else if (tat == 4 && sup)
    {
      results_tally.at(winners).push_back(8);
      results_tally.at(winners++).push_back(c);
    }
  } // end of (for c < games) loop
  results_tally.resize(winners); //Resize to truncate extra vector items we didn't use.
  
  std::sort(results_tally.begin(), results_tally.end());
  if (!winners)
  {
    strout << "You haven't won anything!" << std::endl;
    strout << "Better luck next time..." << std::endl << std::ends;
    return strout.str();
  }
  
  for (c = 0; c < winners; ++c)
  {
    strout << "Division " << results_tally[c][0] << ":\n";
    strout << "  Game  " << (results_tally[c][1] + 1) << std::endl;
    strout << numbers[results_tally[c][1]][0] << "\t" << numbers[results_tally[c][1]][1] << "\t";
    strout << numbers[results_tally[c][1]][2] << "\t" << numbers[results_tally[c][1]][3] << "\t"; 
    strout << numbers[results_tally[c][1]][4] << "\t" << numbers[results_tally[c][1]][5] << "\t";
    strout << numbers[results_tally[c][1]][6] << "\t" << numbers[results_tally[c][1]][7] << "\t";
    strout << "\n\n";
  }
 

  if (winners == 1)
    strout << "You've won a single game." << std::ends;
  else
    strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
  
}
