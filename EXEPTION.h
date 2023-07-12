#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream >
#include <fstream  >
#include <iomanip  >
#include <exception>
#include <string   >
#include <windows.h>
#include <vector   >
#include <list     >
#include <algorithm>
#include <time.h   >
#include "color_text.h"


using namespace std;



class myExeption :exception
{
	char* message;
	int   codeError;
	char* methodName;
public:
	myExeption();

	myExeption(const char*, const char*, int);
	myExeption(const myExeption& obj);
	void Show();

	~myExeption();
};
