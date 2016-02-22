#ifndef TATTSLOTTO_H
#define TATTSLOTTO_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"
#include "AussieLottoException.h"


class tattslottoGame : public LottoGame
{
  public:
    int saveGame(std::string fname);
    int generateGames(int numGames);
    std::string checkResults();
    ~tattslottoGame();
    tattslottoGame();
    tattslottoGame(char *fname);
    tattslottoGame(int numgames);
    friend std::ostream &operator<<(std::ostream &outstream, tattslottoGame & p);
  private:

};



#endif
