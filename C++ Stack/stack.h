/***********************************************************************
* Header:
*    Week02, Stack
* Summary:
*    This class contains the entirety of the Stack class found in the
*    standard template library.  It can hold a group of any data type 
*    in a certain order.  You can use this class a lot like an array,
*    however it can only change the top data of the stack, or the data
*    that was most recently put on top of the stack.
*
*    This will contain the class definition of:
*        Stack         : A class that holds stuff
* Author
*    Tanner Larson
************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cassert>


/************************************************
 * Stack
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (cap) delete [] data;}

   //operator= overload
   Stack operator = (Stack <T> rhs);
   
   // is the Stack currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Stack
   void clear()        { numItems = 0;                 }

   // how many items are currently in the Stack?
   int size() const    { return numItems;              }

   // what is the capacity of the Stack?
   int capacity() const    { return cap;              }

   // add an item to the Stack
   void push(const T & t) throw (const char *);
   
   void pop();

   T & top();
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Stack?
   int cap;           // how many items can I put on the Stack before full?
};


/***************************************************
 * Stack :: operator =
 * set the data in the stack on the left side equal
 * to the data in the stack on the right side.
 **************************************************/
template <class T>
Stack <T> Stack <T> :: operator = (Stack <T> rhs)
   {
      assert(rhs.cap >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = numItems = 0;
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
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
      cap = rhs.cap;
      numItems = rhs.numItems;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
         data[i] = rhs.data[i];

      // the rest needs to be filled with the default value for T
      for (int i = numItems; i < cap; i++)
         data[i] = T();
      return *this;
   }

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
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
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Stack to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
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
   this->numItems = 0;

   // initialize the Stack by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Stack :: Push
 * Puts a new item on top of the stack
 **************************************************/
template <class T>
void Stack <T> :: push(const T & t) throw (const char *)
{
   // check if data has been initialized
   if (data == NULL)
   {
      data = new T[1];
      cap = 1;
   }
   // if there is no space for a push
   if (cap == numItems)
   {
      int newCap = cap * 2;
      T * dataTemp = new T[newCap];
      for (int i = 0; i < cap; ++i)
      {
         dataTemp[i] = data[i];
      }
      delete [] data;
      data = dataTemp;
      cap = newCap;
   }

   // add an item to the end
   data[numItems++] = t;
}


template <class T>
void Stack <T> :: pop()
{
   if (numItems == 0)
      throw "ERROR: Unable to pop from an empty Stack";

   data[numItems - 1] = T();
   numItems--;
}


template <class T>
T & Stack <T> :: top()
{
   if (numItems == 0)
      throw "ERROR: Unable to reference the element from an empty Stack";


   return data[numItems - 1];
}


#endif // Stack_H

