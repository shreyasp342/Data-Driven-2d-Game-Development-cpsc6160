#include <iostream>

void incrCount(int count){
	count++;
}

void makeSwitch(int& count){
	switch(count){
		case 3: ++count;
		case 4: ++count;
		case 5: ++count;
		case 6: ++count;
		default: ++count;
	}
}

int main(){
	int count = 2;
	incrCount(count);
	std::cout << count << std::endl;

	count = 2;
	count = (count % 2) ? 2 : 3;
	makeSwitch(count);
	std::cout << count << std::endl;
}