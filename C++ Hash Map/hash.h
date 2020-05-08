/***********************************************************************
* Header:
*    Week12, Hash
* Summary:
*    This class implements the hash class completely.  It is special
*    because it organizes data in a very efficient manner.
* Author
*    Tanner Larson
************************************************************************/

#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string> 
#include <cassert>
#include "list.h"



/************************************************
 * Hash
 * A class that holds stuff
 ***********************************************/
template <class T>
class Hash
{
public:
   // default constructor : empty and kinda useless
   Hash() : numItems(0), cap(0), hashTable(NULL) {}

   // non-default constructor
   Hash(int numBuckets);

   // copy constructor : copy it
   Hash(const Hash & rhs) throw (const char *);
      
   // destructor : free everything
   ~Hash();
   
   // is the Hash currently empty
   bool empty() const   { return numItems == 0;       }

   // how many items are currently in the Hash?
   int size() const     { return numItems;            }

   // what is our capacity?
   int capacity() const { return cap;                 }

   // remove all the items from the Hash
   void clear();

   // returns true if value is found in hash
   bool find(T value);

   // insert data into hash
   void insert(T data);

   // returns a hash index
   int virtual hash(const T & value) const = 0;

protected:
   List <T> * hashTable; // dynamically allocated array of lists
   int cap; // capacity
   int numItems; // number of items
};


/*******************************************
 * Hash :: NON-DEFAULT CONSTRUCTOR
 *******************************************/
template <class T>
Hash <T> :: Hash(int numBuckets)
{
   hashTable = new List <T> [numBuckets];
   cap = numBuckets;
   numItems = 0;
}

/*******************************************
 * Hash :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Hash <T> :: Hash(const Hash <T> & rhs) throw (const char *)
{

   cap = rhs.cap;
   numItems = rhs.numItems;
   hashTable = new List <T> [cap];
   if (rhs.empty())
      return;
   for (int i = 0; i < cap; ++i)
      hashTable[i] = rhs.hashTable[i];
}

/*******************************************
 * Hash :: DECONSTRUCTOR
 *******************************************/
template <class T>
Hash <T> :: ~Hash()
{
   clear();
   numItems = 0;
   cap = 0;
   delete [] hashTable;
}


/***************************************************
 * Hash :: clear
 * clears all daat from the Hash
 **************************************************/
template <class T>
void Hash <T> :: clear()        
{ 
   for (int i = 0; i < cap; ++i)
   {
      hashTable[i].clear();
   }
   numItems = 0;
}

/***************************************************
 * Hash :: clear
 * returns true if parameter is found in hash
 **************************************************/
template <class T>
bool Hash <T> :: find(T type)
{
   int num = hash(type);
   for (ListIterator <T> it = hashTable[num].begin(); it != hashTable[num].end(); it++)
   {
      if (*it == type)
         return true;
   }
   return false;
}


/***************************************************
 * Hash :: insert
 * inserts data into the Hash in alphabetical or 
 * numerical order
 **************************************************/
template <class T>
void Hash <T> :: insert(T data)
{
   int num = hash(data);
   hashTable[num].push_back(data);
   numItems++;
}


/****************************************
 * I HASH
 * A simple hash of integers
 ****************************************/
class IHash : public Hash <int>
{
public:
   IHash(int numBuckets)    throw (const char *) : Hash <int> (numBuckets) {}
   IHash(const IHash & rhs) throw (const char *) : Hash <int> (rhs)        {}

   //operator= overload
   IHash operator = (IHash rhs)
   {
      clear();
      if (rhs.cap > cap)
      {
         delete [] hashTable;
         hashTable = new List <int> [rhs.cap];
      }
      cap = rhs.cap;
      numItems = rhs.numItems;
      if (rhs.empty())
         return *this;
      for (int i = 0; i < capacity(); ++i)
         hashTable[i] = rhs.hashTable[i];
      return *this;
   }

   // hash function for integers is simply to take the modulous
   int hash(const int & value) const
   {
      return value % capacity();
   }
};


/****************************************
 * F HASH
 * A hash of Floating Point numbers
 ****************************************/
class FHash : public Hash <float>
{
public:
   FHash(int numBuckets, float min, float max) throw (const char *) :
         Hash <float> (numBuckets), min(min), max(max)  {}
   FHash(const FHash & rhs) throw (const char *) :
         Hash <float> (rhs), min(rhs.min), max(rhs.max) {}

   //operator= overload
   FHash operator = (FHash rhs)
   {
      clear();
      if (rhs.cap > cap)
      {
         delete [] hashTable;
         hashTable = new List <float> [rhs.cap];
      }
      cap = rhs.cap;
      numItems = rhs.numItems;
      if (rhs.empty())
         return *this;
      for (int i = 0; i < capacity(); ++i)
         hashTable[i] = rhs.hashTable[i];
      return *this;
   }

   // hash function for strings will add up all the ASCII values
   int hash(const float & value) const
   {
      return (int)((value - min) / (max - min) * capacity()) % capacity();
   }
private:
   float min;
   float max;
};


/****************************************
 * C HASH
 * A simple hash of characters
 ****************************************/
class CHash : public Hash <char>
{
public:
   CHash(int numBuckets)    throw (const char *) : Hash <char> (numBuckets) {}
   CHash(const CHash & rhs) throw (const char *) : Hash <char> (rhs)        {}

   //operator= overload
   CHash operator = (CHash rhs)
   {
      clear();
      if (rhs.cap > cap)
      {
         delete [] hashTable;
         hashTable = new List <char> [rhs.cap];
      }
      cap = rhs.cap;
      numItems = rhs.numItems;
      if (rhs.empty())
         return *this;
      for (int i = 0; i < capacity(); ++i)
         hashTable[i] = rhs.hashTable[i];
      return *this;
   }

   // hash function for integers is simply to take the modulous
   int hash(const char & value) const
   {
      return (int)value % capacity();
   }
};


/****************************************
 * S HASH
 * A simple hash of characters
 ****************************************/
class SHash : public Hash <std::string>
{
public:
   SHash(int numBuckets)    throw (const char *) : Hash <std::string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <std::string> (rhs)        {}

   //operator= overload
   SHash operator = (SHash rhs)
   {
      clear();
      if (rhs.cap > cap)
      {
         delete [] hashTable;
         hashTable = new List <std::string> [rhs.cap];
      }
      cap = rhs.cap;
      numItems = rhs.numItems;
      if (rhs.empty())
         return *this;
      for (int i = 0; i < capacity(); ++i)
         hashTable[i] = rhs.hashTable[i];
      return *this;
   }

   // hash function for integers is simply to take the modulous
   int hash(const std::string & value) const
   {
      // get ASCII value for first letter and double it
      int num = (int)value[0] * 2; 
      // add the rest of the ASCII values
      for (int i = 1; i < value.size() - 1; ++i)
      {
         num += (int)value[i];
      }
      return num % capacity();
   }
};

#endif // Hash_H

