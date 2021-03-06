#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
public:

   // default constructor
   BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL){}

   // non-default constructor
   BinaryNode(T t) : pLeft(NULL), pRight(NULL), pParent(NULL), data(t){}

   // return size (i.e. number of nodes in tree)
   int size() const
   {
      if (this == NULL)
         return 0;
      return 1 +
         (pLeft== NULL? 0 : pLeft->size()) +
         (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);

   void level();
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;

   // the data of unknown type: cannot validate so is public
   T data;
};


/*****************************************************************
 * BINARY NODE :: addLeft
 * Sets parameter node to pLeft
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addLeft(BinaryNode <T> * pNode)
{
   if (pNode == NULL)
      pLeft = NULL;
   else
   {
      pLeft = pNode;
      pNode->pParent = this;
   }
}


/*****************************************************************
 * BINARY NODE :: addRight
 * Sets parameter node to pLeft
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addRight(BinaryNode <T> * pNode)
{
   if (pNode == NULL)
      pRight = NULL;
   else
   {
      pRight = pNode;
      pNode->pParent = this;
   }
}


/*****************************************************************
 * BINARY NODE :: addLeft
 * Creates a new node and sets parameter node to pLeft
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addLeft(const T & t) throw (const char *)
{
   BinaryNode <T> * newNode = new BinaryNode <T>;
   newNode->data = t;
   pLeft = newNode;
   newNode->pParent = this;
}


/*****************************************************************
 * BINARY NODE :: addRight
 * Creates a new node and sets parameter node to pLeft
 *****************************************************************/
template <class T>
void BinaryNode <T> :: addRight(const T & t) throw (const char *)
{
   BinaryNode <T> * newNode = new BinaryNode <T>;
   newNode->data = t;
   pRight = newNode;
   newNode->pParent = this;
}


/*****************************************************************
 * deleteBinaryTree
 * Delete tree and its children
 *****************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T>  * &n)
{
   if (n == NULL)
      return;

   if (n->pLeft != NULL)
   {
      if (n->pRight == NULL) // only pLeft is full
         deleteBinaryTree(n->pLeft);
      else // pLeft and pRight are full
      {
         deleteBinaryTree(n->pLeft);
         deleteBinaryTree(n->pRight);
      }
   }
   else if (n->pRight != NULL) // only pRight is full
      deleteBinaryTree(n->pRight);

   n = NULL;
   delete n; // both pLeft and pRight should be deleted

}


/*****************************************************************
 * operator <<
 * Displays Binary Node infix
 *****************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BinaryNode <T> * rhs)
{
   if (rhs->pLeft != NULL)
   {
      out << rhs->pLeft;
      if (rhs->pParent != NULL)
         out << '^';
      out << rhs->data << ' ';
      if (rhs->pRight != NULL)
         out << rhs->pRight;      
   }
   else
   {
      if (rhs->pParent != NULL)
         out << '^';
      out << rhs->data << ' ';
      if (rhs->pRight != NULL)
         out << rhs->pRight;
   }

   return out;
}


/*****************************************************************
 * operator <<
 * Displays Binary Node infix
 *****************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BinaryNode <T> rhs)
{
   if (rhs.pLeft != NULL)
   {
      out << rhs.pLeft;
      out << rhs.data << ' ';
      if (rhs.pRight != NULL)
         out<< rhs.pRight;      
   }
   else
   {
      out << rhs.data << ' ';
      if (rhs.pRight != NULL)
         out << rhs.pRight;
   }

   return out;
}

template <class T>
void BinaryNode <T> :: level()
{
  const int MAX = 100;
  BinaryNode <T> *queue[MAX];
  BinaryNode <T> *temp;
  int front = 0;
  int back = 0;
  int saveBack = 0;
  int genNumber = 0;

  queue[back++] = this;

  while (front != back)
  {
    // checks for end of generation
    if (saveBack == front)
    {
      switch (genNumber)
      {
        case 0:
          std::cout << "The Ancestors of Gregory Lawrence Cameron:\n";
          break;
        case 1:
          std::cout << "Parents:\n";
          break;
        case 2:
          std::cout << "Grandparents:\n";
          break;
        case 3:
          std::cout << "Great Grandparents:\n";
          break;
        case 4:
          std::cout << "2nd Great Grandparents:\n";
          break;
        case 5:
          std::cout << "3rd Great Grandparents:\n";
          break;
        case 6:
          std::cout << "4th Great Grandparents:\n";
          break;
        case 7:
          std::cout << "5th Great Grandparents:\n";
          break;
      }
      saveBack = back;
      genNumber++;
    }
    temp = queue[front];
    front = (front + 1) % MAX;
    if (temp != NULL)
    {
      // visit
      if (genNumber != 1)
      {
        std::cout.width(4);
        std::cout << "        " << temp->data << " \n";
      }
      // end Visit        
      queue[back] = temp->pLeft;
      back = (back + 1) % MAX;
      queue[back] = temp->pRight;
      back = (back + 1) % MAX;

    }
  }
}

#endif // BNODE_H
