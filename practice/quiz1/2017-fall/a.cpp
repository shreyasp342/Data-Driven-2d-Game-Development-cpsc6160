#include <iostream>

void h(int z){
	++z;
}

void g(int& y){
	++y;
	h(y);
}

void f(int& x){
	++x;
	g(x);
	std::cout << x << std::endl;
}

int main(){
	int q = 7;
	f(q);
	std::cout << q << std::endl;
}