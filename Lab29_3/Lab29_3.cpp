#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

int i, j; // объявлена глобальная переменная, чтобы каждый раз не объявлять ее в функции

struct planes // в нашем классе будет приватная структура, с которой мы будем работать
{
	string place = ""; // пункт назначения
	int number = -1; // номер рейса
	string type = ""; // тип самолета
	int position = -1; // позиция в сортированном списке
};

class aeroflot // наш класс аэрофлот
{
private:
	vector <planes> plane; // вектор структур с данными
public:

	void add_plane() // добавляет в постоянный вектор структур элемент и пользователь вводит данные
	{
		planes temp_plane;
		cout << "Destination: ";
		getline(cin, temp_plane.place); // вводим в новую структуру постоянного вектора структур новые данные
		cout << "Number of flight: ";
		cin >> temp_plane.number; // вводим в новую структуру постоянного вектора структур новые данные
		cin.get();/* после введения данных через "cin" остается символ перевода строки "\n", который "съедает" последующий
		"getline()" и мы не можем ввести свою строку. cin.get() сам "съест" символ перевода строки "\n" и ввод строки удастся */
		cout << "Type of plane: ";
		getline(cin, temp_plane.type); // вводим в новую структуру постоянного вектора структур новые данные
		plane.push_back(temp_plane);
		system("pause");
		system("cls");
	}

	void show_database() // выводит на экран базу данных, тут все легко
	{
		sort_data(); // перед показом сортируем структуры в массиве структур
		cout << "===================================================================" << endl;
		cout << "\tDestination\tNumber of flight\tType of plane" << endl;
		for (i = 0; i < plane.size(); ++i) // цикл
			cout << i + 1 << "\t" << plane[i].place << "\t\t" << plane[i].number << "\t\t\t" << plane[i].type << endl; // вывод данных
		cout << "===================================================================" << endl;
		system("pause");
		system("cls");
	}

	void delete_plane() // удаляет структуру из постоянного массива структур
	{
		int i_del = -1; // i_del - номер структуры, которую мы удаляем
		string type; // тип удаляемого самолета (по условию задачи, мы должны работать с самолетами по типу)
		cout << "Enter type of plane: ";
		getline(cin, type); // считываем тип удаляемого самолета
		for (i = 0; i < plane.size(); ++i)
		{
			if (type == plane[i].type) // ищем, есть ли самолет такого типа в базе данных
				i_del = i; // если есть, обозначаем его номер
		}
		if (i_del != -1) // если нашли совпадение, то...
		{
			vector <planes> temp_plane; // временный массив структур, размером на 1 меньше
			for (i = 0; i < plane.size(); ++i) /* копируем нужные (которые не подлежат удалению) структуры из постоянного вектора 
			структур в временный */
			{
				if (i != i_del)
					temp_plane.push_back(plane[i]);
			}
			plane.clear();
			plane = temp_plane; // получаем постоянный вектор структур нового размера
			cout << "Plane " << type << " has been deleted" << endl;
		}
		else // если не нашли совпадение, то...
			cout << "This plane doesn`t exist" << endl; // ошибка :(
		system("pause");
		system("cls");
	}
	
	void edit_data() // изменяет данные постоянного вектора структур
	{
		int i_edit = -1, act = 4; // i_edit - номер изменяемой структуры, act - действие
		string type; // тип изменяемого самолета (по условию задачи, мы должны работать с самолетами по типу)
		cout << "Enter type of plane: ";
		getline(cin, type); // считываем тип изменяемого самолета
		for (i = 0; i < plane.size(); ++i) // цикл 
		{
			if (type == plane[i].type) // ищем, есть ли самолет такого типа в базе данных 
				i_edit = i; // если есть, обозначаем его номер
		}
		if (i_edit != -1) // если нашли совпадение, то...
		{
			do
			{
				if (act == 1) // изменение пункта назначения
				{
					cout << "Enter new destination: ";
					getline(cin, plane[i_edit].place); // вводим в изменяемую структуру постоянного вектора структур новые данные
				}
				else if (act == 2) // изменение номера рейса
				{
					cout << "Enter new number of flight: ";
					cin >> plane[i_edit].number; // вводим в изменяемую структуру постоянного вектора структур новые данные
					cin.get();
				}
				else if (act == 3) // изменение типа самолета
				{
					cout << "Enter new type of plane: ";
					getline(cin, plane[i_edit].type); // вводим в изменяемую структуру постоянного вектора структур новые данные
				}
				else if (act != 4) // если введенное число не имеет смысла в рамках нашего выбора действий, то...
				{
					cout << "This action isn`t available, please, try again" << endl; // ошибка :(
					system("pause");
					system("cls");
				}
				cout << "1 - Edit destination | 2 - Edit Number of flight | 3 - Edit type of plane | 4 - exit" << endl;
				cin >> act; // выбор действия
				cin.get();
			} while (act != 4); // пока мы не введем 4, что значит "Выход", цикл будет продолжаться
		}
		else // если не нашли совпадение, то...
			cout << "This plane didn`t exist" << endl; // ошибка :(
		system("pause");
		system("cls");
	}

	void save_data() // сохраняет данные в файл базы данных
	{
		ofstream data("c:\\files\\Lab29_3\\database.txt"); // открываем файл базы данных для записи данных в него
		for (i = 0; i < plane.size(); ++i) // цикл записи данных в файл базы данных
		{
			if (i != plane.size() - 1) // если это не последняя струтура в постоянном векторе структур, то...
			{
				data << plane[i].place << endl;
				data << plane[i].number << endl;
				data << plane[i].type << endl; // здесь будет перенос строки
			}
			else // а если это последняя структура в постоянном векторе структур, то...
			{
				data << plane[i].place << endl;
				data << plane[i].number << endl;
				data << plane[i].type; /* здесь не будет переноса строки, т.к. в будущем нам надо будет загружать данные 
				из файла базы данных в программу, и при считывании он будет считывать пустую строку, а нам этого не надо*/
			}
		}
		data.close(); // закрываем файл базы данных
		cout << "Your data has been saved" << endl;
		system("pause");
		system("cls");
	}

