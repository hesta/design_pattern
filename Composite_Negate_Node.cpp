/* -*- C++ -*- */
#if !defined (_Composite_Negate_Node_CPP)
#define _Composite_Negate_Node_CPP

template <typename T>
Composite_Negate_Node<T>::Composite_Negate_Node (Component_Node<T> *right)
  // You fill in here.
  :Composite_Unary_Node<T>(right)
{    
}

template <typename T>
Composite_Negate_Node<T>::~Composite_Negate_Node()
{
}

// Visitor.
template <typename T>
void
Composite_Negate_Node<T>::accept (Visitor& v)
{
  // You fill in here.
  v.visit(*this);
}

#endif /*_Composite_Negate_Node_CPP*/
