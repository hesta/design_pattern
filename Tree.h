/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Tree_H
#define _Tree_H

#include "Node.h"
#include "Refcounter.h"
#include "Typedefs.h"

/**
 * @class Tree
 * @brief Defines a bridge to the node implementation that
 *        actually contains the data items for the tree.
 */
template <typename T>
class Tree
{
public:
  /// Default ctor
  Tree ();

  /// Ctor that takes a Node<T> *.
  Tree (Node<T> *root, bool count = false);

  /// Ctor with an item to contain.
  Tree (const T &item);

  /// Ctor that takes a node and 2 children.
  Tree (const T &item, Node<T> *left, Node<T> *right);

  // Copy ctor
  Tree (const Tree &t);

  /// Assignment operator
  void operator= (const Tree &t);

  /// Dtor
  ~Tree (void);

  /// Check if tree is null tree.
  bool is_null (void) const;

  /// Return the item in the tree.
  const T &item (void) const;

  /// Return the left child.
  Tree<T> left (void) const;

  /// Return the right child.
  Tree<T> right (void) const;

private:
  /// The underlying pointer to the implementation. These are
  /// reference counted.
  Refcounter <Node<T> > root_;
};

#include "Tree.cpp"

#endif /* _Tree_H */
