#include<iostream>
#include<cstdio>
#include "Flows.h"

using namespace std;

void menu_output();

int main() {

	str Path;// змінна шляху до файлу
	int nodes = 0, edges = 0, start = 0, finish = 0; // кількість вершин та ребер графу, початкова та кінцева вершина
	char mode; // мод роботи програми
	edge* Edge_List = NULL;// список ребер
	strcpy_s(Path, 100, " < Current file wasn't entered > ");

	cout << " < Flows in Networks > " << endl << endl;

	menu_output(); // вивід меню

	do { // цикл роботи програми, поки користувач не захоче вийти з програми

		fflush(stdin);
		cout << endl << "Enter mode >";
		mode = getchar(); // ввід моду
		mode = tolower(mode);
		getchar();

		switch (mode) { // порівняння введеного моду

		case'n':
			delete[] Edge_List; // видалення  списка ребер

			get_path(&Path); // введення шляху до файлу
			Edge_List = read_file(Path, &edges, &nodes, &start, &finish); // зчитування з файлу

			edge_list_output(Edge_List, edges); // виведення списка ребер
			break;

		case'0':
			menu_output(); // вивід меню
			break;

		case'x':
			delete[] Edge_List; // видалення  списка ребер
			remove(Path); // видалення файлу
			get_path(&Path); // введення шляху до файлу
			Edge_List = read_file(Path, &edges, &nodes, &start, &finish); // зчитування з файлу
			edge_list_output(Edge_List, edges);  // виведення списка ребер
			break;

		case'p': cout << " Current file: " << Path << endl; // вивід шляху поточного файлу
			break;

		case'm':
			Edge_List = read_file(Path, &edges, &nodes, &start, &finish); // зчитування з файлу
			get_min_price_flow(Edge_List, nodes, edges, start, finish);
			break;

		case'f':
			Edge_List = read_file(Path, &edges, &nodes, &start, &finish); // зчитування з файлу
			Edmonds_Karp_algorithm(Edge_List, nodes, edges, start, finish);
			break;

		case'q': // якщо мод виходу, то нічого не робити
			break;

		case'o':
			edge_list_output(Edge_List, edges);  // виведення списка ребер
			break;

		default:
			cout << " < Wrong mode > " << endl; // вівід повідомлення про неправильний мод
			break;

		}

	} while (mode != 'q' && mode != 'Q'); // поки користувач не захоче вийти

	system("pause");
	return 0;
}

void menu_output() { // вивід меню з ключами та поясненнями

	cout << " < Enter \"n\" to open new file and read graph >" << endl;
	cout << " < Enter \"o\" to output edge list>" << endl;
	cout << " < Enter \"q\" to quit >" << endl;
	cout << " < Enter \"x\" to remove current file >" << endl;
	cout << " < Enter \"0\" to output menu >" << endl;
	cout << " < Enter \"m\" to get maximal flow with minimal price in graph >" << endl;
	cout << " < Enter \"f\" to get maximal flow in graph >" << endl;
	cout << " < Enter \"p\" to output a path to current file >" << endl << endl;
}