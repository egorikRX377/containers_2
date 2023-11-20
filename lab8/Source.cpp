#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>	
#include <list>
#include <memory>
#include <algorithm>
#include <functional>
#include <array>

#include <stack>
#include <queue>



using namespace std;


namespace filePATHS
{
	const string studPATH = "students.txt";
}

class Student
{
private:
	string name;
	int age;
	int course;
	double averageRating;
public:
	Student() : name("unknown"), age(-1), course(-1), averageRating(-1) {}
	Student(string name, int age, int course, double averageRating) : name(name), age(age), course(course), averageRating(averageRating) {}

	Student(const Student& other) : name(other.name), age(other.age), course(other.course), averageRating(other.averageRating) {}
	Student& operator=(const Student& other)
	{
		name = other.name;
		age = other.age;
		course = other.course;
		averageRating = other.averageRating;
		return *this;
	}
	~Student() {}
	Student(Student&& other) noexcept
	{
		name = other.name;
		age = other.age;
		course = other.course;
		averageRating = other.averageRating;

		other.name = "";
		other.age = 0;
		other.course = 0;
		other.averageRating = 0;
	}
	Student& operator=(Student&& other) noexcept
	{
		if (this != &other)
		{
			name = other.name;
			age = other.age;
			course = other.course;
			averageRating = other.averageRating;

			other.name = "";
			other.age = 0;
			other.course = 0;
			other.averageRating = 0;
		}
		return *this;
	}

	string getName() { return name; }
	int getAge() { return age; }
	int getCourse() { return course; }
	double getAverageRating() { return averageRating; }

	void setName(string name) { this->name = name; }
	void setAge(int age) { this->age = age; }
	void setCourse(int course) { this->course = course; }
	void setAverageRating(double averageRating) { this->averageRating = averageRating; }

	friend bool operator<(const shared_ptr<Student>& student1, const shared_ptr<Student>& student2)
	{
		return student1->averageRating < student2->averageRating;
	}
	friend bool operator==(const shared_ptr<Student>& student1, const shared_ptr<Student>& student2)
	{
		return student1->averageRating == student2->averageRating;
	}

	friend ostream& operator<<(ostream& buf, const shared_ptr<Student>& student)
	{
		buf << student->name << ' ' << student->age << ' ' << student->course << ' ' << student->averageRating << endl;
		return buf;
	}
	friend istream& operator>>(istream& buf, shared_ptr<Student>& student)
	{
		buf >> student->name >> student->age >> student->course >> student->averageRating;
		return buf;
	}
};

class CompareStudents
{
public:
	bool operator()(const shared_ptr<Student>& student1, const shared_ptr<Student>& student2)
	{
		if (student1->getAverageRating() > student2->getAverageRating())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	//===================================== Работа со стеком =====================================//
	shared_ptr<Student> student1 = make_shared<Student>("Егор", 18, 2, 8.5);
	shared_ptr<Student> student2 = make_shared<Student>("Пётр", 19, 3, 6.2);
	shared_ptr<Student> student3 = make_shared<Student>("Дмитрий", 20, 4, 7.1);

	shared_ptr<Student> student4 = make_shared<Student>("Павел", 20, 3, 8.9);

	vector<shared_ptr<Student>> vStudent;

	vStudent.push_back(student1);
	vStudent.push_back(student2);
	vStudent.push_back(student3);


	stack< shared_ptr<Student>, vector<shared_ptr<Student>> > studentStack(vStudent);

	studentStack.push(student4);

	cout << "Верхний элемент стека: " << studentStack.top() << endl;


	while (!studentStack.empty())
	{
		cout << studentStack.top() << endl;
		studentStack.pop();
	}


	cout << "Текущий размер стека: " << studentStack.size() << endl;
	//===================================================================================================//


	//===================================== Работа с очередью =====================================//
	queue<shared_ptr< Student>, vector<shared_ptr<Student>> > studentQueue(vStudent);

	studentQueue.push(student4);

	cout << "Первый студент в очереди: " << studentQueue.front() << endl;
	cout << "Последний студент в очереди: " << studentQueue.back() << endl;

	cout << endl;

	cout << "Вывод на экран всех студентов в очереди: " << endl;

	while (!studentQueue.empty())
	{
		cout << studentQueue.front() << endl;
		studentQueue.pop();
	}

	cout << "Текущий размер очереди: " << studentQueue.size() << endl;
	//============================================================================================================//

	//===================================== Работа с приоритетной очередью =====================================//

	priority_queue<shared_ptr<Student>, vector<shared_ptr<Student>>, CompareStudents> studentPrQueue;

	studentPrQueue.push(student1);
	studentPrQueue.push(student3);
	studentPrQueue.push(student2);

	cout << "Вывод на экран всех студентов в приоритетной очереди (компаратор по среднему баллу): " << endl;
	while (!studentPrQueue.empty())
	{
		cout << studentPrQueue.top() << endl;
		studentPrQueue.pop();
	}
	//============================================================================================================//
	return 0;
}