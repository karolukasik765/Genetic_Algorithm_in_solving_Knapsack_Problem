#pragma once
#include<iostream>
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {

	
	int values[] = {55,10,47,5,4,50,8,61,85,87};
	int weights[] = {95,4,60,32,23,72,80,62,65,46};
	int max = 269;


	CKnapsackProblem problem2("plik200genow.txt"); 
	// Get starting timepoint
	auto start = high_resolution_clock::now();

	problem2.vRunGeneticAlgorithm();

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;




	//CKnapsackProblem problem(10, max, weights, values);
	
	
		//(int iTableSize, int iKnapsackSize, int weightsTable[], int valuesTable[])

	//CGeneticAlgorithm algorytm(10);

	//algorytm.vGeneratePopulation(values, max, weights);
	//algorytm.vShowPopulation();
	//algorytm.vShowBestIndividual();

	/*
	int i = 2;
	double r = i;
	cout << r / 12 << " " << i / 12 << " " << 9 / 23 << endl;
	*/
	/*
	int values[] ={ 5, 1, 4, 3 };
	int weights[] ={ 4,1,3,2 };
	int max = 5;
	*/
	/*

	CGeneticAlgorithm algorytm(10);

	algorytm.vGeneratePopulation(values, max, weights);
	//algorytm.vShowPopulation();
	algorytm.vShowBestIndividual();

	algorytm.vRunAlgorithm(values, max, weights);

	//algorytm.vShowPopulation2();
	algorytm.vShowBestIndividual();
	*/


	
	/*
	int os1[] = {1,1,1,1};
	int os2[] = {0,0,1,1};
	int os3[] = {1,1,1,0};
	int os4[] = {0,1,0,1};

	CIndividual Indiv_1(4, os1);//  13/(5)=2,6
	CIndividual Indiv_2(4, os2);
	CIndividual Indiv_3(4, os3);// 10/(3)=3,3
	CIndividual Indiv_4(4, os4);
	CIndividual Indiv_5(4, true);
	

	Indiv_1.vSetFitnessandWeight(values, max, weights);
	Indiv_2.vSetFitnessandWeight(values, max, weights);
	Indiv_3.vSetFitnessandWeight(values, max, weights);
	Indiv_4.vSetFitnessandWeight(values, max, weights);

	cout << Indiv_3.bIsbetterThan(Indiv_1);
	*/

	//Indiv_5.vShowGenotype();
	
	/*

	Indiv_1.vSetFitnessandWeight(values, max, weights);
	Indiv_2.vSetFitnessandWeight(values, max, weights);
	Indiv_3.vSetFitnessandWeight(values, max, weights);
	Indiv_4.vSetFitnessandWeight(values, max, weights);


	CIndividual Marek = *Indiv_1.cCreateChildrenWith(Indiv_2, 3);
	CIndividual Harek = *Indiv_2.cCreateChildrenWith(Indiv_1, 3);

	Marek.vShowGenotype();
	Harek.vShowGenotype();
	*/
	
	/*
	Indiv_1.vMutateIndividual(54);
	Indiv_1.vShowGenotype();
	Indiv_2.vMutateIndividual(15);
	*/
}