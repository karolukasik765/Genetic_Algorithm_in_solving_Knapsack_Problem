#include "CGeneticAlgorithm.h"
#pragma once
#include <vector>
#include "CIndividual.h"
#pragma once
#include <random>
#include<iostream>
using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm() {

	table_lenght = 10;
	population_size = 100;
	mutation_probability=10;
	crossing_probability = 60;
	number_of_iterations = 100;

	best_individual = new CIndividual(400, false);

}
CGeneticAlgorithm::CGeneticAlgorithm(int iTableLenght) {

	table_lenght= iTableLenght;
	population_size = 100;
	mutation_probability = 10;
	crossing_probability = 60;
	number_of_iterations = 10000;

	best_individual = new CIndividual(iTableLenght,false);

}

void CGeneticAlgorithm::vGeneratePopulation(int valuesTable[], int iKnapsackSize, int weightsTable[]) {

	for (int ii = 0; ii < population_size; ii++)
	{
		CIndividual* new_individual = new CIndividual(table_lenght,true);

		//calculating individual's features and checking if we got new best individual
		new_individual->vSetFitnessandWeight(valuesTable,iKnapsackSize,weightsTable);
		//cout << new_individual->iGetWeightsSum();
		//new_individual->vShowGenotype();
		if ((*new_individual).iGetWeightsSum() >= 0) {
			if ((*new_individual).iGetFitness() > (*best_individual).iGetFitness()) {
				best_individual->operator=(*new_individual);
			}
		}

		population_vector1.push_back(new_individual);

	}
}
CGeneticAlgorithm::~CGeneticAlgorithm(){
	delete best_individual;

	vDeleteVector1();
	vDeleteVector2();

}


void CGeneticAlgorithm::vDeleteVector1() {

	for (int jj = 0; jj < population_vector1.size(); jj++) {

		delete population_vector1.at(jj);

	}

}
void CGeneticAlgorithm::vDeleteVector2() {

	for (int jj = 0; jj < population_vector2.size(); jj++) {

		delete population_vector2.at(jj);

	}

}

void CGeneticAlgorithm::vShowPopulation() {
	for (int ii = 0; ii < population_size; ii++){
		(*population_vector1[ii]).vShowGenotype();
	}
}

void CGeneticAlgorithm::vShowPopulation2() {
	for (int ii = 0; ii < population_size; ii++) {
		(*population_vector2[ii]).vShowGenotype();
	}
}

void CGeneticAlgorithm::vShowBestIndividual() {
	cout << "Best Individual: " << endl;
	(*best_individual).vShowGenotype();
	cout << "fitness: " << (*best_individual).iGetFitness()<< endl;
	cout << "weights sum: " << (*best_individual).iGetWeightsSum() << endl;
}

