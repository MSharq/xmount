if HAVE_LOCAL_LIBMFDATA
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBBFIO_CPPFLAGS@ \
	@LIBMFCACHE_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

noinst_LTLIBRARIES = libmfdata.la

libmfdata_la_SOURCES = \
	libmfdata_array_type.c libmfdata_array_type.h \
	libmfdata_date_time.h \
	libmfdata_definitions.h \
	libmfdata_error.c libmfdata_error.h \
	libmfdata_extern.h \
	libmfdata_file.c libmfdata_file.h \
	libmfdata_file_list.c libmfdata_file_list.h \
	libmfdata_group.c libmfdata_group.h \
	libmfdata_inline.h \
	libmfdata_libbfio.h \
	libmfdata_libmfcache.h \
	libmfdata_list.c libmfdata_list.h \
	libmfdata_list_element.c libmfdata_list_element.h \
	libmfdata_range.c libmfdata_range.h \
	libmfdata_segment.c libmfdata_segment.h \
	libmfdata_segment_table.c libmfdata_segment_table.h \
	libmfdata_notify.c libmfdata_notify.h \
	libmfdata_support.c libmfdata_support.h \
	libmfdata_types.h \
	libmfdata_unused.h
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libmfdata ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libmfdata_la_SOURCES) 

