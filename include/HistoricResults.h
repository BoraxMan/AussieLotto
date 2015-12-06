#ifndef HISTORICRESULTS_H
#define HISTORICRESULTS_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

float dollarsToFloat(std::string &prize);

struct tatts_historic_result {
	int drawnumber;
	char date[8];
	std::vector<int> drawnballs; // Including powerball.
	std::vector<int> supps; // If any
	std::vector<float> prizes; // If any, from 1 to whatever
};


class FindDraw {
  public:
    FindDraw();
	FindDraw(const int draw);
	void setDraw(const int draw);
	bool operator() (const tatts_historic_result &drawRequested);
  private:
	int _draw;
};

class LottoHistoricResults {
public:
	LottoHistoricResults();
	LottoHistoricResults(const int bls, const int sups, const char *filename);
	int loadHistoricData(const char *filename);
	void setBalls(const int balls);
	void setSupps(const int supps);
	int size(void);
	std::vector<int> getResults(int draw = 0);
	std::vector<int> getSupps(int draw = 0);
	std::vector<float> getPrizes(int draw = 0);
	

private:
	std::ifstream fin;
	std::vector<tatts_historic_result> results;
	void getDate(std::string &token, char *date);
	int readLine(tatts_historic_result &destination);
	int tokenToInt(std::string &token);
	int balls;
	int supps;
	bool loaded;
};

#endif
