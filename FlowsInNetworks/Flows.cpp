#include "Flows.h"

using namespace std;

template<class T>
T** del_matrix(T** Matrix, int row) { // ��������� �������

	if (Matrix != NULL) { // ���� ������� �� �������
		for (int count = 0; count < row; count++) { // ������ �� ��� ������

			delete[] * (Matrix + count); // �������� �������� �����
		}
		delete[] Matrix; // �������� ����� ��������� �� �����
	}
	return NULL;
}

str* get_path(str* Path) { // ��� ����� �� �����

	cout << " < Enter an absolute path to file (D:\\Docs\\file.txt) > " << endl << ">";
	gets_s(*Path, 100); // ��� ����� �� �����

	if (strstr(*Path, ".txt") == NULL) strcat_s(*Path, 80, ".txt"); // ���� ��������� ����������, ������

	return Path; // ��������� ����� �����
}

FILE* open_file(str Path, const char* mode) { // ������� ����

	FILE* file; // �������� �� ����
	// ��������� �����
	if (fopen_s(&file, Path, mode) != NULL) { // ���� ���� �� �������
		cout << " < ERROR! This File can not be open, or doesn't exist > " << endl; // ��� ����������� ��� �������
		system("pause");
		exit(0); // ��������� ��������
	}

	return file; // ��������� �������� �� ����
}

edge* read_file(str Path, int* edges, int *nodes, int* start, int* finish) { // ���������� ����� � �����

	FILE* file = open_file(Path, "r"); // ��������� �����
	int start_node, finish_node, weight, price;

	fscanf_s(file, "%d %d %d %d", nodes, edges, start, finish);
	if (feof(file)) {

		cout << " < File is incorrectly filled > " << endl;
		system("pause");
		return NULL;
	}

	if (2 >= *nodes || *nodes >= 100) { // �������� �� ���������� �������� �����

		cout << " < Error! Number of nodes must be (2 < nodes < 100) > " << endl;
		return NULL;
	}
	if (*nodes - 1 >= *edges || *edges >= 200) { // �������� �� ���������� �������� �����

		cout << " < Error! Number of edges must be (nodes - 1 < edges < 200) > " << endl;
		return NULL;
	}

	edge* Edge_List = new edge[*edges]; // �������� ���'�� �� ����� �����

	for (int count = 0; count < *edges; count++) { // ���� �� ���������� ���� ����� �����

		fscanf_s(file, "%d %d %d %d", &start_node, &finish_node, &weight, &price);

		if (feof(file)) break; // �������� �� ����� �����

		// �������� �� ���������� �������� �����
		if (start_node <= 0 || start_node > *nodes || finish_node <= 0 || finish_node > *nodes) { // �������� �� ���������� �������� �����
			cout << " < Error! Nunber of nodes cann't be less then null and bigger then number of all nodes > " << endl;
			system("pause");
			return NULL;
		}
		// �������� �� ���������� �������� �����
		if (weight < 0 || price < 0) {

			cout << " < Error! Distance or price between two nodes cann't be less then null > " << endl;
			system("pause");
			return NULL;
		}

		(Edge_List + count)->start_node = start_node; // ����� �������� ������� �����
		(Edge_List + count)->finish_node = finish_node; // ����� ������ ������� ������
		(Edge_List + count)->weight = weight; // ����� ���� �����
		(Edge_List + count)->price = price; // ����� ������� ������� �� �����
	}

	fclose(file); // ��������� �����
	return Edge_List; // ��������� ������ �����
}

void edge_list_output(edge* Edge_List, int edges) { // ������� ������ �����

	if (Edge_List != NULL) { // ���� ������ ����� �� �������
		cout << endl << " < Edge list > " << endl;

		cout << " < e[i] - edge number, v[i] - start node, u[i] - finish node, w[i] - weight, p[i] - price > " << endl;

		if (edges == 0) { // ���� ������� ����� = 0
			cout << " < Graph is null-graph > " << endl << endl; // ������� �������� �����������
			return; // ����� � �������
		}

		for (int num_edge = 0; num_edge < edges; ++num_edge) { // ���� �� ������ ������ �����

			cout << endl << " e[" << num_edge + 1 << "]" << "\t";
			cout << " v[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->start_node; // ������� ���������� �������
			cout << "\t" << " u[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->finish_node; // ������� ������ �������
			cout << "\t" << " w[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->weight;  // ������� ���� �����
			cout << "\t" << " p[" << num_edge + 1 << "] = " << (Edge_List + num_edge)->price << endl;; // ������� ����

		}
	}
	else {
		cout << " < Edge list is empty > " << endl; // ������� �������� �����������
	}

	cout << endl;
}

