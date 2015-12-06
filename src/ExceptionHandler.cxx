#include "ExceptionHandler.h"


void exceptionHander(const AussieLottoException &aussieLottoException)
{
  fl_message_title("Error encountered.");
  fl_message("Error : %s\n\n%s",aussieLottoException.what(), aussieLottoException.where());
}

