#include "Flows.h"

using namespace std;

template<class T>
T** del_matrix(T** Matrix, int row) { // видалення матриці

	if (Matrix != NULL) { // якщо матриця не порожня
		for (int count = 0; count < row; count++) { // пройти по всім рядкам

			delete[] * (Matrix + count); // видалити поточний рядок
		}
		delete[] Matrix; // вмдалити масив показчиків на рядки
	}
	return NULL;
}

str* get_path(str* Path) { // ввід шляху до файлу

	cout << " < Enter an absolute path to file (D:\\Docs\\file.txt) > " << endl << ">";
	gets_s(*Path, 100); // ввід шляху до файлу

	if (strstr(*Path, ".txt") == NULL) strcat_s(*Path, 80, ".txt"); // якщо невказано розширення, додати

	return Path; // повернути змінну шляху
}

FILE* open_file(str Path, const char* mode) { // відкрити файл

	FILE* file; // показчик на файл
	// відчинення файлу
	if (fopen_s(&file, Path, mode) != 0) { // якщо файл не відкритій
		cout << " < ERROR! This File can not be open, or doesn't exist > " << endl; // вівід повідомлення про помилку
		system("pause");
		exit(0); // зачинення програми
	}

	return file; // певернути показчик на файл
}

edge* read_file(str Path, meta* meta_data) { // зчитуфання графу з файлу

	FILE* file = open_file(Path, "r"); // відчинення файлу
	edge* cur_edge = new edge();

	fscanf_s(file, "%d %d %d %d", &(meta_data->num_of_nodes), &(meta_data->num_of_edges), &(meta_data->start_node), &(meta_data->finish_node));
	if (feof(file)) {
		cout << " < File is incorrectly filled > " << endl;
		system("pause");
		return NULL;
	}

	if(check_meta(*meta_data)) return NULL;

	edge* Edge_List = new edge[meta_data->num_of_edges]; // виділення пам'яті під масив ребер

	for (int count = 0; count < meta_data->num_of_edges; count++) { // поки не заповнений весь масив ребер

		fscanf_s(file, "%d %d %d %d", &(cur_edge->start_node), &(cur_edge->finish_node), &(cur_edge->weight), &(cur_edge->price));

		if (feof(file)) break; // перевірка на кінець файлу

		if (check_edge(*meta_data, *cur_edge)) return NULL;

		*(Edge_List + count) = *cur_edge;
	}

	fclose(file); // зачинення файлу
	return Edge_List; // повернути список ребер
}

bool check_edge(meta meta_data, edge edge) {

	// перевірка на коректність введених даних
	if (edge.start_node <= 0 || edge.start_node > meta_data.num_of_nodes || edge.finish_node <= 0 || edge.finish_node > meta_data.num_of_nodes) { // перевірка на коректність зчитаних даних
		cout << " < Error! Number of node cann't be less then null and bigger then number of all nodes > " << endl;
		system("pause");
		return true;
	}
	else if (edge.weight < 0 || edge.price < 0) {

		cout << " < Error! Distance or price between two nodes cann't be less then null > " << endl;
		system("pause");
		return true;
	}
	return false;
}

bool check_meta(meta meta_data) {

	if (2 >= meta_data.num_of_nodes || meta_data.num_of_nodes >= 100) { // перевірка на коректність введених даних

		cout << " < Error! Number of nodes must be (2 < nodes < 100) > " << endl;
		return true;
	}else if (meta_data.num_of_nodes - 1 >= meta_data.num_of_edges || meta_data.num_of_edges >= 200) { // перевірка на коректність введених даних

		cout << " < Error! Number of edges must be (nodes - 1 < edges < 200) > " << endl;
		return true;
	}
	else if (meta_data.start_node > meta_data.num_of_nodes || meta_data.start_node <= 0 || meta_data.finish_node <= 0 || meta_data.finish_node > meta_data.num_of_nodes) { // перевірка на коректність введених даних

		cout << " < Error! Number of node cann't be less then null and bigger then number of all nodes > " << endl;
		return true;
	}
	return false;
}

void connect_file(edge** Edge_List, str* Path, meta* meta_data) {
	delete[] * Edge_List; // видалення  списка ребер
	get_path(Path); // введення шляху до файлу
	*Edge_List = read_file(*Path, meta_data); // зчитування з файлу
	edge_list_output(*Edge_List, meta_data->num_of_edges);  // виведення списка ребер
}

