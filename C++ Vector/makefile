###############################################################
# Program:
#     Week 01, Vector
#     Brother Ercanbrack, CS235
# Author:
#     Tanner Larson
# Summary:
#     This is a vector class.  It does all the things that a 
#		vector class should do, including the push_back, clear,
#		begin, end, capacity, size, and empty functions, as well
#		as the = and [] operator overloads specific to vectors.
# Time:
#     7 - 8 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
