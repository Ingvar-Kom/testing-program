#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;

void SetColor(int text, int bg);

template<int txt = 7, int bg = 0>
ostream& color(ostream& text) {
	SetColor(txt, bg);
	return text;
}