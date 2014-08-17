// Uncomment the following line, changing it to 1 if you are a graduate student.
#define GRADUATE_STUDENT 1
#ifndef GRADUATE_STUDENT
#error You need to look at the first line of SimpleTest.cpp
#endif

#include "gtest/gtest.h"

#ifdef EXPECT_THROW
#undef EXPECT_THROW
#define EXPECT_THROW(X,Y) EXPECT_ANY_THROW(X)
#endif

#include <iostream>
#include <memory>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

// Yeah, this is dirty, but the only way to test certain error cases.
#define private public
#include "Refcounter.h"
#include "Options.h"

//# if GRADUATE_STUDENT == 1
//#  include "Traversal_Strategy.h"
//# endif

#undef private


#include "Tree.h"
#if GRADUATE_STUDENT ==1
# include "Interpreter.h"
#else
# include "Factories.h"
#endif

#include "getopt.h"
#include "Options.h"

# include "Print_Visitor.h"
# include "Eval_Visitor.h"
#include "Tree_Iterator_Impl.h"
#if GRADUATE_STUDENT == 1
//This method is not used in Assignemtn 4D
//#define MAKE_TREE Tree_Factory ().make_tree ()


struct acceptor
{
    acceptor (Visitor &v): visitor_(v) {}
    void operator () (TREE t) { t.accept (visitor_);}
    Visitor &visitor_;
};


TREE::iterator MAKE_TRAVERSAL_STRATEGY(const std::string &str)
{
  std::string tmp (Options::instance ()->traversal_strategy_);
  Options::instance ()->traversal_strategy_ = str;

  Interpreter_Context context;
  Interpreter interpreter;
  TREE tree = interpreter.interpret(context, str);
  TREE::iterator t = tree.begin (Options::instance ()->traversal_strategy ());
  Options::instance ()->traversal_strategy_ = tmp;
  return t;
}


/*
class TRAVERSAL_HOLDER : private Traversal_Strategy
{
public:
  TRAVERSAL_HOLDER (void) : Traversal_Strategy (new Null_Traversal_Strategy ()) {}
  TRAVERSAL_HOLDER (const Traversal_Strategy &s) : Traversal_Strategy (s) {}
  TRAVERSAL_HOLDER (Traversal_Strategy_Impl *s) : Traversal_Strategy (s) {}
  void reset (const Traversal_Strategy &s)
  {
    Traversal_Strategy::operator=(s);
  }

  Traversal_Strategy_Impl * get (void)
  {
    return Traversal_Strategy::strategy_impl_.ptr_;
  }
};
*/
#else
#define MAKE_TREE make_tree ()

TREE::iterator * MAKE_TRAVERSAL_STRATEGY(const std::string &str)
{
  std::string tmp (Options::instance ()->traversal_strategy_);
  Options::instance ()->traversal_strategy_ = str;
  TREE tree = MAKE_TREE;
  TREE::iterator *itr = tree.create_iterator (Options::instance ()->traversal_strategy ());
  Options::instance ()->traversal_strategy_ = tmp;
  return itr;
}

/*
#define MAKE_TRAVERSAL_STRATEGY(X) make_traversal_strategy (X)
typedef std::unique_ptr <Traversal_Strategy_Impl> TRAVERSAL_HOLDER;
*/
TREE make_leaning_tree () {
  //             +
  //        /         |
  //      *             /
  //    /   |         /   |
  //  1       3     *       9
  //               / |
  //              5   7

//Pre-Order    +*13/*579
//In-Order     1*3+5*7/9
//Post-Order   13*57*9/+
//Level-Order  +*/13*957

  COMPONENT_NODE* l1 = new LEAF_NODE(1);
  COMPONENT_NODE* l3 = new LEAF_NODE(3);
  COMPONENT_NODE* l5 = new LEAF_NODE(5);
  COMPONENT_NODE* l7 = new LEAF_NODE(7);
  COMPONENT_NODE* l9 = new LEAF_NODE(9);

  COMPONENT_NODE* b1 = new COMPOSITE_MULTIPLY_NODE (l1 , l3);
  COMPONENT_NODE* b2 = new COMPOSITE_MULTIPLY_NODE (l5 , l7);
  COMPONENT_NODE* b3 = new COMPOSITE_DIVIDE_NODE (b2, l9);
  COMPONENT_NODE* b4 = new COMPOSITE_ADD_NODE (b1 , b3);

  return TREE(b4);
}

#endif

#define RESET_OPTIONS()                         \
  do {    \
delete Options::options_impl_;                  \
Options::options_impl_ = 0;                     \
} while (0)

int argc = 5;



void cleanup_options (void)
{
  RESET_OPTIONS();
}

/*
class Appender : public virtual Visitor
{
public:
  Appender (void) {}
  virtual ~Appender (void) {}
  virtual void visit (const NODE &node)
  {
    str_ += node.item ();
  }
  std::string result (void) { return str_; }
private:
  std::string str_;
};
*/

