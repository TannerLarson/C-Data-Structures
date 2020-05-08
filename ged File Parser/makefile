###############################################################
# Program:
#     Week 13, Genealogy
#     Brother Ercanbrack, CS235
# Author:
#     Tanner Larson
# Summary:
#     This program reads in a GED file, parses it into usable data, and
#    displays the genealogical tree for the individual mentioned in the
#    GED file.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
	g++ -o a.out week13.o -g
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: week13.cpp list.h bnode.h node.h
	g++ -c week13.cpp -g


