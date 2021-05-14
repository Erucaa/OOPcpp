#pragma once
#include<exception>
#include<string>
#include<iostream>
template<typename T>
struct Node
{
	T value;
	Node<T>* next;
	Node<T>* prev;
};

template<typename T>
class LastNode
{
public:
	Node<T>* m_endNode;
public:
	LastNode()
		:m_endNode(nullptr) {}
	LastNode(Node<T>* last_of_list) {
		m_endNode->next = nullptr;
		m_endNode->prev = last_of_list;
	}
};

template<typename T>
class Container
{
private:

	Node<T>* m_head;
	Node<T>* m_tail;
	LastNode<T> m_end;
	std::size_t listLength;

public:

	class MyIterator
	{
	private:
		Node<T> * pointer;
		const Container<T> * parent;
	public:
		MyIterator(const Container<T>* list, Node<T>* ptr)
			:parent(list)
			, pointer(ptr)
		{}

		MyIterator & operator =(const  Node<T>(*node))
		{
			pointer = node;
			return *this;
		}
		MyIterator & operator++()
		{
			if (pointer != parent->m_end.m_endNode)
			{
				pointer = pointer->next;
				return *this;
			}
			throw std::out_of_range("There is no next elemetns!");

		}

		MyIterator operator++(int)
		{
			if (pointer != parent->m_end.m_endNode)
			{
				MyIterator returned_ptr = *this;
				pointer = pointer->next;
				return returned_ptr;
			}
			throw std::out_of_range("There is no next elemetns!");


		}

		MyIterator & operator--()
		{
			if (pointer != parent->m_head)
			{
				pointer = pointer->prev;
				return *this;
			}
			throw std::out_of_range("There is no previous elements!");

		}

		MyIterator operator--(int)
		{
			if (pointer != parent->m_head)
			{
				MyIterator returned_ptr = *this;
				pointer = pointer->prev;
				return returned_ptr;
			}
			throw std::out_of_range("There is no previous elemetns!");
		}

		bool operator !=(const MyIterator& iterator) const
		{
			return pointer != iterator.pointer;
		}

		T operator*()
		{
			if (pointer == parent->m_end.m_endNode)
				throw std::out_of_range("You can't get value of Container.end()!");
			return pointer->value;
		}


	};

	Container():m_head(nullptr), m_tail(nullptr),listLength(0)
	{
		m_end.m_endNode = nullptr;
	}

	~Container()
	{
		Erase();

	}
	
	bool Empty() { return (listLength == 0); }

	Container(const Container<T>  & otherList)
	{
		listLength = 0;
		Container<T>::MyIterator it = otherList.begin();

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
		Container<T>::MyIterator it = otherList.begin();
		while (it != otherList.end())
		{
			AddToBottom(*it);
			++it;
		}

		it = nullptr;

		return *this;
	}

	MyIterator begin() const
	{
		MyIterator it(this, m_head);
		return it;
	}
	MyIterator end() const
	{
		MyIterator it((this), m_end.m_endNode);
		return it;
	}

	void PrintList()const
	{

		Container<T>::MyIterator it = this->begin();

		while (it != this->end())
		{
			std::cout << *it << "->";
			++it;
		}
		std::cout << std::endl;
	}

	void AddToTop(const T new_value)
	{
		Node<T> *new_node = new Node<T>;
		new_node->value = new_value;
		if (Empty())
		{
			Node<T> *end_node = new Node<T>;
			m_end.m_endNode = end_node;
			m_end.m_endNode->next = nullptr;

			new_node->next = m_end.m_endNode;
			new_node->prev = nullptr;
			m_head = new_node;
			m_tail = new_node;

			m_end.m_endNode->prev = m_tail;

		}
		else
		{
			new_node->prev = nullptr;
			new_node->next = m_head;
			m_head->prev = new_node;
			m_head = new_node;
		}

		++listLength;

	}

	void AddToBottom(const T new_value)
	{
		Node<T> *new_node = new Node<T>;
		new_node->value = new_value;
		if (Empty())
		{
			Node<T> *end_node = new Node<T>;
			m_end.m_endNode = end_node;
			m_end.m_endNode->next = nullptr;


			new_node->next = m_end.m_endNode;
			new_node->prev = nullptr;
			m_head = new_node;
			m_end.m_endNode->prev = m_tail;
			m_tail = new_node;
		}
		else
		{
			new_node->prev = m_tail;
			m_end.m_endNode->prev = new_node;
			new_node->next = m_end.m_endNode;
			m_tail->next = new_node;
			m_tail = new_node;

		}

		++listLength;
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

		Node<T>* temp = m_head;
		while (temp != m_end.m_endNode) {
			temp = m_head->next;
			delete m_head;
			m_head = temp;
		}
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_end.m_endNode = nullptr;
		listLength = 0;
	}

	void DeleteFirst()
	{

		if (Empty())
			return;
		if (listLength > 1)
		{
			Node<T> *deleted_node = m_head;
			(m_head->next)->prev = nullptr;
			m_head = m_head->next;
			delete deleted_node;

			
		}
		else
		{
				delete m_head;
				m_head = nullptr;
				m_tail = nullptr;
				m_end.m_endNode = nullptr;
		}
		--listLength;
	}

	void DeleteLast()
	{
		if (Empty())
			return;
		if (listLength > 1)
		{
			Node<T> *deletedNode = m_tail;
			(m_tail->prev)->next = nullptr;
			m_tail = m_tail->prev;
			delete deletedNode;
			
		}
		else
		{
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
			m_end.m_endNode = nullptr;
		}
		--listLength;
	}

	void ReverseList()
	{
		Node<T> *it = m_head;

		while (it != m_end.m_endNode)
		{
			Node<T> * ptr = it->next;
			it->next = it->prev;
			it->prev = ptr;
			it = ptr;
		}

		it = m_head;
		m_head = m_tail;
		m_tail = it;
		m_tail->next = m_end.m_endNode;
		m_head->prev = nullptr;
		m_end.m_endNode->prev = m_tail;

		/*Node<T> * iter2;
		iter = m_head->next;


		iter2 = m_head;
		for (int i = 0; i < listLength; ++i)
		{
			iter2->next = iter2->prev;
			iter2->prev = iter;

			if (i != this->listLength - 1)
			{
				iter2 = iter;
				iter = iter->next;
			}
			else
			{
				iter = m_head;
				m_head = m_tail;
				m_tail = iter;
				m_head->prev = nullptr;
				m_end.m_endNode->prev = m_tail;
				m_tail->next = m_end.m_endNode;
			}
		}*/
	}

	int  GetLenght() const
	{
		int lenght = 0;
		for (Container<T>::MyIterator it = this->begin(); it != this->end(); ++it)
		{
			++lenght;
		}
		return lenght;
	}

};