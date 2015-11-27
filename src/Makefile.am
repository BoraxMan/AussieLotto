#AM_CXXFLAGS =
#AM_CXXFLAGS = -Wall -O2 `fltk-config --cxxflags --use-images` 

AM_LDFLAGS = `fltk-config --ldflags --use-images`
#AM_LDFLAGS = `fltk-config --ldflags --use-images` -s

AM_CPPFLAGS =  '-DDATADIR="$(datadir)"' -I$(srcdir)/../include 

bin_PROGRAMS = aussielotto
aussielotto_SOURCES = MersenneTwister.cpp AussieLotto.cxx AussieLottoGUI.cxx LottoGame.cxx
aussielotto_LDADD = libgui.a
noinst_LIBRARIES = libgui.a
libgui_a_SOURCES = AussieLottoGUI.cxx
libgui_a_CXXFLAGS = `fltk-config --cxxflags --use-images` 
