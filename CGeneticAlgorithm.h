#pragma once
#include <vector>
#include "CIndividual.h"
#pragma once
#include <random>
#include<iostream>
using namespace std;

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm();
	~CGeneticAlgorithm();
	CGeneticAlgorithm(int iTableLenght);
	void vGeneratePopulation(int valuesTable[], int iKnapsackSize, int weightsTable[]);
	void vRunAlgorithm(int valuesTable[], int iKnapsackSize, int weightsTable[]);

	void vAddNewChildrentoVector2(CIndividual& parent1, CIndividual& parent2, int valuesTable[], int iKnapsackSize, int weightsTable[]);
	void vAddNewChildrentoVector1(CIndividual& parent1, CIndividual& parent2, int valuesTable[], int iKnapsackSize, int weightsTable[]);

	void vShowPopulation();
	void vShowPopulation2();
	void vShowBestIndividual();
	void vDeleteVector1();
	void vDeleteVector2();
	

	
private:
	int table_lenght;
	int population_size;
	int mutation_probability;
	int crossing_probability;
	int number_of_iterations;

	CIndividual* best_individual;

	vector<CIndividual*> population_vector1;
	vector<CIndividual*> population_vector2;
};

