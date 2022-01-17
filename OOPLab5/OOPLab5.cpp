#include <iostream>
using namespace std;

class BaseClass
{
public:
	BaseClass() {
		cout << "BaseClass constructor\n";
	}
	virtual ~BaseClass() {
		cout << "BaseClass destructor\n";
	}
	virtual void method1() {
		cout << "BaseClass.method1 => ";
		method2();
		method3();
	}
	void method2() {
		cout << "BaseClass.method2 => ";
	}
	virtual void method3() {
		cout << "BaseClass.method3\n";
	}
	virtual string classname()
	{
		return "BaseClass";
	}
	virtual bool isA(string str)
	{
		return (str == "BaseClass");
	}
};
class AdvancedClass : public BaseClass {
public:
	AdvancedClass() {
		cout << "AdvancedClass constructor\n";
	}
	~AdvancedClass() {
		cout << "AdvancedClass destructor\n";
	}
	
	void method2() {
		cout << "AdvancedClass.method2 => ";
	}
	virtual void method3() {
		cout << "AdvancedClass.method3\n";
	}
	virtual void method4() {
		cout << "AdvancedClass.method4\n";
	}
	virtual string classname()
	{
		return "AdvancedClass";
	}
	virtual bool isA(string str)
	{
		return(str == "AdvancedClass");
	}
};
class Base //классы с отладочными выводами для функций
{
public:
	Base()
	{
		cout << "Base\n";
	}
	Base(Base* obj)
	{
		cout << "Base by (* obj)\n";
	};

	Base(Base& obj)
	{
		cout << "Base by (& obj)\n";
	};
	~Base()
	{
		cout << "~Base\n";
	};
	void draw() {
		cout << "Base.draw\n";
	}
};
class Desc : public Base
{
public:
	Desc()
	{
		cout << "Desc\n";
	}
	Desc(Desc* obj)
	{
		cout << "Desc by (* obj)\n";
	};

	Desc(Desc& obj)
	{
		cout << "Desc by (& obj)\n";
	};

	~Desc()
	{
		cout << "~Desc\n";
	}
};
void func1(Base obj)
{
	cout << "func1 by (Base obj)\n";
};
void func2(Base* obj)
{
	cout << "func2 by (Base* obj)\n";
};
void func3(Base& obj)
{
	cout << "func3 by (Base& obj)\n";
};
Base func1()
{
	Base* bs = new Base();
	cout << "Base func1\n";
	return *bs;
};
Base* func2()
{
	Base* bs = new Base();
	cout << "Base* func2\n";
	return bs;
};
Base& func3()
{
	Base bs = new Base();
	cout << "Base& func3\n";
	return bs;
};

int main()
{
	setlocale(LC_ALL, "RU");
	cout << "Объект класса родителя\n";
	BaseClass *bc = new BaseClass();
	cout << "Объект класса потомка\n";
	AdvancedClass *ac = new AdvancedClass();
	cout << "Объект класса потомка, помещенный в переменную класса родителя\n";
	BaseClass *abc = new AdvancedClass();
	cout << "Вызов метода1 у предка и потомка, вызывеющего невиртуальный и переопрделенный\n у потомка метод2, а также виртуальный и переопрделенный метод3\n";
	bc->method1();
	ac->method1();
	cout << "Вызов невиртуального метода\n";
	bc->method2();
	cout << "\n";
	ac->method2();
	cout << "\n";
	cout << "Вызов виртуального метода\n";
	bc->method3();
	ac->method3();
	cout << "Проверки на принадлежность некоторому классу через classname\n";
	cout << "ac принадлежит классу" << ac->classname() << "\n";
	cout << "bc принадлежит классу" << bc->classname() << "\n";
	cout << "abc принадлежит классу" << abc->classname() << "\n";
	cout << "Проверки на принадлежность некоторому классу через isA\n";
	cout << "bc принадлежит классу BaseClass? " << bc->isA("BaseClass") << "\n";
	cout << "bc принадлежит классу AdvancedClass? " << bc->isA("AdvancedClass") << "\n";
	cout << "ac принадлежит классу BaseClass? " << ac->isA("BaseClass") << "\n";
	cout << "ac принадлежит классу AdvancedClass? " << ac->isA("AdvancedClass") << "\n";
	cout << "abc принадлежит классу BaseClass? " << abc->isA("BaseClass") << "\n";
	cout << "abc принадлежит классу AdvancedClass? " << abc->isA("AdvancedClass") << "\n";
	cout << "Безопасное приведение типов dynamic_cast\n";
	if (dynamic_cast<AdvancedClass*>(abc))
	{
		dynamic_cast<AdvancedClass*>(abc)->method4();
	}
	cout << "Безопасное приведение типов вручную\n";
	if (abc->isA("AdvancedClass"))
	{
		((AdvancedClass*)abc)->method4();
	}
	cout << "Удаление объекта класса родителя\n";
	delete bc;
	cout << "Удаление объекта класса потомка\n";
	delete ac;
	cout << "Удаление объекта класса потомка, помещенного в переменную класса родителя\n";
	delete abc;
	printf("Создание объектов Base и Desc\n");
	Base* base = new Base();
	Desc* desc = new Desc();
	printf("Вызов функций с параметром Base:\n");
	func1(*base);
	func2(base);
	func3(*base);
	printf("Вызов функций с параметром Desc:\n");
	func1(*desc);
	func2(desc);
	func3(*desc);
	printf("Вызов функций, которые возвращают Base:\n");
	func1();
	func2();
	func3();
	delete base;
	delete desc;
	cout << "Создание shared_ptr<Base> sptr1\n";
	shared_ptr<Base> sptr1(new Base());
	cout << "Создание shared_ptr<Base> sptr2\n";
	shared_ptr<Base> sptr2(sptr1);
	cout << "Создание unique_ptr<Base> uptr\n";
	unique_ptr<Base> uptr(new Base());
	uptr->draw();
	cout << "Выход из области видимости\n";
}
