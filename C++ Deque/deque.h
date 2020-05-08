/***********************************************************************
* Header:
*    Week03, Deque
* Summary:
*    This class contains the entirety of the Deque class found in the
*    standard template library.  It can hold a group of any data type 
*    in a certain order.  You can use this class a lot like an array,
*    however it can only change the front and back data of the Deque.
*    Users may add or remove data from the beginning or the end of the
*    Deque, making it a combination of a stack and a queue.
*
*    This will contain the class definition of:
*        Deque         : A class that holds stuff
* Author
*    Tanner Larson
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <cassert>


/************************************************
 * Deque
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
public:
   // default constructor : empty and kinda useless
   Deque() : myFront(0), myBack(0), cap(0), numItems(0), data(NULL) {}

   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Deque()        { if (cap) delete [] data;}

   //operator= overload
   Deque operator = (Deque <T> rhs);
   
   // is the Deque currently empty
   bool empty() const  { return numItems == 0;              }

   // remove all the items from the Deque
   void clear()        { myFront = myBack = numItems = 0;   }

   // SWAB THE DEQUE
   void swab()         { clear();                           }

   // how many items are currently in the Deque?
   int size() const    {return numItems;                    }

   // what is the capacity of the Deque?
   int capacity() const    { return cap;              }

   // add an item to the Deque
   void push_back(const T & t) throw (const char *);

   void push_front(const T & t) throw (const char *);
   
   void pop_front();

   void pop_back();

   T & front();

   T & back();
   
private:
   T * data;          // dynamically allocated array of T
   int myFront;         // number in array that has the front of my Deque
   int myBack;          // refers to data at the end of my Deque
   int cap;           // what is the capacity of my Deque?
   int numItems;      // number of items in Deque
};


/***************************************************
 * Deque :: operator =
 * set the data in the Deque on the left side equal
 * to the data in the Deque on the right side.
 **************************************************/
