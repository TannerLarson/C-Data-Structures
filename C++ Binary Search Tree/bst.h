/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack

// forward declaration for the BST iterator
template <class T>
class BSTIterator; 

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // constructor
   BST(): root(NULL){};
   
   // copy constructor
   BST(const BST & rhs);    
   
   ~BST();

   int size() const  { return empty() ? 0 : root->size(); }   // BinaryNode class needs a size function
   
   
   // determine if the tree is empty
   bool empty() const
   {
      if (root == NULL || root->size() == 0)
         return true; 
      return false;
   }

   // remove all the nodes from the tree.  Makes an empty tree.
   void clear()
   {
      if (root != NULL)
      {
         deleteBinaryTree(root);
         root = NULL;
      }
   }

   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   {
      clear();
      if (rhs.root == NULL)
         return *this;
      BinaryNode <T> * x = rhs.root; // create iterator through BST

      copyBinaryNode (x);
      return *this;
   }
      
   // insert an item
   void insert(const T & t) throw (const char * );

   // copies binary node into BST
   void copyBinaryNode (BinaryNode <T> * n);

   // remove an item
   void remove(BSTIterator <T> & it);

   // find a given item
   BSTIterator <T> find(const T & t);

   // the usual iterator stuff
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
   
private:

   BinaryNode <T> * root;
};

/*****************************************************
 * BST :: copyBinaryNode
 * Copies binary node into BST
 ****************************************************/
template <class T>
void BST <T> :: copyBinaryNode (BinaryNode <T> * n)
{
   insert(n->data);
   if (n->pLeft != NULL)
   {
      if (n->pRight != NULL)
         copyBinaryNode(n->pRight);
      copyBinaryNode(n->pLeft);
   }
   else if (n->pRight != NULL)
      copyBinaryNode(n->pRight);
}

/*********************************************************
* Copy Constructor
**********************************************************/
template <class T>
BST<T>::BST(const BST &rhs)
{
   root = NULL;
   if (rhs.empty())
   {
      clear();
      return;
   }
   copyBinaryNode (rhs.root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST()
{
   clear();
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char *)
{
   if (root == NULL)
   {
      root = new BinaryNode <T>;
      root->data = t;
      return;
   }

   BinaryNode <T> * x = root; // create iterator through BST

   while (1)
   {
      while (t <= x->data) // finds leftmost node
      {
         if (x->pLeft != NULL)
            x = x->pLeft;
         else
            break;
      }
      if (t <= x->data) // is t still smaller
      {
         x->addLeft(t);
         return;
      }
      else // t is bigger
      {
         if (x->pRight == NULL) 
         {
            x->addRight(t);
            return;
         }
         x = x->pRight;
      }
   }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it)
{
   BinaryNode <T> * n = it.getNode();
   BinaryNode <T> * x = n;

   if (n->pLeft != NULL)
   {
      if (n->pRight != NULL) // n has two children
      {
         x = n->pRight;
         while (x->pLeft != NULL) // find successor
            x = x->pLeft;

         n->data = x->data; // replace n data with successor data
         remove(++it); // recursively call remove for successor
      }
      else // n has only left child
      {
         std::cerr << "\nn has only a left child\n";

         if (n->pParent->pLeft == n)
            n->pParent->pLeft = n->pLeft;
         else
            n->pParent->pRight = n->pLeft;
         n->pLeft->pParent = n->pParent;
         delete n;
         n = NULL;
      }
   }
   else if (n->pRight != NULL) // n has only right child
   {
      std::cerr << "\nn has only a right child\n";

      if (n->pParent->pLeft == n)
         n->pParent->pLeft = n->pRight;
      else
         n->pParent->pRight = n->pRight;
      n->pRight->pParent = n->pParent;
      delete n;
      n = NULL;
   }
   else // n has no children
   {
      if (n == n->pParent->pLeft)
         n->pParent->pLeft = NULL;
      else
         n->pParent->pRight = NULL;
      delete n;
      n = NULL;
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BSTIterator <T> it = begin();
   while (it != end() && *it != t)
      it++;

   return it;
}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

   // must give friend status to remove so it can call getNode() from it
   friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


#endif // BST_H
