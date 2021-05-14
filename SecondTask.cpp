
#include<Container.h>

class Object
{
protected:
	static std::size_t counter;
public:
	Object()
	{
		++counter;
	}
	virtual ~Object()
	{
		--counter;
	}
	virtual std::string toString() const = 0;
	static std::size_t getCount() { return counter; }

};

std::size_t Object::counter = 0;

class Task :  virtual public Object 
{
protected:
	bool isExacute = false;
public:
	virtual void Execute() = 0;
};

class Named : virtual public Object
{
public:

	Named(std::string const& newName):name(newName){}

protected:
	std::string name;
};

template<typename T>
class EraseContainer : public Task
{
private:

	Container<Object *> & container;

public:


	EraseContainer(Container<Object*> & list)
		:container(list){}

	std::string toString() const
	{
		if (isExacute)
			return std::string("List was erased.");
		else
			return std::string("Task 'Erase conatiner' isn't execute yet");
	};

	void Execute()
	{
		isExacute = true;
		container.Erase();
	}
};

class AddTasktoList : public Task
{
public:
	AddTasktoList(Task * added_task, Container<Task*> & container) 
		:task(added_task), m_container(container){}
	
	std::string toString() const
	{
		if (isExacute)
			return "I'm  already add task to Container";
		else
			return "Task isn't added yet.";
	}
	void Execute()
	{
		if (isExacute)
			return;
		m_container.AddToBottom(task);
		isExacute = true;
	}
private:
	Task * task;
	Container<Task*> &m_container;
};

template<typename T>
class CountContainerSize : public Task
{
public:
	CountContainerSize(Container<Object *> & list)
		:container(list){}
	
	std::string toString() const
	{
		if (isExacute)
			return "Size of container is " + std::to_string(result);
		else
			return "Task of Count Container size isn't execute yet. ";
	}

	void Execute()
	{
		result = container.GetLenght();
		isExacute = true;

	}
	int GetResult() { return result; }
private:
	std::size_t result;
	Container<Object *> &container;

};


class NamedBinaryTask : public Task, public Named
{
private:

	double result,leftArgument,rightArgument;
	std::string myAction;
	char operatorSigne;
	bool zeroDivision = false;
public:
	NamedBinaryTask(std::string const& operationName, char const signe, double lArg, double  rArg)
		: Named(operationName), leftArgument(lArg),rightArgument(rArg), operatorSigne(signe){}
	
	std::string toString() const
	{
		if (isExacute)
			return "Task '"+name + "': "+myAction+" Result of operation : " + std::to_string(result);
		else
		{
			if (zeroDivision)
				return std::string("Cannot execute this operation because of incorrect task!");
			return std::string( "Task of NamedBinaryTask isn't execute yet.");
		}
	}

	void Execute()
	{
		if (isExacute)
			return;
		switch (operatorSigne)
		{
		case '+':
		{
			isExacute = true;
			result = leftArgument + rightArgument;
			myAction = "Addition of " + std::to_string(leftArgument) + " and " + std::to_string(rightArgument);
			break;
		}
		
		case '-':
		{
			isExacute = true;
			result = leftArgument - rightArgument;
			myAction = "Substraction of " + std::to_string(leftArgument) + " on " + std::to_string(rightArgument);
			break;
		}

		case '*':
		{
			result = leftArgument * rightArgument;
			myAction = "Multiplication of " + std::to_string(leftArgument) + " and " + std::to_string(rightArgument);
			isExacute = true;
			break;
		}

		case '/':
		{
			if (rightArgument == 0)
			{
				zeroDivision = true;
				break;
			}
			isExacute = true;
			result = leftArgument / rightArgument;
			myAction = "Division of " + std::to_string(leftArgument) + " on " + std::to_string(rightArgument);
			break;
		}
		default:
			zeroDivision = true;
			break;
		}
		
	}
};

class CountObject : public Task
{
private:
	std::size_t objectsQuantity;
public:
	std::string toString()
	{
		if (isExacute)
			return std::string("I count Objects in program. Now there is " + std::to_string(objectsQuantity) + " in program. ");
		return std::string(" Task of counting quantity of Objects in this Programm isn't execute yet. ");
	}
	void Execute()
	{
		objectsQuantity = counter;
		isExacute = true;
	}

	std::size_t countObject()
	{
		if (!isExacute)
			throw std::domain_error("This task isn't Execute yet!");
		return counter;
	}
	
};

