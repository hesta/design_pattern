/* -*- C++ -*- */
#ifndef _Typedefs_H
#define _Typedefs_H

template <typename T>
class Array;

template <typename T>
class Queue;

template <typename T, typename QUEUE>
class Queue_Adapter;

template <typename T, typename QUEUE_NODE>
class LQueue;

template <typename T>
class LQueue_Node;

template <typename T, typename ARRAY>
class AQueue;

template <typename T>
class Node;

template <typename T>
class Tree;

typedef Node<char> NODE;
typedef Tree<char> TREE;

// This part of the solution uses the Adapter pattern.  Note that
// LQUEUE_ADAPTER and AQUEUE_ADAPTER are both children of the Queue
// class.  
typedef Queue_Adapter<TREE, LQueue <TREE, LQueue_Node<TREE> > > LQUEUE_ADAPTER;
typedef Queue_Adapter<TREE, AQueue <TREE, Array<TREE> > > AQUEUE_ADAPTER;

typedef Queue<TREE> QUEUE;

#endif /* _Typedefs_H */
