#ifndef DATE_H
#define DATE_H
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>

class Date {
public:
  Date(const int day, const int month, const int year);
  Date(const char date[8]);
  Date();
  operator std::string() const;
  friend bool operator==(const Date &lhs, const Date& rhs);
  friend std::ostream& operator<<(std::ostream& ostr, const Date& date);
  void setDay(int day);
  void setMonth(int month);
  void setYear(int year);
  
private:
  int m_day;
  int m_month;
  int m_year;
  
  
  
};

#endif
