/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    Tanner Larson
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "share.h"
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{

   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   string input;
   Dollars value;
   int numShares = 0;
   Queue <Share> stocksHeld; 
   Queue <Share> stocksSold;
   Share share;

   do
   {
      cout << "> ";
      cin >> input;
      if (input == "quit")
         break;
      if (cin.fail())
      {
         cout << "\nIncorrect input, aborted\n";
         break;
      }

      switch (input.at(0))
      {
         case 'b': // buy
            cin >> share.amount;
            cin >> share.dollars;
            stocksHeld.push(share);
            break;
         case 's': // sell
         {
            cin >> share.amount;
            cin >> share.dollars;
            share.profit = 0;

            int i = share.amount;
            while (1) // calculate profit and subtract from stocksHeld
            {
               if (i > stocksHeld.front().amount) // over entire batch sold
               {
                  share.amount = stocksHeld.front().amount;
                  share.profit = share.profit + share.dollars * stocksHeld.front().amount - stocksHeld.front().dollars * stocksHeld.front().amount;
                  stocksSold.push(share);
                  i -= stocksHeld.front().amount;
                  stocksHeld.pop();
               }
               else if (i != stocksHeld.front().amount) // entire batch not sold
               {
                  share.amount = i;
                  share.profit = share.profit + share.dollars * i - stocksHeld.front().dollars * i;
                  stocksHeld.front().amount -= i;
                  stocksSold.push(share);
                  break;
               }
               else // exactly entire batch sold
               {
                  share.amount = i;
                  share.profit = share.profit + share.dollars * i -  stocksHeld.front().dollars * stocksHeld.front().amount;
                  stocksSold.push(share);
                  stocksHeld.pop();
                  break;
               }
               share.profit = 0;
            }
            break;
         }
         case 'd': // display
         {
            Queue <Share> stocksTemp;

            if (!stocksHeld.empty()) // Currently Held
            {
               stocksTemp = stocksHeld;
               cout << "Currently held:\n";
               do
               {
                  cout << "\tBought " << stocksTemp.front().amount \
                     << " shares at " << stocksTemp.front().dollars << endl;
                  stocksTemp.pop();
               }
               while (!stocksTemp.empty());
            }

            if (!stocksSold.empty()) // Sell History
            {
               stocksTemp = stocksSold;
               cout << "Sell History:\n";
               do
               {
                  cout << "\tSold " << stocksTemp.front().amount << " shares at " 
                     << stocksTemp.front().dollars << " for a profit of " 
                     << stocksTemp.front().profit << endl;
                     stocksTemp.pop();
               }
               while (!stocksTemp.empty());
            }
            Dollars proceeds;
            stocksTemp = stocksSold;
            cout << "Proceeds: ";
            if (!stocksSold.empty())
            {
               do
               {
                  proceeds += stocksTemp.front().profit;
                  stocksTemp.pop();
               }
               while (!stocksTemp.empty());
            }
            cout << proceeds;
            cout << endl;
         break;
         }
         default:
            cout << "\nError\n";
      }
   }
   while (input != "quit");
}


