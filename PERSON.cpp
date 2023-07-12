#include "PERSON.h"
#include "color_text.h"
//Default паролей
Person::Person()
{
	this->login = "Default login";
	this->password = "Default password";
}

//
istream& operator>>(istream& is, Student& S)
{
	is >> S.FullName >> S.homeAdress >> S.telNumber >> S.login >> S.password; return is;
}
ostream& operator<<(ostream& os, const Student& S)
{
	os << S.FullName << S.homeAdress << S.telNumber << S.login << S.password; return os;
}
//

//Default данные
Student::Student() :Person()
{
	this->FullName = "Default fullname";
	this->homeAdress = "Default homeadress";
	this->telNumber = "Default telnumber";

	int counter = 0;
}
//this данных в приватные переменные
Student::Student(string FullName, string homeAdress, string telNumber)
{
	this->FullName = FullName;
	this->homeAdress = homeAdress;
	this->telNumber = telNumber;
}
//this паролей в приватные переменные
Student::Student(const string login, const string password)
{
	this->login = login;
	this->password = password;
}
//регистрация данных студента
void   Student::Registration()
{
	system("cls");
	cout << "Введите Имя:" << color<2, 0>;
	cin >> FullName;
	cout << color << "Введите домашний адрес:" << color<2, 0>;
	cin >> homeAdress;
	cout << color << "Введите номер телефона:" << color<2, 0>;
	cin >> telNumber;
	cout << color;

	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << endl << FullName << "  " << homeAdress << "  " << telNumber;
	fout.close();
	RegisLogPas();
	system("cls");
	cout << color<8, 0> << "РЕГИСТРАЦИЯ ПРОШЛА УСПЕШНО!\n" << color;
	system("pause>0");

}
//регистрация пароля студента
void   Student::RegisLogPas()
{
	bool flag = true;
	string logUser, passUser, buf;
	system("cls");

	do
	{
		cout << "РЕГИСТРАЦИЯ\n";
		flag = true;
		cout << "Придумайте логин:" << color<2, 0>;
		cin >> logUser;
		cout << color;
		cout << "Придумайте пароль:" << color<2, 0>;
		cin >> passUser;
		cout << color;
		buf = logUser + " " + passUser;
		CheckRegis(buf, flag);
	} while (flag != true);

	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);

	ofstream fout("Student_entrance.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str << endl;
	fout.close();
}
//регистрация студента
void   Student::CheckRegis(string buf, bool flag)
{

	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);

	string buf_str, buf_str2;
	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	while (!fin.eof())
	{
		getline(fin, buf_str);

		if (str == buf_str) {
			cout << color<4, 0> << "Такой логин существует!:\n" << color;
			flag = false;
			return;
		}

	}
	fin.close();
}
//авторизация студента
void   Student::AutorizationSt(bool& flagStasus)
{
	system("cls");
	cout << "АВТОРИЗАЦИЯ:\n";
	string logUser, passUser;
	string buf_str, buf_str2;

	cout << "Логин:" << color<2, 0>;
	cin >> logUser;
	cout << color;
	cout << "Пароль:" << color<2, 0>;
	cin >> passUser;
	cout << color;

	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	buf_str2 = logUser + " " + passUser;
	bool flag = true;
	while (!fin.eof())
	{
		getline(fin, buf_str);
		char* str = new char[buf_str.size() + 1];
		strcpy(str, buf_str.c_str());
		Deshifr(str);


		if (buf_str2 == this->login) {
			system("cls");
			cout << "Student:\n";
			cout << color<8, 0> << "АВТОРИЗАЦИЯ ПРОШЛА УСПЕШНО!!\n" << color;
			system("pause>0");
			flagStasus = true;
			flag = false;
			return;
		}

	}
	if (flag == true) {
		system("cls");
		cout << color<4, 0> << "НЕВЕРНЫЙ ЛОГИН ИЛИ ПАРОЛЬ, возожно следует зарегистрироваться!\n" << color;
		system("pause>0");
		flagStasus = false;
	}
	fin.close();
}
//шифрование
void   Student::Shifr(char* log)
{
	int key = 3;

	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] += key;
	}
}
//дешифровка
void   Student::Deshifr(char* log)
{
	int key = 3;
	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')log[i] -= key;
	}
	this->login = string(log);
}
//counter
int    Student::GetCount() { return counter; }
//имя
string Student::GetFullName() { return FullName; }
//логин
string Student::GetLogin() { return login; }
//пароль
string Student::GetPassword() { return password; }
//тестирование
void   Student::PassTest(string SubName, string numName)
{
	system("cls");
	string buf, all_answers;
	char answer;
	int i = 0;
	ifstream fin1(SubName + numName + "_question.txt", ios_base::in);
	ifstream fin2(SubName + numName + "_answer.txt", ios_base::in);
	ifstream fin3(SubName + numName + "_correct_answer.txt", ios_base::in);
	while (!fin1.eof() && !fin2.eof() && !fin3.eof())
	{
		getline(fin1, buf);

		if (buf.length() != 0)
		{
			cout << i + 1 << ". " << buf << endl;
			i++;
			for (char j = 'a'; j <= 'c'; j++)
			{
				getline(fin2, buf);
				cout << j << ") " << buf << endl;
			}
			cout << color<2, 0>;
			cin >> answer;
			cout << color;
			cin.ignore();
			all_answers += answer;
		}
	}
	int count = 0;
	int max_count = all_answers.size();
	for (int i = 0; i < max_count; i++)
	{
		fin3.get(answer);
		if (answer == all_answers[i])
		{
			count++;
		}
	}
	fin1.close();
	fin2.close();
	fin3.close();
	double percent = (double)count / max_count * 100;
	double mark = 12 * percent / 100;
	cout << "Правильных ответов " << color<6, 0> << count << color << "  из вопросов: " << color<6, 0> << max_count << endl;
	cout << percent << "%\n" << color;
	cout << "Ваша оценка - " << color<6, 0> << mark << color << endl;
	system("pause>0");
	ofstream fout(this->login + "TestResults.txt", ios_base::out | ios_base::app);
	fout << " " << SubName << " " << count << " " << percent << " " << mark;
}
//вывод данных о результате теста
void   Student::RezultOfTest()
{
	string buf;
	ifstream fin(this->login + "TestResults.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);
		cout << buf;
	}

	fin.close();
}

