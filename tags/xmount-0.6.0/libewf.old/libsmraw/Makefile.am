if HAVE_LOCAL_LIBSMRAW
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBMFCACHE_CPPFLAGS@ \
	@LIBMFDATA_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

noinst_LTLIBRARIES = libsmraw.la

libsmraw_la_SOURCES = \
	libsmraw_codepage.h \
	libsmraw_definitions.h \
	libsmraw_error.c libsmraw_error.h \
	libsmraw_extern.h \
	libsmraw_filename.c libsmraw_filename.h \
	libsmraw_handle.c libsmraw_handle.h \
	libsmraw_information_file.c libsmraw_information_file.h \
	libsmraw_legacy.c libsmraw_legacy.h \
	libsmraw_libbfio.h \
	libsmraw_libfvalue.h \
	libsmraw_libmfdata.h \
	libsmraw_libuna.h \
	libsmraw_metadata.c libsmraw_metadata.h \
	libsmraw_notify.c libsmraw_notify.h \
	libsmraw_support.c libsmraw_support.h \
	libsmraw_types.h \
	libsmraw_unused.h

libsmraw_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libnotify/libnotify.la \
	@LIBUNA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBMFCACHE_LIBADD@ \
	@LIBMFDATA_LIBADD@ \
	@LIBFVALUE_LIBADD@
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libsmraw ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libsmraw_la_SOURCES) 

