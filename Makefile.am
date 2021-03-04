AUTOMAKE_OPTIONS = foreign
SUBDIRS=

################
bin_PROGRAMS = wave

################
wave_SOURCES = main.c wave.c 

################
wave_CPPFLAGS = -DCONFIG_DIR=\“$(sysconfdir)\” -DLIBRARY_DIR=\”$(pkglibdir)\”

################
CURRENTPATH=$(shell /usr/bin/pwd)
INCLUDES=-I$(CURRENTPATH) -I$(CURRENTPATH)/wave_utils

################
noinst_HEADERS=wave.h wave_utils/wave_list.h
#include_HEADERS=wave.h wave_utils/wave_list.h


