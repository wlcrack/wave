AUTOMAKE_OPTIONS = foreign
SUBDIRS=
bin_PROGRAMS = wave
wave_SOURCES = main.c wave.c wave.h wave_list.h 
wave_CPPFLAGS = -DCONFIG_DIR=\“$(sysconfdir)\” -DLIBRARY_DIR=\”$(pkglibdir)\”
CURRENTPATH=$(shell /usr/bin/pwd)
INCLUDES=-I$(CURRENTPATH)
noinst_HEADERS=wave.h wave_list.h


