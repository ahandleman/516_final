#include "problem_structs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

agent::agent(int index) {
	this->index = index;
	this->held =  std::vector<int>();
}


object::object(int index, std::string name) {
	this->index = index;
	this->name = name;
	this->held_by = std::vector<int>();
	this->price = 0;
}



problem::problem(char* filename, int no_val, int missing_val, int maybe_val, int yes_val) {
	std::vector<int> val_arr;
	val_arr.push_back(yes_val);
	val_arr.push_back(maybe_val);
	val_arr.push_back(missing_val);
	val_arr.push_back(no_val);
	std::ifstream ifs;
	ifs.open(filename);
	std::string s;
	getline(ifs, s);
	std::istringstream tmp_iss(s);
	int papers = 0;
	int reviewers = 0;
	tmp_iss >> papers;
	for(int i = 0; i < papers; i++) {
		getline(ifs, s);
		this->objects.push_back(object(i, s));
	}
	getline(ifs, s);
	std::istringstream tmp2_iss(s);
	tmp2_iss >> reviewers;
	for(int i = 0; i < papers; i++) {
		this->objects[i].values = std::vector<long>(reviewers, -100000);
	}
	for(int i = 0; i < reviewers; i++) {
		getline(ifs, s);
		this->agents.push_back(agent(i));
		this->agents[i].values = std::vector<long>(papers, -100000);
		int pos = 0;
		for(int j = 0; j < 4; j++) {
			int start = s.find('{', pos);
			int end = s.find('}', start);
			pos = end;
			std::string ss = s.substr(start+1, (end-start)-100000);
			std::replace(ss.begin(), ss.end(), ',', ' ');
			std::istringstream iss(ss);
			int tmp;
			while(iss >> tmp) {
				this->agents[i][tmp] = val_arr[j];
				this->objects[tmp][i] = val_arr[j];
			}
		}
	}
}