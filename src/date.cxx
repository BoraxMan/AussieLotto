#include "date.h"
#include <iostream>
#include <cassert>

namespace {
  
  const char *month[] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
  };
  
};

Date::Date(const int day, const int month, const int year)
{
  m_year = year;
  m_month = month;
  m_day = day;
}

Date::Date() : m_day(0), m_month(0), m_year(0)
{
  
}


Date::Date(const char date[8])
{
  std::string s(date);
  s.resize(8);
  char num[3];
  char lnum[5];
  num[2] = 0;
  lnum[4] = 0;
  strncpy(lnum, date, 4);
  m_year = atoi(lnum);
  strncpy(num, date + 4, 2);
  m_month = atoi(num);
  strncpy(num, date + 6, 2);
  m_day = atoi(num);
  assert(m_day > 0 && m_day <= 31);
  assert(m_month > 0 && m_month <= 12);

}

bool operator==(const Date &lhs, const Date& rhs)
{
 if ((lhs.m_day == rhs.m_day)
      && (lhs.m_month == rhs.m_month)
      && (lhs.m_year == rhs.m_year)) {
   return true;
 } else {
   return false;
 }
 return false;
  
}

Date::operator std::string() const
{
 if (m_day == 0 && m_month == 0 && m_year == 0) {
   return std::string("");
 }
 
 std::stringstream sdate;
 sdate << m_day << "/" << month[m_month - 1] << "/" << m_year;
 return sdate.str();
  
}

std::ostream& operator<<(std::ostream& ostr, const Date& date)
{
  std::string s = date;
  ostr << s;
  return ostr;
}

void Date::setDay(int day)
{
  m_day = day;
}

void Date::setMonth(int month)
{
  m_month = month;
}

void Date::setYear(int year)
{
  m_year = year;
}





