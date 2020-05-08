/***********************************************************************
* Program:
*    Week 13, Genealogy
*    Brother Ercanbrack, CS 235
* Author:
*    Tanner Larson
* Summary: 
*    This program reads in a GED file, parses it into usable data, and
*    displays the genealogical tree for the individual mentioned in the
*    GED file.
************************************************************************/

#include <iostream>      // for CIN and COUT
#include <string>        // for STRING
#include <fstream>
#include <cctype>
#include <sstream>
#include "list.h" 
#include "bnode.h" 
#include "node.h" 
using namespace std;


/*******************************************************
* compareMonth
* return 0 if a < b
* return 1 if a == b
* return 2 if a > b
* a and b need to be in all caps
*******************************************************/
int compareMonth(string a, string b)
{
   if (a == b)
      return 1;
   if (a == "JAN")
      return 2;
   if (a == "FEB")
   {
      if (b == "JAN")
         return 0;
      else
         return 2;
   }
   if (a == "MAR")
   {
      if (b == "JAN" || b == "FEB")
         return 0;
      else
         return 2;
   }
   if (a == "APR")
   {
      if (b == "JAN" || b == "FEB" || b == "MAR")
         return 0;
      else
         return 2;
   }
   if (a == "MAY")
   {
      if (b == "JAN" || b == "FEB" || b == "MAR" || b == "APR")
         return 0;
      else
         return 2;
   }
   if (a == "JUN")
   {
      if (b == "JAN" || b == "FEB" || b == "MAR" || b == "APR" || b == "MAY")
         return 0;
      else
         return 2;
   }
   if (b == "JUL")
   {
      if (a == "DEC" || a == "NOV" || a == "SEP" || a == "AUG")
         return 2;
      else
         return 0;
   }
   if (b == "AUG")
   {
      if (a == "DEC" || a == "NOV" || a == "SEP")
         return 2;
      else
         return 0;
   }
   if (b == "SEP")
   {
      if (a == "DEC" || a == "NOV")
         return 2;
      else
         return 0;
   }
   if (b == "NOV")
   {
      if (a == "DEC")
         return 2;
      else
         return 0;
   }
   if (b == "DEC")
   {
      return 0;
   }
}


/************************************************
 * Date
 * A struct that holds the information for a date
 ***********************************************/
struct Date
{
public:

   Date() : day(0), year(0), yearFrom(0) {}

   Date operator = (Date rhs)
   {
      day = rhs.day;
      if (!rhs.month.empty())
         month = rhs.month;
      else
         month.clear();
      year = rhs.year;
      yearFrom = rhs.yearFrom;

      return *this;
   }

   bool operator >= (Date rhs)
   {
      if (year >= rhs.year)
      {
         if (year == rhs.year)
         {
            if (compareMonth(month, rhs.month) > 1)
            {
               if (month == rhs.month)
               {
                  if (day >= rhs.day)
                     return true;
                  else
                     return false;
               }
               else
                  return true;
            }
            else
               return false;
         }
         else
            return true;
      }
      else
         return false;
   }

   int day;
   string month;
   int year;
   int yearFrom;
};


/*****************************************************************
 * operator <<
 * Displays a date
 *****************************************************************/
ostream & operator << (ostream & out, Date rhs)
{
   if (rhs.year > 0)
   {
      if (rhs.yearFrom > 0)
      {
         cout << rhs.yearFrom << '/' << rhs.year;
      }
      else if (rhs.month[0] != NULL)
      {
         if (rhs.day > 0)
            cout << rhs.day << ' ' << rhs.month << ' ' << rhs.year;
         else if (!rhs.month.empty())
            cout << rhs.month << ' ' << rhs.year;
      }
      else
         cout << rhs.year;
   }

   return out;
}


/************************************************
 * Person
 * A struct that holds information for a person
 ***********************************************/
struct Person
{
public:

   Person() : id(0), dad(NULL), mom(NULL) {}

   Person operator = (Person rhs)
   {
      id = 0;
      fName.clear();
      lName.clear();
      dad = NULL;
      mom = NULL;
      birthday.year = 0;
      birthday.month.clear();
      birthday.day = 0;

      if (!rhs.fName.empty())
         fName = rhs.fName;
      else
         fName.clear();

      if (!rhs.lName.empty())
         lName = rhs.lName;
      else
         lName.clear();

      if (rhs.birthday.year != 0)
      {
         birthday = rhs.birthday;
      }
      if (rhs.id != 0)
         id = rhs.id;
      mom = rhs.mom;
      dad = rhs.dad;

      return *this;
   }

   string fName;
   string lName;
   Date birthday;
   Person * mom;
   Person * dad;
   int id;
};


/*****************************************************************
 * operator <<
 * Displays a person
 *****************************************************************/
ostream & operator << (ostream & out, Person rhs)
{
   out << rhs.fName;
   if (!rhs.lName.empty() && !rhs.fName.empty())
      out << ' ' << rhs.lName;
   else if (!rhs.lName.empty())
      out << rhs.lName;
   if (rhs.birthday.year > 0)
      out << ", b. " << rhs.birthday;

   return out;
}