void edge_list_output(edge* Edge_List, int edges) { // вивести список ребер

	if (Edge_List != NULL) { // якщо список ребер не порожній
		cout << endl << " < Edge list > " << endl;

		cout << " < e[i] - edge number, v[i] - start node, u[i] - finish node, w[i] - weight, p[i] - price > " << endl;

		if (edges == 0) { // якщо кількість ребер = 0
			cout << " < Graph is null-graph > " << endl << endl; // вивести відповідне повідомлення
			return; // вийти з функції
		}

		for (int num_edge = 0; num_edge < edges; ++num_edge) { // поки не квнець списку ребер

			cout << endl << " e[" << num_edge + 1 << "]" << "\t";
			cout << " v[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->start_node; // вивести поччаткову вершину
			cout << "\t" << " u[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->finish_node; // вивести кінцеву вершину
			cout << "\t" << " w[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->weight;  // вивести вагу ребра
			cout << "\t" << " p[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->price << endl;; // вивести ціну

		}
	}
	else {
		cout << " < Edge list is empty > " << endl; // вивести відповідне повідомлення
	}

	cout << endl;
}

int** ajacency_matrix(edge* Edge_List, int edges, int nodes) { // створення матриці суміжності

	int** Adjacency_Matrix = new int*[nodes]; // виділення пам'яті під матрицю суміжності

	for (int num_row = 0; num_row < nodes; ++num_row) { // виділення пам'яті під матрицю суміжності
		*(Adjacency_Matrix + num_row) = new int[nodes];
	}

	for (int row = 0; row < nodes; ++row) { // заповнення матрицці суміжності нулями
		for (int column = 0; column < nodes; ++column) {

			*(*(Adjacency_Matrix + row) + column) = 0;
		}
	}

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // заповнення матрицці суміжності

		int row = (Edge_List + edge_num)->start_node - 1; // номер рядка
		int column = (Edge_List + edge_num)->finish_node - 1; // номер колонки

		if (*(*(Adjacency_Matrix + row) + column) < (Edge_List + edge_num)->weight) {
			*(*(Adjacency_Matrix + row) + column) = (Edge_List + edge_num)->weight;
		}
	}

	return Adjacency_Matrix; // повернути матрицю суміжності
}

//==========================================================================================

void write_answer(FILE* file, std::vector<int>& Path) { // запис відповіді до вихідного файлу

	for (int count = 0; count < (int)Path.size() - 1; count++) { // поки не передостанній елелмент 

		fprintf(file, "%d->", Path[count]); // записати номер вершини до файлу
		printf("%d->", Path[count]);
	}
	fprintf(file, "%d\n", Path.back()); // записати останній елемент
	printf("%d\n", Path.back());

}

void Edmonds_Karp_algorithm(edge* Edge_List, meta meta_data) { // алгоритм Єдмондса-Карпа

	str Path; // шлях до вихідного фйлу
	int cur_flow, max_flow = 0; // поточний та максимальний потік
	vector<int> cur_Path; // поточний шлях у мережі
	cout << " < Writing to the output file > " << endl;
	get_path(&Path); // введення шляху до поточного файлу

	FILE* file = open_file(Path, "w+"); // відчинення файлу

	int count = 0;
	do {
		cur_Path = Dijkstras_algorithm(Edge_List, meta_data, &cur_flow, weight); // пошук мінімального шляху між вершинами за допомогою алгоритма Дейкстри

		if (count == 0) {
			if (cur_Path.empty()) {
				cout << " < There is no path between the entered nodes in the current graph > " << endl; // вивести відповідне повідомлення
				fprintf(file, " < There is no path between the entered nodes in the current graph > \n");
				fclose(file); // закрити файл
				return;
			}
			else printf(" flow / path \n");
		}
		else if (cur_Path.empty())break; // якщо шлях більше не існує, вийти із циклу

		max_flow += cur_flow; // додати поточний потік до загального
		get_residual_network(Edge_List, meta_data.num_of_edges, cur_Path, cur_flow); // отримати залишкову мережу

		fprintf(file, "%d / ", cur_flow); // записати знайдений потік
		printf("%d / ", cur_flow);
		write_answer(file, cur_Path); // записати знайдений шлях
		count++;
	} while (!cur_Path.empty());

	fprintf(file, " < Maximal flow from node \"%d\" to node \"%d\" is  %d / > \n", meta_data.start_node, meta_data.finish_node, max_flow); // записати значення максимального потоку
	printf(" < Maximal flow from node \"%d\" to node \"%d\" is  %d / > \n", meta_data.start_node, meta_data.finish_node, max_flow);

	fclose(file); // закрити файл
}

