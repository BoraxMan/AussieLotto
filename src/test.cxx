#include <iostream>
#include <cstdlib>
#include <sstream>
#include "AussieLotto.h"
#include "LottoGame.h"
#include "types.h"

std::string ss(void)
{
  std::stringstream test;
  test << "Test message" << std::endl;
  return test.str();
}


int func1()
{
  std::cout << "Function 1" << std::endl;
  if(1)
    throw std::string("Exception!");
  return 0;
  
}
int main()
{
  std::string s;

  randomizeSeed();

  lottostrikeGame ls;
  ls.setResults(1,23,31,14,5,16);
  ls.generateGames(999999);
  ls.checkResults();
ls.checkResults();
ls.checkResults();
ls.checkResults();
ls.checkResults();
ls.checkResults();
  return 0;
}

