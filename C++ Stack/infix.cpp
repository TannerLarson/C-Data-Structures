/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Tanner Larson
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <cctype>      // for isdigit
#include "stack.h"     // for STACK
#include "infix.h"     // for INFIX
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;
   postfix += " ";

   Stack <char> operators;

   for (int i = 0; i < infix.size(); ++i)
   {
      // check for anything that isn't an operator
      if (isdigit(infix.at(i)) || isalpha(infix.at(i)) || infix.at(i) == '.')
      {
         // this loop accounts for multi-digit numbers,
         //  multi-letter words, and decimal places
         do
         {
            postfix.push_back(infix.at(i));
            if (i >= infix.size() - 1)
            {
               break;
            }
            // accounts for infix equations without spaces such as 3-2
            if (!isOperator(infix.at(i + 1)))
               i++;
            else
               break;
         }
         while (isdigit(infix.at(i)) || isalpha(infix.at(i)) || infix.at(i) == '.');
         // put spaces in between postfix characters
         postfix.push_back(' ');
      }
      else
      {
         switch (infix.at(i)) // figure out which operator I'm dealing with
         {
            case '(':
               operators.push(infix.at(i));
               break;
            case ')': // push operators onto postfix until ( is reached
               while (operators.top() != '(')
               {
                  postfix.push_back(operators.top());
                  postfix.push_back(' ');
                  if (operators.empty())
                     throw "Error: No left parenthesis found";
                  operators.pop();
               }
               operators.pop(); // get rid of (
               break;
            case '^':
            case '*':
            case '/':
            case '%':
            case '+':
            case '-':
               if (operators.empty() || hasPriority(infix.at(i), operators.top()))
               {
                  operators.push(infix.at(i));
               }
               else // token operator doesn't have priority over operator at top of stack
               {
                  do
                  { // push top of operators stack onto postfix until token operator has priority
                     postfix.push_back(operators.top());
                     postfix.push_back(' ');
                     operators.pop();
                     if (operators.empty()) // make sure we don't mess with stack when there's nothing in it
                        break;   
                  }
                  while (!hasPriority(infix.at(i),operators.top()));
                  operators.push(infix.at(i));
               }
            break;
         }
      }
   }
   for (int i = 0; !operators.empty(); ++i) // push and pop the rest of my operators stack
   {
      postfix.push_back(operators.top());
      if (i <= operators.size() - 2)
         postfix.push_back(' ');
      operators.pop();
   }
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}

/*****************************************************
 * HasPritority
 * Checks if left operator has priority over right 
 * operator
 *****************************************************/
bool hasPriority (char a, char b)
{
   switch(a)
   {
      case '^':
         if (b == '^')
            return false;
         else
            return true;
      case '*':
      case '/':
      case '%':
         if (b == '^' || b == '*' || b == '/' || b == '%')
               return false;
            else
               return true;
      case '-':
      case '+':
         if (b == '(')
            return true;
         else
            return false;
      case '(':
         return false;
   }
}

/*****************************************************
 * IsOperator
 * Checks if char is a usable operator
 *****************************************************/
bool isOperator (char a)
{
   switch (a)
   {
      case '(':
      case ')':
      case '^':
      case '*':
      case '/':
      case '%':
      case '+':
      case '-':
      return true;
   }
   return false;
}