#pragma once
#include <string>
#include <vector>
#define INCREASED_SIZE 10
#define EPSILON 1
struct object
{
	int index;
	std::vector<int> held_by;
	long price;
	std::string name;
	std::vector<long> values;
	object(int index, std::string name);
	long& operator[](std::size_t index)       { return this->values[index]; }
    const long& operator[](std::size_t index) const { return this->values[index]; }
};
struct agent
{
	int index;
	std::vector<int> held;
	std::vector<long> values; 
	agent(int index);
	long& operator[](std::size_t index)       { return this->values[index]; }
    const long& operator[](std::size_t index) const { return this->values[index]; }
};
struct problem {
	std::vector<agent> agents;
	std::vector<object> objects;
	problem(char* filename, int no_val, int missing_val, int maybe_val, int yes_val);
};