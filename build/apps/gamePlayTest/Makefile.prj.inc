#-----------------------------------------------------------------------------
# GNU Makefile for static libraries: project dependent part
#
#-----------------------------------------------------------------------------

NAME = gamePlayTest
DBG_NAME = $(NAME)
REL_NAME = $(NAME)

ROOT = ../../..
VPATH = $(ROOT)

DBG_OBJDIR = $(ROOT)/objs/$(NAME)/debug
REL_OBJDIR = $(ROOT)/objs/$(NAME)/release
DBG_BINDIR = $(ROOT)/bin/debug
REL_BINDIR = $(ROOT)/bin/release

PROJ_CXXFLAGS = -I$(ROOT)/utils  -I$(ROOT)/environments 

PROJ_DBG_CXXFLAGS = $(PROJ_CXXFLAGS)
PROJ_REL_CXXFLAGS = $(PROJ_CXXFLAGS)

PROJ_DBG_LNFLAGS = -L$(DBG_BINDIR)
PROJ_REL_LNFLAGS = -L$(REL_BINDIR)

PROJ_DBG_LIB =  -lutils -lenvironments 
PROJ_REL_LIB =  -lutils -lenvironments

PROJ_DBG_DEP = \
  $(DBG_BINDIR)/libutils.a \
  $(DBG_BINDIR)/libenvironments.a \


PROJ_REL_DEP = \
  $(REL_BINDIR)/libutils.a \
  $(REL_BINDIR)/libenvironments.a \



default : all

SRC_CPP = \
	apps/gamePlayTest/Driver.cpp \


