/* -*- C++ -*- */
#if !defined (_Component_Node_CPP)
#define _Component_Node_CPP

// Ctor
template <typename T>
Component_Node<T>::Component_Node ()
  : use_ (1)
{    
}

// Dtor
template <typename T>
Component_Node<T>::~Component_Node ()
{
}

/// Return the item stored in the node.
template <typename T>
const T& 
Component_Node<T>::item (void) const
{
  //throw an exception if this method is called where it should not be
  std::string errormsg = "No implementation for Component_Node<T>::item  ";
  throw typename Component_Node<T>::NoImplementation(errormsg);
}

/// Return the left child.
template <typename T>
Component_Node<T>*
Component_Node<T>::left (void) const
{
  return 0;
}

/// Return the right child.
template <typename T>
Component_Node<T>*
Component_Node<T>::right (void) const
{
  return 0;
}

/// Return the item stored in the node.
template <typename T>
void 
Component_Node<T>::accept (Visitor& v)
{

  //throw an exception if this method is called where it should not be
  std::string errormsg = "No implementation for Component_Node<T>::accept  ";
  throw typename Component_Node<T>::NoImplementation(errormsg);
}

#endif /* _Component_Node_CPP */
















