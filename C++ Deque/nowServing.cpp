/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Tanner Larson
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * STRUCT: STUDENT
 * This struct is to help keep track of all the 
 * separate variables used in a reservation
 ***********************************************/
struct Student
{
   public:
   string cName;
   string sName;
   int time;
   bool emergency;

   Student() // default constructor
   {
      time = 0;
      emergency = false;
   }
};

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";
   int clock = 0;
   string input;
   Deque <Student> deque;
   Student serving;

   do
   {
      cout << '<' << clock << "> ";
      cin >> input;

      if (input.at(0) == '!') // emergency reservation
      {
         Student student;
         cin >> student.cName;
         cin >> student.sName;
         cin >> student.time;
         student.emergency = true;
         deque.push_front(student);
      }
      else if (input == "none") // nothing happened
      {}
      else if (input == "finished") // end simulation
         break;
      else // normal reservation
      {
         Student student;
         student.cName = input;
         cin >> student.sName;
         cin >> student.time;
         deque.push_back(student);
      }
      if (!deque.empty() && serving.time == 0) // student is done being served
      {
         serving = deque.front();
         deque.pop_front();
      }

      if ((deque.empty() && serving.cName.size() == 0) || serving.time == 0) // no one to serve
         {}
      else // display currently serving
      {
         if (serving.emergency) // student has an emergency
         {
            cout << "\tEmergency for " << serving.sName << " for class " << serving.cName << ". Time left: " << serving.time << endl;
            serving.time--;
         }
         else // student doesn't have an emergency
         {
            cout << "\tCurrently serving " << serving.sName << " for class " << serving.cName << ". Time left: " << serving.time << endl;
            serving.time--;
         }
      }

      clock++;
   }
   while (1);

   // end
   cout << "End of simulation\n";
   return;
}



