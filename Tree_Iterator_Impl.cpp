/* -*- C++ -*- */
#if !defined (_Tree_Iterator_Impl_CPP)
#define _Tree_Iterator_Impl_CPP

#include "Tree_Iterator_Impl.h"
#include <iostream>

// Size for the AQueue.
const size_t AQUEUE_SIZE = 80;

// Default ctor - needed for reference counting.
template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl ()
  : use_ (1)
{
}

template <typename T>
Tree_Iterator_Impl<T>::Tree_Iterator_Impl (Tree<T> &tree)
  : use_ (1)
{
}


// This needs to be virtual so that subclasses are correctly destroyed.
template <typename T>
Tree_Iterator_Impl<T>::~Tree_Iterator_Impl ()
{
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl()
  // You fill in here.
  :queue_(make_queue(Options::instance()->queue_type())), rvalue(0, false)
{
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl (Tree<T> &tree)
  // You fill in here.
  :queue_(make_queue(Options::instance()->queue_type())), rvalue()
{
  // You fill in here.
  if(!tree.is_null())
    {
      queue_->enqueue(tree);
      rvalue = queue_->front();
    }
}

// Ctor
template <typename T>
Level_Order_Tree_Iterator_Impl<T>::Level_Order_Tree_Iterator_Impl(
	const Level_Order_Tree_Iterator_Impl<T>& rhs)
  // You fill in here.
  :queue_(rhs.queue_->clone()), rvalue(rhs.rvalue)
{
  // You fill in here.
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>::~Level_Order_Tree_Iterator_Impl(void)
{
  //The queue is held in an auto_ptr which will call the destructor
  //when moving out of scope
}

template <typename T>
Tree<T>& Level_Order_Tree_Iterator_Impl<T>::operator* (void)
{
  // You fill in here.
  return rvalue;
}

template <typename T>
const Tree<T>& Level_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
  // You fill in here.
  return rvalue;
}

template <typename T>
Level_Order_Tree_Iterator_Impl<T>&
Level_Order_Tree_Iterator_Impl<T>::operator++ (void)
{
  // You fill in here.
  if(!queue_->is_empty())
    {
      Tree<T> temp = queue_->front();
      queue_->dequeue();
      if(!temp.left().is_null())
	queue_->enqueue(temp.left());
      if(!temp.right().is_null())
	queue_->enqueue(temp.right());

      if(!queue_->is_empty())
	rvalue = queue_->front();
      else
	rvalue = Tree<T>(0, false);
    }

  return *this;
}

/// Equality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator== (const Tree_Iterator_Impl<T> &rhs) const
{
  // You fill in here.
  return rvalue == *rhs;
}

/// Nonequality operator
template <typename T>
bool Level_Order_Tree_Iterator_Impl<T>::operator!= (const Tree_Iterator_Impl<T> &rhs) const
{
  return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Level_Order_Tree_Iterator_Impl<T>*
Level_Order_Tree_Iterator_Impl<T>::clone(void)
{
  // You fill in here.
  return new Level_Order_Tree_Iterator_Impl<T>(*this);
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl()
  // You fill in here.
  :stack_(), rvalue(0, false)
{
  // You fill in here.
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl
(Tree<T> &tree)
  // You fill in here.
  :stack_(), rvalue()
{
  // You fill in here.
  if(!tree.is_null())
    {
      stack_.push(tree); 
      rvalue = stack_.top();
    }
}

// Ctor
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::Pre_Order_Tree_Iterator_Impl(
	const Pre_Order_Tree_Iterator_Impl<T>& rhs)
  // You fill in here.
  :stack_(rhs.stack_), rvalue(rhs.rvalue)
{
  // You fill in here.
}

template <typename T>
Pre_Order_Tree_Iterator_Impl<T>::~Pre_Order_Tree_Iterator_Impl(void)
{
}

template <typename T>
Tree<T>& Pre_Order_Tree_Iterator_Impl<T>::operator* (void)
{
  // You fill in here.
  return rvalue;
}

template <typename T>
const Tree<T>& Pre_Order_Tree_Iterator_Impl<T>::operator* (void) const
{
  // You fill in here.
  return rvalue;
}

template <typename T>
Pre_Order_Tree_Iterator_Impl<T>&
Pre_Order_Tree_Iterator_Impl<T>::operator++ (void)
{
  // You fill in here.
  if(!stack_.empty())
    {
      Tree<T> temp = stack_.top();
      stack_.pop();
      if(!temp.right().is_null())
	stack_.push(temp.right());
      if(!temp.left().is_null())
	stack_.push(temp.left());

      if(!stack_.empty())
	rvalue = stack_.top();
      else
	rvalue = Tree<T>(0, false);
    }

  return *this;
  
}

/// Equality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator==
(const Tree_Iterator_Impl<T> &rhs) const
{
  // You fill in here.
  return rvalue == *rhs;
}

/// Nonequality operator
template <typename T>
bool Pre_Order_Tree_Iterator_Impl<T>::operator!=
(const Tree_Iterator_Impl<T> &rhs) const
{
  return !((*this) == rhs);//use the operator==
}

//clone for post increment in the bridge class
template <typename T>
Pre_Order_Tree_Iterator_Impl<T>*
Pre_Order_Tree_Iterator_Impl<T>::clone(void)
{
  // You fill in here.
  return new Pre_Order_Tree_Iterator_Impl<T>(*this);
}

#endif /*_Tree_Iterator_Impl_CPP */
