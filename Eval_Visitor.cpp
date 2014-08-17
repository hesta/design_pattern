#if !defined (_Eval_Visitor_CPP)
#define _Eval_Visitor_CPP

#include "Component_Node.h"
#include "Leaf_Node.h"
#include "Composite_Negate_Node.h"
#include "Composite_Add_Node.h"
#include "Composite_Subtract_Node.h"
#include "Composite_Divide_Node.h"
#include "Composite_Multiply_Node.h"
#include "Tree.h"
#include "Eval_Visitor.h"

/// Ctor
template <typename T>
Post_Order_Eval_Visitor<T>::Post_Order_Eval_Visitor (void)
  :stack_()
{
  // You fill in here.
}

/// Dtor
template <typename T>
Post_Order_Eval_Visitor<T>::~Post_Order_Eval_Visitor (void)
{
  // You fill in here.
}

/// visit method for Leaf_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const LEAF_NODE& node)
{
  // You fill in here.
  stack_.push(node.item());
}

/// visit method for Composite_Negate_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const COMPOSITE_NEGATE_NODE& node)
{
  // You fill in here.
  if(!stack_.empty())
    {
      T tmp = -stack_.top();
      stack_.pop();
      stack_.push(tmp);
    }
  else 
    throw std::underflow_error("Empty stack");
}

/// visit method for Composite_Add_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const COMPOSITE_ADD_NODE& node)
{
  // You fill in here.
  if(stack_.size() < 2)
    throw std::underflow_error("Empty stack");
  else
    {
      T tmp1 = stack_.top();
      stack_.pop();
      T tmp2 = stack_.top();
      stack_.pop();
      stack_.push(tmp1 + tmp2);
    }
}

/// visit method for Composite_Subtract_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const COMPOSITE_SUBTRACT_NODE& node)
{
  // You fill in here.
  if(stack_.size() < 2)
    throw std::underflow_error("Empty stack");
  else
    {
      T tmp1 = stack_.top();
      stack_.pop();
      T tmp2 = stack_.top();
      stack_.pop();
      stack_.push(tmp2 - tmp1);
    }
}

/// visit method for Composite_Multiply_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const COMPOSITE_MULTIPLY_NODE& node)
{
  // You fill in here.
  if(stack_.size() < 2)
    throw std::underflow_error("Empty stack");
  else
    {
      T tmp1 = stack_.top();
      stack_.pop();
      T tmp2 = stack_.top();
      stack_.pop();
      stack_.push(tmp1 * tmp2);
    }
}

/// visit method for Composite_Divide_Node<int> instance
template <typename T> void
Post_Order_Eval_Visitor<T>::visit (const COMPOSITE_DIVIDE_NODE& node)
{
  // You fill in here.
  if(stack_.size() < 2)
    throw std::underflow_error("Empty stack");
  else
    {
      T tmp1 = stack_.top();
      stack_.pop();
      T tmp2 = stack_.top();
      stack_.pop();
      if(!tmp1 == 0)
	stack_.push(tmp2 / tmp1);
      else
	throw std::invalid_argument("Divide by 0 error");
    }
}

// yields the output of the visit
template <typename T> T
Post_Order_Eval_Visitor<T>::yield (void)
{
  // You fill in here.
  if(stack_.empty())
    throw std::underflow_error("Empty stack");
  else
    return stack_.top();
}

/// Ctor
template <typename T>
Pre_Order_Eval_Visitor<T>::Pre_Order_Eval_Visitor (void)
{
}

/// Dtor
template <typename T>
Pre_Order_Eval_Visitor<T>::~Pre_Order_Eval_Visitor (void)
{
}

/// visit method for Composite_Subtract_Node<int> instance
template <typename T> void
Pre_Order_Eval_Visitor<T>::visit (const COMPOSITE_SUBTRACT_NODE& node)
{
  // You fill in here.
  if (Post_Order_Eval_Visitor<T>::stack_.size() < 2)
    throw std::underflow_error("Empty stack");
  else 
    {
      T tmp1 = (Post_Order_Eval_Visitor<T>::stack_).top();
      (Post_Order_Eval_Visitor<T>::stack_).pop();
      T tmp2 = (Post_Order_Eval_Visitor<T>::stack_).top();
      (Post_Order_Eval_Visitor<T>::stack_).pop();
      (Post_Order_Eval_Visitor<T>::stack_).push(tmp1 - tmp2);
    }
}


/// visit method for Composite_Divide_Node<int> instance
template <typename T> void
Pre_Order_Eval_Visitor<T>::visit (const COMPOSITE_DIVIDE_NODE& node)
{
  // You fill in here.
  if (Post_Order_Eval_Visitor<T>::stack_.size() < 2)
    throw std::underflow_error("stack is empty");
  else 
    { 
      T tmp1 = (Post_Order_Eval_Visitor<T>::stack_).top();
      (Post_Order_Eval_Visitor<T>::stack_).pop();
      T tmp2 = (Post_Order_Eval_Visitor<T>::stack_).top();
      (Post_Order_Eval_Visitor<T>::stack_).pop();
      if(!tmp2 == 0)
	(Post_Order_Eval_Visitor<T>::stack_).push(tmp1 / tmp2);
      else
	throw std::invalid_argument("Divide by 0 error");
    }
}

#endif /* _Eval_Visitor_CPP */
