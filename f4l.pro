# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: .
# Target is a subdirs project 

SUBDIRS += src/flagStonePort/transform-cxx-bsd/transform \
           src/flagStonePort/transform-util-cxx/transform-util \
           src 
CONFIG += release \
warn_on \
qt \
thread
TEMPLATE = subdirs
QT += widgets
LIBS= -lpthread -lrt -lz
