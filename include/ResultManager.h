#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include <string>
#include <fstream>
#include "LottoGame.h"
#include "types.h"
#include "HistoricResults.h"
#include "date.h"
#include "ResultDownloader.h"


typedef enum resultType
{
  R_TATTSLOTTO,
  R_OZLOTTO,
  R_POWERBALL,
  R_SET_FOR_LIFE,
  R_WEEKDAY_TATTSLOTTO,
  TOTAL_COUNT // Also serves to get number of gametypes out there.
} resultType;

class ResultManager {
  public:
    ResultManager(const std::string &configdir);
    ~ResultManager();
    std::vector<int> getResults(resultType game, int draw = 0);
    std::vector<int> getSupps(resultType game, int draw = 0);
    std::vector<float> getPrizes(resultType game, int draw = 0);
    Date getDate(resultType game, int draw = 0);
    int getLastDraw(resultType game);
    void downloadResults(resultType game);
    
    
  private:

    std::vector<std::string> URLlist;
    std::vector<LottoHistoricResults*> results;
    std::vector<std::string> csv_files;
    bool dbInitialised;
    int populateURLlist(const std::string &g, const std::string &u);
    int initResultFileDatabase();
    std::string homedir;
    
};


#endif
