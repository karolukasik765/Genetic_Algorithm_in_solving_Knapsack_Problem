#pragma once
#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <vector>
#include <random>
#include<iostream>

using namespace std;

class CKnapsackProblem
{
public:
	
	CKnapsackProblem(int iTableSize, int iKnapsackSize, int weightsTable[], int valuesTable[]);
	CKnapsackProblem(string file_path);
	~CKnapsackProblem();
	int vLoadData(string file_path);
	int iResultForGenotype(int genotype[]);
	void vRunGeneticAlgorithm();
	int vCheckCorrectness(int iTableSize, int iKnapsackSize);

	//int iKnapsackProblemResult();
	
private:
	
	int table_lenght;
	int i_knapsack_size;
	int* pc_weights_table;
	int* pc_values_table;
	

};

