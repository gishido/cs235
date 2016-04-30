###############################################################
# Program:
#     Week 02, STACK
#     Brother XXXX, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################
###############################################################
# Makefile variables for windows, mac, or linux
###############################################################
ifeq ($(OS),Windows_NT)
    #Windows stuff
    RM = del /f
    PROGRAM = a.exe
    P_EXT = .exe
    #FixPath = $(subst /,\,$1)
else
    ifeq ($(shell uname), Linux)
        #Linux stuff
        RM = rm -f
        PROGRAM = a.out
        P_EXT = .out
        TAR = tar -cf week02.tar *.h *.cpp makefile
    endif
    ifeq ($(shell uname),Darwin)
        #Mac stuff
        RM = rm -f
        PROGRAM = a.out
        P_EXT = .out
        TAR = tar -cf week02.tar *.h *.cpp makefile
    endif
endif

##############################################################
# The main rule
##############################################################
$(PROGRAM): week02.o infix.o
	g++ -o a.out week02.o infix.o 
	$(TAR)

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

###############################################################
# General rules
###############################################################
clean :
	$(RM) *$(P_EXT) *.o *.tar *~
