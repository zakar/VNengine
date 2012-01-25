#ifndef Reflection_Exceptions
#define Reflection_Exceptions
#include <string>


class Exception {
public:
	Exception(const char * str):msg(str){}
	~Exception(){}
	const char* what() {
		return msg.c_str();
	}
private:
	std::string msg;
};
#endif
