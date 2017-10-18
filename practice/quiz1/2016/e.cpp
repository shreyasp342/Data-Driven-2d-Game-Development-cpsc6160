#include <iostream>

class Bird{
public:
	Bird(int w) : wingSpan(w), speed(2 * wingSpan){
		std::cout << "Speed: " << speed << std::endl;
		std::cout << "Wing Span: " << wingSpan << std::endl;
	}
private:
	int speed;
	int wingSpan;
};

int main(){
	Bird robin(5);
}