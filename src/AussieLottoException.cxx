#include "AussieLottoException.h"

AussieLottoException::AussieLottoException() {}

AussieLottoException::AussieLottoException(const char *what, const char *where)
{
  m_message = what;
  m_where = where;
}

