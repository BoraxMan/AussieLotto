#include "Powerball.h"


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


int powerballGame::setResults(int x1, int x2, int x3, int x4, int x5, int x6, int pb) throw (AussieLottoException)
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
    if (results[c] > highest_ball) {
      std::string s;
      std::stringstream out;
      out << "You chose ";
      out << results[c];
      s = out.str(); 
      throw (AussieLottoException("Can not have a lotto number greater than 45", s.c_str()));
    }
    if (results[c] == 0)
      throw (AussieLottoException("Can not have a lottery number of zero", " "));
  }
  result_pb = pb; // This is the powerball
  if (result_pb > highest_ball) {
    std::string s;
    std::stringstream out;
    out << "You chose ";
    out << result_pb;
    s = out.str();
    throw (AussieLottoException("Powerball cannot be greater than 45", s.c_str()));
  }
  if (!result_pb)
    throw (AussieLottoException("Cannot have a powerball number of zero", " "));
  
  for (c = 0; c < (balls - 1); ++c)
  {
    for(int x = (c + 1); x < balls; ++x)
      if(results[c] == results[x]) {
      std::string s;
      std::stringstream out;
      out << "You chose ";
      out << results[c];
      s = out.str();
      throw (AussieLottoException("Can not have duplicate draw numbers", s.c_str()));
      }
  }
  return 0;
}


int powerballGame::saveGame(std::string fname)
{
  std::ofstream file_out;
  int c;
  file_out.open(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  
  if (!file_out.is_open())
    throw (AussieLottoException("Could not open file", fname.c_str()));

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
    throw (AussieLottoException("Could not open file", fname));
  
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
      throw (AussieLottoException("Can't have zero as a number.", " "));

  if (results[0] > highest_ball || results[1] > highest_ball || 
  results[2] > highest_ball || results[3] > highest_ball ||
  results[4] > highest_ball || result_pb > highest_ball)
      throw (AussieLottoException("Cannot have a ball higher than the maximum allowed", " "));
      
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
    else if (tat == 6 && !pow)
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
    strout << "You haven't won anything!" << std::endl;
    strout << "Better luck next time..." << std::endl << std::ends;
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


void powerballGame::addGame(int x1, int x2, int x3, int x4, int x5, int x6, int x7) throw (AussieLottoException)
{
  std::vector<int> data;
  
  if (!x1 || !x2 || !x3 || !x4 || !x5 || !x6 || !x7)
    throw (AussieLottoException("Not enough numbers entered", " "));

  if((x1 > highest_ball) || (x2 > highest_ball) || (x3 > highest_ball) ||
	  (x4 > highest_ball) || (x5 > highest_ball) || (x6 > highest_ball) ||
	  (x7 > highest_ball))
    throw (AussieLottoException("Can not have a number greater than 45", " "));
    
  data.push_back(x1);
  data.push_back(x2);
  data.push_back(x3);
  data.push_back(x4);
  data.push_back(x5);
  data.push_back(x6);
  std::sort(data.begin(), data.end());
  for (size_t c = 0; c < data.size() - 1; ++c)
  {
    if (data[c] == data[c + 1]) {
      std::string s;
      std::stringstream out;
      out << "You chose ";
      out << data[c];
      s = out.str();
      throw (AussieLottoException("Can not have duplicate numbers", s.c_str()));
    }
  }
  
  numbers.push_back(data);

  pb.push_back(x7);
  ++games;
  
  return;  
} 
