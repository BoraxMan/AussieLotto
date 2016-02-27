#include "LottoStrike.h"


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

void lottostrikeGame::addGame(int x1, int x2, int x3, int x4) throw (AussieLottoException)
{
  std::vector<int> data;
  
  if (!x1 || !x2 || !x3 || !x4)
    throw (AussieLottoException("Not enough numbers entered", " "));
  else if((x1 > highest_ball) || (x2 > highest_ball) || (x3  > highest_ball) ||
	  (x4 > highest_ball))
    throw (AussieLottoException("Can not have a number greater than 45" , " "));
    
  data.push_back(x1);
  data.push_back(x2);
  data.push_back(x3);
  data.push_back(x4);

  // We DON'T sort here, as order is important.
  for (size_t c = 0; c < (data.size() - 1); ++c)
  {
    for(size_t x = (c + 1); x < data.size(); ++x)
      if(data[c] == data [x]) {
	std::string s;
	std::stringstream out;
	out << "You chose ";
	out << data[c];
	s = out.str();
	throw (AussieLottoException("Can not have duplicate numbers", s.c_str()));
      }
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
    throw (AussieLottoException("Could not open file", fname.c_str()));
  
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
      throw (AussieLottoException("Can't have zero as a lottery number.", " "));

  if (results[0] > highest_ball || results[1] > highest_ball || 
      results[2] > highest_ball || results[3] > highest_ball)
      throw (AussieLottoException("You have entered a number greater than the maximum possible.", " "));
  
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
    strout << "\n\n";
  }
 
if (winners == 1)
  strout << "You've won a single game." << std::endl;
else
  strout << "You've won " << winners << " games." << std::endl << std::ends;

return strout.str();
  
}
