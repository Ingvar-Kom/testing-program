#include "PERSON.h"
#include "color_text.h"
//Default �������
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

//Default ������
Student::Student() :Person()
{
	this->FullName = "Default fullname";
	this->homeAdress = "Default homeadress";
	this->telNumber = "Default telnumber";

	int counter = 0;
}
//this ������ � ��������� ����������
Student::Student(string FullName, string homeAdress, string telNumber)
{
	this->FullName = FullName;
	this->homeAdress = homeAdress;
	this->telNumber = telNumber;
}
//this ������� � ��������� ����������
Student::Student(const string login, const string password)
{
	this->login = login;
	this->password = password;
}
//����������� ������ ��������
void   Student::Registration()
{
	system("cls");
	cout << "������� ���:" << color<2, 0>;
	cin >> FullName;
	cout << color << "������� �������� �����:" << color<2, 0>;
	cin >> homeAdress;
	cout << color << "������� ����� ��������:" << color<2, 0>;
	cin >> telNumber;
	cout << color;

	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("���� �� ��������!", "SaveToFile", 102);
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
	cout << color<8, 0> << "����������� ������ �������!\n" << color;
	system("pause>0");

}
//����������� ������ ��������
void   Student::RegisLogPas()
{
	bool flag = true;
	string logUser, passUser, buf;
	system("cls");

	do
	{
		cout << "�����������\n";
		flag = true;
		cout << "���������� �����:" << color<2, 0>;
		cin >> logUser;
		cout << color;
		cout << "���������� ������:" << color<2, 0>;
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
			throw myExeption("������ �������� �����!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str << endl;
	fout.close();
}
//����������� ��������
void   Student::CheckRegis(string buf, bool flag)
{

	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);

	string buf_str, buf_str2;
	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("���� �� �������� ��� ������ !", "ShowFromFile", 103);
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
			cout << color<4, 0> << "����� ����� ����������!:\n" << color;
			flag = false;
			return;
		}

	}
	fin.close();
}
//����������� ��������
void   Student::AutorizationSt(bool& flagStasus)
{
	system("cls");
	cout << "�����������:\n";
	string logUser, passUser;
	string buf_str, buf_str2;

	cout << "�����:" << color<2, 0>;
	cin >> logUser;
	cout << color;
	cout << "������:" << color<2, 0>;
	cin >> passUser;
	cout << color;

	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("���� �� �������� ��� ������ !", "ShowFromFile", 103);
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
			cout << color<8, 0> << "����������� ������ �������!!\n" << color;
			system("pause>0");
			flagStasus = true;
			flag = false;
			return;
		}

	}
	if (flag == true) {
		system("cls");
		cout << color<4, 0> << "�������� ����� ��� ������, ������� ������� ������������������!\n" << color;
		system("pause>0");
		flagStasus = false;
	}
	fin.close();
}
//����������
void   Student::Shifr(char* log)
{
	int key = 3;

	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] += key;
	}
}
//����������
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
//���
string Student::GetFullName() { return FullName; }
//�����
string Student::GetLogin() { return login; }
//������
string Student::GetPassword() { return password; }
//������������
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
	cout << "���������� ������� " << color<6, 0> << count << color << "  �� ��������: " << color<6, 0> << max_count << endl;
	cout << percent << "%\n" << color;
	cout << "���� ������ - " << color<6, 0> << mark << color << endl;
	system("pause>0");
	ofstream fout(this->login + "TestResults.txt", ios_base::out | ios_base::app);
	fout << " " << SubName << " " << count << " " << percent << " " << mark;
}
//����� ������ � ���������� �����
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

