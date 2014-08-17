/* -*- C++ -*- */
#ifndef _Leaf_Node_H
#define _Leaf_Node_H


#include "Component_Node.h"

/**
 * @class Leaf_Node
 * @brief Defines the leaf node of Composite Hierarchy.
 */
template <typename T>
class Leaf_Node : public Component_Node<T>
{
public:
  /// Ctor
  Leaf_Node(const T &item);

  /// Dtor
  virtual ~Leaf_Node();

  /// Accept method for visitor
  virtual void accept(Visitor& v);

  /// Return the item stored in the node.
  virtual const T &item (void) const;
  
protected:

  /// Item stored in the node.
  T item_;
};

#include "Leaf_Node.cpp"

#endif /* _Leaf_Node_H */
