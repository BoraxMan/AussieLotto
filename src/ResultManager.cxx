#include "ResultManager.h"
#include <iostream>

namespace {
  
  const int URL_COUNT = 5;

  const char* csv_files_basenames[] = { // The order is important here.  Must corrleate with resultTypes enum.
    "TattsLotto.csv",
    "OzLotto.csv",
    "Powerball.csv",
    "SetForLife.csv",
    "MondayWednesdayLotto.csv"
  };
  
};

ResultManager::ResultManager(const std::string &configdir) : dbInitialised(false)
{
  std::string x;
  homedir = configdir;
  URLlist.resize(TOTAL_COUNT);
  
  if (initResultFileDatabase() == 0) {
        dbInitialised = true;
  } else {
    return;
  }
  for (int c = 0; c < TOTAL_COUNT; ++c) {
    x = homedir;
    x += csv_files_basenames[c];
    csv_files.push_back(x);
  }
  
  results.push_back(new LottoHistoricResults(6,2, csv_files[R_TATTSLOTTO].c_str()));
  results.push_back(new LottoHistoricResults(7,2, csv_files[R_OZLOTTO].c_str()));
  results.push_back(new LottoHistoricResults(7,0, csv_files[R_POWERBALL].c_str()));
  results.push_back(new LottoHistoricResults(8,2, csv_files[R_SET_FOR_LIFE].c_str()));
  results.push_back(new LottoHistoricResults(6,2, csv_files[R_WEEKDAY_TATTSLOTTO].c_str()));

}



std::vector<int> ResultManager::getResults(resultType game, int draw)
{
  return results[game]->getResults(draw);
}

std::vector<int> ResultManager::getSupps(resultType game, int draw)
{
  return results[game]->getSupps(draw);
}

std::vector<float> ResultManager::getPrizes(resultType game, int draw)
{
  return results[game]->getPrizes(draw);
}

ResultManager::~ResultManager()
{
  for (int c = 0; c < results.size(); c++) {
    delete results[c];
  }
  
}

int ResultManager::getLastDraw(resultType game)
{

 return results[game]->getLastDrawNumber(); 
}


int ResultManager::rowToDraw(resultType game, int row)
{
  return results[game]->rowToDraw(row);
}
  
Date ResultManager::getDate(resultType game, int draw)
{
 return results[game]->getDate(draw);
}

int ResultManager::size(resultType game)
{
  return results[game]->size();
}

int ResultManager::cols(resultType game)
{
  return results[game]->cols();
}

void ResultManager::downloadResults(resultType game)
{
  downloadFile(URLlist[game].c_str(), csv_files[game].c_str(), progress_callback, ptr);
  
}


int ResultManager::populateURLlist(const std::string &g, const std::string &u)
{
  if (g == tatts_id) {
    URLlist[R_TATTSLOTTO] = u; 
  } else if(g == ozlotto_id) {
    URLlist[R_OZLOTTO] = u;
  } else if(g == powerball_id) {
    URLlist[R_POWERBALL] = u;
  } else if(g == setforlife_id) {
    URLlist[R_SET_FOR_LIFE] = u;
  } else if(g== weekdaytatts_id) {
    URLlist[R_WEEKDAY_TATTSLOTTO] = u;
  }

  return 0;
}

int ResultManager::initResultFileDatabase()
{
  std::string game;
  std::string url;
  if (!dbInitialised) {

    std::ifstream urlsfile;
    urlsfile.open("lottourls", std::ios::in);

    if (!urlsfile.is_open()) {
      return -1;
    }

    for (int x = 0; x < URL_COUNT; ++x) {
      urlsfile >> game;
      urlsfile >> url;
      if (urlsfile.bad()) { return -1;}
      populateURLlist(game, url);
    }
    urlsfile.close();

  }
  return 0;
}

