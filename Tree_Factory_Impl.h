/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Tree_Factory_Impl_H
#define _Tree_Factory_Impl_H

#include <string>
#include "Tree.h"
#include "Traversal_Strategy.h"
#include "Refcounter.h"

// Forward declare needed classes
class Traversal_Strategy_Impl;

/**
 * @class Tree_Factory_Impl
 * @brief Defines a Tree Abstract Factory interface for subclasses that
 *        need to create (and delete) trees and tree traversal strategies.
 */
class Tree_Factory_Impl
{
  /// Needed for reference counting.
  friend class Tree_Factory;
  friend class Refcounter <Tree_Factory_Impl>; // allows refcounting

public:
  /// Dtor - make it virtual since we subclass from this interface.
  virtual ~Tree_Factory_Impl (void);

  /// Create the tree traversal strategy.
  virtual Traversal_Strategy make_traversal_strategy (const std::string &traversal_strategy_name) = 0;

  /// Create the binary tree to traverse.
  virtual TREE make_tree (void) = 0;

protected:
  /// Ctor - only visible to derived classes.
  Tree_Factory_Impl (void);

private:
  /// Reference counter
  int use_;
};

/**
 * @class Tree_Tree_Factory_Impl
 * @brief This is a concrete factory to create tree traversal strategies.
 */
class Binary_Tree_Factory_Impl : public Tree_Factory_Impl
{
public:
  /// Default constructor
  Binary_Tree_Factory_Impl (void);

  /// Dtor
  virtual ~Binary_Tree_Factory_Impl (void);

  /// Create the binary tree to traverse.
  virtual TREE make_tree (void);

  /// Method for tree traversal strategy.
  virtual Traversal_Strategy make_traversal_strategy (const std::string &name);
};

#endif /* _Tree_Factory_Impl_H */
