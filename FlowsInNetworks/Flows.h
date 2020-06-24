#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>

typedef char str[100]; // рядок

struct edge {

	int start_node, finish_node, weight, price;

	edge() {

		start_node = finish_node = weight = price = NULL;
	}
};

template<class T>
T** del_matrix(T** Matrix, int row); // видалення матриці
str* get_path(str* Path); // ввід шляху до файлу
FILE* open_file(str Path, const char* mode); // відкрити файл
edge* read_file(str Path, int* edges, int *nodes, int* satrt, int* finish); // зчитуфання графу з файлу
void edge_list_output(edge* Edge_List, int edges); // вивід списка ребер
int** ajacency_matrix(int** Adjacency_Matrix, edge* Edge_List, int edges, int nodes);
bool visited(std::vector<int>& Visited, int node_num); // перевірка на відвідуване ребра
int weight(edge*Edge_List, int start, int finish, int edges); // визначення ваги ребра

void Edmonds_Karp_algorithm(edge* Edge_List, int nodes, int edges, int start, int finish); // алгоритм Едмондса–Карпа
void get_residual_network(edge* Edge_List, int edges, std::vector<int>& Path, int min_flow);
void write_answer(FILE* file, std::vector<int>& Path);
std::vector<int> Dijkstras_algorythm(int** Adjacency_Matrix, edge* Edge_List, int nodes, int edges, int start, int finish, int* min_flow, int(*weight)(edge*, int, int, int));
int get_min_flow(edge* Edge_List, std::vector<int>& Path, int edges);
void get_min_price_flow(edge* Edge_List, int nodes, int edges, int start, int finish);
int get_path_price(edge* Edge_List, std::vector<int>& Path, int edges, int flow);

