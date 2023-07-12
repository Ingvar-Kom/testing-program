#pragma once

#include "EXEPTION.h"
#include "color_text.h"



class Test
{

public:
	Test();
	void  Show_statistic(string log);
	void Show_statistic(string, string);
	~Test();
};

class Person
{
protected:
	string login;
	string password;
public:
	Person();
	virtual void RegisLogPas() = 0;
	virtual string GetLogin() = 0;
	virtual string GetPassword() = 0;
	virtual void Shifr(char* log) = 0;
	virtual void Deshifr(char* log) = 0;
};

class Student : public Person {
private:
	string FullName;
	string homeAdress;
	string telNumber;
	int counter;
public:
	Student();
	Student(string, string, string);
	Student(string, string);

	void   Registration();
	void   RegisLogPas();
	void   CheckRegis(string, bool);
	void   AutorizationSt(bool& flagStasus);
	void   Shifr(char* log);
	void   Deshifr(char* log);
	int    GetCount();

	string GetFullName();
	string GetLogin();
	string GetPassword();

	void   PassTest(string, string);
	void   RezultOfTest();

	friend istream& operator>>(istream& is, Student& S);
	friend ostream& operator<<(ostream& os, const Student& S);
	virtual void SaveToFile() {}
};

class Administrator : public Person {

public:
	Administrator();
	Administrator(string, string);

	void   RegisLogPas();

	string GetLogin();
	string GetPassword();

	void   AutorizationAd(bool& flagStasus);
	void   Shifr(char*);
	void   Deshifr(char*);
	void   ModifyStud();
	void   ShowDatabase();
	void   CreateStud();
	void   RemoveStud();
	void   AddCategory();
	void   AddNameTest(int, string);
	void   AddQuestion(string, string);

	friend istream& operator>>(istream& is, Administrator& Ad);
	friend ostream& operator<<(ostream& os, const Administrator& Ad);
};