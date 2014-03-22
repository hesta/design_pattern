#include "Options.h"
#include "LQueue.h"
#include "Traversal_Strategy.h"
#include "Tree.h"
#include "Tree_Factory.h"
#include "Typedefs.h"
#include <iostream>
#include <cstdio>

// The tree doesn't have to be balanced or full.
// Here we construct a tree that is overloaded to one side.
TREE make_leaning_tree (void)
{
  //             *
  //        /         \
  //      +             /
  //    /   \         /   \
  //  4       1     -       5
  //               / \
  //              3   5

  NODE *t1 = new NODE ('4');
  NODE *t2 = new NODE ('1');
  NODE *t3 = new NODE ('+', t1, t2);
  NODE *t4 = new NODE ('3');
  NODE *t5 = new NODE ('5');
  NODE *t6 = new NODE ('-', t4, t5);
  NODE *t7 = new NODE ('5');
  NODE *t8 = new NODE ('/', t6, t7);
  TREE tree = TREE ('*', t3, t8);

  return tree;
}

// make a default tree and 
void makeTrees(TREE * trees)
{
  // use the binary tree factory implementation for the default tree
  Binary_Tree_Factory_Impl factory;

  // make the default tree
  trees[0] = factory.make_tree ();

  // make our own leaning tree
  trees[1] = make_leaning_tree ();
}

void testTraversals(TREE * trees)
{
  std::cout << "--Testing traversal strategies--\n\n";

  Level_Order_Traversal_Strategy level_order;
  In_Order_Traversal_Strategy in_order;
  Pre_Order_Traversal_Strategy pre_order;
  Post_Order_Traversal_Strategy post_order;

  // Test the default tree

  std::cout << "  1. Testing traversals on default tree (balanced)\n\n";

  std::cout << "        Inorder should be: 1 + 5 * 7 - 9\n";
  std::cout << "                   actual: ";
  in_order.traverse (trees[0]);

  std::cout << "\n\n";

  std::cout << "      Pre order should be: * + 1 5 - 7 9\n";
  std::cout << "                   actual: ";
  pre_order.traverse (trees[0]);

  std::cout << "\n\n";

  std::cout << "     Post order should be: 1 5 + 7 9 - *\n";
  std::cout << "                   actual: ";
  post_order.traverse (trees[0]);

  std::cout << "\n\n";

  std::cout << "    Level order should be: * + - 1 5 7 9\n";
  std::cout << "                   actual: ";
  level_order.traverse (trees[0]);

  std::cout << "\n\n";

  // Test the leaning tree

  std::cout << "  2. Testing traversals on leaning tree (unbalanced)\n\n";

  std::cout << "        Inorder should be: 4 + 1 * 3 - 5 / 5\n";
  std::cout << "                   actual: ";
  in_order.traverse (trees[1]);

  std::cout << "\n\n";

  std::cout << "      Pre order should be: * + 4 1 / - 3 5 5\n";
  std::cout << "                   actual: ";
  pre_order.traverse (trees[1]);

  std::cout << "\n\n";

  std::cout << "     Post order should be: 4 1 + 3 5 - 5 / *\n";
  std::cout << "                   actual: ";
  post_order.traverse (trees[1]);

  std::cout << "\n\n";

  std::cout << "    Level order should be: * + / 4 1 - 5 3 5\n";
  std::cout << "                   actual: ";
  level_order.traverse (trees[1]);

  std::cout << "\n\n";

  std::cout << "Press enter to continue.\n";
  getchar ();

}

int 
main (int argc, char *argv[])
{
  try
    {
      std::auto_ptr <Options> o (Options::instance ());

      // Parse the command-line options. If the user requested help (via "-h"
      // or "-?") then print out the usage and return.
      if (!Options::instance ()->parse_args (argc, argv))
        return 0;

      std::cout << "--Testing options class (singleton)--\n\n";

      // Print out the options used.
      std::cout << "  traversal option: " << Options::instance ()->traversal_strategy ()
                << std::endl;
      std::cout << "  queue option: " << Options::instance ()->queue_type ()
                << std::endl << std::endl;

      // Create a factory.
      Tree_Factory factory;
      
      // Use the factory to create the tree.
      TREE root_node = factory.make_tree ();

      std::cout << "--Testing traversal strategy (context from singleton)--\n\n  ";

      // Use the factory to create desired traversal strategy.
      Traversal_Strategy traversal_strategy = factory.make_traversal_strategy ();

      // Use the specified traversal strategy to traverse the tree.
      traversal_strategy.traverse (root_node);

      std::cout << "\n\n";

      TREE trees[2];
      makeTrees(trees);
      testTraversals(trees);
    }
  catch (Traversal_Strategy_Impl::Unknown_Strategy s)
    {
      std::cerr << "exception Traversal_Strategy_Impl::Unknown_Strategy thrown: " << s.what () << std::endl;
    }
  catch (...)
    {
      std::cerr << "some exception was thrown\n";
    }
}
