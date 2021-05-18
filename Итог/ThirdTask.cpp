#include<Object.h>
#include<ctime>

int randomNumber(int min, int max)
{
	static const double dr = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand()*dr*(max - min + 1) + min);

}
Task * GenerateArithmeticTask()
{
	switch (randomNumber(1, 4))
	{
	case 1:
		return new ArithmeticTask("Add", '+', randomNumber(-250, 250), randomNumber(-250, 250));
	case 2:
		return new ArithmeticTask("Substraction", '-', randomNumber(-250, 250), randomNumber(-250, 250));
	case 3:
		return new ArithmeticTask("Multiplication", '*', randomNumber(-250, 250), randomNumber(-250, 250));
	case 4:
		return new ArithmeticTask("Division", '/', randomNumber(-250, 250), randomNumber(-250, 250));
	}

}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	Container<Task *> toDoList;
	for (int i = 0; i < 13; ++i)
	{
		AddTasktoList add(GenerateArithmeticTask(), toDoList);
		add.Execute();
	}
	
	toDoList.AddToTop(new CountObjectTask);


	Container<std::string> tasksInformation;

	while (!toDoList.Empty())
	{

		Task * task = toDoList.GetFirstValue();
		task->Execute();
		tasksInformation.AddToBottom(task->toString());
		delete task;
		toDoList.DeleteFirst();
	}

	Container<std::string>::Iterator it = tasksInformation.begin();

	while (it != tasksInformation.end())
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << *it << std::endl;
	std::cout << std::endl;

	tasksInformation.Erase();

	std::cout << Object::getCount();

	return 0;
}
