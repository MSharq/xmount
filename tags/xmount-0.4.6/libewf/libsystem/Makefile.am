AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	@LIBUNA_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

noinst_LTLIBRARIES = libsystem.la

libsystem_la_SOURCES = \
	libsystem.h \
	libsystem_date_time.c libsystem_date_time.h \
	libsystem_definitions.h \
	libsystem_directory.h \
	libsystem_directory_io.h \
	libsystem_error_string.c libsystem_error_string.h \
	libsystem_find.h \
	libsystem_file.c libsystem_file.h \
	libsystem_file_io.h \
	libsystem_file_stream.h \
	libsystem_getopt.c libsystem_getopt.h \
	libsystem_glob.c libsystem_glob.h \
	libsystem_i18n.h \
	libsystem_libuna.h \
	libsystem_notify.c libsystem_notify.h \
	libsystem_path.c libsystem_path.h \
	libsystem_signal.c libsystem_signal.h \
	libsystem_split_string.c libsystem_split_string.h \
	libsystem_string.c libsystem_string.h \
	libsystem_support.c libsystem_support.h \
	libsystem_unused.h

libsystem_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	@LIBUNA_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libsystem ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libsystem_la_SOURCES) 

