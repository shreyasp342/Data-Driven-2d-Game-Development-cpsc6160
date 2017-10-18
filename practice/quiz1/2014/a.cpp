#include <iostream>

void f(int x) {
	std::cout << "x is : " << x << std::endl;
	int count = 0;
	switch(x) {
		case 0: count++;
		case 1: count++;
		case 2: count++;
		case 3: count++;
		case 4: count++;
		case 5: count++;
	}
	std::cout << "count is: " << count << std::endl;
}

int main(){
	int x = 55 % 5;
	f((x ? 1:2));
	return 0;
}