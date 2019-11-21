#ifndef POWERBALL_H
#define POWERBALL_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"
#include "AussieLottoException.h"


class powerballGame : public LottoGame
{
  public:
    int saveGame(std::string fname);
    void addGame(int x1, int x2, int x3, int x4, int x5, int x6, int pb)/* throw (AussieLottoException)*/;
    int generateGames(int numGames, bool ensurePowerball);
    int setResults(int x1, int x2, int x3, int x4, int x5, int x6, int pb)/* throw (AussieLottoException)*/;
    std::string checkResults();
    int loadGame(char *fname);
    ~powerballGame();
    powerballGame();
    powerballGame(char *fname);
    powerballGame(int numgames, bool ensurePowerball);
    friend std::ostream &operator<<(std::ostream &outstream, powerballGame & p);

  private:
    void resetPowerballRandomPool(void);
    int result_pb;
    std::vector<int> powerballPool;
    std::vector<int> pb;
    int powerballsRemaining;
    using LottoGame::addGame;
    using LottoGame::generateGames;
    using LottoGame::setResults;
};



#endif
