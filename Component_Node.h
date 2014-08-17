/* -*- C++ -*- */
#ifndef _Component_Node_H
#define _Component_Node_H
#include <stdlib.h>
#include <stdexcept>

#include "Typedefs.h"

#include "Visitor.h"

template <typename T>
class Refcounter;

/**
 * @class Component_Node
 * @brief Defines the abstract base class of Composite Hierarchy.
 */
template <typename T>
class Component_Node
{
  /// Needed for reference counting.
  friend class Tree<T>;
  friend class Refcounter<Component_Node<T> >;

public:

  /// NoImplementation class for exceptions when there is no implementation
  class NoImplementation
  {
  public:
    NoImplementation(const std::string &msg)
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

  /// Ctor
  Component_Node();

  /// Dtor
  virtual ~Component_Node();

  /// Accept method for visitor
  virtual void accept(Visitor& v);

  /// Return the item stored in the node.
  virtual const T& item (void) const;

  /// Return the left child.
  virtual Component_Node* left (void) const;

  /// Return the right child.
  virtual Component_Node* right (void) const;
    
private:
  
  /// Reference counter
  int use_;
};

#include "Component_Node.cpp"

#endif /* _Component_Node_H */

