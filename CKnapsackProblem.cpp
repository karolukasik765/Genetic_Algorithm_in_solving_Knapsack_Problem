#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include "CIndividual.h"
#include <vector>
#include <random>
#include<iostream>
#pragma once
#define CKNAP_UNABLE_TO_OPEN -1;
#define CKNAP_INVALID_ARGUMENT_ERROR -2;
using namespace std;

using std::cerr;
#include <fstream>
using std::ifstream;
#include <cstdlib> 



CKnapsackProblem::CKnapsackProblem(int iTableSize, int iKnapsackSize, int weightsTable[], int valuesTable[]){

	vCheckCorrectness(iTableSize, iKnapsackSize);
	table_lenght = iTableSize;
	i_knapsack_size=iKnapsackSize;
	pc_weights_table = weightsTable;
	pc_values_table = valuesTable;
}
CKnapsackProblem::CKnapsackProblem(string file_path) {
	vLoadData(file_path);
	
}

int CKnapsackProblem::vLoadData(string file_path) {

	fstream file(file_path, ios_base::in);
	if (!file.is_open())
		return CKNAP_UNABLE_TO_OPEN;


	int newKnapsackSize;
	int lenght;

	file >> lenght;
	table_lenght = lenght;

	pc_weights_table = new int[lenght];
	pc_values_table = new int[lenght];

	file >> newKnapsackSize;
	if (newKnapsackSize < 0) {
		return CKNAP_INVALID_ARGUMENT_ERROR;
	}
	i_knapsack_size = newKnapsackSize;
	

	int a, b;
	int ii = 0;
	while (file >> a >> b &&ii<lenght)
	{
		pc_values_table[ii] = a;
		pc_weights_table[ii] = b;
		//cout << a << " " << b << endl;
		ii+= 1;

	}
	file.close();

	return 0;

}
int CKnapsackProblem::vCheckCorrectness(int iTableSize, int iKnapsackSize) {

	if (iKnapsackSize < 0 || iTableSize<0) {
		return CKNAP_INVALID_ARGUMENT_ERROR;
	}
	return 0;
}



CKnapsackProblem::~CKnapsackProblem() {
	delete[] pc_weights_table;
	delete[] pc_values_table;
}


void CKnapsackProblem::vRunGeneticAlgorithm() {

	CGeneticAlgorithm algorytm(table_lenght);

	algorytm.vGeneratePopulation(pc_values_table, i_knapsack_size, pc_weights_table);

	algorytm.vShowBestIndividual();
	algorytm.vRunAlgorithm(pc_values_table, i_knapsack_size, pc_weights_table);

	algorytm.vShowBestIndividual();
}



int CKnapsackProblem::iResultForGenotype(int genotype[]){
	
		int fitness = 0;
		int weight = 0;

		
		for (int ii = 0; ii < table_lenght; ii++)
		{
			weight += genotype[ii] * pc_weights_table[ii];
		}

		if (weight < i_knapsack_size){
			for (int ii = 0; ii < table_lenght; ii++)
			{
				fitness += genotype[ii] * pc_values_table[ii];
			}
		}
		return fitness;
	
}




	