//
istream& operator>>(istream& is, Administrator& Ad)
{
	is >> Ad.login >> Ad.password;
	return is;

}
ostream& operator<<(ostream& os, const Administrator& Ad)
{
	os << Ad.login << Ad.password;
	return os;
}
//

//конструктор по умолчанию
Administrator::Administrator() :Person()
{

}
//this паролей в приватные переменные
Administrator::Administrator(string login, string password)
{
	this->login = login;
	this->password = password;

}
//регистрация администратора
void Administrator::RegisLogPas()
{
	system("cls");
	cout << "РЕГИСТРАЦИЯ\n";
	cout << "Придумайте логин:" << color<2, 0>;
	cin >> login;
	cout << color;
	cout << "Придумайте пароль:" << color<2, 0>;
	cin >> password;
	cout << color;
	string buf = login + " " + password;
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);
	ofstream fout("Admin_registration.txt", ios_base::out | ios_base::trunc);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str << endl;
	fout.close();
	system("cls");
	cout << color<8, 0> << "РЕГИСТРАЦИЯ АДМИНИСТРАТОРА ПРОШЛА УСПЕШНО!" << color;
	system("pause>0");
}

//вывод данных о паролях из приватных переменных 
string Administrator::GetLogin()
{
	return login;
}
string Administrator::GetPassword()
{
	return password;
}
//