#if GRADUATE_STUDENT == 1
bool traverseTest(TREE *tree, std::string str, Pre_Order_Eval_Visitor<int> * eval_visitor) {
    //Create buffer in which to redirect std::cout to
    std::stringstream buffer;

    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();

    std::cout.flush ();
    // Redirect cout to the stringstream buffer
    std::cout.rdbuf(buffer.rdbuf());

    try
      {
        std::vector<TREE> stack_;

        Print_Visitor print_visitor;

        ////Prof. Will's
        //    Appender app;

        // Use the STL copy() algorithm.
      std:copy(tree->begin(Options::instance ()->traversal_strategy ()), tree->end(Options::instance ()->traversal_strategy ()), back_inserter(stack_));

        // Use the STL for_each() algorithm.
        std::for_each ((stack_).rbegin (),
                       (stack_).rend (),
                       acceptor (print_visitor));

        std::for_each ((stack_).rbegin (),
                       (stack_).rend (),
                       acceptor (*eval_visitor));



        ////Prof. Will's
        //    EXPECT_EQ (app.result (), str);

        //    EXPECT_NO_THROW (strategy->traverse (*tree));
        std::cout.flush ();
        // Redirect cout back to its old self
        std::cout.rdbuf(sbuf);

        //Doubling the Reference String since we are Iterating twice through the Tree
        ////   str = str+str;

        //    std::cerr << "Full str: " << buffer.str () << std::endl;

        char c;
        //    std::cout << "\nGot traversal: ";
        for(std::string::iterator i = str.begin(); i != str.end(); i++ ) {
          c = buffer.get();

          if (c == EOF)
            {
              std::cout << std::endl << "Reached the end of input.\n";
              return false;
            }
          //        std::cout << c;
          if(*i != c) {
            std::cout<<std::endl<<"Failed Traversal For One Node.";
            std::cout<<std::endl<<"Make sure you are not printing spaces between the items in each Node.";
            std::cout<<std::endl<<"\nIn the Tree String "<<str;

            std::cout<<std::endl<<"Expected "<< *i;
            std::cout<<std::endl<<"Actual "<< c << std::endl;

            // Comment this so that students can see the whole string and debug it
            return false;
          }
        }
      }
    catch (...)
      {
        std::cout.flush ();
        // Redirect cout back to its old self
        std::cout.rdbuf(sbuf);
        throw;
      }
    return true;
}

#else
//Undergraduate

bool traverseTest(TREE::iterator *beginIter, std::string str, Pre_Order_Eval_Visitor<int> * eval_visitor) {
    //Create buffer in which to redirect std::cout to
    std::stringstream buffer;

    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();

    std::cout.flush ();
    // Redirect cout to the stringstream buffer
    std::cout.rdbuf(buffer.rdbuf());

    try
      {
        std::stack<TREE> stack_;



        for (std::auto_ptr<TREE::iterator> iter (beginIter); !iter->done (); iter->advance ())
          stack_.push(iter->current_item ());  //changed this for 4D


        Print_Visitor print_visitor;

        while (stack_.size () > 0)
          {
            TREE t = stack_.top ();
            t.accept (*eval_visitor);
            t.accept (print_visitor);
            stack_.pop ();
          }


        //    EXPECT_NO_THROW (strategy->traverse (*tree));
        std::cout.flush ();
        // Redirect cout back to its old self
        std::cout.rdbuf(sbuf);


        char c;
        //std::cout << "\nGot traversal: ";
        for(std::string::iterator i = str.begin(); i != str.end(); i++ ) {
          c = buffer.get();

          if (c == EOF)
            {
              std::cout << std::endl << "Reached the end of input.\n";
              return false;
            }
          //std::cout << c;
          if(*i != c) {
            std::cout<<std::endl<<"Failed Traversal For One Node.";
            std::cout<<std::endl<<"Make sure you are not printing spaces between the items in each Node.";
            std::cout<<std::endl<<"\nIn the Tree String "<<str;

            std::cout<<std::endl<<"Expected "<< *i;
            std::cout<<std::endl<<"Actual "<< c << std::endl;

            // Commented this so that students can see the whole string and debug it
            //return false;
          }
        }
      }
    catch (...)
      {
        std::cout.flush ();
        // Redirect cout back to its old self
        std::cout.rdbuf(sbuf);
        throw;
      }

 return true;
}
#endif

TEST(Singleton, OptionsInstance) {
   atexit (cleanup_options);
   Options *o1 = Options::instance();

   {
       Options *o2 = Options::instance();
       EXPECT_EQ(o1, o2);
   }

   Options *o3 = Options::instance();
   EXPECT_EQ(o1, o3);
}


TEST(MakeSimpleTree, DefaultQueueType) {
#if GRADUATE_STUDENT == 1
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");
#else
    TREE tree = MAKE_TREE;
#endif
}

TEST(MakeLeaningTree, DefaultQueueType) {
#if GRADUATE_STUDENT == 1
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

#else
    TREE tree = make_leaning_tree();
#endif
}

TEST(TraverseSimpleTree, DefaultQueueType) {


  EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
  EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators

    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#else
//UnderGraduate1
  TREE tree = MAKE_TREE;

    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
//    EXPECT_EQ(0, eval_visitor.yield());
#endif
}

