###############################################################
# Program:
#     Week 10, Word Count
#     Brother Ercanbrack, CS235
# Author:
#     Tanner Larson
# Summary:
#     
# Time:
#     
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week10.o
	g++ -o a.out week09.o 
	tar -cf week10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week10.cpp

