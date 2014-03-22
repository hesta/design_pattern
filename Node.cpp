/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Node_CPP)
#define _Node_CPP

// Ctor
template <typename T>
Node<T>::Node (const T &item, Node<T> *left, Node<T> *right)
  : item_ (item),
    left_ (left),
    right_ (right),
    use_ (1)
{    
}

// Dtor
template <typename T>
Node<T>::~Node ()
{
  // Clean up the subtrees first and then the root recursively
  delete left_;
  delete right_;
}

// Return the item in the node.
template <typename T>
const T &
Node<T>::item (void) const
{
  return item_;
}

// Return the left child.
template <typename T>
Node<T> *
Node<T>::left (void) const
{
  return left_;
}

// Return the right child.
template <typename T>
Node<T> *
Node<T>::right (void) const
{
  return right_;
}

#endif /* _Node_CPP */
