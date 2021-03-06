#############################################################################
# Makefile for building: libtranslate-asl.a
# Generated by qmake (1.07a) (Qt 3.3.4) on: Mon Jul 11 22:31:20 2005
# Project:  translate-asl.pro
# Template: lib
# Command: $(QMAKE) -o Makefile translate-asl.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -g  -DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -g  -DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt3/mkspecs/default -I. -I. -I$(QTDIR)/include
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = ./

####### Files

HEADERS = ActionScriptLexer.hpp \
		ActionScriptParser.hpp \
		ActionScriptParserTokenTypes.hpp \
		ActionScriptTokenTypes.hpp \
		ASNode.h \
		ASParser.h \
		ASTranslate.h \
		DLLInterface.h \
		Preprocessor.hpp \
		PreprocessorTokenTypes.hpp \
		translate.h
SOURCES = ActionScriptLexer.cpp \
		ActionScriptParser.cpp \
		ASNode.cpp \
		ASParser.cpp \
		ASTranslate.cpp \
		Preprocessor.cpp
OBJECTS = ActionScriptLexer.o \
		ActionScriptParser.o \
		ASNode.o \
		ASParser.o \
		ASTranslate.o \
		Preprocessor.o
FORMS = 
UICDECLS = 
UICIMPLS = 
SRCMOC   = 
OBJMOC = 
DIST	   = translate-asl.pro
QMAKE_TARGET = translate-asl
DESTDIR  = 
TARGET   = libtranslate-asl.a

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET) 

staticlib: $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGET)
	$(AR) $(TARGET) $(OBJECTS) $(OBJMOC)


mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: translate-asl.pro  /usr/lib/qt3/mkspecs/default/qmake.conf /usr/lib/qt3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile translate-asl.pro
qmake: 
	@$(QMAKE) -o Makefile translate-asl.pro

dist: 
	@mkdir -p .tmp/translate-asl && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .tmp/translate-asl/ && ( cd `dirname .tmp/translate-asl` && $(TAR) translate-asl.tar translate-asl && $(GZIP) translate-asl.tar ) && $(MOVE) `dirname .tmp/translate-asl`/translate-asl.tar.gz . && $(DEL_FILE) -r .tmp/translate-asl

mocclean:

uiclean:

yaccclean:
lexclean:
clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

ActionScriptLexer.o: ActionScriptLexer.cpp ActionScriptLexer.hpp \
		ActionScriptParser.hpp \
		ActionScriptTokenTypes.hpp \
		ASParser.h \
		ASNode.h \
		translate.h \
		ASTranslate.h \
		DLLInterface.h

ActionScriptParser.o: ActionScriptParser.cpp ActionScriptParser.hpp \
		ActionScriptTokenTypes.hpp \
		ASParser.h \
		ASNode.h \
		translate.h \
		ASTranslate.h \
		DLLInterface.h

ASNode.o: ASNode.cpp ASNode.h \
		translate.h \
		ASTranslate.h \
		ASParser.h \
		DLLInterface.h

ASParser.o: ASParser.cpp ASParser.h \
		ASNode.h \
		Preprocessor.hpp \
		ActionScriptLexer.hpp \
		ActionScriptParser.hpp \
		translate.h \
		ASTranslate.h \
		DLLInterface.h \
		PreprocessorTokenTypes.hpp \
		ActionScriptTokenTypes.hpp

ASTranslate.o: ASTranslate.cpp translate.h \
		ASTranslate.h \
		ASParser.h \
		ASNode.h \
		DLLInterface.h

Preprocessor.o: Preprocessor.cpp Preprocessor.hpp \
		PreprocessorTokenTypes.hpp

####### Install

install:  

uninstall:  

