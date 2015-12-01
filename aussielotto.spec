Summary: A tattslotto game player and checker
Name: aussielotto
VERSION: 1.0.4
RELEASE: 1
LICENSE: GPL
Group: Applications
Source: aussielotto-1.0.4.tar.gz
#Source0: http://dennisk.customer.netspace.net.au/aussielotto/aussielotto-1.0.4.tar.gz

URL: http://dennisk.customer.netspace.net.au/aussielotto.html
Distribution: Fedora
Vendor: DK Soft
Packager: Dennis Katsonis <dennisk@netspace.net.au>

%description
Tattslotto number generator and game player for
Australian lotteries.  This application makes
it easy to select random numbers, save games
and then check which divisions you've won by checking
the numbers against the results.  You can also
add your own chosen numbers.
This supports Tattslotto, Lotto Strike, Ozlotto,
Powerball and Lotto X.

%prep
%setup

%build
%_configure --prefix=/usr CFLAGS="" CXXFLAGS="-O3 -DNDEBUG" --without-gcc-arch 
make

%install
rm -rf $RPM_BUILD_ROOT
make install-strip DESTDIR=$RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_docdir}/*
%{_bindir}/*
%{_datadir}/applications/*
%{_datadir}/icons/hicolor/64x64/apps/*



%clean
rm -rf $RPM_BUILD_ROOT