int** ajacency_matrix(int** Adjacency_Matrix, edge* Edge_List, int edges, int nodes) { // ��������� ������� ��������

	Adjacency_Matrix = new int*[nodes]; // �������� ���'�� �� ������� ��������

	for (int num_row = 0; num_row < nodes; ++num_row) { // �������� ���'�� �� ������� ��������
		*(Adjacency_Matrix + num_row) = new int[nodes];
	}

	for (int row = 0; row < nodes; ++row) { // ���������� �������� �������� ������
		for (int column = 0; column < nodes; ++column) {

			*(*(Adjacency_Matrix + row) + column) = 0;
		}
	}

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // ���������� �������� ��������

		int row = (Edge_List + edge_num)->start_node - 1; // ����� �����
		int column = (Edge_List + edge_num)->finish_node - 1; // ����� �������

		if (*(*(Adjacency_Matrix + row) + column) < (Edge_List + edge_num)->weight) {
			*(*(Adjacency_Matrix + row) + column) = (Edge_List + edge_num)->weight;
		}
	}

	return Adjacency_Matrix; // ��������� ������� ��������
}

//==========================================================================================

void write_answer(FILE* file, std::vector<int>& Path) { // ����� ������ �� ��������� �����

	for (int count = 0; count < (int)Path.size() - 1; count++) { // ���� �� ������������ �������� 

		fprintf(file, "%d->", Path[count]); // �������� ����� ������� �� �����
		printf("%d->", Path[count]);
	}
	fprintf(file, "%d\n", Path.back()); // �������� ������� �������
	printf("%d\n", Path.back());

}

void Edmonds_Karp_algorithm(edge* Edge_List, int nodes, int edges, int start, int finish) { // �������� ��������-�����

	str Path; // ���� �� ��������� ����
	int cur_flow, max_flow = 0; // �������� �� ������������ ����
	vector<int> cur_Path; // �������� ���� � ��
	int** Adjacency_Matrix = NULL; // ������� ��������
	cout << " < Writing to the output file > " << endl;
	get_path(&Path); // �������� ����� �� ��������� �����

	FILE* file = open_file(Path, "w+"); // ��������� �����

	cur_Path = Dijkstras_algorythm(Adjacency_Matrix, Edge_List, nodes, edges, start, finish, &cur_flow, weight); // ����� ���������� ����� �� ��������� �� ��������� ��������� ��������

	if (cur_Path.empty()) { // ���� ���� �� ����

		cout << " < There is no path between the entered nodes in the current graph > " << endl; // ������� �������� �����������
		fprintf(file, " < There is no path between the entered nodes in the current graph > \n");
		fclose(file); // ������� ����
		return;
	}

	max_flow += cur_flow; // ������ �������� ���� �� ����������
	get_residual_network(Edge_List, edges, cur_Path, cur_flow); // �������� ��������� ������
	printf(" flow / path \n");
	do {

		fprintf(file, "%d / ", cur_flow); // �������� ��������� ����
		printf("%d / ", cur_flow);
		write_answer(file, cur_Path); // �������� ��������� ����

		cur_Path = Dijkstras_algorythm(Adjacency_Matrix, Edge_List, nodes, edges, start, finish, &cur_flow, weight); // ����� ���������� ����� �� ��������� �� ��������� ��������� ��������
		if (cur_Path.empty())break; // ���� ���� ����� �� ����, ����� �� �����
		get_residual_network(Edge_List, edges, cur_Path, cur_flow);
		max_flow += cur_flow;

	} while (!cur_Path.empty()); // ���� ���� ���� ��� �������� ���������

	fprintf(file, " < Maximal flow from node \"%d\" to node \"%d\" is  %d / > \n", start, finish, max_flow); // �������� �������� ������������� ������
	printf(" < Maximal flow from node \"%d\" to node \"%d\" is  %d / > \n", start, finish, max_flow);

	Adjacency_Matrix = del_matrix(Adjacency_Matrix, nodes); // ��������� ������� ��������
	fclose(file); // ������� ����
}

bool visited(vector<int> &Visited, int node_num) { // �������� �� ��������� �����

	for (int count = 0; count < (int)Visited.size(); ++count) { // ������ ��� ����� 

		if (Visited[count] == node_num) { // ���� � ������� �������
			return true; // ��������� 1
		}
	}
	return false; // ��������� 0
}

