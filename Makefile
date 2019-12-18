#-----------------------------------------------------------------------------
# Choose a compiler and its options. Recommend using:
# g++ for compiling on Linux
# clang++ for compiling on MacOS
# Visual C++ for compiling on Windows
#-----------------------------------------------------------------------------
CXX = g++
OPTS = -O0
DEBUG = -g -std=c++14

#--------------------------------------------------------------------------
# Add the names of the directories (Add them after each ./)
#--------------------------------------------------------------------------
SRCDIR=./src
OBJDIR=./obj
INCDIR=./inc
BINDIR=./bin

#------------------------------------------------------------------------------------
# If you wish to list the source files on different lines, 
# Don't forget to add the '\' character at the end of each line to continue the line. 
# You don't need it after the last source file.
#
# Example:
# SRCS=$(SRCDIR)/file1.cpp $(SRCDIR)/file2.cpp \
# $(SRCDIR)/file3.cpp $(SRCDIR)/file4.cpp
#
# Note: The source directory, $(SRCDIR), needs to be given for each individual file. 
# Note that there should only be one SRCS= (i.e. don't add more of them as you add files).
#-------------------------------------------------------------------------------------
SRCS=$(SRCDIR)/main.cpp $(SRCDIR)/predict.cpp

#--------------------------------------------------------------------
# Define flags used in the compilation of the source code
#--------------------------------------------------------------------
INCLUDE_python3 = -I/Library/Frameworks/Python.framework/Versions/3.7/include/python3.7m -I/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include
LIB_DIR_python3 = -L/Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin
LIB_python3 = -lpython3.7m

INCLUDE_python2 = -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include
LIB_DIR_python2 = -L/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config
LIB_python2 = -lpython2.7

INCLUDE = $(addprefix -I,$(INCDIR)) $(INCLUDE_python3) 
LINK = $(LIB_DIR_python3) $(LIB_python3)
OBJS=${SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o}

CXX_FLAGS = $(OPTS) $(INCLUDE) $(DEBUG) $(LINK)

#--------------------------------------------------------------------
# Add the name of the executable after the $(BINDIR)/
#--------------------------------------------------------------------
TARGET = $(BINDIR)/main 

all: $(TARGET)

$(TARGET): $(OBJS)
	${CXX} ${CXX_FLAGS} -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

#--------------------------------------------------------------------
# This clean target will remove all the object files, but not the executable
#--------------------------------------------------------------------
clean:
	rm -f $(OBJS)

#---------------------------------------------------------------------
# cleanall that will remove the object files as well as the executable
#---------------------------------------------------------------------
cleanall:
	rm -f $(OBJS) $(BINDIR)/*
