###############################################################
# Program:
#     Week 01, Vector
#     Brother Jones, CS235
# Author:
#     Adam Shumway
# Summary:
#     Week 01, Vector Makefile
# Time:
#     <how long did it take to complete this program?>
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
        POSITIONTEST = positionText.out
        MOVETEST = moveTest.out
        TAR = tar -cf week01.tar *.h *.cpp makefile
        #FixPath = $1
    endif
    ifeq ($(shell uname),Darwin)
        #Mac stuff
        RM = rm -f
        PROGRAM = a.out
        P_EXT = .out
        POSITIONTEST = positionText.out
        MOVETEST = moveTest.out
        TAR = tar -cf chess.tar *.h *.cpp makefile
    endif
endif

##############################################################
# The main rule
##############################################################
$(PROGRAM): week01.o
	g++ -o $(PROGRAM) week01.o
	$(TAR)

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp

###############################################################
# General rules
###############################################################
clean :
	$(RM) *$(P_EXT) *.o *.out *.tar *~