	void load_data() // загружает данные из файла базы данных в программу
	{
		ifstream data("c:\\files\\Lab29_3\\database.txt"); // открываем файл базы данных для записи данных из него
		while (!data.eof()) // цикл, передающий данные из файла в наш постоянный вектор структур
		{
			planes temp_plane;
			getline(data, temp_plane.place); // считываем пункт назначения
			data >> temp_plane.number; // считываем номер рейса
			data.get(); // аналогично cin.get()
			getline(data, temp_plane.type); // считываем тип самолета
			plane.push_back(temp_plane);
		}
		data.close(); // закрываем файл базы данных
		cout << "Your data has been loaded" << endl;
		system("pause");
		system("cls");
	}

	void sort_data() // сортировка структур в векторе по первой букве пункта назначения в алфавитном порядке
	{
		char letters[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; // это прописной алфавит
		char big_letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' }; // это заглавный алфавит
		int* pos = new int[plane.size()]; // массив позиций в алфавите, занимаемых первыми буквами рассматриваемых строк
		int ch; // переменная для хранения данных в процессе сортировки
		for (i = 0; i < plane.size(); ++i) // цикл, проходящий весь массив структур
		{
			for (j = 0; j < 26; ++j) // цикл, находящий позицию в алфавите, занимаемую первой буквой рассматриваемой строки
			{
				if (plane[i].place[0] == letters[j] || plane[i].place[0] == big_letters[j]) /* если первая буква рассматриваемой
				строки сходится с рассматриваемой буквой массива афавита, то ... */
					pos[i] = j; // вносим порядковый номер найденной буквы в массив позиций
			}
		} /* после работы этого цикла наш массив будет выглядеть подобно примеру: {0, 17, 12, 8, 12} - это порядковые номера в алфавите 
		  первых букв наших строк */
		for (i = 0; i < plane.size(); ++i) // сортировка массива позиций
		{
			for (j = 0; j < plane.size() - 1; ++j) /* мы сравниваем каждый элемент со следующим, а последний элемент сравнивать не с чем, 
			поэтому на нем вложенный цикл остановится */
			{
				if (pos[j] > pos[j + 1]) // если текущий элемент больше следующего, то мы меняем их местами
				{
					ch = pos[j]; // сохраняем текущий элемент в переменную "ch"
					pos[j] = pos[j + 1]; // текущий элемент заменяем следующим
					pos[j + 1] = ch; // следующий элемент заменяем предыдущим
				}
			}
		}/* после работы этого цикла наш массив будет выглядеть подобно примеру: {0, 8, 12, 12, 17} - это отсортированные
		 порядковые номера в алфавите первых букв наших строк */
		for (i = 0; i < plane.size(); ++i)// этот цикл передаст нужные порядковые номера в структуру
		{
			for (j = 0; j < plane.size(); ++j)
			{
				if (letters[pos[i]] == plane[j].place[0] || big_letters[pos[i]] == plane[j].place[0]) /* если элемент буквенного массива,
				индекс которого равен элементу сортированного массива, совпадает с первой буквой рассматриваемой строки, то... */
					plane[j].position = i; // передаем в структуру позицию этой структуры в массиве структур, пусть знает свое место :)
			}
		}
		for (i = 0; i < plane.size(); ++i) // цикл для устранения повторяющихся позиций
		{
			for (j = i + 1; j < plane.size(); ++j) // j = i + 1 берем потому, что нам не нужно сравнивать переменную с самим собой
			{
				if (plane[i].position == plane[j].position) // если позиция структуры[i] равна позиции структуры[j], то...
					--plane[j].position; // уменьшаем позицию структуры[j] на 1
			}
		}
		vector <planes> temp_plane; // создаем временный вектор
		for (i = 0; i < plane.size(); ++i)
			temp_plane.push_back(plane[i]); // из постоянного вектора копируем данные во временный, но с учетом сортировки
		plane = temp_plane; // получаем отсортированный вектор
	}
};

int main()
{
	int act = 7; // 7 действий доступно в программе
	aeroflot plane1; // объект класса, с которым мы работаем
	do
	{
		if (act == 1)
			plane1.add_plane(); // добавить самолет в базу данных
		else if (act == 2)
			plane1.show_database(); // вывести на экран базу данных
		else if (act == 3)
			plane1.edit_data(); // изменить данные о самолете в базе данных
		else if (act == 4)
			plane1.delete_plane(); // удалить данные о самолете в базе данных
		else if (act == 5)
			plane1.save_data(); // сохранить базу данных в файл
		else if (act == 6)
			plane1.load_data(); // загрузить базу данных из файла
		else if (act != 7) // если введенное число не имеет смысла в рамках нашего выбора действий, то...
		{
			cout << "This action isn`t available, please, try again" << endl; // ошибка :(
			system("pause");
			system("cls");
		}
		cout << "==================================" << endl;
		cout << "\tAEROFLOT" << endl;
		cout << "1 - add plane\n2 - show database\n3 - edit data\n4 - delete plane\n5 - save data\n6 - load data\n7 - exit" << endl;
		cout << "==================================" << endl;
		cin >> act; // выбор действия
		cin.get();
		system("cls");
	} while (act != 7); // пока мы не введем 7, что значит "Выход", цикл будет продолжаться
	cout << "Good bye" << endl;
	return 0;
}