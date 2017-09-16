#ifndef ALEXCEPTION_H
#define ALEXCEPTION_H

#include <stdexcept>
#include <string>

class AussieLottoException : public std::exception
{
public:
  AussieLottoException();
  AussieLottoException(const char *what, const char *where);
  virtual ~AussieLottoException() throw() {};
  virtual const char *what() const throw() {return m_message.c_str(); }
  virtual const char *where() const throw() {return m_where.c_str(); }
private:
  std::string m_message;
  std::string m_where;
};

#endif
