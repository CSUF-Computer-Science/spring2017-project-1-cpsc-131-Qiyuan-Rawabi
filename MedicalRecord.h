#pragma once
#include <string>
#include <stdexcept>

#include "Baby.h"

using namespace std;

class MedicalRecord {

public:
	MedicalRecord();										// default constructor
	MedicalRecord(const MedicalRecord& rec);				// copy constructor
	~MedicalRecord();										// destructor
	MedicalRecord& operator= (const MedicalRecord& rec);	// assignment operator overload

															// Load information from a text file with the given filename.
	void buildMedicalRecordfromDatafile(string filename);

	// return the most frequently appearing name in the text file
	string mostPopularName();

	// return the number of baby records loaded from the text file
	int numberOfBirths();

	// return the number of babies who had birth weight < 2500 grams
	int numberOfBabiesWithLowBirthWeight();

	// return the number of babies who have the name contained in string s
	int numberOfBabiesWithName(string s);

private:
	// update the data structure with information contained in Baby object
	Baby* babyWeightRec;
	int numOfEntry;
	string uniNameList[1000];
	int uniNameCount[1000] = { 0 };
	void addEntry(const Baby& b);

	// Add private member variables for your data structure along with any 
	// other variables required to implement the public member functions
};

MedicalRecord::MedicalRecord()
{
	babyWeightRec = new Baby[1000000];
	numOfEntry = 0;
}

MedicalRecord::MedicalRecord(const MedicalRecord& rec)
{
	babyWeightRec = new Baby[1000000];
	numOfEntry = rec.numOfEntry;
	for (int i = 0; i < numOfEntry; i++)
	{
		babyWeightRec[i] = rec.babyWeightRec[i];
	}

}

MedicalRecord::~MedicalRecord()
{
	delete[] babyWeightRec;
}

MedicalRecord& MedicalRecord::operator= (const MedicalRecord& rec)
{
	if (this != &rec)
	{
		delete[] babyWeightRec;
		numOfEntry = rec.numOfEntry;
		babyWeightRec = new Baby[1000000];
		for (int i = 0; i < numOfEntry; i++)
		{
			babyWeightRec[i] = rec.babyWeightRec[i];
		}
	}
	return *this;
}

void MedicalRecord::addEntry(const Baby& b)
{
	babyWeightRec[numOfEntry] = b;
	numOfEntry++;
}

void MedicalRecord::buildMedicalRecordfromDatafile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string name;
		int weight;
		while (myfile >> name >> weight) {
			// cout << name << " " << weight << endl;
			Baby b(name, weight);
			addEntry(b);
		}
		myfile.close();
	}
	else
		throw invalid_argument("Could not open file " + filename);
}

string MedicalRecord::mostPopularName()
{
	int nOfUniN = 1;
	uniNameList[0] = babyWeightRec[0].getName();
	for (int i = 0; i < numOfEntry; i++)
	{
		int j = 0;
		for (j = 0; j < nOfUniN; j++)
		{
			if (uniNameList[j] == babyWeightRec[i].getName())
			{
				uniNameCount[j]++;
				break;
			}
		}
		if (j == nOfUniN)
		{
			uniNameList[nOfUniN] = babyWeightRec[i].getName();
			uniNameCount[nOfUniN] = 1;
			nOfUniN++;
		}
	}

	int max = uniNameCount[0], index = 0;
	for (int i = 0; i < nOfUniN; i++)
	{
		if (uniNameCount[i] > max)
		{
			max = uniNameCount[i];
			index = i;
		}
	}
	return uniNameList[index];
}

int MedicalRecord::numberOfBirths()
{
	return numOfEntry;
}

int MedicalRecord::numberOfBabiesWithLowBirthWeight()
{
	int count = 0;
	for (int i = 0; i < numOfEntry; i++)
	{
		if (babyWeightRec[i].weight < 2500)
			count++;
	}
	return count;
}

int MedicalRecord::numberOfBabiesWithName(string s)
{
	int count = 0;
	for (int i = 0; i < numOfEntry; i++)
	{
		if (babyWeightRec[i].name == s)
			count++;
	}
	return count;
}
