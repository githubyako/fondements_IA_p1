## ~(*_*)~
CXX			=	g++
CFLAGS		=	-Wall
OFLAGS		=	-O2
DEBUG		=	-g
STD			= 	-std=c++11
RM			=	rm

## files
SRC			=	main.cpp \
				diagnostic.cpp \
				solver.cpp \
				rule.cpp \
				literal.cpp \
				boolean.cpp \
				true.cpp \
				false.cpp
OBJ			=	main.o \
				diagnostic.o \
				solver.o \
				rule.o \
				literal.o \
				boolean.o \
				true.o \
				false.o
TGT			=	projet


## building rules
all:	$(TGT)	
	@echo "[Building complete]"

## linking
$(TGT):	$(OBJ)
	$(CXX) -o $(TGT) $(OBJ)

## compiling
%.o:	%.cpp
	$(CXX) -c $(CFLAGS) $(OFLAGS) $(DEBUG) $(STD) -o $@ $<

## cleaning
clean:	$(OBJ)
	$(RM) $(OBJ)