/***************************************************
 * insertInOrder
 * inserts person into list in order; first by 
 * last name, then first name, then birthday.
 **************************************************/
void insertInOrder(Person person, List <Person> & tree)
{
   // take care of lower case first letter of last name
   Person temp1 = person;
   Person temp2;
   if (tree.empty())
   {
      tree.push_back(person);
      return;
   }
   // set person.lName to lowers for comparison
   for (int i = 0; i < temp1.lName.size(); ++i)
      temp1.lName[i] = toupper(temp1.lName[i]);
   // set person.fName to lowers for comparison
   for (int i = 0; i < temp1.fName.size(); ++i)
      temp1.fName[i] = toupper(temp1.fName[i]);

   for (ListIterator <Person> it = tree.begin(); ; ++it)
   {
      if (it == tree.end())
      {
         tree.push_back(person);
         break;
      }
      temp2 = *it;
      // set (*it).lName to lowers for comparison
      for (int i = 0; i < temp2.lName.size(); ++i)
         temp2.lName[i] = toupper(temp2.lName[i]);
      // set (*it).fName to lowers for comparison
      for (int i = 0; i < temp2.fName.size(); ++i)
         temp2.fName[i] = toupper(temp2.fName[i]);
      // Sort by Last Name
      if (temp1.lName >= temp2.lName)
      {
         if (temp1.lName == temp2.lName)
         {
            // Sort by First Name
            if (temp1.fName >= temp2.fName)
            {
               if (temp1.fName == temp2.fName)
               {
                  // Sort by birthday
                  if (temp1.birthday >= temp2.birthday)
                  {
                     tree.insert(++it, person);
                     break;
                  }
                  else
                  {
                     tree.insert(it, person);
                     break;
                  }
               }
            }
            else
            {
               tree.insert(it, person);
               break;
            }
         }
      }
      else
      {
         tree.insert(it, person);
         break;
      }
   }
}


/********************************************************************
 * readFile
 * Reads file from GED file line by line, puts data into a Person, 
 * and inserts Person into a list
 *******************************************************************/
