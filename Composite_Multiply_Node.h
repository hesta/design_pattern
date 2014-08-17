/* -*- C++ -*- */
#ifndef _Composite_Multiply_Node_H
#define _Composite_Multiply_Node_H

#include "Composite_Binary_Node.h"

/**
 * @class Composite_Multiply_Node
 * @brief Defines a Binary  Multiply node derived from Binary node.
          Composite Concrete class in Composite Hierarchy.
 */

template <typename T>
class Composite_Multiply_Node : public Composite_Binary_Node<T>
{
public:
  /// Ctor
  Composite_Multiply_Node(Component_Node<T> *left = 0, 
                          Component_Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Multiply_Node();

  /// Accept method for visitor
  virtual void accept(Visitor& v);
};

#include "Composite_Multiply_Node.cpp"

#endif /*_Composite_Multiply_Node_H*/
