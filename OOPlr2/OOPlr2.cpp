#include <stdio.h>
#include <iostream>
using namespace std;

class Group {
public:
	int num;
	Group() : quantity(0), num(0) {
		cout << typeid(this).name() << " : default constuctor \n";
		show();
	}
	Group(int);
	Group(Group&);
	virtual void show() {
		cout << "num = " << num << ",  quantity = " << quantity << endl;
	}
	~Group() {
		cout << typeid(this).name() << " : destructor" << '\n';
	}
	void set(int n) {
		this->num = n;
	}
protected:
	int quantity;
};
Group::Group(int in) : quantity(in), num(num) {
	cout << typeid(this).name() << " : constructor with parametrs\n";
	show();
}
Group::Group(Group& s) : num(s.num), quantity(s.quantity) {
	cout << typeid(this).name() << " : copy constructor\n";
	show();
}


class Person : public Group {
private:
	Group* nect;
public:
	int age;
	string name;
	Person();
	Person(int);
	Person(Group&, Group&);
	int GetNum();
	~Person();
	void show() override {
		cout << "num = " << num << ", age = " << age << ", name = \"" << name << "\"" << endl;
	}
};
Person::Person() : age(0), name("") {
	quantity++;
	nect = new Group();
	cout << typeid(this).name() << " : constructor\n";
	show();
};
Person::Person(int i) : age(i), name("") {
	quantity++;
	nect = new Group(i + 1);
	cout << typeid(this).name() << " : constructor with parameters\n";
	show();
}
Person::Person(Group& t, Group& s) {
	quantity++;
	this->num = t.num + s.num;
	nect = new Group(s);
	cout << typeid(this).name() << " : copy constructor\n";
	show();
}
int Person::GetNum()
{
	return Group::num;
}
Person::~Person()
{
	delete nect;
	cout << typeid(this).name() << " : destructor" << '\n';
}


class Point {
protected:
	int x, y;
public:
	virtual void show() {
		cout << "x = " << x << ",  y = " << y << endl;
	}
	Point() : x(0), y(0) {
		cout << typeid(this).name() << " : constructor\n";
		show();
	}
	Point(int, int);
	Point(Point&);
	int DisttoStart() {
		return sqrt(x * x + y * y);
	}
	~Point() {
		cout << typeid(this).name() << " : destructor\n";
	}
};
Point::Point(int x, int y) : x(x), y(y) {
	cout << typeid(this).name() << " : constructor with parameters\n";
	show();
}
Point::Point(Point& t) :x(t.x), y(t.y) {
	cout << typeid(this).name() << " : copy constructor\n";
	show();
}

class Point3d : public Point {
private:
	int z;
	Point a;
public:
	void show() override {
		cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
	}
	Point3d() : z(0), a(0, 0) {
		cout << typeid(this).name() << " : constructor\n";
		show();
	};
	Point3d(int x, int y, int z) : a(x, y), z(z) {
		cout << typeid(this).name() << ": constructor with parameters\n";
		show();
	}
	Point3d(Point3d& b) : a(b.x, b.y), z(b.z) {
		cout << typeid(this).name() << " : copy constructor\n";
		show();
	};
	int DisttoStart3d() {
		int s = Point::DisttoStart();
		return sqrt(s * s + z * z);
	}
	~Point3d() {
		cout << typeid(this).name() << " : destructor\n";
	}
};

class Parent {
public:
	int b;
	Parent() {
		b = 0;
		cout << typeid(this).name() << " : default constuctor\n";
	}

	~Parent()
	{
		cout << typeid(this).name() << " : destructor" << '\n';
	}
};

class Kid : public Parent {
	int a;
};

int main()
{
	char choice;
	char skip;
	do {
		cout << "Select and enter the appropriate number:\n"
			"   1 - static creating of object \n"
			"   2 - dynamic creating of object\n"
			"   3 - composition\n"
			"   4 - creating an object of the parent class using the constructor of the heir class\n"
			"   5 - in the parent class there is a constructor and a destructor, and in the heir class there is neither(creating Parent)\n"
			"   6 - in the parent class there is a constructor and a destructor, and in the heir class there is neither(creating Heir)\n"
			"   q - exit\n";
		cin >> choice;
		switch (choice) {
		case '1': {
			Group group;
			break;
		}
		case '2': {
			Person* person = new Person();
			delete person;
			break;
		}
		case '3': {
			Group group;
			group.set(3);
			Group group1 = group;
			group1.set(1);
			Person person (group, group1);
			break;
		}
		case '4': {
			Point* point = new Point3d();
			break;
		}
		case '5': {
			Parent parent;
			break;
		}
		case '6': {
			Kid kid;
			break;
		}
		}
		do {
			cout << "   Enter 's' to go next:\n";
			cin >> skip;
		} while (skip != 's');
	} while (choice != 'q');
	return 0;
}
