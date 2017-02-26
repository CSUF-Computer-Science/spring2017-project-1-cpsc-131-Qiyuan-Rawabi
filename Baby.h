#pragma once
#include <string>

using namespace std;

// class that contains information related to a single birth or baby name
class Baby {

public:
	Baby();									// default constructor
	Baby(string s, int w);					// constructor
	Baby(const Baby& baby);					// copy constructor
	Baby& operator= (const Baby& baby);		// assignment operator overload
	int getWeight();						// a "getter" method
	string getName();						// a "getter" method

private:
	string name;
	int weight;
	friend class MedicalRecord;
};

Baby::Baby()
{
	name = "";
	weight = 0;
}

Baby::Baby(string s, int w)
{
	name = s;
	weight = w;
}

Baby::Baby(const Baby& baby)
{
	name = baby.name;
	weight = baby.weight;
}

Baby& Baby::operator= (const Baby& baby)
{
	if (this != &baby)
	{
		name = baby.name;
		weight = baby.weight;
	}
	return *this;
}

int Baby::getWeight()
{
	return weight;
}

string Baby::getName()
{
	return name;
}
