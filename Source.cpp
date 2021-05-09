#include<iostream>
#include<algorithm>
#include <string>
#include<exception>

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
	LastNode(Node<T>* listEnding) {
		m_endNode->next = nullptr;
		m_endNode->prev = listEnding;
	}
};

template<typename T>
class Container
{
private:

	Node<T>* m_head;
	Node<T>* m_tail;
	LastNode<T> m_end;
	int listLenght;

public:

	class MyIterator
	{
	private:
		Node<T> * pointer;
		const Container<T> * parent;
	public:
		MyIterator( const Container<T>* list, Node<T>* ptr)
			:parent(list)
			,pointer(ptr)
		{}

		MyIterator & operator =(const  Node<T>(*node))
		{
			pointer = node;
			return *this;
		}
		MyIterator & operator++()
		{
			if (pointer != parent->m_end.m_endNode )
			{
				pointer = pointer->next;
				return *this;
			}
			throw std::out_of_range("There is no next elemetns!");
			
		}

		MyIterator operator++(int)
		{
			if(pointer!=parent->m_end.m_endNode )
			{
				MyIterator returnedPtr = *this;
				pointer = pointer->next;
				return returnedPtr; 
			}
			throw std::out_of_range("There is no next elemetns!");
			
			
		}

		MyIterator & operator--()
		{
			if (pointer!=parent->m_head)
			{
				pointer = pointer->prev;
				return *this;
			}
			throw std::out_of_range("There is no previous elements!");
			
		}

		MyIterator operator--(int)
		{
			if (pointer!= parent->m_head)
			{
				MyIterator returnedPtr = *this;
				pointer = pointer->prev;
				return returnedPtr;
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

	Container()
	{
		
		m_head = nullptr;
		m_tail = nullptr;
		m_end.m_endNode = nullptr;
		listLenght = 0;
	}

	~Container()
	{
		Erase();

	}

	Container(const Container<T>  & otherList)
	{
		listLenght = 0;
		//Node<T>* iter = otherList.m_head;
		Container<T>::MyIterator it = otherList.begin();

		while (it != otherList.end() )
		{
			AddToBottom(*it);
			++it;
		}


	}

	Container & operator = (const Container<T> & otherList)
	{

		Erase();
		//Node<T>* iter = otherList.m_head;
		Container<T>::MyIterator it = otherList.begin();
		while (it!=otherList.end())
		{
			AddToBottom(*it);
			++it;
		}

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
		
		while(it != this->end())
		{
			std::cout << *it << "->";
			++it;
		}
		std::cout << std::endl;
	}

	void AddToTop(const T newValue)
	{
		Node<T> *newNode = new Node<T>;
		newNode->value = newValue;
		if (listLenght == 0)
		{
			Node<T> *endNode = new Node<T>;
			m_end.m_endNode = endNode;
			m_end.m_endNode->next = nullptr;

			newNode->next = m_end.m_endNode;
			newNode->prev = nullptr;
			m_head = newNode;
			m_tail = newNode;
			m_end.m_endNode->prev = m_tail;

		}
		else
		{
			newNode->prev = nullptr;
			newNode->next = m_head;
			m_head->prev = newNode;
			m_head = newNode;
		}

		++listLenght;

	}


	void AddToBottom(const T newValue)
	{
		Node<T> *newNode = new Node<T>;
		newNode->value = newValue;
		if (listLenght == 0)
		{
			Node<T> *endNode = new Node<T>;
			m_end.m_endNode = endNode;
			m_end.m_endNode->next = nullptr;


			newNode->next = m_end.m_endNode;
			newNode->prev = nullptr;
			m_head = newNode;
			m_end.m_endNode->prev = m_tail;
			m_tail = newNode;
		}
		else
		{
			newNode->prev = m_tail;
			m_end.m_endNode->prev = newNode;
			newNode->next = m_end.m_endNode;
			m_tail->next = newNode;
			m_tail = newNode;
			
		}

		++listLenght;
	}

	T GetFirstValue()const
	{
		if (nullptr != m_head)
			return m_head->value;
		throw std::out_of_range("Our list is empty! You can't get first value.");
	}

	T GetLastValue() const
	{
		if (m_tail != nullptr)
			return m_tail->value;
		throw std::out_of_range("Our list is empty! You can't get last value.");
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
		listLenght = 0;
	}

	void DeleteFirst()
	{

		if (listLenght > 1)
		{
			Node<T> *deletedNode = m_head;
			(m_head->next)->prev = nullptr;
			m_head = m_head->next;
			delete deletedNode;

			--listLenght;
		}
		else
			Erase();
	}

	void DeleteLast()
	{
		if (listLenght > 1)
		{
			Node<T> *deletedNode = m_tail;
			(m_tail->prev)->next = nullptr;
			m_tail = m_tail->prev;
			delete deletedNode;
			--listLenght;
		}
		else
			Erase();
	}

	void ReverseList()
	{
		Node<T> *iter;
		Node<T> * iter2;
		iter = m_head->next;


		iter2 = m_head;
		for (int i = 0; i < listLenght; ++i)
		{
			iter2->next = iter2->prev;
			iter2->prev = iter;

			if (i != this->listLenght - 1)
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
		}
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



int main()
{
	Container<int> example;
	try
	{

		
		
		
		int x = 0;
		for (int i = 0; i < 3; ++i)
		{
		
			std::cin >> x;
			example.AddToBottom(x);
		}
		example.PrintList();
		example.ReverseList();
		example.PrintList();

		
	}
	catch (const std::exception & exc_situation)
	{
		std::cout << "You have a problem with list: " << exc_situation.what() << std::endl;
	}
	std::cout << "Great Job!";
}