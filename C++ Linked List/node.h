/***********************************************************************
* Header:
*    Week01, Node
* Summary:
*    This header contains a Node class and functions that alter the
*    nodes so that they come together in a List.  The list is designed
*    in a way that any data type can be used to fill the list.  Each
*    node holds some data and points to the next node in the list.
*
*    This will contain the class definition of:
*        Node         : A class that holds stuff
* Author
*    Tanner Larson
************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cassert>

/************************************************
 * Node
 * A class that holds stuff
 ***********************************************/
template <class T>
class Node
{
public:
   // default constructor : empty and kinda useless
   Node() : pNext(NULL), pPrev(NULL){}

   // non-default constructor : pre-allocate
   Node(T t) : pNext(NULL), pPrev(NULL), data(t){}
   
   T data;          // The thing in the Node
   Node <T> * pNext;      // points to next node in list
   Node <T> * pPrev;      // points to previous node in list
};


/***************************************************
 * Node <T> * copy
 * Copy a list of nodes
 **************************************************/
template <class T>
Node <T> * copy(Node <T> * n)
{
   Node <T> * newList = new Node <T>; // first node of copy
   newList->data = n->data; // set first node's data equal to that of n's first node

   Node <T> * pNode = newList; // will use to iterate through list

   n = n->pNext; // point n to the next node
   while (n != NULL)
   {
      pNode->pNext = new Node <T>; // give pNode->pNext memory
      pNode->pNext->pPrev = pNode;
      pNode = pNode->pNext; // point pNode to newly allocated memory
      pNode->data = n->data; // make the data of pNode and n equivalent
      n = n->pNext; // point n to the next node on the list
   }
  
   return newList;
}

/***************************************************
 * void insertNode
 * Insert a new Node into the current list
 * Parameters: data, node before insertion, isHead
 **************************************************/
template <class T>
void insertNode(const T & newData, Node <T> *& n, bool isHead = false) throw (const char *)
{
   if (n == NULL) // Node is uninitialized
   {
      n = new Node <T>;
      n->data = newData;
      assert (n != NULL);
      return;
   }

   Node <T> * newNode = new Node <T>;
   newNode->data = newData;
   if (isHead)
   {
      newNode->pNext = n;
      n->pPrev = newNode;
      n = newNode;
   }
   else
   {
      newNode->pNext = n->pNext;
      n->pNext = newNode;
      if (newNode->pNext != NULL)
         newNode->pNext->pPrev = newNode;
      newNode->pPrev = n;
   }
}

/***************************************************
 * void freeData
 * Deletes all data in a list and sets the pointer 
 * to the beginning of the list to NULL
 **************************************************/
template <class T>
void freeData(Node <T> *& header)
{
   Node <T> * toDelete = header;
   while (header != NULL)
   {
      header = header->pNext;
      delete toDelete;
      toDelete = header;
   }

   delete header;
   header = NULL;
}

/***************************************************
 * Node <T> * find
 * Returns a pointer to a node that has the same 
 * data as parameter
 **************************************************/
template <class T>
Node <T> * find(Node <T> * front, T & t)
{
   Node <T> * pNode = front;
   while (pNode->data != t && pNode->pNext != NULL)
      pNode = pNode->pNext;

   if (pNode->data != t)
      return NULL;

   return pNode;
}

/***************************************************
 * operator <<
 * Displays list
 **************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, Node <T> * rhs)
{
   while (rhs != NULL)
   {
      out << rhs->data;
      if (rhs->pNext != NULL)
         out << ", ";
      rhs = rhs->pNext;
   }
   return out;
}

#endif // NODE_H