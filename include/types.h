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

#ifndef TYPES_H
#define TYPES_H


const int tattsBalls = 6;
const int ozlottoBalls = 7;
const int powerballBalls = 7;
const int lottostrikeBalls = 4;
const int setforlifeBalls = 8;

typedef enum gameType
{
  TATTSLOTTO,
  OZLOTTO,
  POWERBALL,
  LOTTOSTRIKE,
  SET_FOR_LIFE,
  WEEKDAY_TATTSLOTTO,
  UNDEFINED // Also serves to get number of gametypes out there.
} gameType;


typedef enum helpFunctions
{
  SHOW_LICENSE,
  SHOW_HELP
} helpType;

#endif
