#include "assignment.h"
#include "problem_structs.h"
#include "linear.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>

int min_review;
int max_paper;

int no_val;
int missing_val;
int maybe_val;
int yes_val;
int verbose;

using namespace std;

void print_problem(problem p) {
	cout << "   ";
	string s = "";
	ostringstream oss(s);
	for(object ob : p.objects) {
		cout << " " << setfill('0') << setw(3) << ob.index;
	}
	cout << endl;
	for(unsigned int i = 0; i < p.agents.size(); i++) {
		std::cout << setfill('0') << setw(3) << p.agents[i].index;
		for(unsigned int j = 0; j < p.objects.size(); j++) {
			if(p.objects[j][i] != p.agents[i][j]) {
				std::cout << " " << "!!!";
			} else {
				if(p.agents[i][j] == no_val) {
					std::cout << " no ";
				} else if(p.agents[i][j] == missing_val) {
					std::cout << " mis";
				} else if(p.agents[i][j] == maybe_val) {
					std::cout << " may";
				} else if(p.agents[i][j] == yes_val) {
					std::cout << " yes";
				} else {
					std::cout << " a" << setfill('0') << setw(2) << p.agents[i][j];
				}
			}
		}
		std::cout << std::endl;
	}
}

void print_solution(problem& p) {
	int no_n = 0;
	int may_n = 0;
	int mis_n = 0;
	int yes_n = 0;
	int bad_n = 0;

	long sum = 0;
	for(agent a : p.agents) {
		if (verbose) std::cout << "A" << setfill('0') << setw(3) << a.index << " :";
		for(int i : a.held) {
			sum += a[i];
			if (verbose) std::cout << " O" << setfill('0') << setw(3) << p.objects[i].index;
			if(a[i] == no_val) {
				no_n++;
			} else if(a[i] == missing_val) {
				mis_n++;
			} else if(a[i] == maybe_val) {
				may_n++;
			} else if(a[i] == yes_val) {
				yes_n++;
			} else {
				bad_n++;
			}
		}
		
	}
	std::cout << "No value:" << no_val << endl;
	std::cout << "Missing value:" << missing_val << endl;
	std::cout << "Maybe value:" << maybe_val << endl;
	std::cout << "Yes value:" << yes_val << endl;
	std::cout << "Min Reviewers:" << min_review << endl;
	std::cout << "Max Papers:" << max_paper << endl;

	std::cout << "Total Value: " << sum/10 << std::endl;
	std::cout << "Average Value: " << ((double)(sum/10))/((double)p.agents.size()) << std::endl;
	std::cout << "Bad Matchings: " << bad_n << std::endl;
	std::cout << "Disliked Matchings: " << no_n << std::endl;
	std::cout << "Unknown Matchings: " << mis_n << std::endl;
	std::cout << "Maybe Matchings: " << may_n << std::endl;
	std::cout << "Approved Matchings: " << yes_n << std::endl;


}

int solve_file(char* filename) {
	problem p(filename, no_val, missing_val, maybe_val, yes_val);
	if(min_review*p.objects.size() > max_paper*p.agents.size()) {
		cout << "I can't let you do that dave, there aren't enough papers" << endl;
	}
	if (verbose) print_problem(p);
	linear_solve(p, max_paper, min_review);
	print_solution(p);
	return 0;
}

int main(int argc, char* argv[]) {
	// arg 1 filename 
	// arg2 max per reviewer 
	// arg3 min per paper 
	// arg4 no val 
	// arg 5 missing val 
	// arg 6 maybe val
	// arg 7 yes val
	// arg 8 verbose
	max_paper = atoi(argv[2]);
	min_review = atoi(argv[3]);
	no_val = atoi(argv[4]);
	missing_val = atoi(argv[5]);
	maybe_val = atoi(argv[6]);
	yes_val = atoi(argv[7]);
	verbose = atoi(argv[8]);

	if(argc == 9) {
		solve_file(argv[1]);
	}
}
