/***********************************************************************
* Header:
*    Week01, Vector
* Summary:
*    This class contains the entirety of the Vector class found in the
*    Vector library.  It can hold a group of any data type in a certain
*    order.  You can use this class a lot like an array, however it is
*    much more dynamic than an array because you can change the size
*    and what is in it at will.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An iterator through Vector
* Author
*    Tanner Larson
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (cap) delete [] data;}

   //operator[] overload
   T & operator [] (int index)   {return data[index];}

   //const operator[] overload
   T & operator [] (int index) const   {return data[index];}

   //operator= overload
   Vector operator = (Vector <T> rhs);
   
   // is the Vector currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Vector
   void clear()        { numItems = 0;                 }

   // how many items are currently in the Vector?
   int size() const    { return numItems;              }

   // what is the capacity of the Vector?
   int capacity() const    { return cap;              }

   // add an item to the Vector
   void push_back(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int cap;           // how many items can I put on the Vector before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
 *************************************************/
template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

    // copy constructor : copy it
   VectorIterator(const VectorIterator & rhs) throw (const char *)
   { p = rhs.p;}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}

  // equals operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

      // equivalent operator
   bool operator == (const VectorIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()       {return *p;}

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};

/***************************************************
 * Vector :: operator =
 * set the data in the vector on the left side equal
 * to the data in the vector on the right side.
 **************************************************/
template <class T>
Vector <T> Vector <T> :: operator = (Vector <T> rhs)
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
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
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
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
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

   // initialize the Vector by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Vector :: Push_back
 * push_back an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
   // check if data has been initialized
   if (data == NULL)
   {
      data = new T[1];
      cap = 1;
   }
   // if there is no space for a push_back
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


#endif // Vector_H

