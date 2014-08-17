/* -*- C++ -*- */
#ifndef _Tree_H
#define _Tree_H
#include <string>

#include "Component_Node.h"
#include "Refcounter.h"
#include "Typedefs.h"

//Forward Declaration
template <typename T>
class Tree_Iterator;

template <typename T>
class Const_Tree_Iterator;

class Visitor;

/**
 * @class Tree
 * @brief Defines a bridge to the node implementation that
 *        actually contains the data items for the tree.
 */


template <typename T>
class Tree
{
  friend class Tree_Iterator<T>;
  friend class Const_Tree_Iterator<T>;
public:
  /// Default ctor
  Tree ();

  /// Ctor that takes a Node<T> *.
  Tree (Component_Node<T> *root, bool count = false);

  // Copy ctor
  Tree (const Tree &t);

  /// Assignment operator
  void operator= (const Tree &t);

  //Equality operator
  bool operator == (const Tree& rhs)const;

  //Inequality operator
  bool operator != (const Tree& rhs)const;

  /// Dtor
  ~Tree (void);

  /// Check if tree is null tree.
  bool is_null (void) const;

  /// Return the item in the tree.
  const T &item (void) const;

  Component_Node<T>* get_root() const;

  /// Return the left child.
  Tree<T> left (void) const;

  /// Return the right child.
  Tree<T> right (void) const;

  // = Traits for the class.
  typedef T value_type;
  typedef Tree_Iterator<T> iterator;
  typedef Const_Tree_Iterator<T> const_iterator;
  
  // = Factory methods that create iterators.

  // Get an iterator that points to the beginning of the Tree 
  // based on the traversal order
  Tree_Iterator<T> begin(const std::string &traversal_order);

  // Get an iterator that points to the end of the Tree 
  // based on the traversal order
  Tree_Iterator<T> end(const std::string &traversal_order);

  // Get a const iterator that points to the beginning of the Tree 
  // based on the traversal order
  Const_Tree_Iterator<T> begin(const std::string &traversal_order) const;

  // Get a const iterator that points to the end of the Tree 
  // based on the traversal order
  Const_Tree_Iterator<T> end(const std::string &traversal_order) const;

  //Accept method for the Visitor 
  void accept(Visitor&);



private:
  /// The underlying pointer to the implementation. These are
  /// reference counted.
  Refcounter <Component_Node<T> > root_;
};

#include "Tree_Iterator.h"

#include "Tree.cpp"

#endif /* _Tree_H */