bool visited(vector<int> &Visited, int node_num) { // перевірка на відвідуване ребра

	for (int count = 0; count < (int)Visited.size(); ++count) { // пройти всю чергу 

		if (Visited[count] == node_num) { // якщо є шуканий елемент
			return true; // повернути 1
		}
	}
	return false; // повернути 0
}

int weight(edge*Edge_List, int start, int finish, int edges) { // визначення ваги ребра

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // поки не кінець списку ребер

		if ((Edge_List + edge_num)->start_node == start) { // якщо перший елемент дорівнює першому шуканому

			if ((Edge_List + edge_num)->finish_node == finish) { // якщо другий елемент дорівнює другому шуканому

				return (Edge_List + edge_num)->weight; //повернути вагу
			}
		}
	}
	return 0; // повернути 0
}

std::vector<int> Dijkstras_algorithm(edge* Edge_List, meta meta_data, int* min_flow, int(*weight)(edge*, int, int, int)) { // алгоритм Едмондса–Карпа

	vector<int> Path, Weight, Visited, opened_nodes;
	queue<int> Queue;

	int cur_node = meta_data.start_node - 1;// номер поточної вершини, поточна вершина - стартова,

	Path.resize(meta_data.num_of_nodes, -1);
	Weight.resize(meta_data.num_of_nodes, 0);
	Queue.push(cur_node); // записати її в чергу

	int** Adjacency_Matrix = ajacency_matrix(Edge_List, meta_data.num_of_edges, meta_data.num_of_nodes); // матриця суміжності

	while (!Queue.empty()) { // поки черга не порожня

		Visited.push_back(cur_node); // поточна вершина відвідана

		for (int column_num = 0; column_num < meta_data.num_of_nodes; ++column_num) { // поки не пройдені усі колонки матриці суміжності

			if (*(*(Adjacency_Matrix + cur_node) + column_num) > 0) { // якщо поточна вершина з'єднана з іншою

				if (!visited(Visited, column_num)) { // перевірити чи не відвідана ця вершини

					opened_nodes.push_back(column_num); // записуємо його у поточний масив відкритих вершин
					std::sort(opened_nodes.begin(), opened_nodes.end()); // відсортувати поточний масив відкритих вершин
				}

				if (Weight[column_num] == 0 || Weight[column_num] > weight(Edge_List, cur_node + 1, column_num + 1, meta_data.num_of_edges) + Weight[cur_node]) { // якщо вага шляху до вершини = 0 або більша ніж через поточну вершину

					Weight[column_num] = weight(Edge_List, cur_node + 1, column_num + 1, meta_data.num_of_edges) + Weight[cur_node]; // оновоти інформацію про вагу до вершини

					Path[column_num] = cur_node; // додати у масив шляху поточну вершину
				}
			}
		}

		for (int count = 0; count < (int)opened_nodes.size(); count++) { // поки не кінець поточного масиву

			Queue.push(opened_nodes[count]); // додати у чергу усі елементи з поточного масиву відкритих вершин
		}
		opened_nodes.clear(); // обнулити масив відкритих вершин

		if (!Queue.empty()) Queue.pop();
		if (!Queue.empty()) cur_node = Queue.front(); // поточна вершина - перша у черзі вершина
	}

	Adjacency_Matrix = del_matrix(Adjacency_Matrix, meta_data.num_of_nodes);

	return get_restored_path(Edge_List, Path, meta_data, min_flow); // повернути масив шляху
}

std::vector<int> get_restored_path(edge* Edge_List, std::vector<int> Path, meta meta_data, int* min_flow) {

	vector<int> Path_uv, Path_vu; // інвертований шлях, шлях між вершинами
	int cur_node = meta_data.finish_node - 1; // поточна вершина - кінцева
	Path_uv.push_back(cur_node + 1); // перша вершина інвертованого шляху - поточна вершина 
	int flow; //потік у поточному ребрі
	*min_flow = INT_MAX; // мінімальна пропускна здатність на шляху
	while (Path_uv.back() != meta_data.start_node) { // поки стартова вершина не поточна 

		cur_node = Path[cur_node]; // нова поточна вершина - вешрина у массиву шляху з номером поточної вершини
		if (cur_node == -1) return Path_vu;
		Path_uv.push_back(cur_node + 1); // записати поточнеy вершину у інвертований шлях	
	}

	for (int count = Path_uv.size() - 1; count >= 0; --count) { // поки не перший елемент інвертоаного шляху

		Path_vu.push_back(Path_uv[count]); // записати її до масиву шляху

		if (count != 0) {
			flow = weight(Edge_List, Path_vu.back(), Path_uv[count - 1], meta_data.num_of_edges); // визначити потік між вершинами
			if (*min_flow > flow) *min_flow = flow; // якщо він меньший за поточний, то зробити його поточним
		}
	}
	return Path_vu; // повернути масив шляху
}

