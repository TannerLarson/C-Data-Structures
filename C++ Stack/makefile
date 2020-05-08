###############################################################
# Program:
#     Week 02, STACK
#     Brother Ercanbrack, CS235
# Author:
#     Tanner Larson
# Summary:
#     This program includes both the entirety of the stack class
#		as found in the standard template library and also a method
#		to convert an infix mathematical equation into a postfix 
#		function.  For example, it would turn 3*(2-1) into 
#		2 1 - 3 *
# Time:
#     7 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

