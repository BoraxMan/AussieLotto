#ifndef LOTTOSTRIKE_H
#define LOTTOSTRIKE_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"
#include "AussieLottoException.h"

class lottostrikeGame : public LottoGame
{
  public:
    int saveGame(std::string fname);
    int generateGames(int numGames);
    ~lottostrikeGame();
    lottostrikeGame();
    lottostrikeGame(char *fname);
    lottostrikeGame(int numgames);
    void addGame(int x1, int x2, int x3, int x4)/* throw (AussieLottoException)*/;
    std::string checkResults();
    
    friend std::ostream &operator<<(std::ostream &outstream, lottostrikeGame & p);
  private:
    using LottoGame::addGame;
};


#endif
