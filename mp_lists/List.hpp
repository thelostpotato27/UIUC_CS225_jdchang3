/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1

  return List<T>::ListIterator(tail_ -> next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {  //all my change
  ListNode* curr = head_;
  while (curr != NULL){
    ListNode* follow = curr->next;
    delete curr;
    curr = follow;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  ListNode * tempPointer = head_;

  if(tempPointer == NULL){
    newNode -> next = NULL;
    newNode -> prev = NULL;
    head_ = newNode;
    tail_ = newNode;
  }

  newNode -> next = tempPointer;
  newNode -> prev = NULL;
  if(tempPointer != NULL){
    tempPointer -> prev = newNode;
    head_ = newNode;
  }


  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {     //all my change
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  newNode -> next = NULL;

  if(head_ == NULL){
    head_ = newNode;
    tail_ = newNode;
    newNode -> prev = NULL;
    length_++;
    return;
  }

  
  
  if(tail_ != NULL){
    tail_ -> next = newNode;
    newNode -> prev = tail_;
    tail_ = newNode;
    length_++;
    return;
  }

  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  using namespace std;
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {

    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int lengthHolder = length_ - (length_ % 3);
  lengthHolder /= 3;
  ListNode * mover = head_;
  for (int i = 0; i < lengthHolder; i++){
    if (mover -> prev != NULL){
      mover -> prev -> next = mover -> next;
    }
    mover -> next -> prev = mover -> prev;    //setting prev of next item to prev of the first item in group of 3
    mover -> prev = mover -> next -> next;    
    mover -> next = mover -> next -> next -> next;
    mover -> prev -> next = mover;
    if(mover -> next != NULL){
      mover -> next -> prev = mover;
      mover = mover -> next;
    }
  }

  while (tail_ -> next != NULL){
    tail_ = tail_ -> next;
  }
  while (head_ -> prev != NULL){
    head_ = head_ -> prev;
  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint == NULL || endPoint == NULL || startPoint == endPoint ){
    return;
  }
  
  ListNode * temphead = startPoint;
  ListNode * tempheadPrev = startPoint -> prev;
  ListNode * endNext = endPoint -> next;
  

  while(temphead != endPoint){

    ListNode * temp = temphead -> next;
    temphead -> next = temphead -> prev;
    temphead -> prev = temp;
    temphead = temp;

  }
  startPoint->next = endPoint->next;
  endPoint->next = endPoint->prev;
  endPoint->prev = tempheadPrev;
  ListNode * temp1 = startPoint;
  startPoint = endPoint;
  endPoint = temp1;


  if(endNext != NULL){
    endNext->prev = endPoint;
  }
  if(tempheadPrev != NULL){
    tempheadPrev->next = startPoint;
  }
  

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  // ListNode * temp = head_;
  // ListNode * holder = temp;
  // // ListNode * startptr = head_;



  if(n >= length_){
    reverse(head_, tail_);
    return;
  }else if(n <= 1 || length_ <= 1){
    return;
  }
  int reversable_chunk = length_ / n;
  ListNode * chunk_start = head_;
  ListNode * chunk_end = head_;

  for(int i = 0; i < reversable_chunk; i++){
    for(int j =1; j < n; j++){
      chunk_end = chunk_end->next;
    }

    if(chunk_start == head_){
      reverse(chunk_start, chunk_end);
      head_ = chunk_start;
    }else if(chunk_end == tail_){
      reverse(chunk_start, chunk_end);
      tail_ = chunk_end;
    }else{
      reverse(chunk_start, chunk_end);
    }
    
    chunk_start = chunk_end->next;
    chunk_end = chunk_start;
  }
  if(length_ % n != 0){
    reverse(chunk_start, tail_);
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  ListNode * merge_Head;
  ListNode * temp;

  if(first->data < second-> data){
    merge_Head = first;
    first = first -> next;
  }else{
    merge_Head = second;
    second = second -> next;
  }

  temp = merge_Head;

  while(first != NULL && second != NULL){
    if(first->data < second-> data){
      temp -> next = first;
      first -> prev = temp;
      first = first -> next;
    }else{
      temp -> next = second;
      second -> prev = temp;
      second = second -> next;
    }
    temp = temp->next;
  }
  if(first != NULL || second != NULL){
    if(first != NULL){
      temp -> next = first;
      first -> prev = temp;
    }else{
      temp -> next = second;
      second -> prev = temp;
    }
  }

  return merge_Head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    return start;
  }
  ListNode* midpoint = split(start, chainLength/2);
  start = mergesort(start, chainLength/2);
  midpoint = mergesort(midpoint, (chainLength/2) + (chainLength%2));
  ListNode* merged_list = merge(start, midpoint);
  return merged_list;
}
