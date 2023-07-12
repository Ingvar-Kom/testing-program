/*Реализовать полнофункциональную систему тестирования.
В системе должны быть реализовано 2 режима:
■ Администратор;
■ Тестируемый.
Описание режима работа для Тестируемого (в дальнейшем гость)
Для входа в систему гость должен зарегистрироваться. Данная процедура выполняется один раз, при дальнейших входах в систему доступ идет по логину
и паролю.
При регистрации нужно указывать ФИО, домашний адрес, телефон.
Важно, чтобы логины для пользователей были уникальными.
После входа гость имеет возможность просмотреть свои предыдущие результаты тестирования, сдать новое тестирование.
Тестирование может осуществляться по различным категориям знаний.
Например:
Математика (раздел) –> Дискретная математика (конкретный тест);
 –> Математический анализ (конкретный тест).
Физика (раздел) –> Квантовая физика (конкретный тест);
 –> Механика (конкретный тест).
После сдачи теста гость видит результат тестирования, количество правильно
отвеченных вопросов, процент правильных ответов и полученную оценку.
Студент имеет возможность прервать тестирование и продолжить его тогда,
когда ему это будет удобно.
Оценивание нужно вести на основании 12-балльной системы, привязанной
к количеству вопросов теста.
Пароли и логины гостей хранятся в зашифрованном виде.
Описание режима работа для Администратора (в дальнейшем админ)
В системе может быть только один админ, логин и пароль админа задается
при первом входе в программу.
В дальнейшем пароль и логин можно изменить (но данную возможность имеет
только админ).
Пароль и логин необходимо хранить только в зашифрованном виде.
При работе с системой админ имеет следующие возможности:
• -Управление пользователеми- создание удоление модификация пользователей.
•Просмотр стаистики - просмотр результатов тестирования в общем
по категориям, по конкретным тестам, по конкретным пользователям.
Результаты просмотра статистики можно вывести в файл.
• -Управление тестированием - админ имеет возможность управлять категории,
тесты, вопросы к тестам, задавать правильные и неправильные ответы, импортировать и экспортировать категории и тесты с
вопросами из файла (и в файл).*/

#include "PERSON.h"
#include "color_text.h"




