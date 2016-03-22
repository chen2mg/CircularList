#include "CircularList.hpp"
/*********************** iterator *****************************************/

// pre increment
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator& CircularList<T, Compare, Alloc>::iterator::operator++() {

	if (pnode_ == nullptr)
		return nullptr;

	pnode_ = pnode_->next_;
	return *this;
}

// post increment
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::iterator::operator++(int) {
	iterator tmp(*this);
	operator++();
	return tmp;
}

// pre decrement
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator& CircularList<T, Compare, Alloc>::iterator::operator--() {

	if (pnode_ == nullptr)
		return nullptr;

	pnode_ = pnode_->prev_;
	return *this;
}

// post decrement
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::iterator::operator--(int) {
	iterator tmp(*this);
	operator--();
	return tmp;
}

/*****************************************************************************/

/**************************** const_iterator *********************************/

// pre increment
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator& CircularList<T, Compare, Alloc>::const_iterator::operator++() {

	if (pnode_ == nullptr)
		return nullptr;

	pnode_ = pnode_->next_;
	return *this;
}

// post increment
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::const_iterator::operator++(int) {
	const_iterator tmp(*this);
	operator++();
	return tmp;
}

// pre decrement
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator& CircularList<T, Compare, Alloc>::const_iterator::operator--() {

	if (pnode_ == nullptr)
		return nullptr;

	pnode_ = pnode_->prev_;
	return *this;
}

// post decrement
template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::const_iterator::operator--(int) {
	const_iterator tmp(*this);
	operator--();
	return tmp;
}