TEST(TraverseLeaningTree, DefaultQueueType) {

  EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
  EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators

    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "759*31/*+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());

#else
//UnderGraduate2
    TREE tree = make_leaning_tree();

    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

   Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "759*31/*+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#endif

}


 TEST(BadStrategy, TraversalType)
   {
#if GRADUATE_STUDENT == 1
     EXPECT_THROW (MAKE_TRAVERSAL_STRATEGY ("Asdf"),
                   Tree_Iterator_Impl<int>::Unknown_Order);
#else
     EXPECT_THROW (MAKE_TRAVERSAL_STRATEGY ("Asdf"),
                   Unknown_Strategy);
#endif
   }

 TEST(BadStrategy, QueueType)
   {
     Options *opts = Options::instance ();
     opts->queue_type_ = "asdf";
#if GRADUATE_STUDENT == 1
     EXPECT_THROW (MAKE_TRAVERSAL_STRATEGY ("Levelorder"),
                   Tree_Iterator_Impl<int>::Unknown_Order);
#else
     EXPECT_THROW (MAKE_TRAVERSAL_STRATEGY ("Asdf"),
                   Unknown_Strategy);
#endif
}




TEST(LevelOrderSimpleTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "L", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());

#else
    TREE tree = MAKE_TREE;

    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#endif
}

TEST(LevelOrderSimpleTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "L", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());


#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());

#else
    TREE tree = MAKE_TREE;

    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "5743*-+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#endif
}



TEST(PreOrderSimpleTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "P", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Preorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "57*43-+", &eval_visitor);

    EXPECT_EQ(34, eval_visitor.yield());

#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));
    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "57*43-+", &eval_visitor);

    EXPECT_EQ(34, eval_visitor.yield());

#endif
}

TEST(PreOrderSimpleTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "P", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Preorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators

    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "57*43-+", &eval_visitor);

    EXPECT_EQ(34, eval_visitor.yield());
#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "57*43-+", &eval_visitor);

    EXPECT_EQ(34, eval_visitor.yield());

#endif
}

TEST(InOrderSimpleTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "I", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Inorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);
    EXPECT_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);

#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()), Unknown_Strategy);
#endif
}

TEST(InOrderSimpleTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "I", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Inorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());


#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);
    EXPECT_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);

#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()), Unknown_Strategy);
#endif
}

TEST(PostOrderSimpleTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "O", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Postorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);
    EXPECT_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);

#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()), Unknown_Strategy);
#endif
}

TEST(PostOrderSimpleTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "O", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Postorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "3-4+7*5");

    EXPECT_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);
    EXPECT_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()), Tree_Iterator_Impl<int>::Unknown_Order);

#else
    TREE tree = MAKE_TREE;
    TREE::iterator *itr;
    EXPECT_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()), Unknown_Strategy);
#endif
}

/************************************LEANING TREE************************************************/

TEST(LevelOrderLeaningTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "L", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "759*31/*+", &eval_visitor);
#else
    TREE tree = make_leaning_tree();
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "759*31/*+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#endif
}

TEST(LevelOrderLeaningTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "L", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Levelorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "759*31/*+", &eval_visitor);
#else
    TREE tree = make_leaning_tree();
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "759*31/*+", &eval_visitor);

//No yield() defined for Levelorder
    //EXPECT_EQ(0, eval_visitor.yield());
#endif
}


TEST(PreOrderLeaningTree, AQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "P", "-q", "A"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Preorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("AQueue", Options::instance ()->queue_type ());


#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "975*/31*+", &eval_visitor);
#else
      TREE tree = make_leaning_tree();
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "975*/31*+", &eval_visitor);

    EXPECT_EQ(6, eval_visitor.yield());
#endif
}

TEST(PreOrderLeaningTree, LQueue) {
    parsing::optind = 0;
    const char *argv[] = { "tree-traversal", "-t", "P", "-q", "L"};

    Options::instance ()->parse_args (argc, (char **)argv);

    EXPECT_EQ("Preorder", Options::instance ()->traversal_strategy ());
    EXPECT_EQ("LQueue", Options::instance ()->queue_type ());

#if GRADUATE_STUDENT == 1
//Non-const iterators
    Interpreter_Context context;
    Interpreter interpreter;
    TREE tree = interpreter.interpret(context, "1*3+5*7/9");

    EXPECT_NO_THROW(TREE::iterator itr1 = tree.begin (Options::instance ()->traversal_strategy ()));
    EXPECT_NO_THROW(TREE::iterator itr2 = tree.end (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, &tree, "975*/31*+", &eval_visitor);
#else
      TREE tree = make_leaning_tree();
    TREE::iterator *itr;
    EXPECT_NO_THROW(itr = tree.create_iterator (Options::instance ()->traversal_strategy ()));

    Pre_Order_Eval_Visitor<int> eval_visitor;

    EXPECT_PRED3(traverseTest, itr, "975*/31*+", &eval_visitor);

    EXPECT_EQ(6, eval_visitor.yield());
#endif
}
