/* -*- C++ -*- */
#ifndef _Composite_Negate_Node_H
#define _Composite_Negate_Node_H


#include "Composite_Unary_Node.h"

/**
 * @class Composite_Negate_Node
 * @brief Defines a Negate node derived from Unary node.
          Composite Concrete class in Composite Hierarchy.
 */
template <typename T>
class Composite_Negate_Node : public Composite_Unary_Node<T>
{
public:
  /// Ctor
  Composite_Negate_Node(Component_Node<T>*right = 0);

  /// Dtor
  virtual ~Composite_Negate_Node();

  /// Accept method for visitor
  virtual void accept(Visitor& v);
};

#include "Composite_Negate_Node.cpp"

#endif /*_Composite_Negate_Node_H*/