int weight(edge*Edge_List, int start, int finish, int edges) { // ���������� ���� �����

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // ���� �� ����� ������ �����

		if ((Edge_List + edge_num)->start_node == start) { // ���� ������ ������� ������� ������� ��������

			if ((Edge_List + edge_num)->finish_node == finish) { // ���� ������ ������� ������� ������� ��������

				return (Edge_List + edge_num)->weight; //��������� ����
			}
		}
	}
	return 0; // ��������� 0
}

std::vector<int> Dijkstras_algorythm(int** Adjacency_Matrix, edge* Edge_List, int nodes, int edges, int start, int finish, int* min_flow, int(*weight)(edge*, int, int, int)) { // �������� ��������������

	vector<int> Path, Weight, Visited, opened_nodes;
	queue<int> Queue;

	int cur_node = start - 1, flow;// ����� ������� �������, ������� ������� - ��������, ���� � ��������� ���� 
	*min_flow = INT_MAX;  // �������� ��������� �������� �� �����
	Path.resize(nodes, -1);
	Weight.resize(nodes, 0);
	Queue.push(cur_node); // �������� �� � �����

	Adjacency_Matrix = ajacency_matrix(Adjacency_Matrix, Edge_List, edges, nodes);

	while (!Queue.empty()) { // ���� ����� �� �������

		Visited.push_back(cur_node); // ������� ������� �������

		for (int column_num = 0; column_num < nodes; ++column_num) { // ���� �� ������� �� ������� ������� ��������

			if (*(*(Adjacency_Matrix + cur_node) + column_num) > 0) { // ���� ������� ������� �'������ � �����

				if (!visited(Visited, column_num)) { // ��������� �� �� ������� �� �������

					opened_nodes.push_back(column_num); // �������� ���� � �������� ����� �������� ������
					sort(opened_nodes.begin(), opened_nodes.end()); // ����������� �������� ����� �������� ������
				}

				if (Weight[column_num] == 0 || Weight[column_num] > weight(Edge_List, cur_node + 1, column_num + 1, edges) + Weight[cur_node]) { // ���� ���� ����� �� ������� = 0 ��� ����� �� ����� ������� �������

					Weight[column_num] = weight(Edge_List, cur_node + 1, column_num + 1, edges) + Weight[cur_node]; // ������� ���������� ��� ���� �� �������

					Path[column_num] = cur_node; // ������ � ����� ����� ������� �������
				}
			}
		}

		for (int count = 0; count < (int)opened_nodes.size(); count++) { // ���� �� ����� ��������� ������

			Queue.push(opened_nodes[count]); // ������ � ����� �� �������� � ��������� ������ �������� ������
		}
		opened_nodes.clear(); // �������� ����� �������� ������


		if (!Queue.empty()) Queue.pop();
		if (!Queue.empty()) cur_node = Queue.front(); // ������� ������� - ����� � ���� �������

	}

	vector<int> Path_uv, Path_vu; // ������������ ����, ���� �� ���������
	cur_node = finish - 1; // ������� ������� - ������
	Path_uv.push_back(cur_node + 1); // ����� ������� ������������� ����� - ������� ������� 

	while (Path_uv.back() != start) { // ���� �������� ������� �� ������� 

		cur_node = Path[cur_node]; // ���� ������� ������� - ������� � ������� ����� � ������� ������� �������
		if (cur_node == -1) return Path_vu;
		Path_uv.push_back(cur_node + 1); // �������� �������y ������� � ������������ ����	
	}

	for (int count = Path_uv.size() - 1; count >= 0; --count) { // ���� �� ������ ������� ������������ �����

		Path_vu.push_back(Path_uv[count]); // �������� �� �� ������ �����

		if (count != 0) {
			flow = weight(Edge_List, Path_vu.back(), Path_uv[count - 1], edges); // ��������� ���� �� ���������
			*min_flow > flow ? *min_flow = flow : *min_flow; // ���� �� ������� �� ��������, �� ������� ���� ��������
		}
	}

	return Path_vu; // ��������� ����� �����
}

void get_residual_network(edge* Edge_List, int edges, std::vector<int>& Path, int min_flow) { // �������� ��������� ������

	for (int count = 0; count < (int)Path.size() - 1; count++) {

		for (int edge_num = 0; edge_num < edges; ++edge_num) { // ���� �� ����� ������ �����

			if ((Edge_List + edge_num)->start_node == Path[count] && (Edge_List + edge_num)->finish_node == Path[count + 1]) { // ���� ������ ������� ������� ������� ��������
				 // ���� ������ ������� ������� ������� ��������

				(Edge_List + edge_num)->weight -= min_flow;

			}
		}
	}
}

