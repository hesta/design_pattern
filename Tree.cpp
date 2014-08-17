/* -*- C++ -*- */
#if !defined (_Tree_CPP)
#define _Tree_CPP

#include "Visitor.h"

// Default ctor
template <typename T>
Tree<T>::Tree ()
{
}

// Ctor take an underlying Node<T>*.
template <typename T>
Tree<T>::Tree (Component_Node<T> *root, bool count)
  : root_ (root, count)
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
    this->root_ = t.root_;//just copy the pointer to root
}

 //Equality operator
template <typename T>
bool Tree<T>::operator == (const Tree& rhs)const
{
  return (this == &rhs) || (root_.operator->() == rhs.root_.operator->());
}

  //Inequality operator
template <typename T>
bool Tree<T>::operator != (const Tree& rhs)const
{
  return !((*this) == rhs);
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

// Return the root node
template <typename T>
Component_Node<T>*
Tree<T>::get_root (void) const
{
  return root_.operator->();
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

//Accept method for the Visitor 
template <typename T>
void Tree<T>::accept(Visitor& v)
{
  // You fill in here.
  root_->accept(v);
}

 // Get an iterator that points to the beginning of the Tree 
 // based on the traversal order
template <typename T> typename Tree<T>::iterator
Tree<T>::begin(const std::string &name)
{
  // You fill in here.
  if(name == "Preorder")
    return iterator(new Pre_Order_Tree_Iterator_Impl<T>(*this));
  else if(name == "Levelorder")
    return iterator(new Level_Order_Tree_Iterator_Impl<T>(*this));
  
  //throw an exception if the traversal strategy name is unknown
  std::string errormsg = "Unknown /Not Implemented Traversal Order - ";
  errormsg += name;
  throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
}

 // Get an iterator that points to the end of the Tree 
 // based on the traversal order
template <typename T> typename Tree<T>::iterator
Tree<T>::end(const std::string &name)
{
  // You fill in here.
  if(name == "Preorder")
    return iterator(new Pre_Order_Tree_Iterator_Impl<T>());
  else if(name == "Levelorder")
    return iterator(new Level_Order_Tree_Iterator_Impl<T>());

  //throw an exception if the traversal strategy name is unknown
  std::string errormsg = "Unknown /Not Implemented Traversal Order - ";
  errormsg += name;
  throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);


}

// Get a const iterator that points to the beginning of the Tree 
// based on the traversal order
template <typename T> typename Tree<T>::const_iterator
Tree<T>::begin(const std::string &name) const
{
  // You fill in here.
  if(name == "Preorder")
    return iterator(new Pre_Order_Tree_Iterator_Impl<T>(*this));
  else if(name == "Levelorder")
    return iterator(new Level_Order_Tree_Iterator_Impl<T>(*this));
  
  //throw an exception if the traversal strategy name is unknown
  std::string errormsg = "Unknown /Not Implemented Traversal Order - ";
  errormsg += name;
  throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
}

// Get a const iterator that points to the end of the Tree 
// based on the traversal order
template <typename T> typename Tree<T>::const_iterator
Tree<T>::end(const std::string &name) const
{
  // You fill in here.
  if(name == "Preorder")
    return iterator(new Pre_Order_Tree_Iterator_Impl<T>());
  else if(name == "Levelorder")
    return iterator(new Level_Order_Tree_Iterator_Impl<T>());

  //throw an exception if the traversal strategy name is unknown
  std::string errormsg = "Unknown /Not Implemented Traversal Order - ";
  errormsg += name;
  throw typename Tree_Iterator_Impl<T>::Unknown_Order(errormsg);
}

#endif /* _Tree_CPP */
