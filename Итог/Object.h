#pragma once
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
	Object(const Object & otherObject){}
	virtual ~Object()
	{
		--counter;
	}
	virtual std::string toString() const = 0;
	static std::size_t getCount() { return counter; }

};

std::size_t Object::counter = 0;

class Task : virtual public Object
{
protected:
	bool isExecuted = false;
public:
	virtual void Execute() = 0;
};

class Named : virtual public Object
{
public:
	Named(std::string const& newName) :name(newName) {}

protected:
	std::string name;
};


class EraseContainer : public Task
{
private:

	Container<Object *> & container;

public:


	EraseContainer(Container<Object*> & list)
		:container(list) {}

	std::string toString() const
	{
		if (isExecuted)
			return std::string("List was erased.");
		else
			return std::string("Task 'Erase conatiner' isn't execute yet");
	};

	void Execute()
	{
		isExecuted = true;
		container.Erase();
	}
};

class AddTasktoList : public Task
{
public:
	AddTasktoList(Task * added_task, Container<Task*> & other_container)
		:task(added_task), container(other_container) {}

	std::string toString() const
	{
		if (isExecuted)
			return "I'm  already add task to Container";
		else
			return "Task isn't added yet.";
	}
	void Execute()
	{
		if (isExecuted)
			return;
		container.AddToBottom(task);
		isExecuted = true;
	}
private:
	Task * task;
	Container<Task*> &container;
};

class CountContainerSize : public Task
{
public:
	CountContainerSize(Container<Object *> & list)
		:container(list) {}

	std::string toString() const
	{
		if (isExecuted)
			return "Size of container is " + result;
		else
			return "Task of Count Container size isn't execute yet. ";
	}

	void Execute()
	{
		result = std::to_string(container.GetLenght());
		isExecuted = true;

	}
	std::string GetResult() 
	{
		if(isExecuted)
			return result;
		return std::string("This task isn't Execute yet!");
	}
private:
	std::string result;
	Container<Object *> &container;

};


class  ArithmeticTask : public Task, public Named
{
private:

	double result;
	int leftArgument, rightArgument;
	std::string myAction;
	char operatorSigne;
	bool zeroDivision = false;
public:
	 ArithmeticTask(std::string const& operationName, char const signe, int lArg, int rArg)
		: Named(operationName), leftArgument(lArg), rightArgument(rArg), operatorSigne(signe) {}

	std::string toString() const
	{
		if (isExecuted)
			return "Task '" + name + "': " + myAction + " Result of operation : " + std::to_string(result);
		else
		{
			if (zeroDivision)
				return std::string("Cannot execute this operation because of incorrect task!");
			return std::string("Task of  ArithmeticTask isn't execute yet.");
		}
	}

	void Execute()
	{
		if (isExecuted)
			return;
		switch (operatorSigne)
		{
		case '+':
		{
			isExecuted = true;
			result = leftArgument + rightArgument;
			myAction = "Addition of " + std::to_string(leftArgument) + " and " + std::to_string(rightArgument);
			break;
		}

		case '-':
		{
			isExecuted = true;
			result = leftArgument - rightArgument;
			myAction = "Substraction of " + std::to_string(leftArgument) + " on " + std::to_string(rightArgument);
			break;
		}

		case '*':
		{
			result = leftArgument * rightArgument;
			myAction = "Multiplication of " + std::to_string(leftArgument) + " and " + std::to_string(rightArgument);
			isExecuted = true;
			break;
		}

		case '/':
		{
			if (rightArgument == 0)
			{
				zeroDivision = true;
				break;
			}
			isExecuted = true;
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

class CountObjectTask : public Task
{
public:
	std::string toString() const
	{
		if (isExecuted)
			return std::string("I count Objects in program. Now there is " + std::to_string(Object::getCount()) + " in program. ");
		return std::string(" Task of counting quantity of Objects in this Programm isn't execute yet. ");
	}
	void Execute()
	{
		isExecuted = true;
	}
	
};
