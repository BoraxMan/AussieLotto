#include <string>
#include <FL/Fl_Pixmap.H> 
#include <FL/Fl_RGB_Image.H> 
#include "AussieLotto.h"
#include "DrawHistoryManager.h"
#include "ResultManager.h"
#include "AussieLottoException.h"
#include "ExceptionHandler.h"
#include "aussielotto.xpm"

#ifdef __linux
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#elif __APPLE__
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
#elif __WIN32
  std::string path = getenv("APPDATA");
  path += "\\aussielotto\\";
#elif __APPLE__
  passwd* pw = getpwuid(getuid());
  std::string path(pw->pw_dir);
  path += "/Library/Caches/aussielotto/";

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
  Fl_Pixmap aussielotto_32x32_icon(aussielotto);
  Fl_RGB_Image aussielotto_icon(&aussielotto_32x32_icon, Fl_Color(0)); 
 
  AusLotto x(resultManager, homedir);
  x.make_window();
  x.lotto_gui->show();
  x.lotto_gui->icon(&aussielotto_icon);
  x.lotto_gui->xclass("AussieLotto");
  x.createOzlottoEntryWindows();
  x.createTattsEntryWindows();
  x.createPowerballEntryWindows();
  x.createLottostrikeEntryWindows();
  x.createSetForLifeEntryWindows();
  return Fl::run();
}
