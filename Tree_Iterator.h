/* -*- C++ -*- */
#ifndef _Tree_Iterator_H
#define _Tree_Iterator_H

#include "Tree.h"
#include "Tree_Iterator_Impl.h"
#include "Refcounter.h"

/**
 * @class Tree_Iterator
 * @brief Defines a bridge to the Tree_Iterator_Impl that
 *        contains the implementation of the iterator.
 *
 */
template <typename T>
class Tree_Iterator 
{
public:
  /// Construct a Tree_Iterator 
  Tree_Iterator (Tree_Iterator_Impl<T>* impl);

  /// Copy ctor - needed for reference counting.
  Tree_Iterator (const Tree_Iterator<T> &tree_iterator);

  /// Assignment operator - needed for reference counting.
  void operator= (const Tree_Iterator<T> &tree_iterator);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  Tree<T>& operator* (void);

  /// Returns a const reference to the item contained at the current position
  const Tree<T>& operator* (void) const;

  /// Preincrement operator
  Tree_Iterator<T> &operator++ (void);

  /// Postincrement operator
  Tree_Iterator<T> operator++ (int);
  
  /// Equality operator
  bool operator== (const Tree_Iterator<T> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Tree_Iterator<T> &lhs) const;

  // = Necessary traits
  typedef std::forward_iterator_tag iterator_category;
  typedef Tree<T> value_type;
  typedef Tree<T> *pointer;
  typedef Tree<T> &reference;
  typedef int difference_type;

private:
  /// reference counted Pointer to the tree_iterator_impln.
  Refcounter <Tree_Iterator_Impl<T> > tree_iterator_impl_;
};

/**
 * @class Const_Tree_Iterator
 * @brief Defines a bridge to the Const_Tree_Iterator_Impl that
 *        actually contains the implementation of the const_iterator.
 *
 */
template <typename T>
class Const_Tree_Iterator 
{
public:
  /// Construct a Const_Tree_Iterator
  Const_Tree_Iterator (Tree_Iterator_Impl<T>* impl);

  /// Copy ctor - needed for reference counting.
  Const_Tree_Iterator (const Const_Tree_Iterator<T> &tree_iterator);

  /// Assignment operator - needed for reference counting.
  void operator= (const Const_Tree_Iterator<T> &tree_iterator);

 
  /// Returns a const reference to the item contained at the current position
  const Tree<T>& operator* (void) const;

  /// Preincrement operator
  Const_Tree_Iterator<T> &operator++ (void);

  /// Postincrement operator
  Const_Tree_Iterator<T> operator++ (int);

  
  /// Equality operator
  bool operator== (const Const_Tree_Iterator<T> &rhs) const;

  /// Nonequality operator
  bool operator!= (const Const_Tree_Iterator<T> &lhs) const;

  // = Necessary traits
  typedef std::forward_iterator_tag iterator_category;
  typedef Tree<T> value_type;
  typedef Tree<T> *pointer;
  typedef Tree<T> &reference;
  typedef int difference_type;

private:
  /// reference counted Pointer to the tree_iterator_impln.
  Refcounter <Tree_Iterator_Impl<T> > tree_iterator_impl_;
  
};

#include "Tree_Iterator.cpp"

#endif /* _Tree_Iterator_H */
