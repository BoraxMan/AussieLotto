#ifndef OZLOTTO_H
#define OZLOTTO_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"

class ozlottoGame : public LottoGame
{
  public:
    int saveGame(std::string fname);
    int generateGames(int numGames);
    ~ozlottoGame();
    ozlottoGame();
    ozlottoGame(char *fname);
    ozlottoGame(int numgames);
    std::string checkResults();
    friend std::ostream &operator<<(std::ostream &outstream, ozlottoGame & p);
  private:
};

#endif
