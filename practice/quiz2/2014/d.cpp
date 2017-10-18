#include <iostream>

class A{
public:
	A() {}
	virtual void print() const = 0;
	virtual void foo() const {
		std::cout << "I am foo in A" << std::endl;
	}
	void bar() const{
		std::cout << "I am bar in A" << std::endl;
	}
};

class B : public A{
public:
	B() : A() {}
	virtual void print() const {std::cout << "I am a B" << std::endl;}
	virtual void foo() const {
		std::cout << "I am foo in B" << std::endl;
	}
	void bar() const{
		std::cout << "I am bar in A" << std::endl;
	}
};

int main(){
	A* b = new B;
	b->print();
	b->foo();
	b->bar();
}