Name: libewf
Version: 20111015
Release: 1
Summary: Library to support the Expert Witness Compression Format (EWF)
Group: System Environment/Libraries
License: LGPL
Source: %{name}-%{version}.tar.gz
URL: http://libewf.sourceforge.net
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires:     zlib
BuildRequires:     zlib-devel

%description
libewf is a library to support the Expert Witness Compression Format (EWF).
libewf allows you to read media information of EWF files in the SMART (EWF-S01)
format and the EnCase (EWF-E01) format. libewf allows to read files created by
EnCase 1 to 6, linen and FTK Imager.

%package devel
Summary: Header files and libraries for developing applications for libewf
Group: Development/Libraries
Requires: libewf = %{version}-%{release}

%description devel
Header files and libraries for developing applications for libewf.

%package tools
Summary: Several tools for reading and writing EWF files
Group: Applications/System
Requires: libewf = %{version}-%{release} openssl fuse-libs     libuuid
BuildRequires: byacc flex openssl-devel fuse-devel     libuuid-devel

%description tools
Several tools for reading and writing EWF files.
It contains tools to acquire, export, query and verify EWF files.

%prep
%setup -q

%build
%configure --prefix=/usr --libdir=%{_libdir} --mandir=%{_mandir} --enable-v1-api=yes
make %{?_smp_mflags}

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

%clean
rm -rf ${RPM_BUILD_ROOT}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README
%attr(755,root,root) %{_libdir}/*.so.*

%files devel
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README README.dll README.macosx README.mingw README.static ChangeLog
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/libewf.pc
%{_includedir}/*
%{_mandir}/man3/*

%files tools
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README
%attr(755,root,root) %{_bindir}/ewfacquire
%attr(755,root,root) %{_bindir}/ewfacquirestream
%attr(755,root,root) %{_bindir}/ewfexport
%attr(755,root,root) %{_bindir}/ewfinfo
%attr(755,root,root) %{_bindir}/ewfmount
%attr(755,root,root) %{_bindir}/ewfverify
%{_mandir}/man1/*

%changelog
* Mon Oct 10 2011 Joachim Metz <jbmetz@users.sourceforge.net> 20111010-1
- Bug fix

* Thu Oct  6 2011 Joachim Metz <jbmetz@users.sourceforge.net> 20111006-1
- Update for configure changes

* Sun Sep 18 2011 Joachim Metz <jbmetz@users.sourceforge.net> 20110918-1
- Added ewfmount and libfuse dependencies
- Fix in ewftools dependencies
- Added README files

* Mon Aug  1 2011 Joachim Metz <jbmetz@users.sourceforge.net> 20110801-1
- Added libhmac and libfvalue, changed libcrypto build dependencies

* Fri Nov 19 2010 Joachim Metz <jbmetz@users.sourceforge.net> 20101119-1
- Added flex and byacc build dependencies

* Thu Nov  4 2010 Joachim Metz <jbmetz@users.sourceforge.net> 20101104-1
- Added README.static

* Wed Jul 14 2010 Joachim Metz <jbmetz@users.sourceforge.net> 20100714-1
- Clean up of previous version of spec file