/*****************************************************************************/

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::begin() {
	iterator it(head_);
	return it;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::begin() const {
	const_iterator cit(head_);
	return cit;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::end() {
	iterator it(tail_);
	return ++it;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::cbegin() const {
	const_iterator cit(tail_);
	return ++cit;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::end() const {
	return end();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_iterator CircularList<T, Compare, Alloc>::cend() const {
	return this->end();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::reverse_iterator CircularList<T, Compare, Alloc>::rbegin() {
	return --end();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reverse_iterator CircularList<T, Compare, Alloc>::rbegin() const {
	return --end();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reverse_iterator CircularList<T, Compare, Alloc>::crbegin() const {
	return this->rbegin();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::reverse_iterator CircularList<T, Compare, Alloc>::rend() {
	return --begin();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reverse_iterator CircularList<T, Compare, Alloc>::rend() const {
	return --begin();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reverse_iterator CircularList<T, Compare, Alloc>::crend() const {
	return this->rend();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::reference CircularList<T, Compare, Alloc>::front() {
	return *begin();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reference CircularList<T, Compare, Alloc>::front() const {
	return *cbegin();
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::reference CircularList<T, Compare, Alloc>::back() {
	return *(--end());
}

template<class T,class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::const_reference CircularList<T, Compare, Alloc>::back() const {
	return *(--cend());
}

template<class T, class Compare, class Alloc>
template< class... Args >
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::emplace(Args&&... args) {

	// TODO: Handle the case where the value must be inserted somewhere other than the end

	// NOTE: compare_(a, b) is equivalent to (a < b)
	// NOTE: (!compare_(a, b) && !compare_(b, a)) is equivalent to (a == b)

	// A new ListNode should be allocated and the new value should be constructed in-place with allocator_.construct()
	// See the implementation for emplace_back() for more details

	ListNode* tmp = head_;
	ListNode* newNode = new ListNode;

	if (compare_(std::forward<Args>(args)), tmp->element_){//if the 'value' is smaller than the first element in the list
		head_->prev_ = new ListNode;
		head_->prev_->next_ = head_;
		head_ = head_->prev_;

		head_->prev = tail_;
		tail->next_ = head_;
	}
	else{
		while (compare_(tmp->element_, std::forward<Args>(args))){// insert the 'value' between elements in the list 
			tmp = tmp->next_;
		}

		tmp->prev_->next_ = newNode;
		newNode->prev_ = tmp->prev_;
		tmp->prev_ = newNode;
		newNode->next_ = tmp;
	}

	allocator_.construct(&tail_->element_, std::forward<Args>(args));

	capacity_++;
	size_++;

	// Return iterator to newly inserted element

	return iterator(newNode);;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::insert(const value_type& value) {

	// If list is empty or the last element that is currently in the list is smaller than 'value' then simply push_back
	if (empty() || compare_(tail_->element_, value)) {
		emplace_back(std::forward<Args>(args));
		return iterator(tail_);;
	}

	return emplace(value);
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::insert(value_type&& value) {

	// If list is empty or the last element that is currently in the list is smaller than 'value' then simply push_back
	if (empty() || compare_(tail_->element_, value)) {
		emplace_back(std::forward<Args>(args));
		return iterator(tail_);;
	}

	return emplace(std::move(value));
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::find(const value_type& value) {

	assert(!empty());

	ListNode* tmp = head_;
	do{
		if ((!compare_(tmp->element_, value) && !compare_(tmp->element_, value))){
			return iterator(tmp);;
		}
		tmp = tmp->next_;
	} while (tmp != tail_);
	perror("item no found");
	return NULL;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::iterator CircularList<T, Compare, Alloc>::find(value_type&& value) {
	find(std::move(value));
}


template<class T, class Compare, class Alloc>
template <class ...Args>
void CircularList<T, Compare, Alloc>::emplace_back(Args... args) {

	// end() = tail_->next_

	// If list is empty, then end() and begin() are both "nullptr"

	if (end() == begin()) { // Either empty or full, allocate more memory

		if (capacity() == 0) {
			head_ = tail_ = new ListNode();
		}
		else {
			tail_->next_ = new ListNode();
			tail_->next_->prev_ = tail_;
			tail_ = tail_->next_;
		}

		tail_->next_ = head_;
		head_->prev_ = tail_;

		capacity_++;

	}
	else {

		tail_ = tail_->next_;

	}

	// Construct object in-place
	allocator_.construct(&tail_->element_, std::forward<Args>(args));

	size_++;
}

template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::push_back(const T& new_item) {
	emplace_back(new_item);
}

template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::push_back(T&& new_item) {
	emplace_back(std::move(new_item));
}

template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::pop_front() {
	assert(!empty());

	// Must call destructor for element
	allocator_.destroy(&head_->element_);

	head_ = head_->next_;
	size_--;
}

template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::pop_back() {
	assert(!empty());

	// Must call destructor for element
	allocator_.destroy(tail_->element_);

	tail_ = tail_->prev_;
	size_--;
}



template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::erase(const T& new_item) {
	assert(!empty());

	if ((!compare_(head_->element_, new_item) && !compare_(head_->element_, new_item))){
		pop_front();
		return;
	}

	else if ((!compare_(tail_->element_, new_item) && !compare_(tail_->element_, new_item))){
		pop_back();
		return;
	}
	else{
		ListNode* tmp = head_->next_;
		while (tmp != tail_){
			if ((!compare_(tmp->element_, new_item) && !compare_(tmp->element_, new_item))){
				allocator_.destroy(tmp->element_);
				tmp->prev_->next_ = tmp->next_;
				tmp->next_->prev_ = tmp->prev_;
				size_--;
				return;
			}
			tmp = tmp->next_;
		}
	}
	else{
		perror("No such item");
	}
}


template<class T, class Compare, class Alloc>
void CircularList<T, Compare, Alloc>::erase(T&& new_item) {
	erase(std::move(new_item));
}



template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::size_type CircularList<T, Compare, Alloc>::size() {
	return num_elements_;
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::size_type CircularList<T, Compare, Alloc>::max_size() {
	return size_type(-1) / sizeof(T);
}

template<class T, class Compare, class Alloc>
bool CircularList<T, Compare, Alloc>::empty() {
	return (size_ == 0);
}

template<class T, class Compare, class Alloc>
typename CircularList<T, Compare, Alloc>::size_type CircularList<T, Compare, Alloc>::capacity() {
	return capacity_;
}

