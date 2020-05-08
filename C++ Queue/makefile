###############################################################
# Program:
#     Week 03, QUEUE
#     Brother Ercanbrack, CS235
# Author:
#     Tanner Larson
# Summary:
#     This project contains the queue data structure, as well
#		as an implementation of the queue in the form of a 
#		program that keeps track of stock transactions.  It also
#		includes the Dollars and Share class to help simplify
#		the stock transactions program.
# Time:
#     7 Hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week03.o dollars.o stock.o share.o
	g++ -o a.out week03.o dollars.o stock.o share.o
	tar -cf week03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
#		 share.o 		 : the Share class
##############################################################
week03.o: queue.h week03.cpp
	g++ -c week03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp

share.o: share.h share.cpp
	g++ -c share.cpp