//авторизация админа
void Administrator::AutorizationAd(bool& flagStasus)
{
	system("cls");
	cout << "АВТОРИЗАЦИЯ:\n";
	string log_admin, pass_admin;
	string buf_str, buf_str2;
	cout << "Логин:" << color<2, 0>;
	cin >> log_admin;
	cout << color;
	cout << "Пароль:" << color<2, 0>;
	cin >> pass_admin;
	cout << color;
	ifstream fin("Admin_registration.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}


	bool flag = true;
	while (!fin.eof())
	{
		buf_str2 = log_admin + " " + pass_admin;
		getline(fin, buf_str);
		char* str = new char[buf_str.size() + 1];
		strcpy(str, buf_str.c_str());
		Deshifr(str);


		if (buf_str2 == this->login) {
			system("cls");
			cout << color<8, 0> << "АВТОРИЗАЦИЯ ПРОШЛА УСПЕШНО!\n" << color;
			system("pause>0");
			flagStasus = true;
			flag = false;
			break;
		}
	}
	if (flag == true) {
		system("cls");
		flagStasus = false;
		cout << color<4, 0> << "НЕВЕРНЫЙ ЛОГИН ИЛИ ПАРОЛЬ, возможно следует зарегистрироваться!\n" << color;
		system("pause>0");
	}
	fin.close();
}
//шифровальшик
void Administrator::Shifr(char* log)
{
	int key = 3;
	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] += key;
	}
}
//дешифровщик
void Administrator::Deshifr(char* log)
{
	int key = 3;
	for (int i = 0; i < strlen(log); i++) {
		if (log[i] != ' ')log[i] -= key;
	}
	this->login = string(log);
}
//регистрация
void Administrator::CreateStud()
{
	system("cls");
	string FullName, homeAdress, telNumber;
	cout << "РЕГИСТРАЦИЯ СТУДЕНТА:\n";
	cout << "Введите Имя:" << color<2, 0>;
	cin >> FullName;
	cout << color;
	cout << "Введите домашний адрес:" << color<2, 0>;
	cin >> homeAdress;
	cout << color;
	cout << "Введите номер телефона:" << color<2, 0>;
	cin >> telNumber;
	cout << color;

	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	fout << endl << FullName << "  " << homeAdress << "  " << telNumber;
	fout.close();
	//РЕГИСТРАЦИЯ ЛОГИНА

	string logUser, passUser, buf;
	cout << "РЕГИСТРАЦИЯ ЛОГИНА СТУДЕНТА:\n";
	cout << "Придумайте логин:" << color<2, 0>;
	cin >> logUser;
	cout << color;
	cout << "Придумайте пароль:" << color<2, 0>;
	cin >> passUser;
	cout << color;

	buf = logUser + " " + passUser;
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);

	ofstream fout1("Student_entrance.txt", ios_base::out | ios_base::app);
	try {
		if (!fout1.is_open()) {
			throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout1 << str << endl;
	fout1.close();

	system("cls");
	cout << color<8, 0> << "РЕГИСТРАЦИЯ ПРОШЛА УСПЕШНО!\n" << color;
	system("pause>0");
}
//удаление студента
void Administrator::RemoveStud() {
	system("cls");
	cout << "УДАЛЕНИЕ ДАННЫХ О СТУДЕНТЕ:\n";
	string buf_str1, buf_str2;
	int pos = 0;
	bool flag = true;
	string lo, porol;
	int counter = 0;

	cout << "Введите логин студента:" << color<2, 0>;
	cin >> lo;
	cout << color;
	cout << "Введите пароль студента:" << color<2, 0>;
	cin >> porol;
	cout << color;

	string log = lo + " " + porol;
	char* str1 = new char[log.size() + 1];
	strcpy(str1, log.c_str());
	Shifr(str1);

	vector <string> vec1, vec2;
	ifstream fin1("Student_entrance.txt", ios_base::in);
	ifstream fin2("Student_registration.txt", ios_base::in);

	try {
		if (!fin1.is_open() && !fin2.is_open()) {
			throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "ShowFromFile", 103);
			exit(1);
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	while (!fin1.eof() && !fin2.eof())
	{
		getline(fin1, buf_str1);
		getline(fin2, buf_str2);
		vec1.push_back(buf_str1);
		vec2.push_back(buf_str2);

		if (buf_str1.find(str1) != -1) {
			pos = counter;
			flag = false;
		}
		counter++;
	}
	fin1.close();
	fin2.close();

	if (flag == false)
	{
		ofstream fout1("Student_entrance.txt", ios_base::out);
		ofstream fout2("Student_registration.txt", ios_base::out);

		try {
			if (!fout1.is_open() && !fin2.is_open()) {
				throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "SaveToFile", 102);
				return;
			}
		}
		catch (myExeption obj) {
			obj.Show();
		}

		for (int i = 0; i < counter; i++)
		{
			if (i != pos) {
				fout1 << vec1[i] << endl;
				fout2 << vec2[i] << endl;
			}

		}
		fout1.close();
		fout2.close();
		system("pause>0");
		cout << color<8, 0> << "ДАННЫЕ УСПЕШНО УДОЛЕНЫ!" << color;
		system("pause>0");
	}
	else if (flag == true)
	{
		system("cls");
		cout << color<4, 0> << "ДАННЫЙ ПОЛЬЗОВАТЕЛЬ НЕ НАЙДЕН!" << color;
		system("pause>0");
	}

}
//создание/редактирование категорий
void Administrator::AddCategory()
{
	string Category, buf;
	cout << "Введите название категории: " << color<2, 0>;
	cin >> Category;
	cout << color;
	ofstream fout("Categories.txt", ios_base::out | ios_base::app);
	fout << Category << endl;
	fout.close();

	ifstream fin("Categories.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("ОШИБКА ОТКРЫТИЯ ФАЙЛА!", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	int i = 0;
	while (!fin.eof())
	{
		getline(fin, buf);
		for (int i = 0; i < buf.length(); i++) {
			if (Category == buf)
			{
				break;
			}
		}
	}
	fin.close();
	AddNameTest(i + 1, Category);
}
//создание/редактирование тестов
void Administrator::AddNameTest(int SubName, string bu)
{
	string TestName;
	cout << "Введите название теста: " << color<2, 0>;
	cin >> TestName;
	cout << color;
	ofstream fout(bu + "Tests_name.txt", ios_base::out | ios_base::app);
	fout << TestName << endl;
	fout.close();
	AddQuestion(TestName, bu);
}
//создание вопросов
void Administrator::AddQuestion(string SbName, string bu)
{
	string tmp, buf;
	ofstream fout1(SbName + bu + "_question.txt", ios_base::out | ios_base::app);
	cout << "Введите вопрос: " << color<2, 0>;
	cin >> buf;
	cout << color;
	fout1 << buf << endl;
	fout1.close();
	ofstream fout2(SbName + bu + "_answer.txt", ios_base::out | ios_base::app);
	cout << "Введите ответ: a \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	cout << "Введите ответ: b \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	cout << "Введите ответ: c \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	fout2.close();
	ofstream fout3(SbName + bu + "_correct_answer.txt", ios_base::out | ios_base::app);
	char correct;
	cout << "Введите букву правильного ответа: \n" << color<2, 0>;
	cin >> correct;
	cout << color;
	fout3 << correct;
	fout3.close();
}
//просмотр кол-во студентов
void Administrator::ShowDatabase()
{
	system("cls");
	cout << "СПИСОК СТУДЕНТОВ:\n";
	string buf;
	vector <string> vec;
	ifstream fin("Student_registration.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);
		vec.push_back(buf);
	}
	fin.close();

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
	system("pause>0");
}
//редактирование данных студента
void Administrator::ModifyStud()
{
	system("cls");
	cout << "ИЗМИНЕНИЕ ДАННЫХ О СТУДЕНТЕ:\n";
	cout << "Список студентов:\n";
	string mod, buf;
	int counter = 0;
	int pos;
	vector <string> vec;
	ifstream fin("Student_registration.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);
		vec.push_back(buf);
		cout << color<6, 0> << counter << color << " " << buf << endl;
		counter++;
	}
	fin.close();
	ofstream fout("Student_registration.txt", ios_base::out);
	cout << "Введите позицию для изменения данных:\n" << color<2, 0>;
	cin >> pos;
	cout << color;
	cin.ignore();
	cout << "Введите данные студента: Имя, адрес, телефон:\n" << color<2, 0>;
	getline(cin, mod);
	cout << color;
	for (int i = 0; i < counter; i++)
	{
		if (i == 0)
		{
			if (pos == 0)
			{
				vec[i] = mod;
			}
			fout << vec[i];
		}
		else if (i != 0 || i != pos)
		{
			fout << endl << vec[i];
		}
		else if (i == pos)
		{
			vec[i] = mod;
			fout << endl << vec[i];

		}
	}
	fout.close();
	system("cls");
	cout << color<8, 0> << "ДАННЫЕ УСПЕШНО ИЗМЕНЕНЫ!" << color;
	system("pause>0");
}