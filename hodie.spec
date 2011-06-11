Summary: A program that prints out the current date and time in latin.
Name: hodie
Version: 1.4
Release: 1
Copyright: MIT
Group: Amusement/Games
Source: hodie-1.4.tar.gz
BuildRoot: /tmp/RPM_BUILD
%description
hodie was originally written to participate in the roman-numeral
    challenge from dotcomma. It has extensive, grammatical correct
    functionality of the same type as date (1)... only difference is
    the language.

Author: Mikael Johansson <mikael.johansson@wineasy.se>
%prep

%setup -q

%build
CFLAGS=$RPM_EXTRA_CFLAGS make all

%install
install -s hodie $RPM_BUILD_ROOT/usr/bin
install hodie.1 $RPM_BUILD_ROOT/usr/man/man1

%clean

%files
%defattr(-,root,root)
%doc LICENSE README BUGS CREDITS CHANGELOG TODO

%attr(755,-,-) /usr/bin/hodie
%attr(644,-,-) /usr/man/man1/hodie.1

%changelog
* Fri Nov 17 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Added support for explicit numbers (i.e. fully declined and written
  out...)

* Mon Sep 11 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- See CHANGELOG for details about new implementation.
  Mainly bugfixing though.
- Added CHANGELOG to the project.

* Wed Sep 6 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Added some extra functionality (i.e. verbosified numbers) and
    Sourceforgified the project.
- Beautified the Makefile after FreeBSD-recommendations from Peter
    Pentchev.

* Thu Aug 24 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Twiddled the .spec.
- Fixed all core dumps when not giving enough arguments (ex. 'hodie -r')
  --- I think... :-)

* Sun Aug 20 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Fixed a ton of bugs in the month handling.
- Added the BUGS and CREDITS files.
- Added the --republican feature (tnx to Anders Sandberg for the idea)
- Popped up to v1.2 and released.

* Thu Aug 17 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Partial revamp of .spec according to tips from *Insert name here*
- Started adding a custom date feature on request from Philip
    Zeyliger.
- Corrected bad grammar for accusative of September through December

* Mon Aug 14 2000 Harri Haataja <realblades@yahoo.com>
- Checked and fixed the spec file some


* Mon Aug 14 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Responded to most of the bugs reported. Should be running rather
  well rather soon now :-)
- To be more specific, the man page got a revamp, the source coded
  was splitted into one source file per callable function and the
  header and makefile were extensively cleaned up and improved 
  (at least in my own opinion :-)

* Sun Aug 13 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Verbosified a lot more. Fixed a few bugs. Got overwhelmed by the
    response from my release (6 e-mails overnight! WOW!)

* Sat Aug 12 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Grammar check done. Leap year february done. We are ready to launch.
  :-)

* Fri Aug 11 2000 Mikael Johansson <mikael.johansson@wineasy.se>
- Nearing full release state. Put version number on 1.0pre, awaiting
  grammar control.


