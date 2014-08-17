/* -*- C++ -*- */
#ifndef _Composite_Subtract_Node_H
#define _Composite_Subtract_Node_H

#include "Typedefs.h"

/**
 * @class Composite_Subtract_Node
 * @brief Defines a Binary  Subtract node derived from Binary node.
          Composite Concrete class in Composite Hierarchy.
 */

template <typename T>
class Composite_Subtract_Node : public Composite_Binary_Node<T>
{
public:
  /// Ctor
  Composite_Subtract_Node(Component_Node<T> *left = 0, 
                          Component_Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Subtract_Node();

  /// Accept method for visitor
  virtual void accept(Visitor& v);
};

#include "Composite_Subtract_Node.cpp"

#endif /*_Composite_Subtract_Node_H*/
