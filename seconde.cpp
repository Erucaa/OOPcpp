#include<iostream>
#include<algorithm>
#include <string>

class Object
{
public:
	virtual std::string toString() const = 0;	
	static int counter;
};

int Object::counter = 0;

 class Task : public virtual Object{
 public:
	 std::string toString() const
	 {
		 return "I'm a task";
	 };
	 virtual void Execute()
	 {
		 isExacute = true;
	 }
	 bool isExacute = false;
 };

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
	 int length_of_list;

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

	 Container()
	 {

		 m_head = nullptr;
		 m_tail = nullptr;
		 m_end.m_endNode = nullptr;
		 length_of_list = 0;
	 }

	 ~Container()
	 {
		 Erase();

	 }

	 Container(const Container<T>  & otherList)
	 {
		 length_of_list = 0;
		 //Node<T>* iter = otherList.m_head;
		 Container<T>::MyIterator it = otherList.begin();

		 while (it != otherList.end())
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
		 while (it != otherList.end())
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
		 if (length_of_list == 0)
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

		 ++length_of_list;

	 }


	 void AddToBottom(const T new_value)
	 {
		 Node<T> *new_node = new Node<T>;
		 new_node->value = new_value;
		 if (length_of_list == 0)
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

		 ++length_of_list;
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
		 length_of_list = 0;
	 }

	 void DeleteFirst()
	 {

		 if (length_of_list > 1)
		 {
			 Node<T> *deleted_node = m_head;
			 (m_head->next)->prev = nullptr;
			 m_head = m_head->next;
			 delete deleted_node;

			 --length_of_list;
		 }
		 else
			 Erase();
	 }

	 void DeleteLast()
	 {
		 if (length_of_list > 1)
		 {
			 Node<T> *deleted_node = m_tail;
			 (m_tail->prev)->next = nullptr;
			 m_tail = m_tail->prev;
			 delete deleted_node;
			 --length_of_list;
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
		 for (int i = 0; i < length_of_list; ++i)
		 {
			 iter2->next = iter2->prev;
			 iter2->prev = iter;

			 if (i != this->length_of_list - 1)
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



class Named : public virtual Object
{
public:
	std::string toString() const
	{
		return "I'm named object";
	};
private:
	std::string name;
};

template<typename T>
class EraseContainer : public Task
{
private:

	Container<T>* container;

public:

	std::string toString() const
	{
		if(isExacute)
			return "List was erased.";
		else
		{
			return "Task 'Erase conatiner' isn't execute yet";
		}

	};

	EraseContainer(Container<T> * list)
	{
		container = list;
		++counter;
	}

	void  Erase()
	{
		container.Erase();
	}

	void Execute()
	{
		isExacute = true;
		this->Erase();
	}
};

class AddTasktoList : public Task
{
public:
	AddTasktoList( Task added_task, Container<Task> * container)
	{
		task = added_task;
		toDoList = container;
		++counter;
	}
	std::string toString() const
	{
		if (isExacute)
			return "I'm  already add task to Container";
		else
			return "Task 'Add task to List' isn't execute.";
	}
	void Execute()
	{
		toDoList->AddToBottom(task);
		isExacute = true;
	}
private:
	Task task;
	Container<Task> *toDoList;
};


class CountContainerSize: public Task
{
public:
	CountContainerSize( Container<Task> * list)
	{
		container = list;
		++(counter);
	}

	std::string toString() const
	{
		if (isExacute)
			return "Size of container is" + std::to_string(result);
		else
			return "Task of Count Container size isn't execute yet. ";
	}

	void Execute()
	{
		result = container->GetLenght();
		isExacute = true;

	}
private:
	int result;
	Container<Task> *container;
	
};

class NamedBinaryTask : public Task,public Named
{
private:

	int result;
	std::string task_name;
	std::string my_doing;
	int argum1;
	int argum2;
	char operation_signe;

public:
	NamedBinaryTask( const char  signe,int arg1,int  arg2 ) 
	{
		operation_signe = signe;
		argum1 = arg1;
		argum2 = arg2;

		++(counter);
	};

	std::string toString() const
	{
		if(isExacute)
			return my_doing+". Result of operation : " + std::to_string(result);
		else
		{
			return " Task of NamedBinaryTask isn't execute yet.";
		}
	}

	void Execute()
	{
		
		if (operation_signe == '+')
		{
			result = argum1 + argum2;
			my_doing = "Addition of " + std::to_string(argum1) + " and " + std::to_string(argum2);
		}
		else
		{
			if (operation_signe == '-')
			{
				result = argum1 - argum2;
				my_doing = "Substraction of " + std::to_string(argum1) + " on " + std::to_string(argum2);
			}
			else
			{
				if (operation_signe == '*')
				{
					result = argum1 * argum2;
					my_doing = "Multiplication of " + std::to_string(argum1) + " and " + std::to_string(argum2);
				}
				else
				{
					if (operation_signe == '/')
					{
						result = argum1 / argum2;
						my_doing = "Division of " + std::to_string(argum1) + " on " + std::to_string(argum2);
					}
					else
					{
						result = 0;//!!!!assert
						throw "Non valid signe of operation!";
					}

				}
			}
		}
		isExacute = true;
	}
};

class CountObject : public Task
{
private:
	int numberOfObjects;
public:
	 CountObject()
	{
		 ++(counter);
		
	}
	std::string toString()
	{
		if(isExacute)
			return "I count Objects in program. Now there is "+std::to_string(numberOfObjects)+" in program. ";
		return " Task of count number of Objects in this Programm isn't execute yet. ";
	}
	void Execute()
	{
		numberOfObjects = Object::counter;
		isExacute = true;
	}
};



int main()
{
	
	try {
		Container<NamedBinaryTask> list_of_task;
		NamedBinaryTask minus('-',23,12);
		NamedBinaryTask delit('/', 24, 2);
		NamedBinaryTask mult('*', 2, 12);
		NamedBinaryTask plus('+', 12, 23);
		minus.Execute();
		std::cout << minus.toString() << std::endl;
		delit.Execute();
		plus.Execute();
		
		CountObject numberofobj;
		numberofobj.Execute();
		std::cout << numberofobj.toString() << std::endl;
		std::cout << mult.toString() << std::endl;
		mult.Execute();
		AddTasktoList add(minus,list_of_task);
		
	}
	catch (const std::exception & exc_situation)
	{
		std::cout << "You have a problem with list: " << exc_situation.what() << std::endl;

	}
	std::cout << "Great  job!";
	return 0;
}