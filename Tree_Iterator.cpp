/* -*- C++ -*- */
#if !defined (_Tree_Iterator_CPP)
#define _Tree_Iterator_CPP

template <typename T>
Tree_Iterator<T>::Tree_Iterator(Tree_Iterator_Impl<T>* impl)
  :tree_iterator_impl_(impl)//stores the tree_iterator_impl instance
{
}

/// Copy ctor - needed for reference counting.
template <typename T>
Tree_Iterator<T>::Tree_Iterator(const Tree_Iterator<T> &rhs)
  :tree_iterator_impl_(rhs.tree_iterator_impl_)
{
}

/// Assignment operator - needed for reference counting.
template <typename T>
void Tree_Iterator<T>::operator= (const Tree_Iterator<T> &rhs)
{
  // You fill in here.
  if (this != &rhs)
    tree_iterator_impl_ = rhs.tree_iterator_impl_;
}

  /// Dereference operator returns a reference to the item contained
  /// at the current position
template <typename T>
Tree<T>& Tree_Iterator<T>::operator* (void)
{
  return (*(*tree_iterator_impl_));
}


/// Returns a const reference to the item contained at the current position
template <typename T>
const Tree<T>& Tree_Iterator<T>::operator* (void) const
{
  return (*(*tree_iterator_impl_));
}

/// Preincrement operator
template <typename T>
Tree_Iterator<T>& Tree_Iterator<T>::operator++ (void)
{
  ++(*tree_iterator_impl_);//increment on the impl

  return (*this);//return an instance with the current state
}

/// Postincrement operator
template <typename T>
Tree_Iterator<T> Tree_Iterator<T>::operator++ (int)
{
  Tree_Iterator<T> ret (*(tree_iterator_impl_->clone()));
  //perform increment
  ++(*tree_iterator_impl_);
  return ret;//return the instance before the increment
}
  
/// Equality operator
template <typename T>
bool Tree_Iterator<T>::operator== (const Tree_Iterator<T> &rhs) const
{
  return ((this ==&rhs) 
          || ((*tree_iterator_impl_)== *(rhs.tree_iterator_impl_)));
}

/// Nonequality operator
template <typename T>
bool Tree_Iterator<T>::operator!= (const Tree_Iterator<T> &rhs) const
{
  return !((*this)==rhs);
}

template <typename T>  
Const_Tree_Iterator<T>::Const_Tree_Iterator (Tree_Iterator_Impl<T>* impl)
  :tree_iterator_impl_(impl)
{
}

/// Copy ctor - needed for reference counting.
template <typename T>
Const_Tree_Iterator<T>::Const_Tree_Iterator (const Const_Tree_Iterator<T> &rhs)
  :tree_iterator_impl_(rhs.tree_iterator_impl_)//store the iterator impl
{
}

/// Assignment operator - needed for reference counting.
template <typename T>
void Const_Tree_Iterator<T>::operator= (const Const_Tree_Iterator<T> &rhs)
{
  if (this != &rhs)
    *tree_iterator_impl_ = *(rhs.tree_iterator_impl_);
}

/// Returns a const reference to the item contained at the current position
template <typename T>
const Tree<T>& Const_Tree_Iterator<T>::operator* (void) const
{
  return (*(*tree_iterator_impl_));
}

/// Preincrement operator
template <typename T>
Const_Tree_Iterator<T>& Const_Tree_Iterator<T>::operator++ (void)
{
  ++(*tree_iterator_impl_);
  return (*this);

}

/// Postincrement operator
template <typename T>
Const_Tree_Iterator<T> Const_Tree_Iterator<T>::operator++ (int)
{
  //new tree_iterator instance using the cloned copy of impl
  Tree_Iterator<T> ret = Tree_Iterator<T>(*(tree_iterator_impl_->clone()));
  //increment
  ++(*tree_iterator_impl_);
  return ret;//return instance with the previous state
}

/// Equality operator
template <typename T>
bool Const_Tree_Iterator<T>::operator== (const Const_Tree_Iterator<T> &rhs) const
{
  return ((this ==&rhs) 
          || ((*tree_iterator_impl_)==(*(rhs.tree_iterator_impl_))));
}

/// Nonequality operator
template <typename T>
bool Const_Tree_Iterator<T>::operator!= (const Const_Tree_Iterator<T> &rhs) const
{
  return !((*this)==rhs);
}

#endif //_Tree_Iterator_CPP