template <class T>
Deque <T> Deque <T> :: operator = (Deque <T> rhs)
   {
      assert(rhs.cap >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         swab(); // SWAB THAT DEQUE YA LILLY-LIVERED SEA DOGS
         cap = 0;
         delete [] this-> data;
         data = NULL;
         return *this;
      }

      // attempt to allocate
      try
      {
         delete [] data;
         data = new T[rhs.cap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy over the capacity and size
      assert(rhs.size() >= 0 && rhs.size() <= rhs.cap);
      cap = rhs.cap;
      myFront = rhs.myFront;
      myBack = rhs.myBack;
      numItems = rhs.numItems;

      // copy the items over one at a time using the assignment operator
      if (myFront < myBack)
      {
         for (int i = myFront; i < myBack; i++)
            data[i] = rhs.data[i];
         // the rest needs to be filled with the default value for T
         for (int i = myBack; i < cap; i++)
            data[i] = T();
         for (int i = 0; i < myFront; ++i)
            data[i] = T();
      }
      else if (myFront != myBack) // back is in front of front
      {
         for (int i = 0; i < myBack; ++i) // copy beginning to myBack
            data[i] = rhs.data[i];
         for (int i = myBack; i < myFront; ++i) // fill in between with default
            data[i] = T();
         for (int i = myFront; i < cap; ++i) // copy front to end of Deque
            data[i] = rhs.data[i];
      }
      else
         std::cerr << "\nmyFront = myBack this is bad\n";
      return *this;
   }

/*******************************************
 * Deque :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      swab(); // IF YE DON'T SWAB THAT DEQUE YE'LL END UP IN DAVY JONES' LOCKER MATEY
      cap = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.size() >= 0 && rhs.size() <= rhs.cap);
   cap = rhs.cap;
   myFront = rhs.myFront;
   myBack = rhs.myBack;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   if (myFront < myBack)
   {
      for (int i = myFront; i < myBack; i++)
         data[i] = rhs.data[i];
      // the rest needs to be filled with the default value for T
      for (int i = myBack; i < cap; i++)
         data[i] = T();
   }
   else // back is in front of front
   {
      for (int i = 0; i < myBack; ++i) // copy beginning to myBack
         data[i] = rhs.data[i];
      for (int i = myBack; i < myFront; ++i) // fill in between with default
         data[i] = T();
      for (int i = myFront; i < cap; ++i) // copy front to end of Deque
         data[i] = rhs.data[i];
   }
}

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Deque to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->myFront = this->myBack = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->cap = capacity;
   this->myFront = this->myBack = numItems = 0;

   // initialize the Deque by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Deque :: Push_back
 * Puts a new item on the back of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_back(const T & t) throw (const char *)
{
   // check if data has been initialized
   if (data == NULL || cap == 0)
   {
      data = new T[1];
      cap = 1;
   }
   // if there is no space for a push
   if (numItems == cap) // double capacity of Deque
   {
      int newCap = cap * 2;
      T * dataTemp = new T[newCap];
      int numItemsTemp = numItems;

      for (int i = 0; numItems != 0; ++i)
      {
         dataTemp[i] = front();
         pop_front();
      }
      swab(); // YA BETTER GET TO SWABBING THAT DEQUE I'M A PIRATE ARRRRR
      numItems = numItemsTemp;
      myFront = 0;
      myBack = size();
      delete [] data;
      data = dataTemp;
      cap = newCap;
   }

   // add an item to back
   if (myBack == cap) // wrap myBack from end of Deque to myFront
   {
      myBack = 1;
      data[0] = t;
   }
   else
   {
      data[myBack] = t;
      myBack++;
   }

   numItems++;
}

/***************************************************
 * Deque :: Push_front
 * Puts a new item on the front of the Deque
 **************************************************/
template <class T>
void Deque <T> :: push_front(const T & t) throw (const char *)
{
   // check if data has been initialized
   if (data == NULL || cap == 0)
   {
      data = new T[1];
      cap = 1;
   }
   // if there is no space for a push
   if (numItems == cap) // double capacity of Deque
   {
      int newCap = cap * 2;
      T * dataTemp = new T[newCap];
      int numItemsTemp = numItems;

      for (int i = 0; numItems != 0; ++i)
      {
         dataTemp[i] = front();
         pop_front();
      }
      swab(); // SHIVER ME TIMBERS, ME DEQUE BE DIRTY.  GET TO SWABBING.
      numItems = numItemsTemp;
      myFront = 0;
      myBack = size();
      delete [] data;
      data = dataTemp;
      cap = newCap;
   }

   // add an item to front
   if (myFront == 0) // wrap myBack from end of Deque to myFront
   {
      myFront = cap - 1;
      data[cap - 1] = t;
   }
   else
   {
      data[myFront - 1] = t;
      myFront--;
   }

   numItems++;
}

/***************************************************
 * Deque :: Pop_front
 * Removes the front data of the Deque and readjusts
 * front to point to the next data
 **************************************************/
template <class T>
void Deque <T> :: pop_front()
{
   if (empty())
      throw "ERROR: unable to pop from the front of empty deque";

   if (myFront == cap - 1) // wrap front from end to beginning of Deque
   {
      data[myFront] = T();
      myFront = 0;
   }
   else
      myFront++;

   numItems--;
}

/***************************************************
 * Deque :: Pop_back
 * Removes the back data of the Deque and readjusts
 * back to point to the previous data
 **************************************************/
template <class T>
void Deque <T> :: pop_back()
{
   if (empty())
      throw "ERROR: unable to pop from the back of empty deque";

   if (myBack == 1) // wrap front from end to beginning of Deque
   {
      data[0] = T();
      myBack = cap;
   }
   else
      myBack--;

   numItems--;
}

/***************************************************
 * Deque :: Front
 * Returns data at the front of the Deque
 **************************************************/
template <class T>
T & Deque <T> :: front()
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";
   
   return data[myFront];
}

/***************************************************
 * Deque :: Back
 * Returns data at the back of the Deque
 **************************************************/
template <class T>
T & Deque <T> :: back()
{
   if (empty())
      throw "ERROR: unable to access data from an empty deque";

   if (myBack != 0)
      return data[myBack - 1];
   else
      return data[cap - 1];
}


#endif // Deque_H