int main() {
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);

	Student TheStudentBeingTested;
	Administrator TesterAdministrator;
	Test T;

	int SelectingTheMainMenu;

	do {
		system("cls");
		//главное меню выбор пользователя
		cout << "ГЛАВНОЕ МЕНЮ\n";
		cout << "1 - Студент:\n";
		cout << "2 - Администратор:\n";
		cout << "0 - Выйти из программы тестирования:\n" << color<2, 0>;
		cin >> SelectingTheMainMenu;
		cin.ignore();
		cout << color;

		system("cls");
		if (SelectingTheMainMenu == 1) {
			bool flagStasus = false;
			int StudentMenuSelection;
			do {
				//меню студента
				if (flagStasus == false) {
					system("cls");
					cout << "Student:\n";
					cout << "1 - Авторизация пользователя:\n";
					cout << "2 - Регеcтрация пользователя:\n";
					cout << "0 - Выход: \n" << color<2, 0>;
					cin >> StudentMenuSelection;
					cin.ignore();
					cout << color;

					switch (StudentMenuSelection)
					{
					case 1: {
						//авторизация
						TheStudentBeingTested.AutorizationSt(flagStasus);
						break;
					}
					case 2: {
						//регистрация 
						TheStudentBeingTested.Registration();
						break;
					}
					}
				}
				else if (flagStasus == true)
				{
					//меню студента после авторизации
					system("cls");
					cout << "1 - Пройти тест:\n";
					cout << "2 - Просмотреть результаты:\n";
					cout << "0 - Выход: \n" << color<2, 0>;

					cin >> StudentMenuSelection;
					cout << color;
					cin.ignore();
					switch (StudentMenuSelection)
					{

					case 1: {
						system("cls");
						//выбор категорий
						string buf, bu, Category;
						string line;
						int countLin = 1;
						cout << "Выберите категорию:\n";
						//выбор категории
						ifstream fin("Categories.txt", ios_base::in);
						while (!fin.eof())
						{
							getline(fin, buf);
							cout << countLin << buf << endl;

							countLin++;
						}
						cout << color<2, 0>;
						cin >> Category;
						cout << color;
						fin.close();
						//запись в переменную bu название категории для того чтобы найти и открыть файл данной категории
						ifstream ff("Categories.txt", ios_base::in);
						for (int i = 0; to_string(i) != Category; )
						{
							getline(ff, bu);
							i++;
						}
						ff.close();
						//выбор теста
						string buf2, TestName;
						cout << "Выберите тест:\n";
						ifstream fin2(bu + "Tests_name.txt", ios_base::in);
						countLin = 1;
						while (!fin2.eof())
						{
							getline(fin2, buf2);
							cout << countLin << buf2 << endl;
							countLin++;
						}
						countLin = 1;
						cout << color<2, 0>;
						cin >> TestName;
						cout << color;
						fin2.close();
						//запись в переменную testNm названия тета чтобы открыть файл тест
						string testNm;
						ifstream ff2(bu + "Tests_name.txt", ios_base::in);
						for (int i = 0; to_string(i) != TestName; )
						{
							getline(ff2, testNm);
							countLin++;
							i++;
						}
						//тестирование
						TheStudentBeingTested.PassTest(testNm, bu);
						ff2.close();
						break;
					}
					case 2: {
						//просмотр результатов
						system("cls");
						ifstream fin(TheStudentBeingTested.GetLogin() + "TestResults.txt", ios_base::in);
						string buf;
						while (!fin.eof())
						{
							fin >> buf;
							cout << "Тест: " << color<5, 0> << buf << color << endl;
							fin >> buf;
							cout << "Правельных ответов: " << color<5, 0> << buf << color << "\n";
							fin >> buf;
							cout << "Это: " << color<5, 0> << buf << "%\n" << color;
							fin >> buf;
							cout << "Ваша оценка: " << color<5, 0> << buf << color << endl;
						}
						fin.close();
						system("pause>0");
						break;
					}
					case 0: {
						//снятие статуса авторизован
						flagStasus = false;
						break;
					}
					}
				}

			} while (StudentMenuSelection != 0);
		}
		else if (SelectingTheMainMenu == 2) {
			//меню админа
			bool flagStasus = false;
			auto SelectingTheAdminMenu = 0;
			do {
				if (flagStasus == false) {
					system("cls");
					//меню входа администратора
					cout << "Admin:\n";
					cout << "1 - Авторизация Админа\n";
					cout << "2 - Регестрация Админа\n";
					cout << "0 - выход:\n" << color<2, 0>;

					cin >> SelectingTheAdminMenu;
					cin.ignore();


					cout << color;

					switch (SelectingTheAdminMenu)
					{
					case 1: {
						//автризация
						TesterAdministrator.AutorizationAd(flagStasus);
						break;
					}
					case 2: {
						//регистрация
						TesterAdministrator.RegisLogPas();
						break;
					}
					}

				}
				else if (flagStasus == true)
				{
					system("cls");
					//меню администратора
					cout << "Admin:\n";
					cout << "1 - Изменить свой логин и пароль:\n";
					cout << "2 - Показать список студентов:\n";
					cout << "3 - Удалить данные о студенте:\n";
					cout << "4 - Создать нового студента\n";
					cout << "5 - Изменить данные о студенте:\n";
					cout << "6 - Добавить категорию и тест:\n";
					cout << "7 - Статистика:\n";
					cout << "0 - выход:\n" << color<2, 0>;
					cin >> SelectingTheAdminMenu;
					cin.ignore();
					cout << color;

					switch (SelectingTheAdminMenu)
					{
					case 1: {
						//изменение логина и пароля
						TesterAdministrator.RegisLogPas();//?
						//cout << "Логин и пароль изменены:\n";
						break;
					}
					case 2: {
						//вывод списка студентов
						TesterAdministrator.ShowDatabase();
						break;
					}
					case 3: {
						//удoление учотной записи студента
						TesterAdministrator.RemoveStud();
						break;
					}
					case 4: {
						//создание учотной записи нового студента
						TesterAdministrator.CreateStud();
						break;
					}
					case 5: {
						//изменение данных студента
						TesterAdministrator.ModifyStud();
						break;
					}
					case 6: {
						//добавление/изменение тестов
						TesterAdministrator.AddCategory();
						break;
					}
					case 7: {
						//просмотр статистики студентов
						string buf, buf2, log, passt, logre;
						cout << "Введите логин студента:\n" << color<2, 0>;
						cin >> log;
						cout << color;
						cout << "Введите пароль студента:\n" << color<2, 0>;
						cin >> passt;
						cout << color;
						//запись лога и пароля в одну переменную для упрощения дальнейшей работы с этими данными
						logre = log + " " + passt;
						//получение категории
						ifstream fin1("Categories.txt", ios_base::in);
						while (!fin1.eof()) { getline(fin1, buf); }
						fin1.close();
						//открытие и запись информации тестов
						ifstream fin2(buf + "Tests_name.txt", ios_base::in);
						while (!fin2.eof())
						{
							fin2 >> buf2;
							//работа с файлом статистики
							T.Show_statistic(buf2, logre);
						}
						fin2.close();
						break;
					}
					case 0: {
						flagStasus = false;
						break;
					}
					}
				}

			} while (SelectingTheAdminMenu != 0);
		}

	} while (SelectingTheMainMenu != 0);

	system("pause>0");
};