int price(edge*Edge_List, int start, int finish, int edges) { // ���������� ���� �����

	for (int edge_num = 0; edge_num < edges; ++edge_num) { // ���� �� ����� ������ �����

		if ((Edge_List + edge_num)->start_node == start) { // ���� ������ ������� ������� ������� ��������

			if ((Edge_List + edge_num)->finish_node == finish) { // ���� ������ ������� ������� ������� ��������

				return (Edge_List + edge_num)->price; //��������� �������� �������
			}
		}
	}
	return 0; // ��������� 0
}

int get_min_flow(edge* Edge_List, std::vector<int>& Path, int edges) { // �������� ��������� �������� ���������� �����

	int min_flow, cur_flow; // ��������� ����, �������� ����
	min_flow = weight(Edge_List, Path.front(), Path[1], edges); // ��������� ���� ����� ����� �����

	for (int count = 1; count < (int)Path.size() - 1; count++) { // ��������� �� �����

		cur_flow = weight(Edge_List, Path[count], Path[count + 1], edges);

		if (min_flow > cur_flow) min_flow = cur_flow; // ������ ��������� ����
	}

	return min_flow; // ��������� ���� �� ���������� �����
}

int get_path_price(edge* Edge_List, std::vector<int>& Path, int edges, int flow) { // ������ ������� ������� �� ���������� �����

	int sum = 0;

	for (int count = 0; count < (int)Path.size() - 1; count++) { // ��������� �� �����

		sum += price(Edge_List, Path[count], Path[count + 1], edges); // ������� ������� ������� �� ���
	}
	return sum * flow; // ��������� ������� �� �������� ������
}

void get_min_price_flow(edge* Edge_List, int nodes, int edges, int start, int finish) {

	int cur_price, cur_flow, min_price = 0, max_flow = 0;
	str Path;
	vector<int> cur_Path;
	int** Adjacency_Matrix = NULL; // ������� ��������
	cout << " < Writing to the output file > " << endl;
	get_path(&Path); // �������� ����� �� ��������� �����

	FILE* file = open_file(Path, "w+"); // ��������� �����

	cur_Path = Dijkstras_algorythm(Adjacency_Matrix, Edge_List, nodes, edges, start, finish, &cur_price, price); // ����� ���������� ����� �� �������� �� ��������� �� ��������� ��������� ��������

	if (cur_Path.empty()) { // ���� ���� �� ����

		cout << " < There is no path between the entered nodes in the current graph > " << endl; // ������� �������� �����������
		fprintf(file, " < There is no path between the entered nodes in the current graph > \n");
		fclose(file); // ������� ����
		return;
	}

	cur_flow = get_min_flow(Edge_List, cur_Path, edges); // �������� ��������� �������� ���������� �����
	cur_price = get_path_price(Edge_List, cur_Path, edges, cur_flow); // ������ ������� ������� �� ���������� �����
	min_price += cur_price; // ���������� �������� ������� ������ � �����
	max_flow += cur_flow; // ���������� �������� ��� ������ � �����
	get_residual_network(Edge_List, edges, cur_Path, cur_flow); // �������� ��������� ������
	printf(" flow / price / path \n");

	do {

		fprintf(file, "%d %d / ", cur_flow, cur_price); // �������� ��������� ���� 
		printf("%d %d / ", cur_flow, cur_price);
		write_answer(file, cur_Path); // �������� ��������� ����

		cur_Path = Dijkstras_algorythm(Adjacency_Matrix, Edge_List, nodes, edges, start, finish, &cur_price, price); // ����� ���������� ����� �� ��������� �� ��������� ��������� ��������
		if (cur_Path.empty())break; // ���� ���� ����� �� ����, ����� �� �����
		cur_flow = get_min_flow(Edge_List, cur_Path, edges); // �������� ��������� �������� ���������� �����
		get_residual_network(Edge_List, edges, cur_Path, cur_flow);  // �������� ��������� ������
		cur_price = get_path_price(Edge_List, cur_Path, edges, cur_flow); // ������ ������� ������� �� ���������� �����
		min_price += cur_price; // ���������� �������� ������� ������ � �����
		max_flow += cur_flow; // ���������� �������� ��� ������ � �����

	} while (!cur_Path.empty()); // ���� ���� ���� ��� �������� ���������

	fprintf(file, " < Minimal price from node \"%d\" to node \"%d\" is  %d > \n", start, finish, min_price); // �������� �������� ������������� ������
	printf(" < Minimal price from node \"%d\" to node \"%d\" is  %d > \n", start, finish, min_price);

	Adjacency_Matrix = del_matrix(Adjacency_Matrix, nodes); // ��������� ������� ��������
	fclose(file); // ������� ����
}