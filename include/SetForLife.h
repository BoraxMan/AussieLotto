#ifndef SETFORLIFE_H
#define SETFORLIFE_H
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LottoGame.h"
#include "AussieLottoException.h"

class setforlifeGame : public LottoGame
{
  public:
    int saveGame(std::string fname);
    int generateGames(int numGames);
    ~setforlifeGame();
    setforlifeGame();
    setforlifeGame(char *fname);
    setforlifeGame(int numgames);
    std::string checkResults();
    
    friend std::ostream &operator<<(std::ostream &outstream, setforlifeGame & p);
  private:

};


#endif
