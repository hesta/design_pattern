#if !defined (_Composite_Multiply_Node_CPP)
#define _Composite_Multiply_Node_CPP

template <typename T>
Composite_Multiply_Node<T>::Composite_Multiply_Node 
(Component_Node<T> *left,Component_Node<T> *right)
  // You fill in here.
  :Composite_Binary_Node<T>(left, right)
{    
}

template <typename T>
Composite_Multiply_Node<T>::~Composite_Multiply_Node()
{
}

// Visitor.
template <typename T>
void
Composite_Multiply_Node<T>::accept (Visitor& v)
{
  // You fill in here.
  v.visit(*this);
}

#endif /*_Composite_Multiply_Node_CPP*/
