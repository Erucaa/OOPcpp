#pragma once
#include<exception>
#include<string>
#include<iostream>

template<typename T>
class Container
{
	struct Node
	{
		T value;
		Node* next;
		Node* prev;
	};
private:

	Node* m_head;
	Node* m_tail;
	std::size_t m_size;

public:

	class Iterator
	{
	private:
		Node* pointer;
	public:
		Iterator( Node* ptr)
			:pointer(ptr){}

		Iterator & operator =(const Iterator & other)
		{
			pointer = other.pointer;
			return *this;
		}
		Iterator & operator++()
		{
			if (pointer == nullptr)
				throw std::out_of_range("There is no next elemetns!");
			if (pointer->next == nullptr)
				throw std::out_of_range("There is no next elemetns!");

			pointer = pointer->next;
			return *this;
		}

		Iterator operator++(int)
		{
			if (pointer == nullptr)
				throw std::out_of_range("There is no elemetns!");
			if(pointer-> next == nullptr)
				throw std::out_of_range("There is no next elemetns!");
			Iterator returned_ptr = *this;
			pointer = pointer->next;
			return returned_ptr;

		}

		Iterator & operator--()
		{
			if (pointer == nullptr)
				throw std::out_of_range("There is no previous elements!");
			if( pointer->prev == nullptr)
				throw std::out_of_range("There is no previous elements!");

			pointer = pointer->prev;
			return *this;
		}

		Iterator operator--(int)
		{
			if (pointer == nullptr)
				throw std::out_of_range("There is no previous elements!");
			if (pointer->prev == nullptr)
				throw std::out_of_range("There is no previous elements!");
			
			Iterator returned_ptr = *this;
			pointer = pointer->prev;
			return returned_ptr;
		}

		bool operator !=( Iterator const & otherPtr) const
		{
			return pointer != otherPtr.pointer;
		}
		bool operator ==(Iterator const& otherPtr)const { return (pointer == otherPtr.pointer); }
		T& operator*()
		{
			if (pointer == nullptr)
				throw std::out_of_range("There is no previous elements!");
			return pointer->value;
		}


	};

	Container():m_head(nullptr), m_tail(nullptr),m_size(0){}
	~Container()
	{
		Erase();

	}
	
	bool Empty() { return (m_size == 0); }

	Container(const Container<T>  & otherList)
	{
		m_size = 0;
		Container<T>::Iterator it = otherList.begin();

		while (it != otherList.end())
		{
			AddToBottom(*it);
			++it;
		}

		it = nullptr;
	}

	Container & operator = (const Container<T> & otherList)
	{

		Erase();
		Container<T>::Iterator it = otherList.begin();
		while (it != otherList.end())
		{
			AddToBottom(*it);
			++it;
		}

		it = nullptr;

		return *this;
	}

	Iterator begin() const
	{
		Iterator it(m_head);
		return it;
	}
	Iterator end() const
	{
		Iterator it(m_tail);
		return it;
	}

	void PrintList()const
	{

		Container<T>::Iterator it = this->begin();

		while (it != this->end())
		{
			std::cout << *it << "->";
			++it;
		}
		std::cout << *it << std::endl;
		std::cout << std::endl;
	}

	void AddToTop(const T & new_value)
	{
		Node *new_node = new Node;
		new_node->value = new_value;
		if (Empty())
		{
			new_node->next = nullptr;
			new_node->prev = nullptr;
			m_head = m_tail = new_node;

		}
		else
		{
			new_node->prev = nullptr;
			new_node->next = m_head;
			m_head->prev = new_node;
			m_head = new_node;
		}

		++m_size;

	}

	void AddToBottom(const T & new_value)
	{
		Node *new_node = new Node;
		new_node->value = new_value;
		if (Empty())
		{
			new_node->next = nullptr;
			new_node->prev = nullptr;
			m_head = m_tail = new_node;

		}
		else
		{
			new_node->prev = m_tail;
			new_node->next = nullptr;
			m_tail->next = new_node;
			m_tail = new_node;

		}

		++m_size;
	}

	T& GetFirstValue()
	{
		if (Empty())
			throw std::out_of_range("Try to take element of empty list.");
		return m_head->value;
	}

	T& GetLastValue()
	{
		if (Empty())
			throw std::out_of_range("Try to take element of empty list.");
		return m_tail->value;
	}

	T const& GetFirstValue()const
	{
		if (Empty())
			throw std::out_of_range("Our list is empty! You can't get first value.");
		return m_head->value;
	}

	T const& GetLastValue() const
	{
		if (Empty())
			throw std::out_of_range("Our list is empty! You can't get last value.");
		return m_tail->value;
	}

	void Erase()
	{

		Node* temp = m_head;
		while (temp != nullptr) {
			temp = m_head->next;
			delete m_head;
			m_head = temp;
		}
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}

	void DeleteFirst()
	{

		if (Empty())
			return;
		if (m_size > 1)
		{
			Node *deleted_node = m_head;
			(m_head->next)->prev = nullptr;
			m_head = m_head->next;
			delete deleted_node;

			
		}
		else
		{
				delete m_head;
				m_head = nullptr;
				m_tail = nullptr;
				
		}
		--m_size;
	}

	void DeleteLast()
	{
		if (Empty())
			return;
		if (m_size > 1)
		{
			Node *deletedNode = m_tail;
			(m_tail->prev)->next = nullptr;
			m_tail = m_tail->prev;
			delete deletedNode;
			
		}
		else
		{
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
			
		}
		--m_size;
	}

	void ReverseList()
	{
		Node *it = m_head;

		while (it != nullptr)
		{
			Node * ptr = it->next;
			it->next = it->prev;
			it->prev = ptr;
			it = ptr;
		}

		it = m_head;
		m_head = m_tail;
		m_tail = it;
		m_tail->next = nullptr;
		m_head->prev = nullptr;
		

	}

	std::size_t  GetLenght() const
	{
		return m_size;
	}

};