void CGeneticAlgorithm::vRunAlgorithm(int valuesTable[], int iKnapsackSize, int weightsTable[]) {
	for (int ii = 0; ii < number_of_iterations; ii++) {
		if (ii % 2 == 0) {
			while (population_vector2.size() < population_size) {


				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distrib(0, population_size - 1);

				int parent1 = distrib(gen);
				int parent2 = distrib(gen);
				int parent3 = distrib(gen);
				int parent4 = distrib(gen);


				//cout << parent1 << parent2 << parent3 << parent4 << endl;

				if (population_vector1[parent1]->bIsbetterThan(*population_vector1[parent2])) {
					if (population_vector1[parent3]->bIsbetterThan(*population_vector1[parent4])) {
						vAddNewChildrentoVector2(*population_vector1[parent1], *population_vector1[parent3], valuesTable, iKnapsackSize, weightsTable);
					}
					else {
						vAddNewChildrentoVector2(*population_vector1[parent1], *population_vector1[parent4], valuesTable, iKnapsackSize, weightsTable);
					}
				}
				else {
					if (population_vector1[parent3]->bIsbetterThan(*population_vector1[parent4])) {
						vAddNewChildrentoVector2(*population_vector1[parent2], *population_vector1[parent3], valuesTable, iKnapsackSize, weightsTable);
					}
					else {
						vAddNewChildrentoVector2(*population_vector1[parent2], *population_vector1[parent4], valuesTable, iKnapsackSize, weightsTable);
					}
				}

			}
			population_vector1.clear();
			//vShowPopulation2();
		}
		else {
			while (population_vector1.size() < population_size) {


				std::random_device rd;
				std::mt19937 gen(rd());
				std::uniform_int_distribution<> distrib(0, population_size - 1);

				int parent1 = distrib(gen);
				int parent2 = distrib(gen);
				int parent3 = distrib(gen);
				int parent4 = distrib(gen);


				if (population_vector2[parent1]->bIsbetterThan(*population_vector2[parent2])) {
					if (population_vector2[parent3]->bIsbetterThan(*population_vector2[parent4])) {
						vAddNewChildrentoVector1(*population_vector2[parent1], *population_vector2[parent3], valuesTable, iKnapsackSize, weightsTable);
					}
					else {
						vAddNewChildrentoVector1(*population_vector2[parent1], *population_vector2[parent4], valuesTable, iKnapsackSize, weightsTable);
					}
				}
				else {
					if (population_vector2[parent3]->bIsbetterThan(*population_vector2[parent4])) {
						vAddNewChildrentoVector1(*population_vector2[parent2], *population_vector2[parent3], valuesTable, iKnapsackSize, weightsTable);
					}
					else {
						vAddNewChildrentoVector1(*population_vector2[parent2], *population_vector2[parent4], valuesTable, iKnapsackSize, weightsTable);
					}
				}

			}
			population_vector2.clear();
			//vShowPopulation();
		}
		
	}
}
void CGeneticAlgorithm::vAddNewChildrentoVector2(CIndividual& parent1, CIndividual& parent2, int valuesTable[], int iKnapsackSize, int weightsTable[]) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 100);

	CIndividual* new_individual;
	CIndividual* new_individual2;

	int crossing_value  = distrib(gen);
	
	if (crossing_value < crossing_probability) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib2(1, table_lenght - 1);

		int cutting_point = distrib2(gen);

		new_individual = parent1.cCreateChildrenWith(parent2, cutting_point);
		new_individual2 = parent2.cCreateChildrenWith(parent1, cutting_point);
	}
	else {
		new_individual = new CIndividual(table_lenght,false);
		new_individual->operator=(parent1);
		
		new_individual2 = new CIndividual(table_lenght, false);
		new_individual2->operator=(parent2);
		/*
		new_individual = &parent1;
		new_individual2 = &parent2;
		*/
	}
	
	//new_individual->vMutateIndividual(mutation_probability);
	//new_individual2->vMutateIndividual(mutation_probability);
	// 
	// 
	//NEW CODE - MODIFICATION DURING CLASSES
	/*
	std::uniform_int_distribution<> dismod(0, population_size - 1);

	int mod1 = dismod(gen);
	int mod2 = dismod(gen);
	*/

	new_individual->vMutateIndividual(mutation_probability);
	new_individual2->vMutateIndividual(mutation_probability);
	
	
	new_individual->vSetFitnessandWeight(valuesTable, iKnapsackSize, weightsTable);
	new_individual2->vSetFitnessandWeight(valuesTable, iKnapsackSize, weightsTable);


	population_vector2.push_back(new_individual);
	population_vector2.push_back(new_individual2);

	if (new_individual->iGetWeightsSum() >= 0) {
		if (new_individual->iGetFitness() > best_individual->iGetFitness()) {
			best_individual->operator=(*new_individual);
		}
	}


}

void CGeneticAlgorithm::vAddNewChildrentoVector1(CIndividual& parent1, CIndividual& parent2, int valuesTable[], int iKnapsackSize, int weightsTable[]) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 100);

	CIndividual* new_individual;
	CIndividual* new_individual2;

	int crossing_value = distrib(gen);

	if (crossing_value < crossing_probability) {

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib2(1, table_lenght - 1);

		int cutting_point = distrib2(gen);

		new_individual = parent1.cCreateChildrenWith(parent2, cutting_point);
		new_individual2 = parent2.cCreateChildrenWith(parent1, cutting_point);
	}
	else {
		new_individual = new CIndividual(table_lenght, false);
		new_individual->operator=(parent1);

		new_individual2 = new CIndividual(table_lenght, false);
		new_individual2->operator=(parent2);
		/*
		new_individual = &parent1;
		new_individual2 = &parent2;
		*/
	}

	//NEW CODE - MODYFICATION DURING CLASSES

	/*
	std::uniform_int_distribution<> dismod(0, population_size - 1);

	int mod1 = dismod(gen);
	int mod2 = dismod(gen);
	*/

	new_individual->vMutateIndividual(mutation_probability);
	new_individual2->vMutateIndividual(mutation_probability);


	new_individual->vSetFitnessandWeight(valuesTable, iKnapsackSize, weightsTable);
	new_individual2->vSetFitnessandWeight(valuesTable, iKnapsackSize, weightsTable);


	population_vector1.push_back(new_individual);
	population_vector1.push_back(new_individual2);

	if (new_individual->iGetWeightsSum() >= 0) {
		if (new_individual->iGetFitness() > best_individual->iGetFitness()) {
			best_individual->operator=(*new_individual);
		}
	}


}