void readFile(List <Person> & tree)
{
   string line;
   int num = 0;
   string type;
   string info;
   Person person;
   Person * momTemp = NULL;
   Person * dadTemp = NULL;
   bool isBirth = false;
   bool isFirst = true;
   bool isMom = false;
   bool isDad = false;
   int dadID = 0;
   int momID = 0;
   int childID = 0;

   // put dictionary into a hash
   ifstream fin;
   fin.open("/home/cs235e/week13/cameron.ged");
   if (fin.fail()) // check for fin.fail()
   {
      cout << "File does not exist\n";
      return;
   }
   // read in input word by word
   while (getline(fin, line))
   {
      // input number
      num = (int)line[0];
      switch (num)
      {
         case 48:
            num = 0;
            break;
         case 49:
            num = 1;
            break;
         case 50:
            num = 2;
            break;
      }

      // input type
      int i = 2;
      while (i < 6)
      {
         type += line[i];
         ++i;
      }
      if (line[6] == '@' || isdigit(line[6]))
      {
         type += line[6];
         if (isdigit(line[6]))
            type += line[7];
      }
      // input information
      if (i < line.size())
      {
         i++;
         while (i < line.size())
         {
            info += line[i];
            ++i;
         }
      }



      // set person if certain conditions are met
      switch (num)
      {
         case 0:
            if (type[0] == '@' && type[1] == 'I')
            {
               // insert last person into list
               if (!isFirst)
                  insertInOrder(person, tree);
               // clear person for new person
               person.fName.clear();
               person.lName.clear();
               person.birthday.day = person.birthday.year = 0;
               person.birthday.month.clear();
               isMom = isDad = isFirst = false;
               momID = dadID = childID = person.id = person.birthday.yearFrom = 0;
               // set new person's ID
               switch (type.size())   
               {
                  case 6:
                     person.id = (type[2] - 48) * 100;
                     person.id += (type[3] - 48) * 10;
                     person.id += type[4] - 48;
                     break;
                  case 5:
                     person.id = (type[2] - 48) * 10;
                     person.id += type[3] - 48;
                     break;
                  case 4:
                     person.id = type[2] - 48;
                     break;
               }  
            }
            // 
            if (type[0] == '@' && type[1] == 'F')
            {
               if (!isFirst && person.id == 145)
                  insertInOrder(person, tree);
               person.id = 0;
               momTemp = dadTemp = NULL;
               momID = dadID = childID = 0;
               isMom = true;
               isDad = true;
            }
            break;
         case 1:
            // only set birthday if previous line said BIRT
            isBirth = false;
            if (type == "BIRT" && person.id > 0)
               isBirth = true;
            // only set mom and dad if last line was FAM
            if (isMom && type == "WIFE")
            {
               // find mom's ID
               switch (info.size())   
               {
                  case 6:
                     momID = (info[2] - 48) * 100;
                     momID += (info[3] - 48) * 10;
                     momID += info[4] - 48;
                     break;
                  case 5:
                     momID = (info[2] - 48) * 10;
                     momID += info[3] - 48;
                     break;
                  case 4:
                     momID = info[2] - 48;
                     break;
               } 
            }
            if (isDad && type == "HUSB")
            {
               // find mom's ID
               switch (info.size())   
               {
                  case 6:
                     dadID = (info[2] - 48) * 100;
                     dadID += (info[3] - 48) * 10;
                     dadID += info[4] - 48;
                     break;
                  case 5:
                     dadID = (info[2] - 48) * 10;
                     dadID += info[3] - 48;
                     break;
                  case 4:
                     dadID = info[2] - 48;
                     break;
               } 
            }
            // find child
            if (type == "CHIL")
            {
               // find child's ID
               switch (info.size())   
               {
                  case 6:
                     childID = (info[2] - 48) * 100;
                     childID += (info[3] - 48) * 10;
                     childID += info[4] - 48;
                     break;
                  case 5:
                     childID = (info[2] - 48) * 10;
                     childID += info[3] - 48;
                     break;
                  case 4:
                     childID = info[2] - 48;
                     break;
               } 
               // locate mother in list
               for (ListIterator <Person> it = tree.begin(); it != tree.end(); it++)
               {
                  if ((*it).id == momID)
                  {
                     momTemp = &(*it);
                     break;
                  }
               }
               // locate father in list
               for (ListIterator <Person> it = tree.begin(); it != tree.end(); it++)
               {
                  if ((*it).id == dadID)
                  {
                     dadTemp = &(*it);
                     break;
                  }
               }
               // locate child in list
               for (ListIterator <Person> it = tree.begin(); it != tree.end(); it++)
               {
                  if ((*it).id == childID)
                  {
                     (*it).mom = momTemp;
                     (*it).dad = dadTemp;
                     break;
                  }
               }
            }
            break;
         case 2:
            if (person.id > 0)
            {
               // set birthday, first, and last name
               if (isBirth && type == "DATE")
               {
                  // input year into x
                  string x;
                  for (int i = info.size() - 4; i < info.size(); ++i)
                     x += info[i];
                  // put x into birthday year
                  stringstream a(x);
                  a >> person.birthday.year;
                  x.clear();
                  // check for a year range and input it into yearFrom
                  if (info[info.size() - 5] == '/')
                  {
                     for (int i = 0; i < 4; ++i)
                        x += info[i];
                     stringstream z(x);
                     z >> person.birthday.yearFrom;
                     x.clear();
                  }
                  // input month into x
                  for (int i = info.size() - 8; i < info.size() - 5; ++i)
                     x += info[i];
                  // put x into birthday month
                  person.birthday.month = x;
                  x.clear();
                  // input day into x
                  if (info.size() == 10) // one digit date
                  {
                     x = info[0];
                     stringstream b(x);
                     b >> person.birthday.day;
                  }
                  if (info.size() == 11) // two digit date
                  {
                     x = info[0];
                     x += info[1];
                     stringstream c(x);
                     // put x into birthday day
                     c >> person.birthday.day;
                  }
               }
               if (type == "GIVN")
                  person.fName = info;
               else if (type == "SURN")
                  person.lName = info;
            }
            break;
      }

      // reset strings for next line
      line.clear();
      type.clear();
      info.clear();
   }

   fin.close();
}


/***************************************************
 * display1
 * displays list
 **************************************************/
void display1(List <Person> & tree)
{
   for (ListIterator <Person> it = tree.begin(); it != tree.end(); it++)
   {
      cout << *it;
      cout << endl;
   }
}


/***************************************************
 * makeTree
 * builds a binary tree based on data found in Person
 **************************************************/
void makeTree(BinaryNode <Person> * & bnode)
{
   if (bnode->data.mom != NULL)
   {
      BinaryNode <Person> * pMom = new BinaryNode <Person>;
      pMom->data = *(bnode->data.mom);
      bnode->addRight(pMom);
      makeTree(pMom);
   }
   if (bnode->data.dad != NULL)
   {
      BinaryNode <Person> * pDad = new BinaryNode <Person>;
      pDad->data = *(bnode->data.dad);
      bnode->addLeft(pDad);
      makeTree(pDad);
   }
}


/***************************************************
 * display2
 * displays binary tree in genealogical order
 **************************************************/
void display2(BinaryNode <Person> * & bnode)
{
   bnode->level();
}


/**********************************************************************
 * MAIN
 * Calls above functions in order.  Also creates a single binary node 
 * for makeTree to use.
 ***********************************************************************/
int main()
{
   List <Person> list;
   BinaryNode <Person> * pRoot = new BinaryNode <Person>;
   readFile(list);
   //display1(list);
   // make Binary Node for root
   for (ListIterator <Person> it = list.begin(); it != list.end(); it++)
   {
      if ((*it).id == 1)
      {
         pRoot->data = (*it);
         break;
      }
   }
   makeTree(pRoot);
   display2(pRoot);
  
   return 0;
}

 
