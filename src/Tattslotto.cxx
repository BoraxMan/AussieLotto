#include <iomanip>
#include "Tattslotto.h"





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
    throw (AussieLottoException("Could not open file.", fname.c_str()));
  
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
  float prize_total = 0;
  int winners = 0;
  std::vector<std::vector<int> > results_tally; 
  
  std::ostringstream strout; // The stream that we will write the results to.
  
  if (!results[0] || !results[1] || !results[2] ||
      !results[3] || !results[4] || !results[5] ||
      !results_supps[0] || !results_supps[1])
      throw (AussieLottoException("Can't have zero as a lottery number.", " "));

  if (results[0] > highest_ball || results[1] > highest_ball || 
      results[2] > highest_ball || results[3] > highest_ball ||
      results[4] > highest_ball || results[5] > highest_ball ||
      results_supps[0] > highest_ball || results_supps[1] > highest_ball) 
      throw (AussieLottoException("You have entered a number greater than the maximum possible.", "Results should only go up to 45."));
  
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
    strout << std::fixed << std::setprecision(2) << std::setfill('0');
    if (m_prizesAvailable)
    {
      strout << "\nPrize : $" << m_prizes[(results_tally[c][0]-1)];
      prize_total += m_prizes[(results_tally[c][0]-1)];
    }
    strout << "\n\n";
  }
 

  if (winners == 1)
    strout << "You've won a single game." << std::endl;
  else
  {
    strout << "You've won " << winners << " games." << std::endl;
    if (m_prizesAvailable)
    {
      strout << "Total prize money won = $" << prize_total << std::endl;
    }
    strout << std::ends;
  }
  
return strout.str();
  
}

