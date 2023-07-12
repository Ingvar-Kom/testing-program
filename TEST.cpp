#include "PERSON.h"

//конструктор по умолчанию
Test::Test()
{
}
//вывод статистики
void Test::Show_statistic(string log)
{
	cout << "Введите логин:" << color<2, 0>;
	cin >> log;
	cout << color;

	Student St;
	vector <string> vec1, vec2;
	string buf_str1, buf_str2;

	int pos, counter = 0;
	log = St.GetLogin();
	ifstream fin1("Student_Entrance.txt", ios_base::in);
	try {
		if (!fin1.is_open()) {
			throw myExeption("Файл не открылся!", "ShowFromFile", 103);
			exit(1);
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	while (!fin1.eof())
	{
		getline(fin1, buf_str1);
		vec1.push_back(buf_str1);
	}
	fin1.close();
	ifstream fin2(buf_str1 + "TestResults.txt", ios_base::in);
	while (!fin2.eof())
	{
		getline(fin2, buf_str2);
		vec2.push_back(buf_str2);
		if (buf_str2.find(log) != string::npos) pos = counter;
	}
	fin2.close();

	ofstream fout2(buf_str1 + "TestResults.txt", ios_base::in);
	for (int i = 0; i < counter; i++)
	{
		if (i != pos) fout2 << vec2[i] << endl;
	}
	fout2.close();
}
//вывод статистики
void Test::Show_statistic(string SubName, string StudName) {
	system("cls");
	string buf1, buf2, pos;
	ifstream fin2(StudName + "TestResults.txt", ios_base::in);
	if (fin2.is_open()) {
		fin2 >> buf2; cout << "Тест - " << color<6, 0> << buf2 << color << endl;
		fin2 >> buf2; cout << "Тестируемый - " << color<6, 0> << StudName << color << endl;
		cout << "Правильных ответов " << color<6, 0> << buf2 << color << " на вопросы\n";
		fin2 >> buf2; cout << "Это " << color<6, 0> << buf2 << color << " %\n";
		fin2 >> buf2; cout << "Оценка - " << color<6, 0> << buf2 << color << endl << endl;
	}
	fin2.close();
	system("pause>0");
}
//деструктор
Test::~Test()
{
}