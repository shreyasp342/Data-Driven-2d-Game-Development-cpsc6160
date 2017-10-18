#include <iostream>


void f(int n){
	static int x = n;
	++x;
	std::cout << x << std::endl;
}

int main(){
	f(5%2 ? 7:8);
	f(17);
}