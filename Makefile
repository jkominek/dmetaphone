# $PostgreSQL: pgsql/contrib/dict_dmetaphone/Makefile,v 1.2 2007/12/02 21:15:38 tgl Exp $

MODULE_big = dict_dmetaphone
OBJS = dict_dmetaphone.o dmetaphone.o
DATA_built = dict_dmetaphone.sql
DATA = uninstall_dict_dmetaphone.sql
REGRESS = dict_dmetaphone

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/dict_dmetaphone
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
