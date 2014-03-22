/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#ifndef _Traversal_Strategy_Impl_H
#define _Traversal_Strategy_Impl_H

// This header defines "size_t"
#include <stdlib.h>

#include <stdexcept>

#include "Tree.h"
#include "Queue.h"
#include "LQueue.h"
#include "AQueue.h"
#include "Typedefs.h"
#include "Refcounter.h"

/**
 * @class Traversal_Strategy_Impl
 * @brief This is abstract class for the strategy pattern that outlines
 *        the interface for the tree traversal strategies.
 */
class Traversal_Strategy_Impl
{
  friend class Traversal_Strategy;
  friend class Refcounter <Traversal_Strategy_Impl>; // allows refcounting

public:
  /// Unknown_Strategy class for exceptions when an unknown strategy
  /// name is passed to the make_traversal_strategy method

  class Unknown_Strategy
    {
      public:
      Unknown_Strategy(const std::string &msg)
        {
          msg_ = msg;
        }

      const std::string what(void)
        {
          return msg_;
        }
      private:
        std::string msg_;
    };

  /// Dtor - make it virtual so subclasses get cleaned up correctly.
  virtual ~Traversal_Strategy_Impl ();

  /// Method to traverse a binary tree given the root. Subclasses
  /// determine different strategies for this.
  virtual void traverse (const TREE &root) = 0;

protected:
  /// Default ctor - needed for reference counting
  Traversal_Strategy_Impl ();

  private:
  /// Reference counter
  int use_;
};

/**
 * @class Level_Order_Traversal_Strategy
 * @brief This is concrete subclass strategy for traversing in level order.
 */
class Level_Order_Traversal_Strategy : public Traversal_Strategy_Impl
{
public:
  /// Ctor
  Level_Order_Traversal_Strategy (void);

  /// Dtor
  virtual ~Level_Order_Traversal_Strategy (void);

  /// Traverses the tree in level order.
  virtual void traverse (const TREE &root);

private:
  /// Factory method to create the appropriate type of queue.
  QUEUE *make_queue_strategy (const std::string &queue_type);

  /// auto_ptr to Queue class used for level traversal.
  std::auto_ptr<QUEUE> queue_;
};

/**
 * @class Pre_Order_Traversal_Strategy
 * @brief This is concrete subclass strategy for traversing in preorder.
 */
class Pre_Order_Traversal_Strategy : public Traversal_Strategy_Impl
{
public:
  /// Method to traverse the tree in preorder.  
  virtual void traverse (const TREE &root);
};

/**
 * @class Post_Order_Traversal_Strategy
 * @brief This is concrete subclass strategy for traversing in postorder.
 */
class Post_Order_Traversal_Strategy : public Traversal_Strategy_Impl
{
public:
  /// Method to traverse the tree in postorder.
  virtual void traverse (const TREE &root);
};

/**
 * @class In_Order_Traversal_Strategy
 * @brief This is concrete subclass strategy for travesing in inorder.
 */
class In_Order_Traversal_Strategy : public Traversal_Strategy_Impl
{
public:
  /// Method to traverse the tree in inorder.  
  virtual void traverse (const TREE &root);
};

/**
 * @class Null_Traversal_Strategy
 * @brief This is a concrete subclass strategy that is a null object
 *        and is there for canonical coding
 */
class Null_Traversal_Strategy : public Traversal_Strategy_Impl
{
public:
  /// Method does nothing at all
  virtual void traverse (const TREE &root);
};


#endif /* _Traversal_Strategy_Impl_H */
