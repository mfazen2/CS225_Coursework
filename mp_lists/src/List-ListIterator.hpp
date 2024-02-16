
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        if (position_->next != NULL){
            position_ = position_->next;
        }
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        auto temp = ListIterator(position_);
        if (position_->next != NULL){
            position_ = position_->next;
        }
        return temp;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if (this->position_->prev != NULL){
            this->position_ = this->position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int a) {
        // @TODO: graded in mp_lists part 1
        auto temp = ListIterator(position_);
        for (int i = a; i > 0; i--){
            if (position_->prev != NULL)
            this->position_ = this->position_->prev;
        }
        return temp;
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        if (this->position_->data == rhs.position_->data && this->position_ == rhs.position_){
            return false;
        }
        return true;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
