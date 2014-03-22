/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Traversal_Strategy_H
#define _Traversal_Strategy_H

class Tree_Factory;

#include "Tree.h"
#include "Traversal_Strategy_Impl.h"
#include "Refcounter.h"

/**
 * @class Traversal_Strategy
 * @brief Defines a bridge to the tree traversal implementation that
 *        actually traverses the tree.
 */
class Traversal_Strategy
{
public:
  /// Ctor - the strategy needs to be allocated dynamically and Strategy
  /// will take ownership of the memory and clean it up appropriately.
  Traversal_Strategy (Traversal_Strategy_Impl *impl);

  /// Copy ctor - needed for reference counting.
  Traversal_Strategy (const Traversal_Strategy &ts);

  /// Assignment operator - needed for reference counting.
  void operator= (const Traversal_Strategy &ts);

  /// Dtor
  ~Traversal_Strategy (void);

  /// Traverse the tree.
  void traverse (const TREE &root);

private:
  /// reference counted Pointer to the strategy implementation.
  Refcounter <Traversal_Strategy_Impl> strategy_impl_;
};

#endif /* _Traversal_Strategy_H */