//����������� �� ���������
Administrator::Administrator() :Person()
{

}
//this ������� � ��������� ����������
Administrator::Administrator(string login, string password)
{
	this->login = login;
	this->password = password;

}
//����������� ��������������
void Administrator::RegisLogPas()
{
	system("cls");
	cout << "�����������\n";
	cout << "���������� �����:" << color<2, 0>;
	cin >> login;
	cout << color;
	cout << "���������� ������:" << color<2, 0>;
	cin >> password;
	cout << color;
	string buf = login + " " + password;
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);
	ofstream fout("Admin_registration.txt", ios_base::out | ios_base::trunc);
	try {
		if (!fout.is_open()) {
			throw myExeption("���� �� �������� ��� ������!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str << endl;
	fout.close();
	system("cls");
	cout << color<8, 0> << "����������� �������������� ������ �������!" << color;
	system("pause>0");
}

//����� ������ � ������� �� ��������� ���������� 
string Administrator::GetLogin()
{
	return login;
}
string Administrator::GetPassword()
{
	return password;
}
//

//����������� ������
void Administrator::AutorizationAd(bool& flagStasus)
{
	system("cls");
	cout << "�����������:\n";
	string log_admin, pass_admin;
	string buf_str, buf_str2;
	cout << "�����:" << color<2, 0>;
	cin >> log_admin;
	cout << color;
	cout << "������:" << color<2, 0>;
	cin >> pass_admin;
	cout << color;
	ifstream fin("Admin_registration.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("���� �� �������� ��� ������ !", "ShowFromFile", 103);
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
			cout << color<8, 0> << "����������� ������ �������!\n" << color;
			system("pause>0");
			flagStasus = true;
			flag = false;
			break;
		}
	}
	if (flag == true) {
		system("cls");
		flagStasus = false;
		cout << color<4, 0> << "�������� ����� ��� ������, �������� ������� ������������������!\n" << color;
		system("pause>0");
	}
	fin.close();
}
//������������
void Administrator::Shifr(char* log)
{
	int key = 3;
	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] += key;
	}
}
//�����������
void Administrator::Deshifr(char* log)
{
	int key = 3;
	for (int i = 0; i < strlen(log); i++) {
		if (log[i] != ' ')log[i] -= key;
	}
	this->login = string(log);
}
//�����������
void Administrator::CreateStud()
{
	system("cls");
	string FullName, homeAdress, telNumber;
	cout << "����������� ��������:\n";
	cout << "������� ���:" << color<2, 0>;
	cin >> FullName;
	cout << color;
	cout << "������� �������� �����:" << color<2, 0>;
	cin >> homeAdress;
	cout << color;
	cout << "������� ����� ��������:" << color<2, 0>;
	cin >> telNumber;
	cout << color;

	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("������ �������� �����!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	fout << endl << FullName << "  " << homeAdress << "  " << telNumber;
	fout.close();
	//����������� ������

	string logUser, passUser, buf;
	cout << "����������� ������ ��������:\n";
	cout << "���������� �����:" << color<2, 0>;
	cin >> logUser;
	cout << color;
	cout << "���������� ������:" << color<2, 0>;
	cin >> passUser;
	cout << color;

	buf = logUser + " " + passUser;
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);

	ofstream fout1("Student_entrance.txt", ios_base::out | ios_base::app);
	try {
		if (!fout1.is_open()) {
			throw myExeption("������ �������� �����!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout1 << str << endl;
	fout1.close();

	system("cls");
	cout << color<8, 0> << "����������� ������ �������!\n" << color;
	system("pause>0");
}
//�������� ��������
void Administrator::RemoveStud() {
	system("cls");
	cout << "�������� ������ � ��������:\n";
	string buf_str1, buf_str2;
	int pos = 0;
	bool flag = true;
	string lo, porol;
	int counter = 0;

	cout << "������� ����� ��������:" << color<2, 0>;
	cin >> lo;
	cout << color;
	cout << "������� ������ ��������:" << color<2, 0>;
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
			throw myExeption("������ �������� �����!", "ShowFromFile", 103);
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
				throw myExeption("������ �������� �����!", "SaveToFile", 102);
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
		cout << color<8, 0> << "������ ������� �������!" << color;
		system("pause>0");
	}
	else if (flag == true)
	{
		system("cls");
		cout << color<4, 0> << "������ ������������ �� ������!" << color;
		system("pause>0");
	}

}
//��������/�������������� ���������
void Administrator::AddCategory()
{
	string Category, buf;
	cout << "������� �������� ���������: " << color<2, 0>;
	cin >> Category;
	cout << color;
	ofstream fout("Categories.txt", ios_base::out | ios_base::app);
	fout << Category << endl;
	fout.close();

	ifstream fin("Categories.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("������ �������� �����!", "ShowFromFile", 103);
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
//��������/�������������� ������
void Administrator::AddNameTest(int SubName, string bu)
{
	string TestName;
	cout << "������� �������� �����: " << color<2, 0>;
	cin >> TestName;
	cout << color;
	ofstream fout(bu + "Tests_name.txt", ios_base::out | ios_base::app);
	fout << TestName << endl;
	fout.close();
	AddQuestion(TestName, bu);
}
//�������� ��������
void Administrator::AddQuestion(string SbName, string bu)
{
	string tmp, buf;
	ofstream fout1(SbName + bu + "_question.txt", ios_base::out | ios_base::app);
	cout << "������� ������: " << color<2, 0>;
	cin >> buf;
	cout << color;
	fout1 << buf << endl;
	fout1.close();
	ofstream fout2(SbName + bu + "_answer.txt", ios_base::out | ios_base::app);
	cout << "������� �����: a \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	cout << "������� �����: b \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	cout << "������� �����: c \n" << color<2, 0>;
	cin >> buf;
	cout << color;
	fout2 << buf << endl;
	fout2.close();
	ofstream fout3(SbName + bu + "_correct_answer.txt", ios_base::out | ios_base::app);
	char correct;
	cout << "������� ����� ����������� ������: \n" << color<2, 0>;
	cin >> correct;
	cout << color;
	fout3 << correct;
	fout3.close();
}
//�������� ���-�� ���������
void Administrator::ShowDatabase()
{
	system("cls");
	cout << "������ ���������:\n";
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
//�������������� ������ ��������
void Administrator::ModifyStud()
{
	system("cls");
	cout << "��������� ������ � ��������:\n";
	cout << "������ ���������:\n";
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
	cout << "������� ������� ��� ��������� ������:\n" << color<2, 0>;
	cin >> pos;
	cout << color;
	cin.ignore();
	cout << "������� ������ ��������: ���, �����, �������:\n" << color<2, 0>;
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
	cout << color<8, 0> << "������ ������� ��������!" << color;
	system("pause>0");
}