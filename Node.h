/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Node_H
#define _Node_H

template <typename T>
class Tree;

template <typename T>
class Refcounter;

/**
 * @class Node
 * @brief Defines a very simple implementation of a binary tree node.
 */
template <typename T>
class Node
{
  /// Needed for reference counting.
  friend class Tree<T>;
  friend class Refcounter<Node<T> >;

public:
  /// Ctor
  Node (const T &item, Node<T> *left = 0, Node<T> *right = 0);

  /// Dtor
  virtual ~Node ();

  /// Return the item stored in the node.
  const T &item (void) const;

  /// Return the left child.
  Node<T> *left (void) const;

  /// Return the right child.
  Node<T> *right (void) const;

private:
  /// Item stored in the node.
  T item_;

  /// Left child.
  Node<T> *left_;

  /// Right child.
  Node<T> *right_;

  /// Reference counter
  int use_;
};

#include "Node.cpp"

#endif /* _Node_H */
