/* -*- C++ -*- */
#ifndef _Eval_Visitor_H
#define _Eval_Visitor_H

#include <stack>
#include "Visitor.h"
#include "Typedefs.h"

/**
 * @class Post_Order_Eval_Visitor is a subclass of Visitor
 * @brief Defines a Expression Evaluator - evaluates the expression represented
          by a tree in post order.
*/

template <typename T>
class Post_Order_Eval_Visitor : public Visitor
{
public:
  ///Ctor
  Post_Order_Eval_Visitor (void);

  ///Dtor
  virtual ~Post_Order_Eval_Visitor (void);
  
  /// Visit method for LEAF_NODE instances
  virtual void visit (const LEAF_NODE& node) ;

  /// Visit method for COMPOSITE_NEGATE_NODE instances
  virtual void visit (const COMPOSITE_NEGATE_NODE& node);

  /// Visit method for COMPOSITE_ADD_NODE instances
  virtual void visit (const COMPOSITE_ADD_NODE& node);

  /// Visit method for COMPOSITE_SUBTRACT_NODE instances
  virtual void visit (const COMPOSITE_SUBTRACT_NODE& node);

  /// Visit method for COMPOSITE_MULTIPLY_NODE instances
  virtual void visit (const COMPOSITE_MULTIPLY_NODE& node);

  /// Visit method for COMPOSITE_DIVIDE_NODE instances
  virtual void visit (const COMPOSITE_DIVIDE_NODE& node);

  T yield();

protected:
  std::stack<T> stack_;
};

/**
 * @class Post_Order_Eval_Visitor is a subclass of Post_Order_Eval_Visitor
 * @brief Defines a Expression Evaluator - evaluates the expression represented
          by a tree in reverse pre order.
*/

template <typename T>
class Pre_Order_Eval_Visitor : public Post_Order_Eval_Visitor<T>
{
public:

  ///Ctor
  Pre_Order_Eval_Visitor (void);

  ///Dtor
  virtual ~Pre_Order_Eval_Visitor (void);

  /// Visit method for COMPOSITE_SUBTRACT_NODE instances
  virtual void visit (const COMPOSITE_SUBTRACT_NODE& node);

  /// Visit method for COMPOSITE_DIVIDE_NODE instances
  virtual void visit (const COMPOSITE_DIVIDE_NODE& node);
};

#include "Eval_Visitor.cpp"

#endif /* _Eval_Visitor_H */
