/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> tree;
   for (int i = 0; i < num; ++i)
      tree.insert(array[i]);

   BSTIterator <T> it = tree.begin();

   for (int i = 0; i < num; ++i)
   {
      array[i] = *it;
      it++;
   }
}


#endif // SORT_BINARY_H
