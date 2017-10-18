#include <iostream>

class string{
public:
	string() {std::cout << "default" << std::endl;}
	string(const char*) {std::cout << "convert" << std::endl;}
	string(const string&) { std::cout << "copy" << std::endl;}
	~string() {std::cout << "destruct" << std::endl;}
	string& operator=(const string&){
		std::cout << "assign" <<std::endl;
		return *this;
	}
};

void crash(string s){}

int main(){
	string x("cat"), y = x;
	crash(y);
	string* z = new string("dog");
}