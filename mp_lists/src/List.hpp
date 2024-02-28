/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    length_ = 0;
    head_ = NULL;
    tail_ = NULL;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}
/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  while (head_){
    tail_ = head_->next;
    delete head_;
    head_ = tail_;
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
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = NULL;
  if (head_ != NULL) {
    newNode -> next = head_;
    head_ -> prev = newNode;
    head_ = newNode;
    length_+=1;
  }
  if (head_ == NULL){
    head_ = newNode;
    tail_ = newNode;
    length_+=1;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  if (tail_ != NULL) {
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
    length_ += 1;
  }
  if (tail_ == NULL){
    head_ = newNode;
    tail_ = newNode;
    newNode->prev = NULL;
    length_ = 1;
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
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
  if (splitPoint < 0){splitPoint=0;}
  if (splitPoint > length_){
    return tail_->next;
  }
  for (int i = 0; i < splitPoint; i++) {
    if(curr -> next == NULL){return curr;}
    curr = curr->next;
  }
  curr->prev->next = NULL;
  curr->prev = NULL;
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (length_ == 0){
    return;
  }
  int othercount = 1;
  ListNode* temp = head_;
  ListNode* iter = head_;
  while (iter->next != NULL){
    if (othercount %2 == 0){
      temp = iter->next;
      iter->next->prev = iter->prev;
      iter->prev->next = iter->next;
      tail_->next = iter;
      iter->prev = tail_;
      tail_ = iter;
      tail_->next = NULL;
      iter = temp;
      othercount++;
      continue;
    }
    
    iter = iter->next;
    othercount++;
  }
  temp = NULL;
  iter = NULL;

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

// /**
//  * Helper function to reverse a sequence of linked memory inside a List,
//  * starting at startPoint and ending at endPoint. You are responsible for
//  * updating startPoint and endPoint to point to the new starting and ending
//  * points of the rearranged sequence of linked memory in question.
//  *
//  * @param startPoint A pointer reference to the first node in the sequence
//  *  to be reversed.
//  * @param endPoint A pointer reference to the last node in the sequence to
//  *  be reversed.
//  */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if (startPoint == endPoint){
    return;
  }


  ListNode * temp1 = startPoint;
  ListNode * temp2 = startPoint;
  ListNode * endhold = endPoint->next;

  while (temp1 !=endhold)
  {
      temp2 = temp1->prev;
      temp1->prev = temp1->next;
      temp1->next = temp2;
      temp1 = temp1->prev;
  }
  temp2 = endPoint->prev;

  if (startPoint->next != NULL){
    endPoint->prev = startPoint->next;
    startPoint->next->next = endPoint;
  }else{
    endPoint->prev = NULL;   
  }
  if(temp2 != NULL){
    startPoint->next = temp2;
    temp2->prev = startPoint;
    
  } else {
    startPoint->next = NULL;
  }
  temp1 = startPoint;
  startPoint = endPoint;
  endPoint = temp1;
  temp1 = NULL;
  temp2 = NULL;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2

  //edge case
  if (n == 1 || length_ <= 1){
    return;
  }
  //full length case
  if (n == length_){
    reverse();
  }
  //standard
  int blockcount = 0;
  int loopcount = 0;
  ListNode* temphead = head_;
  ListNode* iter = head_;
  ListNode* temptail = head_;
  while (iter != NULL){
    if(blockcount == 0){
      //reset blockcount
      if (loopcount == 1){
        head_ = temptail;
      }
      loopcount++;
      blockcount = n;
      reverse(temphead,temptail);
      //reset positions of head and tail to new starting point
      temphead = iter;
      temptail = iter;
    }
    //reverse if tail cannot be updated
    if(iter->next == NULL){
      reverse(temphead,iter);
    }
    //increment tail and iterator
    temptail = iter;
    iter = iter->next;
    blockcount--;
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
  /// @todo Graded in mp_lists part 2
  if (first == NULL){
    return second;
  }
  if (second == NULL){
    return first;
  }
  ListNode* headout = nullptr;
  ListNode* head1 = first;
  ListNode* head2 = second;
  ListNode* holder = nullptr;
  ListNode* temp = nullptr;
  while (head1!=NULL || head2!= NULL){
    //after one or the other is null (used a sort of ladder-like traversal), we will append the rest of whichever list remains onto the new list.
    if (head1 == NULL){
      temp = head2;
      head2 = NULL;
    } else if (head2 == NULL){
      temp = head1;
      head1 = NULL;
    }
    //standard section
    if(head1 != NULL && head2 != NULL){
      if(head1->data < head2->data){
        temp = head1;
        head1 = head1->next;
      } else {
        temp = head2;
        head2 = head2->next;
      }
    }
    //take care of head
    if(headout == NULL){
      headout = temp;
    } else {
      holder->next = temp;
      temp->prev = holder;
    }
    holder = temp;

  }
  

  return headout;
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
  /// @todo Graded in mp_lists part 2
   if (chainLength==1)
        return start;
    int midlength = chainLength/2;
    ListNode *rightlist = split(start,midlength);
    ListNode *leftlist = start;
    rightlist = mergesort(rightlist,chainLength-midlength);
    start = mergesort(leftlist,midlength);
    return merge(rightlist,start);
}
