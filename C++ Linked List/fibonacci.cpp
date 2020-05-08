/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


struct WholeNumber
{
   List <int> number;


   // copy constructor
   WholeNumber(const WholeNumber & rhs) 
   { 
      number = rhs.number; 
   }

   // non-default constructor
   WholeNumber(unsigned int n)
   {
      int numTemp = 0;

      while (n != 0) // first three digits
      {
         numTemp = n % 1000;
         n /= 1000;
         number.push_front(numTemp);
      }

      // put something in there if there is nothing to put
      if (number.empty())
         number.push_front(0);
   }

   WholeNumber operator += (WholeNumber rhs)
   {
      WholeNumber n(*this);
      n = n + rhs;
      number = n.number;
   }

   WholeNumber operator = (WholeNumber rhs) { number = rhs.number; }

   friend WholeNumber operator + (WholeNumber lhs, WholeNumber rhs);

};

ostream & operator << (std::ostream & out, WholeNumber & n);


/************************************************
 * + operator overload
 * adds two WholeNumbers
 ***********************************************/
WholeNumber operator + (WholeNumber lhs, WholeNumber rhs)
{
   bool carry = false;
   int newNum;
   WholeNumber numTemp(0);

   if (rhs.number.empty() || lhs.number.empty())
   {
      if (rhs.number.empty() && !lhs.number.empty())
         return lhs;
      else if (lhs.number.empty() && !rhs.number.empty())
         return rhs;
      else
         return numTemp;
   }

   numTemp.number.clear();

   if (lhs.number.size() >= rhs.number.size())
   {
      ListIterator <int> itB = rhs.number.rbegin();
      // loop through this list
      for (ListIterator <int> itA = lhs.number.rbegin(); itA != lhs.number.rend(); --itA)
      {
         // take care of carry
         if (carry == true)
         {
            newNum = 1;
         }
         else
            newNum = 0;

         newNum += *itA + *itB;

         // check for carry
         if (newNum >= 1000)
         {
            newNum -= 1000;
            carry = true;
         }
         else
            carry = false;

         numTemp.number.push_front(newNum);

         if (itB != rhs.number.begin())
            itB--;
         else
         {
            rhs.number.clear();
            *itB = 0;
         }
      }
   }
   else
   {
      ListIterator <int> itA = lhs.number.rbegin();
      // loop through this list
      for (ListIterator <int> itB = rhs.number.rbegin(); itB != rhs.number.rend(); --itB)
      {
         // take care of carry
         if (carry == true)
         {
            newNum = 1;
         }
         else
            newNum = 0;

         newNum += *itA + *itB;

         // check for carry
         if (newNum >= 1000)
         {
            newNum -= 1000;
            carry = true;
         }
         else
            carry = false;

         numTemp.number.push_front(newNum);

         if (itA != lhs.number.begin())
            itA--;
         else
            *itA = 0;
      }
   }

   // account for possible extra node if there is a carry
   if (carry)
      numTemp.number.push_front(1);

   return numTemp;
}

/************************************************
 * << operator overload
 * Displays a WholeNumber
 ***********************************************/
ostream & operator << (std::ostream & out, WholeNumber & n)
{
   for (ListIterator <int> it = n.number.begin(); it != n.number.end(); it++)
   {
      if (it != n.number.begin())
      {
         cout << ',';
         if (*it == 0)
            out << "000";
         else if (*it < 100 && *it > 9)
            out << '0' << *it;
         else if (*it < 9 && *it > 0)
            cout << "00" << *it;
         else
            out << *it;
      }
      else
         out << *it;
   }
   return out;
}


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   WholeNumber t1(0);
   WholeNumber t2(0);
   WholeNumber t3(1);

   WholeNumber * term1 = &t1;
   WholeNumber * term2 = &t2;
   WholeNumber * term3 = &t3;

   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   for (int i = (number + 3) / 3; i > 0; --i)
   {
      cout << "\t" << *term3 << endl;
      if (i == 1)
         break;
      *term1 = *term2 + *term3;

      cout << "\t" << *term1 << endl;
      if (i == 1)
         break;
      *term2 = *term1 + *term3;

      cout << "\t" << *term2 << endl;
      if (i == 1)
         break;
      *term3 = *term1 + *term2;
   }
   // reset terms and term3   
   t1 = 0;
   t2 = 0;
   t3 = 1;

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   for (int i = number; i > 0; )
   {
      if (i == 1)
      {
         cout << "\t" << *term3 << endl;
         break;
      }
      *term1 = *term3 + *term2;
      --i;

      if (i == 1)
      {
         cout << "\t" << *term1 << endl;
         break;
      }
      *term2 = *term1 + *term3;
      --i;

      if (i == 1)
      {
         cout << "\t" << *term2 << endl;
         break;
      }
      *term3 = *term2 + *term1;
      --i;
   }
}


