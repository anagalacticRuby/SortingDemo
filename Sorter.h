#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//We need fstream to read AND write from/to files

#include <chrono>
#include <random>

#include <string>
#include <time.h>
class Generator {
public:
	void createKeys(int inputConfig);
	void ascendingGenerator(long keyAmount, int AscFileNumber);
	void descendingGenerator(long keyAmount, int DescFileNumber);
	void randomGenerator(long keyAmount, int RandomFileNumber);
};

class MergeSorter {
public:
	void MergeLongSort(long int Array[], long int starting, long int ending);
	void MergeLong(long int Array[], long int p_index, long int middle, long int r_index);
	void TimedMergeSort(int completedArrays);
};
class InsertSorter {
public:
	void InsertLongSort(long array[], long  big);
	void TimedInsertSort(int arraysCompleted);
};
class Populater {
public:
	void populateArrays(int inputConfig);
	void populateAscending(int caseCount, int AscFileNumber);
	void populateDescending(int caseCount, int DescFileNumber);
	void populateRandom(int caseCount, int RandomFileNumber);
};

class Printer {
public:
	void outputResults(int inputConfig);
	void outputAscending(int caseCount, int AscFileNumber);
	void outputDescending(int caseCount, int DescFileNumber);
	void outputRandom(int caseCount, int RandomFileNumber);
	void PrintArray(int array[], int size);
};



