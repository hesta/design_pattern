/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_CPP)
#define _Tree_CPP

// Default ctor
template <typename T>
Tree<T>::Tree ()
{
}

// Ctor take an underlying Node<T>*.
template <typename T>
Tree<T>::Tree (Node<T> *root, bool count)
  : root_ (root, count)
{    
}

// Ctor taking an item to store.
template <typename T>
Tree<T>::Tree (const T &item)
  : root_ (new Node<T> (item))
{
}

// Ctor taking item and two children.
template <typename T>
Tree<T>::Tree (const T &item, Node<T> *left, Node<T> *right)
  : root_ (new Node<T> (item, left, right))
{
}

// Copy ctor
template <typename T>
Tree<T>::Tree (const Tree &t)
  : root_ (t.root_)
{
}

// Assignment operator
template <typename T>
void
Tree<T>::operator= (const Tree &t)
{
  if (this != &t)
    this->root_ = t.root_;
}

// Dtor
template <typename T>
Tree<T>::~Tree ()
{
}

// Check if the tree is empty.
template <typename T>
bool
Tree<T>::is_null (void) const
{
  return root_.is_null ();
}

// Return the stored item.
template <typename T>
const T &
Tree<T>::item (void) const
{
  return root_->item ();
}

// Return the left branch.
template <typename T>
Tree<T>
Tree<T>::left (void) const
{
  // wrap the Node* in a tree object and increase reference count by one.
  return Tree<T> (root_->left (), true);
}

// Return the left branch.
template <typename T>
Tree<T>
Tree<T>::right (void) const
{
  // wrap the Node* in a tree object and increase reference count by one.
  return Tree<T> (root_->right (), true);
}

#endif /* _Tree_CPP */
