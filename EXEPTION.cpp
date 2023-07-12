#include "EXEPTION.h"
#include "color_text.h"


myExeption::myExeption()
{
	this->message = new char[50];
	this->methodName = new char[50];
	this->codeError = 0;
}

myExeption::myExeption(const char* message, const char* methodName, int codeError)
{
	this->message = new char[strlen(message) + 1];    strcpy(this->message, message);
	this->methodName = new char[strlen(methodName) + 1]; strcpy(this->methodName, methodName);
	this->codeError = codeError;
}

myExeption::myExeption(const myExeption& obj)
{
	this->message = new char[strlen(obj.message) + 1];    strcpy(this->message, obj.message);
	this->methodName = new char[strlen(obj.methodName) + 1]; strcpy(this->methodName, obj.methodName);
	this->codeError = obj.codeError;
}

void myExeption::Show()
{
	cout << "Message" << message << endl;
	cout << "codeError" << codeError << endl;
	cout << "MethodName" << methodName << endl;
}

myExeption::~myExeption()
{
	delete[]message;
	delete[]methodName;
}