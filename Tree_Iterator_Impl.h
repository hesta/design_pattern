/* -*- C++ -*- */
#ifndef _Tree_Iterator_Impl_H
#define _Tree_Iterator_Impl_H

#include "Tree.h"
#include "Queue.h"
#include "LQueue.h"
#include "AQueue.h"
#include "Typedefs.h"
#include "Refcounter.h"
#include "Options.h"
#include <stack>

/**
 * @class Tree_Iterator_Impl
 * @brief Abstract base class of the actual implementation of 
 *		  Tree_Iterator.
 *
 */
template <typename T>
class Tree_Iterator_Impl 
{
  friend class Tree_Iterator<T>;
  friend class Refcounter <Tree_Iterator_Impl<T> >; // allows refcounting
public:

  /// Unknown_Order class for exceptions when an unknown order
  /// name is passed to the begin or end methods

  class Unknown_Order
  {
  public:
    Unknown_Order(const std::string &msg)
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

  /// Default ctor - needed for reference counting, for ::end
  Tree_Iterator_Impl ();


  //Should these constructor methods be defined in the base class
  //The class is abstract

  //Constructor that takes in an entry
  Tree_Iterator_Impl (Tree<T> &tree);
  
  //Tree_Iterator_Impl(const Tree_Iterator_Impl<T>& rhs);

  virtual ~ Tree_Iterator_Impl(void);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  virtual Tree<T>& operator* (void) = 0;

  /// Returns a const reference to the item contained at the current position
  virtual const Tree<T>& operator* (void) const = 0;

  /// Preincrement operator
  virtual Tree_Iterator_Impl<T> &operator++ (void) =0;
  
  /// Equality operator
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const =0;

  /// Nonequality operator
  virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const =0;

  virtual Tree_Iterator_Impl<T>* clone(void) = 0;

  // = Necessary traits
  typedef std::forward_iterator_tag iterator_category;
  typedef Tree<T> value_type;
  typedef Tree<T> *pointer;
  typedef Tree<T> &reference;
  typedef int difference_type;


private:
  /// Reference counter
  int use_;

};

/**
 * @class Level_Order_Tree_Iterator_Impl
 * @brief Implementation of the Tree_Iterator based on 
 *		  Level_Order traversal.
 *
 */

template <typename T>
class Level_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

  /// Default ctor - needed for reference counting, for end
  Level_Order_Tree_Iterator_Impl();
  
  /// Constructor that takes in an entry
  Level_Order_Tree_Iterator_Impl (Tree<T> &tree);

  //copy
  Level_Order_Tree_Iterator_Impl(const Level_Order_Tree_Iterator_Impl<T>& rhs);

  virtual ~ Level_Order_Tree_Iterator_Impl(void);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  virtual Tree<T>& operator* (void);

  /// Returns a const reference to the item contained at the current position
  virtual const Tree<T>& operator* (void) const;

  /// Preincrement operator
  virtual Level_Order_Tree_Iterator_Impl<T>& operator++ (void);

  /// Equality operator
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  /// Nonequality operator
  virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const;

  virtual Level_Order_Tree_Iterator_Impl<T>* clone(void);

private:

  // You fill in here.
  QUEUE *
  make_queue (const std::string &queue_type)
  {
    if (queue_type == "LQueue")
      return new LQUEUE_ADAPTER (100);
    else if (queue_type == "AQueue")
      return new AQUEUE_ADAPTER (100);
    else
      throw typename Tree_Iterator_Impl<T>::Unknown_Order("must pass in LQueue AQueue");
  }

  std::unique_ptr<QUEUE> queue_;

  Tree<T> rvalue;

};

/**
 * @class Pre_Order_Tree_Iterator_Impl
 * @brief Implementation of the Tree_Iterator based on 
 *		  Pre_Order traversal.
 *
 */

template <typename T>
class Pre_Order_Tree_Iterator_Impl :public Tree_Iterator_Impl<T>
{
public:

  /// Default ctor - needed for reference counting, for end
  Pre_Order_Tree_Iterator_Impl();
  
  /// Constructor that takes in an entry
  Pre_Order_Tree_Iterator_Impl (Tree<T> &tree);

  //copy
  Pre_Order_Tree_Iterator_Impl(const Pre_Order_Tree_Iterator_Impl<T>& rhs);

  virtual ~ Pre_Order_Tree_Iterator_Impl(void);

  /// Dereference operator returns a reference to the item contained
  /// at the current position
  virtual Tree<T>& operator* (void);

  /// Returns a const reference to the item contained at the current position
  virtual const Tree<T>& operator* (void) const;

  /// Preincrement operator
  virtual Pre_Order_Tree_Iterator_Impl<T>& operator++ (void);

  /// Equality operator
  virtual bool operator== (const Tree_Iterator_Impl<T> &rhs) const;

  /// Nonequality operator
  virtual bool operator!= (const Tree_Iterator_Impl<T> &lhs) const;

  virtual Pre_Order_Tree_Iterator_Impl<T>* clone(void);
 
private:

  // You fill in here.
  std::stack<TREE> stack_;

  Tree<T> rvalue;
  

};

#include "Tree_Iterator_Impl.cpp"

#endif /* __Tree_Iterator_Impl_H */
