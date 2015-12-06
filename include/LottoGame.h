/*
    AussieLotto: A tattslotto number generator and checker.
    Copyright (C) 2014 Dennis Katsonis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LOTTOGAME_H
#define LOTTOGAME_H
#include <stdint.h>
#include <string>
#include <sstream>
#include <vector>

#include "types.h"
#include "MersenneTwister.h"

gameType getFileGameType(char *fname);
void randomizeSeed();

class LottoGame
{
protected:
    bool memoryAllocated;
    int games;
    int outputted;
    int results_supps[2];
    int balls;
    std::ostringstream strout;
    std::string id;
    std::vector<std::vector<int> > numbers;
    std::vector<int> results;
    void printNoWinners();
    
  public:
  //  void setGameType(gameType x);
    virtual int saveGame(std::string fname);
    virtual int loadGame(char *fname);
    virtual int generateGames(int numGames);
    int setResultsSupps(int x1, int x2) throw (AussieLottoException);
    virtual std::string checkResults();
    int getNumGames() const;
    virtual int setResults(std::vector<int> passedResults) throw (AussieLottoException);
    virtual ~LottoGame();
    LottoGame();
    virtual void addGame(std::vector<int>& enteredValues) throw (AussieLottoException);
};


#endif
/* Method description:  Read here if you want to use the LottoGame class for your own programs.
 * 
 * Initialisation.  Create an instance of the class.  Optional arguments are a filename to LOAD
 * or an integer of the number of games to generate upon creating an instance of the class.  If no
 * argument, the class is created with no games.
 * 
 * saveGame() takes a string as an argument, and saves the game to a file.  It doesn't make
 * any changes to the filename nor add any extension.
 * 
 * loadGame() takes a char* argument and loads the file.
 * 
 * setResults() sets the lottery numbers which were /drawn/, and will be used to compare the games
 * against to determine any winners.  This will throw a string upon error (ie, if invalid numbers
 * were passed) otherwise it will return 0.  The arguments are a series of 'ints' each representing
 * one ball.  For Powerball, you pass the 6 balls and the powerball as the 7th 'int'.
 * 
 * addGame() The parameters are the same as setResults().  This ADDS those selected numbers to
 * the list of games. 
 * 
 * setResultsSupps()  Same as setResults() but sets supplementaries.  These aren't used for
 * powerball.
 * 
 * generateGames() Pass an int, and this will generate that number of random games.  Note that this
 * does not add to the existing games, but resets.  Powerball takes an additional parameter, a boolean
 * which is set to true if we want to ensure the powerball, or false if not.  Ensuring the powerball
 * essentially means that every 45 powerballs picked randomly, are guaranteed to be unique.
 * 
 * getNumGames() this function returns an 'int' which is the number games currently generated
 * or created.
 * 
 * checkResults()  This returns an 'ostream', which is a formatted stream listing the winning
 * games and what division those games win, in order from the higest divsion (Div 1) to the lowest.
 * 
 * example 
 * std::string results = tattsgames.checkResults();
 * 
 * <<
 * To output the generated and created games formatted to an output stream, use the << operatore
 * 
 * std::cout << tattsgames;
 * 
 * NOTE: The << has been overloaded so as to ONLY output data which has not been outputted before.
 * Therefore, if you generate it once and call <<, each subsequent call will ONLY print games
 * added since the last call, NOT the entire list again.  It is the callers responsibility to save
 * this data.  This was done this way for efficiency with the AussieLotto GUI, allowing an easy
 * way to update the GUI with new games, without having to export the entire list again.
 */
