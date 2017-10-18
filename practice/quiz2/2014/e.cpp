#include <iostream>
#include <vector>

class A{
public:
	A() {std::cout << "construct" << std::endl;}
	A(const A&) {std::cout << "copy" << std::endl;}
};

int main(){
	std::vector<A> a;
	a.push_back(A());
	a.push_back(A());
	a.push_back(A());
	std::cout << a.size() << std::endl;
	std::cout << a.capacity() << std::endl;
}