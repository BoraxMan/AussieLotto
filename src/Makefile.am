#AM_CXXFLAGS =
#AM_CXXFLAGS = -Wall -O2 `fltk-config --cxxflags --use-images` 

AM_LDFLAGS = `fltk-config --ldflags --use-images` `curl-config --libs`
#AM_LDFLAGS = `fltk-config --ldflags --use-images` -s

AM_CPPFLAGS =  '-DDATADIR="$(datadir)"' -I$(srcdir)/../include ${libcurl_CFLAGS}

bin_PROGRAMS = aussielotto
aussielotto_SOURCES = HistoricResults.cxx ResultManager.cxx MersenneTwister.cpp  LottoGame.cxx SetForLife.cxx LottoStrike.cxx OzLotto.cxx Powerball.cxx Tattslotto.cxx AussieLottoException.cxx ExceptionHandler.cxx ResultDownloader.cxx date.cxx main.cxx
aussielotto_LDADD = libgui.a
noinst_LIBRARIES = libgui.a
libgui_a_SOURCES = AussieLottoGUI.cxx DrawHistoryManagerGUI.cxx AussieLotto.cxx DrawHistoryManager.cxx ResultViewTable.cxx
libgui_a_CXXFLAGS = `fltk-config --cxxflags --use-images` 
