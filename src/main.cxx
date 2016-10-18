#include <string>
#include "AussieLotto.h"
#include "DrawHistoryManager.h"
#include "ResultManager.h"
#include "AussieLottoException.h"
#include "ExceptionHandler.h"

#ifdef __linux
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#endif


int main(void)
{ 
  
  std::string homedir;
#ifdef __linux
  passwd* pw = getpwuid(getuid());
  std::string path(pw->pw_dir);
  path += "/.config/aussielotto/";
#else
  std::string path = getenv("APPDATA");
  path += "\\aussielotto\\";
#endif
  homedir += path;
  ResultManager *resultManager;
  fl_register_images();
  try {
    resultManager = new ResultManager(homedir);
  } catch (AussieLottoException &e) {
    exceptionHander(e);
    // Cant run without the result manager.  Bail out.
    return 1;
  }
  
  AusLotto x(resultManager, homedir);
  
  x.make_window();
  x.lotto_gui->show();
  x.createOzlottoEntryWindows();
  x.createTattsEntryWindows();
  x.createPowerballEntryWindows();
  x.createLottostrikeEntryWindows();
  x.createSetForLifeEntryWindows();
  return Fl::run();
}
