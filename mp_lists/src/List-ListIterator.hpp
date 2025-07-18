
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }


    // Pre-Increment, ++iter.
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListNode* temp = position_;
        position_ = position_->next;
        return ListIterator(temp);
        
    }

    // Pre-Decrement, --iter
 
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1

        std::cout << position_->data;
        this->position_ = this->position_->prev;
        return *this;
    }

    // Post-Decrement, iter-- 
    ListIterator operator--(int a) {
        // @TODO: graded in mp_lists part 1
        
        ListNode* temp = position_;
        position_ = position_->prev;
        return ListIterator(temp);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        return !(*this == rhs);
    }

    bool operator==(const ListIterator& rhs) {
        return (this->position_ == rhs.position_);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
