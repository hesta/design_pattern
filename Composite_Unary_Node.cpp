/* -*- C++ -*- */
#if !defined (_Composite_Unary_Node_CPP)
#define _Composite_Unary_Node_CPP

template <typename T>
Composite_Unary_Node<T>::Composite_Unary_Node (Component_Node<T> *right)
  // You fill in here.
  :right_(right)
{    
}

template <typename T>
Composite_Unary_Node<T>::~Composite_Unary_Node()
{
}

// Return the right child.
template <typename T>
Component_Node<T> *
Composite_Unary_Node<T>::right (void) const
{
  // You fill in here.
  return right_.get();
}

#endif /*_Composite__Unary_Node_CPP*/
