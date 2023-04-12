#pragma once
#include<iostream>
using namespace std;

class CIndividual
{
public:
	CIndividual();
	CIndividual(int iTableLenght, bool randomize);
	CIndividual(int iTableLenght,int pcGenotype[]);
	~CIndividual();
	void vSetFitnessandWeight(int valuesTable[], int iKnapsackSize, int weightsTable[]);
	void vMutateIndividual(int fMutationProb);
	void operator=(CIndividual& pcOther);


	void vShowGenotype();
	int iGetWeightsSum();
	int iGetFitness();
	void iSetWeightsSum(int iNewWeightsSum);
	void iSetFitness(int iNewFitness);
	CIndividual* cCreateChildrenWith(CIndividual& pcOther, int iIndex);
	bool bIsbetterThan(CIndividual& parent2);

private:
	int table_lenght;
	int* t_genotype;
	int fitness; //values sum
	int weights_sum;

};

