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
  srandom(time(NULL));
  tattslottoGame tatts;
  ozlottoGame oz;
  powerballGame pb;
  tatts.generateGames(200);
  pb.generateGames(10);
  oz.generateGames(10);
  tatts.setResults(15,32,45,14,34,33);
  tatts.setResultsSupps(10,3);
  std::cout << tatts;
  s = tatts.checkResults();
  std::cout << s << std::endl;
  try
  {
    std::cout << "Test" << std::endl;
    func1();
  }
  catch (std::string err)
  {
    std::cout << err << std::endl;
  }
  
  return 0;
}
