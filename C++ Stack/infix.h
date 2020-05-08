/***********************************************************************
* Header:
*    INFIX      
* Summary:
*    This will contain just the prototype for the convertInfixToPostfix()
*    function
* Author
*    Tanner Larson
************************************************************************/

#ifndef INFIX_H
#define INFIX_H

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix();

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly();

/*****************************************************
 * hasPriority
 * returns true if left operator has priority over
 * right operator
 *****************************************************/
bool hasPriority(char a, char b);

/*****************************************************
 * isOperator
 * returns true of char is a usable operator
 *****************************************************/
bool isOperator(char a);

#endif // INFIX_H

