AUTOMAKE_OPTIONS = foreign
SUBDIRS=wave_ping

################
bin_PROGRAMS = wave

################
wave_SOURCES = main.c wave.c 

################
wave_CPPFLAGS = -g3 -DCONFIG_DIR=\“$(sysconfdir)\” -DLIBRARY_DIR=\”$(pkglibdir)\”

################
CURRENTPATH=$(shell /usr/bin/pwd)

INCLUDES=-I$(CURRENTPATH) -I$(CURRENTPATH)/wave_utils -I$(CURRENTPATH)/wave_lib -I$(CURRENTPATH)/wave_ping

###############

wave_LDFLAGS=

################
noinst_HEADERS=wave.h 
#include_HEADERS=wave.h wave_utils/wave_list.h

################
wave_LDADD= $(top_builddir)/wave_ping/libping.la
