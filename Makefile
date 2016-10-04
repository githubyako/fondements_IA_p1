## ~(*_*)~
CXX			=	g++
CFLAGS		=	-Wall
OFLAGS		=	-O2
DEBUG		=	-g
STD			= 	-std=c++11
RM			=	rm

## files
SRC			=	src/main.cpp \
				src/diagnostic.cpp \
				src/solver.cpp \
				src/rule.cpp \
				src/literal.cpp \
				src/boolean.cpp \
				src/true.cpp \
				src/false.cpp
OBJ			=	obj/main.o \
				obj/diagnostic.o \
				obj/solver.o \
				obj/rule.o \
				obj/literal.o \
				obj/boolean.o \
				obj/true.o \
				obj/false.o
TGT			=	build/projet


## building rules
all:	$(TGT)	
	@echo "[Building complete]"

## linking
$(TGT):	$(OBJ)
	$(CXX) -o $(TGT) $(OBJ)

## compiling
obj/%.o:	src/%.cpp
	$(CXX) -c $(CFLAGS) $(OFLAGS) $(DEBUG) $(STD) -o $@ $<

## cleaning
clean:	$(OBJ)
	$(RM) $(OBJ)
