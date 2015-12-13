
#include "HistoricResults.h"


void Namedifstream::setName(const char *filename)
{
  fname = filename;
}

const char *Namedifstream::getName(void) const
{
    return fname.c_str();
}


float dollarsToFloat(std::string &prize)
{
  
  std::string value;
  if (prize == "\"Set for Life\"") return 0.0f; // They sometimes put the string "Set for Life".  Treat this as 0.
  value = prize.substr(0, prize.length()-1); // Remove the "," at the end.
  char chars[] = "$,"; // Remove $ and ,.
  
  for (unsigned int i = 0; i < std::strlen(chars); ++i) {
    prize.erase (std::remove(prize.begin(), prize.end(), chars[i]), prize.end());
  }
  
  std::stringstream ss(prize);
  float val = 0;
  ss >> val;	
  return(val);
}



void FindDraw::setDraw(const int draw)
{
  _draw = draw;
}
FindDraw::FindDraw(const int draw)
{
  _draw = draw;
}

FindDraw::FindDraw() : _draw(0) {}

bool FindDraw::operator () (const tatts_historic_result &drawRequested)
{
  return (_draw == drawRequested.drawnumber);
}



LottoHistoricResults::LottoHistoricResults() : loaded(false) {}

LottoHistoricResults::LottoHistoricResults(const int bls, const int sups, const char *filename) : loaded(false)
{
  balls = bls;
  supps = sups;
  if (loadHistoricData(filename) == 0) {
    loaded = true;
  }
}


LottoHistoricResults::~LottoHistoricResults()
{
  if (fin.is_open()) {
    fin.close();
  }
  
}

Date LottoHistoricResults::readDate(std::string &token)
{
  char cdate[8];
  std::string value;
  if (token[0] == '\"') {
    value = token.substr(1, token.length()-2);
  } else {
    value = token;
  }
  std::copy(value.begin(), value.end(), cdate);
  Date date(cdate);
  return date;
}

int LottoHistoricResults::readLine(tatts_historic_result &destination)
{
  std::string line;
  std::stringstream buffer;
  std::string readBuffer;
  std::string value;
  std::string token;
  
  getline(fin, line);
  buffer << line;
  
  if (line.empty()) {
    return -1;
  }
  // Get draw number
  getline(buffer, readBuffer, ',');
  destination.drawnumber = tokenToInt(readBuffer);
  
  //Get date
  getline(buffer, readBuffer, ',');
  destination.date = readDate(readBuffer);
  
  // Process main numbers (drawnballs)
  for (int c = 0; c < balls; ++c) {
    getline(buffer, readBuffer, ',');
    destination.drawnballs.push_back(tokenToInt(readBuffer));
    
  }
  if (supps && buffer.eof()) {
    // If there are supps, but we are at the end of the line
    // then put "0" as the supps.  A few of the old tatts entries 
    // dont have supplementaries, so we need something.
    for (int c = 0; c < supps; ++c) {
      destination.supps.push_back(0);
    }
  } else {
    // Process supplementaries (supps)
    for (int c = 0; c < supps; ++c) {
      getline(buffer, readBuffer, ',');
      destination.supps.push_back(tokenToInt(readBuffer));
    }
    if (!buffer.eof()) {
      std::vector<float> prize_list;
      // Discard the stuff till the first '$'
      getline(buffer, readBuffer, '$');
      // Get tatts divisions
      for (;;) {
	getline(buffer, readBuffer, '$');
	float f = dollarsToFloat(readBuffer);
	prize_list.push_back(f);
	if (buffer.eof()) break;
      }
      destination.prizes = prize_list;
      
    }
  }
  return 0;
  
  
}

int LottoHistoricResults::tokenToInt(std::string &token)
{
  std::string value;
  if (token[0] == '\"') {
    value = token.substr(1, token.length()-2);
  } else {
    value = token;
  }
  
  if (value[0] == '-') {
    return 0;
    
  }
  std::stringstream ss(value);
  int val = 0;
  ss >> val;	
  return (val);
}

int LottoHistoricResults::reload()
{
  results.clear();
  loadHistoricData(fin.getName());
}

int LottoHistoricResults::loadHistoricData(const char *filename)
{
  fin.setName(filename); // Keep for later.
  std::string readBuffer;
  std::string value;
  fin.open(filename, std::ios_base::in);
  if (!fin.is_open()) {
    return -1;
  }
  
  std::string buffer;
  std::getline(fin, buffer);
  // discard the first line.
  if(loaded) {
    // Clear the data, reload.
    results.clear();
    loaded = false;
  }
  
  for(;;) {
    tatts_historic_result temp_result;
    
    if (readLine(temp_result) == -1) {
      break;
    }
    results.push_back(temp_result);	
  }
  loaded = true;
  fin.close();
  return 0;
}

void LottoHistoricResults::setBalls(const int x)
{
  balls = x;
}

void LottoHistoricResults::setSupps(const int x)
{
  supps = x;
}

int LottoHistoricResults::size(void)
{
  return results.size();
}

int LottoHistoricResults::getLastDrawNumber()
{
  if (results.empty()) {
    return 0;
  }
  return results[results.size() - 1].drawnumber;
}

std::vector<int> LottoHistoricResults::getResults(int draw)
{
   if (!loaded) {
    std::vector<int> empty;
    return empty;
  }
  
  if (draw == 0) {
    return results[results.size() - 1].drawnballs;
  } 
  
  FindDraw fd(draw);
  
  std::vector<tatts_historic_result>::iterator it = std::find_if(results.begin(), results.end(), fd);
  
  if (it == results.end()) {
    std::vector<int> empty;
    return empty;
  }
  return it->drawnballs;
  
}

std::vector<int> LottoHistoricResults::getSupps(int draw)
{
  if (!loaded) {
    std::vector<int> empty;
    return empty;
  }
  
  if (draw == 0) { 
    // Return most recent if draw is zero
    return results[results.size() - 1].supps;
  } 
  
  FindDraw fd(draw);
  
  std::vector<tatts_historic_result>::iterator it = std::find_if(results.begin(), results.end(), fd);
  
  if (it == results.end()) {
    std::vector<int> empty;
    return empty;
  }
  return it->supps;
  
}


std::vector<float> LottoHistoricResults::getPrizes(int draw)
{
  if (!loaded) {
    std::vector<float> empty;
    return empty;
  }
  
  if (draw == 0) { 
    // Return most recent if draw is zero
    return results[results.size() - 1].prizes;
  } 
  
  FindDraw fd(draw);
  
  std::vector<tatts_historic_result>::iterator it = 
    std::find_if(results.begin(), results.end(), fd);
  
  if (it == results.end()) {
    std::vector<float> empty;
    return empty;
  }
  return it->prizes;
  
}


Date LottoHistoricResults::getDate(int draw)
{
      std::cout << "N" << std::endl;
  if (!loaded) {
    Date empty;
    return empty;
  }
  
    std::cout << "3232323N" << std::endl;
  if (draw == 0) { 
    // Return most recent if draw is zero
    return results[results.size() - 1].date;
  } 
  
  FindDraw fd(draw);
  
  std::vector<tatts_historic_result>::iterator it = std::find_if(results.begin(), results.end(), fd);
  
  if (it == results.end()) {
    Date empty;
    return empty;
  }

  return it->date;
  
}

