AM_CXXFLAGS = -Wall -O2 `fltk-config --cxxflags --use-images` 
AM_CFLAGS = -Wall -O2
AM_LDFLAGS = `fltk-config --ldflags --use-images` -s
AM_CPPFLAGS = '-DDATADIR="$(datadir)"' -I$(srcdir)/../include

bin_PROGRAMS = aussielotto
aussielotto_SOURCES = MersenneTwister.cpp AussieLotto.cxx AussieLottoGUI.cxx LottoGame.cxx
