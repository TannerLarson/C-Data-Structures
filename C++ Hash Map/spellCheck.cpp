/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Tanner Larson
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   string fileName;
   string word;
   SHash dictionary(3000);
   vector <string> misspelled;
   bool wasUpper = false;

   // put dictionary into a hash
   ifstream fin;
   fin.open("/home/cs235e/week12/dictionary.txt");
   if (fin.fail()) // check for fin.fail()
   {
      cout << "File does not exist\n";
      return;
   }
   // read in input word by word
   while (fin >> word)
   {
      dictionary.insert(word);
   }

   fin.close();


   cout << "What file do you want to check? ";
   cin >> fileName;

   // input file to spell check
   fin.open(fileName.c_str());
   if (fin.fail()) // check for fin.fail()
   {
      cout << "File does not exist\n";
      return;
   }
   // read in input word by word
   while (fin >> word)
   {
      if (isupper(word[0]))
      {
         wasUpper = true;
         string a;
         a += word[0];
         a = tolower(a[0]);
         word.replace(0,1,a);
      }
      else
         wasUpper = false;

      if (!dictionary.find(word))
      {
         if (wasUpper)
         {
            wasUpper = false;
            string a;
            a += word[0];
            a = toupper(a[0]);
            word.replace(0,1,a);
         }
         misspelled.push_back(word);
      }
   }
   fin.close();

   if (misspelled.empty())
      cout << "File contains no spelling errors\n";
   else
   {
      cout << "Misspelled: " << misspelled[0];
      for (int i = 1; i < misspelled.size(); ++i)
      {
         cout << ", " << misspelled[i];
      }
      cout << endl;
   }
}
