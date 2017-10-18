#include <cstring>
#include <iostream>

class string{
public:
	string(): buf(new char[1]) {buf[0] = '\0';}
	string(const char* s) : buf(new char[strlen(s)+1]) {strcpy(buf,s);}
	~string() {delete [] buf;}
	string& operator=(const string& rhs) {
		if (this == &rhs) return *this;
		delete buf;
		buf = new char[strlen(rhs.buf)+1];
		strcpy(buf, rhs.buf);
		return *this;
	}
	const char* getBuf() const {return buf;}
	void setBuf(const char* b){
		if(b == buf || b == NULL) return;
		delete [] buf;
		buf = new char[strlen(b)+1];
		strcpy(buf, b);
	}
private:
	char * buf;
	string(const string&);
};

int main(){
	string x("cat"), y;
	y = x;
	// x.setBuf("What do you wish my Thane");
	x.setBuf(x.getBuf());
	std::cout << y.getBuf() << std::endl;
}