AM_CXXFLAGS = -Wall -O2 `fltk-config --cxxflags --use-images` 
AM_CFLAGS = -Wall -O2
AM_LDFLAGS = `fltk-config --ldflags --use-images` -s
AM_CPPFLAGS = '-DDATADIR="$(datadir)"'

bin_PROGRAMS = aussielotto
aussielotto_SOURCES = MersenneTwister.cpp AussieLotto.cxx AussieLottoGUI.cxx LottoGame.cxx types.h AussieLottoGUI.h AussieLotto.h LottoGame.h