void get_residual_network(edge* Edge_List, int edges, std::vector<int>& Path, int min_flow) { // отримати залишкову мережу

	for (int count = 0; count < (int)Path.size() - 1; count++) {

		for (int edge_num = 0; edge_num < edges; ++edge_num) { // поки не кінець списку ребер

			if ((Edge_List + edge_num)->start_node == Path[count] && (Edge_List + edge_num)->finish_node == Path[count + 1]) { // якщо перший елемент дорівнює першому шуканому
				 // якщо другий елемент дорівнює другому шуканому

				(Edge_List + edge_num)->weight -= min_flow;

			}
		}
	}
}

int price(edge*Edge_List, int start, int finish, int edges) { // визначення ваги ребра

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // поки не кінець списку ребер

		if ((Edge_List + edge_num)->start_node == start) { // якщо перший елемент дорівнює першому шуканому

			if ((Edge_List + edge_num)->finish_node == finish) { // якщо другий елемент дорівнює другому шуканому

				return (Edge_List + edge_num)->price; //повернути значення вартості
			}
		}
	}
	return 0; // повернути 0
}

int get_min_flow(edge* Edge_List, std::vector<int>& Path, int edges) { // отримати пропускну здатність знайденого шляху

	int min_flow, cur_flow; // мінімальний потік, поточний потік
	min_flow = weight(Edge_List, Path.front(), Path[1], edges); // мінімальний потік через перше ребро

	for (int count = 1; count < (int)Path.size() - 1; count++) { // перебрату усі ребра

		cur_flow = weight(Edge_List, Path[count], Path[count + 1], edges);

		if (min_flow > cur_flow) min_flow = cur_flow; // знайти мінімальний потік
	}

	return min_flow; // повернути потік на знайденому шляху
}

int get_path_price(edge* Edge_List, std::vector<int>& Path, int edges, int flow) { // знайти вартість проходу по знайденому шляху

	int sum = 0;

	for (int count = 0; count < (int)Path.size() - 1; count++) { // перебрати усі ребра

		sum += price(Edge_List, Path[count], Path[count + 1], edges); // скласти вартості проходу по ним
	}
	return sum * flow; // помножити вартість на величину потоку
}

void get_min_price_flow(edge* Edge_List, meta meta_data) {

	int cur_price, cur_flow, min_price = 0, max_flow = 0;
	str Path;
	vector<int> cur_Path;
	cout << " < Writing to the output file > " << endl;
	get_path(&Path); // введення шляху до поточного файлу

	FILE* file = open_file(Path, "w+"); // відчинення файлу


	int count = 0;
	do {
		cur_Path = Dijkstras_algorithm(Edge_List, meta_data, &cur_price, price); // пошук мінімального шляху за вартыстю між вершинами за допомогою алгоритма Дейкстри

		if (count == 0) {
			if (cur_Path.empty()) {
				cout << " < There is no path between the entered nodes in the current graph > " << endl; // вивести відповідне повідомлення
				fprintf(file, " < There is no path between the entered nodes in the current graph > \n");
				fclose(file); // закрити файл
				return;
			}
			else printf(" flow / price / path \n");
		}
		else if (cur_Path.empty())break; // якщо шлях більше не існує, вийти із циклу

		cur_flow = get_min_flow(Edge_List, cur_Path, meta_data.num_of_edges); // отримати пропускну здатність знайденого шляху
		cur_price = get_path_price(Edge_List, cur_Path, meta_data.num_of_edges, cur_flow); // знайти вартість проходу по знайденому шляху
		min_price += cur_price; // підрахувати загальну вартість потоків у мережі
		max_flow += cur_flow; // підрахувати величину усіх потоків у мережі
		get_residual_network(Edge_List, meta_data.num_of_edges, cur_Path, cur_flow); // отримати залишкову мережу

		fprintf(file, "%d %d / ", cur_flow, cur_price); // записати знайдений потік 
		printf("%d %d / ", cur_flow, cur_price);
		write_answer(file, cur_Path); // записати знайдений шлях
		count++;
	} while (!cur_Path.empty());

	fprintf(file, " < Minimal price from node \"%d\" to node \"%d\" is  %d > \n", meta_data.start_node, meta_data.finish_node, min_price); // записати значення максимального потоку
	printf(" < Minimal price from node \"%d\" to node \"%d\" is  %d > \n", meta_data.start_node, meta_data.finish_node, min_price);

	fclose(file); // закрити файл
}