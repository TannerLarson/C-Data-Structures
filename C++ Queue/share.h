/***********************************************************************
* Header:
*    Week03, Share
* Summary:
*    This class contains only three variables needed for the stock
*    transactions program: amount, dollars, and profit.  The rest of the
*    functions included are only there to help access those three
*    variables.
*
*    This will contain the class definition of:
*        Share         : A class that holds amount, dollars, and profit
*                          of a share
* Author
*    Tanner Larson
************************************************************************/
#ifndef SHARE_H
#define SHARE_H
#include <iostream>
#include "dollars.h"

/************************************************
 * Share
 * A class that holds amount, dollars, and profit
 *   of a share
 ***********************************************/
class Share
{
   public:
      int amount;
      Dollars dollars;
      Dollars profit;

/**********************************************
 * Share : DEFAULT CONSTRUCTOR
 **********************************************/
   Share()
   {
      amount = 0;
      dollars = Dollars();
      profit = Dollars();
   }

/***************************************************
 * Share :: operator =
 * Set the data in the share on the left side equal
 * to the data in the share on the right side.
 **************************************************/
   Share & operator = (Share rhs)
   {
      amount = rhs.amount;
      dollars = rhs.dollars;
      profit = rhs.profit;
   }

/***************************************************
 * Share :: operator ==
 * Returns if share on right side is exactly equivalent
 * to share on left side.
 **************************************************/
   bool operator == (Share rhs)
   {
      if (amount == rhs.amount && dollars == rhs.dollars && profit == rhs.profit)
         return true;
      else
         return false;
   }
};


#endif