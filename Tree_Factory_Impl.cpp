/* -*- C++ -*- */

/***************************************
Class: CS251
Assignment Number: 4b
Honor Pledge: I pledge that I have not recieved nor given help on this assignment.
***************************************/

#if !defined (_Tree_Factory_Impl_CPP)
#define _Tree_Factory_Impl_CPP

#include "Tree_Factory_Impl.h"
#include "Traversal_Strategy_Impl.h"

// Tree_Factory_Impl Constructor.
Tree_Factory_Impl::Tree_Factory_Impl ()
  // You fill in here.
  :use_(1)
{
}

// Tree_Factory_Impl Destructor.
Tree_Factory_Impl::~Tree_Factory_Impl ()
{
}

// Constructor.
Binary_Tree_Factory_Impl::Binary_Tree_Factory_Impl ()
{
}

// Destructor
Binary_Tree_Factory_Impl::~Binary_Tree_Factory_Impl (void)
{
}

// Constructor.
Traversal_Strategy
Binary_Tree_Factory_Impl::make_traversal_strategy (const std::string &name)
{
  // You fill in here.
  if(name == "Preorder")
    return Traversal_Strategy(new Pre_Order_Traversal_Strategy());
  else if(name == "Postorder")
    return Traversal_Strategy(new Post_Order_Traversal_Strategy());
  else if(name == "Inorder")
    return Traversal_Strategy(new In_Order_Traversal_Strategy());
  else if(name == "Levelorder")
    return Traversal_Strategy(new Level_Order_Traversal_Strategy()); 

}

// Create the binary tree.
TREE
Binary_Tree_Factory_Impl::make_tree ()
{
  //             *
  //        /         \
  //      +             -
  //    /   \         /   \
  //  1       5     7       9
  // 
  // Make/return an expression tree that matches what's shown above.
  NODE *t1 = new NODE('1');
  NODE *t2 = new NODE('5');
  NODE *t3 = new NODE('+', t1, t2);
  NODE *t4 = new NODE('7');
  NODE *t5 = new NODE('9');
  NODE *t6 = new NODE('-', t4, t5);
  TREE tree = TREE('*', t3, t6);
  return tree;

}

#endif /* _Tree_Factory_Impl_CPP */
