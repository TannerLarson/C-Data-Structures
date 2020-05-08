/***********************************************************************
* Header:
*    Week03, Queue
* Summary:
*    This class contains the entirety of the Queue class found in the
*    standard template library.  It can hold a group of any data type 
*    in a certain order.  You can use this class a lot like an array,
*    however it can only change the front and back data of the Queue.
*    Also you can only add data to the back of the Queue and remove
*    data from the front of the Queue, making it first in first out.
*
*    This will contain the class definition of:
*        Queue         : A class that holds stuff
* Author
*    Tanner Larson
************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cassert>


/************************************************
 * Queue
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : myFront(0), myBack(0), cap(0), numItems(0), data(NULL) {}

   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Queue(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (cap) delete [] data;}

   //operator= overload
   Queue operator = (Queue <T> rhs);
   
   // is the Queue currently empty
   bool empty() const  { return numItems == 0;              }

   // remove all the items from the Queue
   void clear()        { myFront = myBack = numItems = 0;   }

   // how many items are currently in the Queue?
   int size() const    {return numItems;                    }

   // what is the capacity of the Queue?
   int capacity() const    { return cap;              }

   // add an item to the Queue
   void push(const T & t) throw (const char *);
   
   void pop();

   T & front();

   T & back();
   
private:
   T * data;          // dynamically allocated array of T
   int myFront;         // number in array that has the front of my queue
   int myBack;          // refers to data at the end of my queue
   int cap;           // what is the capacity of my Queue?
   int numItems;      // number of items in queue
};


/***************************************************
 * Queue :: operator =
 * set the data in the Queue on the left side equal
 * to the data in the Queue on the right side.
 **************************************************/
template <class T>
Queue <T> Queue <T> :: operator = (Queue <T> rhs)
   {
      assert(rhs.cap >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = myFront = myBack = numItems = 0;
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
         for (int i = myFront; i < cap; ++i) // copy front to end of queue
            data[i] = rhs.data[i];
      }
      else
         std::cerr << "\nmyFront = myBack this is bad\n";
      return *this;
   }

/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = myFront = myBack = numItems = 0;
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
      for (int i = myFront; i < cap; ++i) // copy front to end of queue
         data[i] = rhs.data[i];
   }
}

/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Queue to "capacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int capacity) throw (const char *)
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

   // initialize the Queue by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Queue :: Push
 * Puts a new item on the front of the Queue
 **************************************************/
template <class T>
void Queue <T> :: push(const T & t) throw (const char *)
{
   // check if data has been initialized
   if (data == NULL || cap == 0)
   {
      data = new T[1];
      cap = 1;
   }
   std::cerr << "\nCapactiy: " << cap;
   std::cerr << "\nempty(): " << empty();
   std::cerr << "\nnumItems: " << numItems << std::endl;
   // if there is no space for a push
   if (numItems == cap) // double capacity of queue
   {
      int newCap = cap * 2;
      T * dataTemp = new T[newCap];
      int numItemsTemp = numItems;

      for (int i = 0; numItems != 0; ++i)
      {
         dataTemp[i] = front();
         pop();
      }
      numItems = numItemsTemp;
      myFront = 0;
      myBack = size();
      delete [] data;
      data = dataTemp;
      cap = newCap;
   }

   // add an item to back
   if (myBack == cap) // wrap myBack from end of queue to myFront
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
 * Queue :: Pop
 * Removes the front data of the Queue and readjusts
 * front to point to the next data
 **************************************************/
template <class T>
void Queue <T> :: pop()
{
   if (empty())
      throw "ERROR: attempting to pop from an empty queue";

   if (myFront == cap - 1) // wrap front from end to beginning of queue
   {
      data[myFront] = T();
      myFront = 0;
   }
   else
      myFront++;

   numItems--;
}

/***************************************************
 * Queue :: Front
 * Returns data at the front of the Queue
 **************************************************/
template <class T>
T & Queue <T> :: front()
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";
   
   return data[myFront];
}

/***************************************************
 * Queue :: Back
 * Returns data at the back of the Queue
 **************************************************/
template <class T>
T & Queue <T> :: back()
{
   if (empty())
      throw "ERROR: attempting to access an item in an empty queue";

   if (myBack != 0)
      return data[myBack - 1];
   else
      return data[cap - 1];
}


#endif // Queue_H

