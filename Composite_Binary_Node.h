/* -*- C++ -*- */
#ifndef _Composite_Binary_Node_H
#define _Composite_Binary_Node_H


#include "Composite_Unary_Node.h"

/**
 * @class Composite_Binary_Node
 * @brief Defines a Binary node derived from Unary node.
          Composite Abstract class in Composite Hierarchy.
 */

template <typename T>
class Composite_Binary_Node : public Composite_Unary_Node<T>
{
public:
  /// Ctor
  Composite_Binary_Node(Component_Node<T> *left = 0, 
                        Component_Node<T> *right = 0);

  /// Dtor
  virtual ~Composite_Binary_Node();

  /// Return the left child.
  virtual Component_Node<T>  *left (void) const;

protected:
  /// Left child.
  std::auto_ptr< Component_Node<T> > left_;
};

#include "Composite_Binary_Node.cpp"

#endif /*_Composite_Binary_Node_H*/
