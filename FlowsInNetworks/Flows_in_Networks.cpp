#include<iostream>
#include<cstdio>
#include "Flows.h"
#include "cassert"

using namespace std;

void menu_output();
char enter_mode();

void menu();

int main() {
	cout << " < Flows in Networks > " << endl << endl;
	menu();
	system("pause");
	return 0;
}

void menu() {

	str Path;// змінна шляху до файлу

	meta* meta_data = new meta();

	char mode; // мод роботи програми
	edge* Edge_List = NULL;// список ребер
	strcpy_s(Path, 100, " < Current file wasn't entered > ");

	menu_output(); // вивід меню

	do { // цикл роботи програми, поки користувач не захоче вийти з програми

		mode = enter_mode();

		switch (mode) { // порівняння введеного моду

		case'n':
			connect_file(&Edge_List, &Path, meta_data);
			break;

		case'0':
			menu_output(); // вивід меню
			break;

		case'x':
			remove(Path); // видалення файлу
			connect_file(&Edge_List, &Path, meta_data);
			break;

		case'p': cout << " Current file: " << Path << endl; // вивід шляху поточного файлу
			break;

		case'm':
			Edge_List = read_file(Path, meta_data); // зчитування з файлу
			get_min_price_flow(Edge_List, *meta_data);
			break;

		case'f':
			Edge_List = read_file(Path, meta_data); // зчитування з файлу
			Edmonds_Karp_algorithm(Edge_List, *meta_data);
			break;

		case'q': // якщо мод виходу, то нічого не робити
			break;

		case'o':
			edge_list_output(Edge_List, meta_data->num_of_edges);  // виведення списка ребер
			break;

		default:
			cout << " < Wrong mode > " << endl; // вівід повідомлення про неправильний мод
			break;

		}

	} while (mode != 'q'); // поки користувач не захоче вийти
}

char enter_mode() {
	char mode;
	fflush(stdin);
	cout << endl << "Enter mode >";
	mode = getchar(); // ввід моду
	mode = tolower(mode);
	getchar();
	return mode;
}

void menu_output() { // вивід меню з ключами та поясненнями

	cout << " < Enter \"n\" to open new file and read graph >" << endl;
	cout << " < Enter \"o\" to output edge list>" << endl;
	cout << " < Enter \"q\" to quit >" << endl;
	cout << " < Enter \"x\" to remove current file >" << endl;
	cout << " < Enter \"0\" to output menu >" << endl;
	cout << " < Enter \"m\" to get maximal flow with minimal price in graph >" << endl;
	cout << " < Enter \"f\" to get maximal flow in graph >" << endl;
	cout << " < Enter \"p\" to output a path of current file >" << endl << endl;
}