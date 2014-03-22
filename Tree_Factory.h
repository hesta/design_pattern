/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Tree_Factory_H
#define _Tree_Factory_H

#include <string>
#include "Tree.h"
#include "Traversal_Strategy.h"
#include "Refcounter.h"
#include "Tree_Factory_Impl.h"

/**
 * @class Tree_Factory
 * @brief Defines a bridge to the factory implementation that creates
 *        the desired tree related objects e.g., traversal strategy
 *        binary tree).
 */
class Tree_Factory
{
public:
  /// Default ctor
  Tree_Factory (void);

  /// Copy ctor - needed for reference counting.
  Tree_Factory (const Tree_Factory &f);

  /// Assignment operator - needed for reference counting.
  void operator= (const Tree_Factory &f);

  /// Dtor - Make it virtual since we subclass from this interface.
  ~Tree_Factory (void);

  // Method to create the binary tree to traverse.
  TREE make_tree (void);

  // Method to create a tree traversal strategy. Delegate it to the
  // implementation.
  Traversal_Strategy make_traversal_strategy (void);

private:
  // Pointer to actual implementation.
  Refcounter <Tree_Factory_Impl> factory_impl_;
};

#endif /* _Tree_Factory_H */
