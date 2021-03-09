AUTOMAKE_OPTIONS = foreign


################
bin_PROGRAMS = wave

################
wave_SOURCES = wave.c wave_mkaddr.c wave_types.c

################
wave_CPPFLAGS = -g3 -DCONFIG_DIR=\“$(sysconfdir)\” -DLIBRARY_DIR=\”$(pkglibdir)\”

################
CURRENTPATH=$(shell /usr/bin/pwd)

INCLUDES=-I$(CURRENTPATH) -I$(CURRENTPATH)/src

###############

#wave_LDFLAGS=

################
#noinst_HEADERS=wave.h 
#include_HEADERS=wave.h wave_utils/wave_list.h

################
