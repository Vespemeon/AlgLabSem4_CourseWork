#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include "linked_list.h"
#include "arc.h"
#include <cstdlib>

using namespace std;

class Ford_Fulkerson_Alg {
private:
	List<string> list_recs;
	List<arc> list_arcs;
	List<string> list_nodes;
	int source;
	int sink;
	int **matrix_adj;
public:
	int maxflow;
	Ford_Fulkerson_Alg() {
	}
	Ford_Fulkerson_Alg(List<string> *ini_list) {
		this->list_recs = *ini_list;
		string temp_rec, start, finish, capacity;
		int cap, sublen, count_rev = 1;
		bool fl_double_dir;
		for (int i = 0; i < list_recs.get_size(); i++) {
			fl_double_dir = 0;
			arc temp_arc;
			temp_rec = list_recs.at(i);
			sublen = temp_rec.find_first_of(" ");
			start = temp_rec.substr(0, sublen);
			temp_rec.erase(0, sublen + 1);
			sublen = temp_rec.find_first_of(" ");
			finish = temp_rec.substr(0, sublen);
			temp_rec.erase(0, sublen + 1);
			capacity = temp_rec;
			cap = atoi(capacity.c_str());
			for (int j = 0; j < list_arcs.get_size(); j++)
				if ((list_arcs.at(j).start == finish) && (list_arcs.at(j).finish == start)) {
					fl_double_dir = 1;
					string intermed = "H" + to_string(count_rev);
					temp_arc.start = start;
					temp_arc.finish = intermed;
					temp_arc.capacity = cap;
					list_arcs.push_back(temp_arc);
					temp_arc.start = intermed;
					temp_arc.finish = finish;
					temp_arc.capacity = cap;
					list_arcs.push_back(temp_arc);
					count_rev++;
				}
			if (!fl_double_dir) {
				temp_arc.start = start;
				temp_arc.finish = finish;
				temp_arc.capacity = cap;
				list_arcs.push_back(temp_arc);
			}
		}
		cout << " ";
		for (int i = 0; i < list_arcs.get_size(); i++) {
			if (!list_nodes.isThere(list_arcs.at(i).start)) {
				list_nodes.push_back(list_arcs.at(i).start);
				cout << " " << list_arcs.at(i).start;
				if (list_arcs.at(i).start == "S")
					source = list_nodes.get_size() - 1;
			}
			if (!list_nodes.isThere(list_arcs.at(i).finish)) {
				list_nodes.push_back(list_arcs.at(i).finish);
				cout << " " << list_arcs.at(i).finish;
				if (list_arcs.at(i).finish == "T")
					sink = list_nodes.get_size() - 1;
			}
		}
		cout << "\n";
		matrix_adj = new int*[list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			matrix_adj[i] = new int[list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			for (int j = 0; j < list_nodes.get_size(); j++)
				matrix_adj[i][j] = 0;
		for (int i = 0; i < list_arcs.get_size(); i++) {
			int from, to;
			for (int j = 0; j < list_nodes.get_size(); j++) {
				if (list_nodes.at(j) == list_arcs.at(i).start)
					from = j;
				if (list_nodes.at(j) == list_arcs.at(i).finish)
					to = j;
			}
			matrix_adj[from][to] = list_arcs.at(i).capacity;
			matrix_adj[to][from] = 0;

		}
		for (int i = 0; i < list_nodes.get_size(); i++) {
			cout << list_nodes.at(i) << " ";
			for (int j = 0; j < list_nodes.get_size(); j++)
				cout << matrix_adj[i][j] << " ";
			cout << "\n";
		}
		bool flag = 1;
		maxflow = 0;
		while (flag) {
			bool *visited = new bool[list_nodes.get_size()];
			for (int i = 0; i < list_nodes.get_size(); i++)
				visited[i] = 0;
			int currflow = newflow(source, 100000, visited);
			maxflow += currflow;
			flag = currflow;
			delete[] visited;
		}
	}
	int newflow(int surs, int cmin, bool *vis_orig) {
		if (surs == sink)
			return cmin;
		bool *vis_loc = new bool[list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			vis_loc[i] = vis_orig[i];
		vis_loc[surs] = 1;
		for (int i = 0; i < list_nodes.get_size(); i++)
			if ((matrix_adj[surs][i] > 0) && (!vis_loc[i])) {
				int delta = newflow(i, min(cmin, matrix_adj[surs][i]), vis_loc);
				if (delta > 0) {
					matrix_adj[surs][i] -= delta;
					matrix_adj[i][surs] += delta;
					delete[] vis_loc;
					return delta;
				}
			}
		return 0;
	}
	~Ford_Fulkerson_Alg() {
		for (int i = 0; i < list_nodes.get_size(); i++)
			delete[]matrix_adj[i];
	}
};