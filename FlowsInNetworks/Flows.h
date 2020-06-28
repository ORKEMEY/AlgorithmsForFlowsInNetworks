#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include <stdio.h>
#include<algorithm>

typedef char str[100]; // �����

struct edge {

	int start_node, finish_node, weight, price;

	edge() {

		start_node = finish_node = weight = price = 0;
	}
};

struct meta {
	//������ ����� �����
	int num_of_nodes, num_of_edges, start_node, finish_node; // ������� ������ �� ����� �����, ��������� �� ������ �������
	meta() {
		num_of_nodes = num_of_edges = start_node = finish_node = 0;
	}
};


template<class T>
T** del_matrix(T** Matrix, int row); // ��������� �������
str* get_path(str* Path); // ��� ����� �� �����
FILE* open_file(str Path, const char* mode); // ������� ����
edge* read_file(str Path, meta* meta_data); // ���������� ����� � �����
void edge_list_output(edge* Edge_List, int edges); // ���� ������ �����
int** ajacency_matrix(edge* Edge_List, int edges, int nodes);
bool visited(std::vector<int>& Visited, int node_num); // �������� �� ��������� �����
int weight(edge*Edge_List, int start, int finish, int edges); // ���������� ���� �����
void connect_file(edge** Edge_List, str* Path, meta* meta_data);
bool check_meta(meta meta_data);
bool check_edge(meta meta_data, edge edge);

void Edmonds_Karp_algorithm(edge* Edge_List, meta meta_data); // �������� ��������������
void get_residual_network(edge* Edge_List, int edges, std::vector<int>& Path, int min_flow);
void write_answer(FILE* file, std::vector<int>& Path);
std::vector<int> Dijkstras_algorithm( edge* Edge_List, meta meta_data, int* min_flow, int(*weight)(edge*, int, int, int));
int get_min_flow(edge* Edge_List, std::vector<int>& Path, int edges);
void get_min_price_flow(edge* Edge_List, meta meta_data);
int get_path_price(edge* Edge_List, std::vector<int>& Path, int edges, int flow);
std::vector<int> get_restored_path(edge* Edge_List, std::vector<int> Path, meta meta_data, int* min_flow);
