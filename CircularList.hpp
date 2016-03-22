#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

#include <memory>

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class CircularList {
public:

	typedef Alloc allocator_type;
	typedef typename Alloc::value_type value_type;
	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::difference_type difference_type;
	typedef typename Alloc::size_type size_type;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::pointer const_pointer;

	struct ListNode {
		T element_;
		pointer prev_ = nullptr;
		pointer next_ = nullptr;
	};

	class iterator {
	public:
		typedef typename Alloc::difference_type difference_type;
		typedef typename Alloc::value_type value_type;
		typedef typename Alloc::reference reference;
		typedef typename Alloc::pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;

		iterator() = default;
		iterator(ListNode* pnode) : pnode_(pnode) {}
		~iterator() = default;

		// Must have for bidirectional iterator requirements
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		reference operator*() const { return this->pnode_->element_; }
		pointer operator->() const { return &this->pnode_->element_; }

		ListNode* pnode_;
	};

	class const_iterator {
	public:
		typedef typename Alloc::difference_type difference_type;
		typedef typename Alloc::value_type value_type;
		typedef typename Alloc::const_reference reference;
		typedef typename Alloc::const_pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;

		const_iterator() = default;
		const_iterator(ListNode* pnode) : pnode_(pnode) {}
		~const_iterator() = default;

		// Must have for bidirectional iterator requirements
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);

		const_reference operator*() const { return this->pnode_->element_; }
		const_pointer operator->() const { return &this->pnode_->element_; }

		const ListNode* pnode_;
	};

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	CircularList() = default;
	~CircularList() = default;

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator crbegin() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const;
	const_reverse_iterator crend() const;

	reference front();
	const_reference front() const;

	reference back();
	const_reference back() const;

	template<class ...Args>
	iterator emplace(Args&&... args);
	iterator insert(const value_type& value);
	iterator insert(value_type&& value);

	iterator find(const value_type& value);
	iterator find(value_type&& value);

	template<class ...Args>
	void emplace_back(Args...);
	void push_back(const T&);
	void push_back(T&&);

	void pop_front();
	void pop_back();

	void erase(const value_type& value);
	void erase(value_type&& value);

	size_type size();
	size_type max_size();
	bool empty();
	size_type capacity();

protected:

	Alloc allocator_;

	Compare compare_;

private:

	ListNode* head_ = nullptr;

	ListNode* tail_ = nullptr;

	std::size_t size_ = 0;

	std::size_t capacity_ = 0;

};

//#include "CircularList.cpp"

#endif
