/***********************************************************************
* Header:
*    Week01, List
* Summary:
*    This class contains the entirety of the List class found in the
*    List library.  It can hold a group of any data type in either 
*    alphabetical or numerical order, depending on the data type.
*    One may insert new data, but the data must be totally unique, 
*    otherwise the insert command will be ignored.  One may also search
*    for where certain values are stored, and may also remove data
*    using the location integer they are found in.
*
*    This will contain the class definition of:
*        List         : A class that holds stuff
*        ListIterator : An iterator through List
* Author
*    Tanner Larson
************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
#include "node.h"

// forward declaration for ListIterator
template <class T>
class ListIterator;

/************************************************
 * List
 * A class that holds stuff
 ***********************************************/
template <class T>
class List
{
public:
   // default constructor : empty and kinda useless
   List() : numItems(0), head(NULL), butt(NULL) {}

   // copy constructor : copy it
   List(const List & rhs) throw (const char *);
      
   // destructor : free everything
   ~List()        { if (numItems) clear(); }

   //operator= overload
   List operator = (List <T> rhs);
   
   // is the List currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the List
   void clear();

   // how many items are currently in the List?
   int size() const    { return numItems;              }

   void push_back( const T & t);

   void push_front( const T & t);

   T & front()         { return head->data;            }

   T & back()          { return butt->data;            }

   // inserts data into the List as long as it is unique to the List
   ListIterator <T> insert(ListIterator <T> it, const T & t) throw (const char *);

   void remove(ListIterator <T> it);

   // return an iterator to the beginning of the List
   ListIterator <T> begin() { return ListIterator<T>(head); }

   ListIterator <T> rbegin() { return ListIterator<T>(butt); }

   // return an iterator to the end of the List
   ListIterator <T> end();

   ListIterator <T> rend();

private:
   Node <T> * head;          // pointer to beginning node in list
   Node <T> * butt;          // pointer to last node in list
   int numItems;      // how many items are currently in the List?
};

/**************************************************
 * List ITERATOR
 * An iterator through List
 *************************************************/
template <class T>
class ListIterator
{
   friend class List <T>;
   public:
   // default constructor
   ListIterator() : p(NULL) {}

    // copy constructor : copy it
   ListIterator(const ListIterator & rhs) throw (const char *)
   { p = rhs.p;}

   // initialize to direct p to some item
   ListIterator(Node <T> * n) : p(n) {}

   // equals operator
   ListIterator & operator = (const ListIterator & rhs)
   {
      p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const ListIterator & rhs) const
   {
      return rhs.p != this->p;
   }

      // equivalent operator
   bool operator == (const ListIterator & rhs) const
   {
      return rhs.p == this->p;
   }

   // dereference operator
   T & operator * ()       {return p->data;}

   // prefix increment
   ListIterator <T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }

   // prefix decrement
   ListIterator <T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   ListIterator <T> operator ++ (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

   // postfix decrement
   ListIterator <T> operator -- (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   private:
   Node <T> * p;
};

/***************************************************
 * List :: operator =
 * List the data in the List on the left side equal
 * to the data in the List on the right side.
 **************************************************/
template <class T>
List <T> List <T> :: operator = (List <T> rhs)
{
   clear();

   if (rhs.size() == 0)
      return *this;

   numItems = rhs.numItems;
   head = copy(rhs.head);

   butt = head;
   while (butt->pNext != NULL) // find end of list
      butt = butt->pNext; // initialize butt

   return *this;
}


/*******************************************
 * List :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
List <T> :: List(const List <T> & rhs) throw (const char *)
{
   head = copy(rhs.head);
   numItems = rhs.size();

   Node <T> * temp = head;
   while (temp->pNext != NULL) // find end of list
     temp = temp->pNext;
   butt = temp;
}


/***************************************************
 * List :: clear
 * clears all daat from the list
 **************************************************/
template <class T>
void List <T> :: clear()        
{ 
   numItems = 0;
   head = butt = NULL;
   freeData(head); 
}


/***************************************************
 * List :: push_back
 * inserts data on the back end of the list
 **************************************************/
template <class T>
void List<T> :: push_back(const T & t)
{
   insertNode(t, butt);
   if (numItems == 0)
      head = butt; // initialize head
   else
      butt = butt->pNext; // move butt to end of list
   numItems++; 
}


/***************************************************
 * List :: push_front
 * Inserts data at the head of the list
 **************************************************/
template <class T>
void List <T> :: push_front(const T & t) 
{ 
   insertNode(t, head, true);
   if (numItems == 0)
   {
      butt = head; // initialize butt
   }
   numItems++; 
}


/***************************************************
 * List :: insert
 * inserts data into the List in alphabetical or 
 * numerical order
 **************************************************/
template <class T>
ListIterator <T> List <T> :: insert(ListIterator <T> it, const T & t) throw (const char *)
{
   if (it == begin())
   {
      push_front(t);
      return it;
   }
   else if (it == end())
   {
      push_back(t);
      return it;
   }
   else
   {
      it--;
      insertNode(t, it.p);
   }
      numItems++;
      return it++;
}


/***************************************************
 * List :: remove
 * removes data from the list
 **************************************************/
template <class T>
void List <T> :: remove(ListIterator <T> it)
{
   if (it == end())
      throw "ERROR: unable to remove from an invalid location in a list";
   else if (it == begin()) // it is pointing to head
   {
      head = it.p->pNext;
      head->pPrev = NULL;
      delete it.p;
   }
   else if (it.p->pNext == NULL) // it is pointing to butt
   {
      butt = it.p->pPrev;
      butt->pNext = NULL;
      delete it.p;
   }
   else
   {
      it.p->pPrev->pNext = it.p->pNext; // hook up previous node with next node
      it.p->pNext->pPrev = it.p->pPrev; // hook up next node with previous node
      numItems--;
      delete it.p;
   }
   numItems--;
}


/***************************************************
 * List :: end
 * returns iterator to the end of the list
 **************************************************/
template <class T>
ListIterator <T> List <T> :: end() 
{ 
   if (numItems == 0)
      return ListIterator<T>(butt);
   else
      return ListIterator<T>(butt->pNext); 
}


/***************************************************
 * List :: rend
 * returns iterator to th front of list
 **************************************************/
template <class T>
ListIterator <T> List <T> :: rend() 
{ 
   if (numItems == 0)
      return ListIterator<T>(head); 
   else
      return ListIterator<T>(head->pPrev);
}


#endif // List_H

