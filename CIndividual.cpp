#include "CIndividual.h"
#pragma once
#include <random>
#include<iostream>
using namespace std;

CIndividual::CIndividual() {

	table_lenght = 10;
	t_genotype = new int[table_lenght];
	fitness = 0;
	weights_sum = 0;

	for (int ii = 0; ii < table_lenght; ii++)
	{
		t_genotype[ii] = 0;
	}
}
CIndividual::CIndividual(int iTableLenght, int pcGenotype[]) {

	table_lenght = iTableLenght;
	t_genotype = pcGenotype;
	fitness = 0;
	weights_sum = 0;

}

CIndividual::CIndividual(int iTableLenght, bool randomize) {

	table_lenght = iTableLenght;
	t_genotype = new int[iTableLenght];
	fitness = 0;
	weights_sum = 0;

	if (randomize == true) {
		//cout << "Randomized genotype " <<endl;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, 1);


		for (int ii = 0; ii < table_lenght; ii++)
		{
			t_genotype[ii] = distrib(gen);

		}
	}
	else {
		//cout << "All zeros genotype " <<endl;

		for (int ii = 0; ii < table_lenght; ii++)
		{
			t_genotype[ii] = 0;

		}
	}

}

CIndividual::~CIndividual() {
	
	delete[] t_genotype;
}

void CIndividual::vSetFitnessandWeight(int valuesTable[], int iKnapsackSize, int weightsTable[]){

	int result=0;
	weights_sum=0;

	for (int ii = 0; ii < table_lenght; ii++)
	{
		result += t_genotype[ii] * valuesTable[ii];
	}
	fitness = result;

	for (int ii = 0; ii < table_lenght; ii++)
	{
		weights_sum += t_genotype[ii] * weightsTable[ii];
	}
	if (weights_sum > iKnapsackSize) {
		weights_sum = iKnapsackSize - weights_sum;
	}
	//cout << "Fitness: " << fitness << endl;
	//cout << "Weight sum: " << weights_sum << endl;
}

void CIndividual::vShowGenotype() {

	cout << "Genotyp: "<< endl;
	for (int ii = 0; ii < table_lenght; ii++)
	{
		cout << t_genotype[ii] <<" ";
	}
	cout << endl;
}
void CIndividual::operator=(CIndividual& pcOther) {

	weights_sum = pcOther.weights_sum;
	fitness = pcOther.fitness;

	for (int ii = 0; ii < table_lenght; ii++)
	{
		t_genotype[ii] = pcOther.t_genotype[ii];
	}	
}

int CIndividual::iGetWeightsSum() {
	return weights_sum;
}

int CIndividual::iGetFitness() {
	return fitness;
}
void CIndividual::iSetWeightsSum(int iNewWeightsSum) {
	weights_sum=iNewWeightsSum;
}

void CIndividual::iSetFitness(int iNewFitness) {
	fitness=iNewFitness;
}

CIndividual* CIndividual::cCreateChildrenWith(CIndividual& pcOther, int iIndex){

	
	int* new_table = new int[table_lenght];

	for (int ii = 0; ii < iIndex; ii++)
	{
		new_table[ii] = t_genotype[ii];
	}
	for (int ii = iIndex; ii < table_lenght; ii++)
	{
		new_table[ii] = pcOther.t_genotype[ii];
	}

	CIndividual* new_obiect = new CIndividual(table_lenght, new_table);
	return new_obiect;
}

void CIndividual::vMutateIndividual(int fMutationProb) {

	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(1, 100);

	int prob = 0;

	for (int ii = 0; ii < table_lenght; ii++)
	{
		
			prob = distrib(gen);
			if (prob <= fMutationProb) {
				if (t_genotype[ii] == 1) { t_genotype[ii] = 0; }
				else { t_genotype[ii] = 1; }
			}
		
	}
	
}

bool CIndividual::bIsbetterThan(CIndividual& parent2) {
	if (weights_sum >= 0 && parent2.iGetWeightsSum()>=0) {
		if (fitness > parent2.iGetFitness()) {return true;}
		else {return false; }
		
	}
	else if (weights_sum > 0 && parent2.iGetWeightsSum() < 0) {return true; }
	else if (weights_sum < 0 && parent2.iGetWeightsSum() > 0) { ; return false; }
	else {
		
		double d_weights1 = weights_sum;
		double d_weights2 = parent2.iGetWeightsSum();
		double d_fit1 = fitness;
		double d_fit2 = parent2.iGetFitness();
		if ((-1) * d_fit1 / d_weights1 > (-1) * d_fit2 / d_weights2) {
			return true;
		}
		else { return false; }
	}
}
