#ifndef HISTORICRESULTS_H
#define HISTORICRESULTS_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include "date.h"

float dollarsToFloat(std::string &prize);

struct tatts_historic_result {
	int drawnumber;
	Date date;
	std::vector<int> drawnballs; // Including powerball.
	std::vector<int> supps; // If any
	std::vector<float> prizes; // If any, from 1 to whatever
};

class Namedifstream : public std::ifstream
{
public:
    Namedifstream() {};
    void setName(const char *filename);
    const char *getName(void) const;
  private:
    std::string fname;
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
	~LottoHistoricResults();
	LottoHistoricResults(const int bls, const int sups, const char *filename);
	LottoHistoricResults(const LottoHistoricResults &src);
	int loadHistoricData(const char *filename);
	int reload();
	void setBalls(const int balls);
	void setSupps(const int supps);
	int size(void) const;
	int cols(void) const;
	const std::vector<int> &getResults(const int draw = 0) const;
	const std::vector<int> &getSupps(const int draw = 0) const;
	const std::vector<float> &getPrizes(const int draw = 0) const;
	Date getDate(const int draw = 0) const;
	int rowToDraw(const int row) const;
	int getLastDrawNumber() const;
	

private:
	Namedifstream fin;
	std::vector<tatts_historic_result> results;
	Date readDate(std::string &token);
	int readLine(tatts_historic_result &destination);
	int tokenToInt(std::string &token);
	int balls;
	int supps;
	bool loaded;
	std::vector<int> empty;
	std::vector<float> emptyf;
};

#endif
