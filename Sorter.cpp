#include "Sorter.h"

using namespace std;


int ten_keys[10];
int hundred_keys[100];
int thousand_keys[1000];
int ten_thousand_keys[10000];
long  hundred_thousand_keys[100000];
long  million_keys[1000000];
//Initialize unsorted arrays to hold generated key values

long *selectArrays[6] = { (long*)ten_keys,(long*)hundred_keys,(long*)thousand_keys,(long*)ten_thousand_keys,hundred_thousand_keys,million_keys };
//If we make an array of pointers to our holding arrays, we don't have to directly name them which in turn can lead to automation!

string AscInFileNames[] =
{ "10Keys.AscendingInput.txt", "100Keys.AscendingInput.txt","KiloKeys.AscendingInput.txt","10KiloKeys.AscendingInput.txt", "100KiloKeys.AscendingInput.txt","MillionKeys.AscendingInput.txt" };
string DescInFileNames[] =
{ "10Keys.DescendingInput.txt","100Keys.DescendingInput.txt","KiloKeys.DescendingInput.txt","10KiloKeys.DescendingInput.txt","100KiloKeys.DescendingInput.txt","MillionKeys.DescendingInput.txt" };
string RandomInFileNames[] =
{ "10Keys.RandomInput.txt","100Keys.RandomInput.txt","KiloKeys.RandomInput.txt","10KiloKeys.RandomInput.txt","100KiloKeys.RandomInput.txt","MillionKeys.RandomInput.txt" };

string AscOutFileNames[] =
{ "10Keys.AscendingOutput.txt", "100Keys.AscendingOutput.txt","KiloKeys.AscendingOutput.txt","10KiloKeys.AscendingOutput.txt", "100KiloKeys.AscendingOutput.txt","MillionKeys.AscendingOutput.txt" };
string DescOutFileNames[] =
{ "10Keys.DescendingOutput.txt","100Keys.DescendingOutput.txt","KiloKeys.DescendingOutput.txt","10KiloKeys.DescendingOutput.txt","100KiloKeys.DescendingOutput.txt","MillionKeys.DescendingOutput.txt" };
string RandomOutFileNames[] =
{ "10Keys.RandomOutput.txt","100Keys.RandomOutput.txt","KiloKeys.RandomOutput.txt","10KiloKeys.RandomOutput.txt","100KiloKeys.RandomOutput.txt","MillionKeys.Output.txt" };
//Declaring these arrays with the file names allows us to automate more and it removes errors that involve having inconsistent/incorrect file names


//Main method
int main()
{
	char sortMethod = 'd';
	char userConfig = 'u';
	Generator KeyMaker;
	MergeSorter Merger;
	InsertSorter Inserter;
	Populater Populater;
	Printer Printer;
	int inputConfig;
	//Initialize the things we need to go.

	cout << "This program generates keys and then performs sorting algorithms on them. \n";
	cout << "How would you like your keys generated? (Letter inputs only) \n";
	cout << "[A]scending - Generate by lowest to highest \n";
	cout << "[D]escending - Generate by highest to lowest \n";
	cout << "[R]andom - Generate random keys \n";
	while (userConfig == 'u') {
		cin >> userConfig;
		if (userConfig == 'A' || userConfig == 'a') {
			inputConfig = 1;
			//Configure to generate lowest to highest
		}
		else if (userConfig == 'D' || userConfig == 'a') {
			inputConfig = 2;
			//Configure to generate highest to lowest
		}
		else if (userConfig == 'R' || userConfig == 'r') {
			inputConfig = 3;
			//Configure to make random keys
		}
		else {
			cout << "You must have input something invalid. Please enter A, D, or R which correspond to how you want keys to be created. \n";
			userConfig = 'u';
			//Reset the user-side config value so the loop persists.
		}

	}

	//Create the keys
	KeyMaker.createKeys(inputConfig);

	//Populate Arrays using our created keys
	Populater.populateArrays(inputConfig);

	cout << "Select sorting method. [M]erge or [I]nsertion. \n";
	cout << "Please enter M or I to select. \n";
	while (sortMethod == 'd')
	{
		cin >> sortMethod;

		if (sortMethod == 'M' || sortMethod == 'm') {


			//Sample test array to verify sort functions work properly.
			//int ten_keys[10] = { 1, 3, 4, 5, 10, 22, 7, 8, 9, 10 };

			Merger.TimedMergeSort(0);
			Printer.outputResults(inputConfig);


			cout << "All key amounts have been generated, sorted, and the result has been stored in output files. \n";
			cout << "Please verify the results yourself with the generated input and output files in the folder of this program. \n";
			cout << "Thank you for participating. \n";

			exit(0);

		}
		else if (sortMethod == 'I' || sortMethod == 'i') {

			Inserter.TimedInsertSort(0);
			Printer.outputResults(inputConfig);

			cout << "All key amounts have been generated, sorted, and the result has been stored in output files. \n";
			cout << "Please verify the results yourself with the generated input and output files in the folder of this program. \n";
 			cout << "Thank you for participating. \n";

			exit(0);
		}
		else {
			cout << "Invaild input. Type M or I to continue. \n";
			sortMethod = 'd';
		}
	}
}


//Using this we only need to check the configuration 1 time, leading to less errors down the pipeline
void Generator::createKeys(int inputConfig)
{
	if (inputConfig == 1) {
		ascendingGenerator(10, 0);
	}
	else if (inputConfig == 2) {
		descendingGenerator(10, 0);
	}
	else {
		randomGenerator(10, 0);
	}
}

void Generator::ascendingGenerator(long keyAmount, int AscFileNumber)
{
	if (keyAmount > 1000000) {
		return;
	}
	else {
		ascendingGenerator(keyAmount * 10, AscFileNumber + 1);
		ofstream InputFile(AscInFileNames[AscFileNumber]);

		if (InputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				InputFile << e << '\n';

			}//End for
			InputFile.close();

		}//End inner if

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner else

	}//End outer else
}

void Generator::descendingGenerator(long keyAmount, int DescFileNumber)
{
	if (keyAmount > 1000000) {
		return;
	}
	else {
		descendingGenerator(keyAmount * 10, DescFileNumber + 1);
		ofstream InputFile(DescInFileNames[DescFileNumber]);

		if (InputFile.is_open()) {
			for (long e = keyAmount; e > 0; e--) {
				InputFile << e << '\n';

			}//End for
			InputFile.close();

		}//End inner if

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner else

	}//End outer else
}

void Generator::randomGenerator(long keyAmount, int RandomFileNumber)
{
	std::random_device rd;
	//Initialize random number generator for more variety

	srand((unsigned)time(NULL));
	//Used for smaller arrays, since random_device tends to like BIG numbers.

	if (keyAmount > 1000000) {
		return;
	}
	else {
		randomGenerator(keyAmount * 10, RandomFileNumber + 1);
		ofstream InputFile(RandomInFileNames[RandomFileNumber]);

		if (InputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				if (keyAmount <= 10000) {
					int randomNumber = (rand() % 10000) + 1;
					//Cap some numbers so they don't get ridiculous for smaller arrays.
					InputFile << randomNumber << '\n';
				}

				else {
					long randomNumber = abs((long)rd());
					//Generate random number

					InputFile << randomNumber << '\n';
				}//End generator if-else

			}//End for
			InputFile.close();

		}//End inner if

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner else

	}//End outer else
}

void Printer::outputResults(int inputConfig)
{
	if (inputConfig == 1) {
		outputAscending(0, 0);
	}
	else if (inputConfig == 2) {
		outputDescending(0, 0);
	}
	else {
		outputRandom(0, 0);
	}
}

void Printer::outputAscending(int caseCount, int AscFileNumber)
{
	if (caseCount > 5) {
		return; //Limit the amount of times this is run to how many arrays need be output
	}
	else {
		outputAscending(caseCount + 1, AscFileNumber + 1);
		int pickArray = caseCount; //This lets us choose what array we're pulling from to output
		long keyAmount = (long)pow(10, (caseCount + 1)); //Dynamic way of determining how many keys are in the array
		ofstream OutputFile(AscOutFileNames[AscFileNumber]);

		if (OutputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				OutputFile << selectArrays[pickArray][e] << '\n';
				//pickArray chooses the array that we're outputting to
			}//End for
			OutputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner if-else

	}//End recursive if-else
}

void Printer::outputDescending(int caseCount, int DescFileNumber)
{
	if (caseCount > 5) {
		return;
	}
	else {
		outputDescending(caseCount + 1, DescFileNumber + 1);
		int pickArray = caseCount; //This lets us choose what array we're pulling from to output
		long keyAmount = (long)pow(10, (caseCount + 1)); //Dynamic way of determining how many keys are in the array
		ofstream OutputFile(DescOutFileNames[DescFileNumber]);

		if (OutputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				OutputFile << selectArrays[pickArray][e] << '\n';
			}//End for
			OutputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner if-else

	}//End recursive if-else
}

void Printer::outputRandom(int caseCount, int RandomFileNumber)
{
	if (caseCount > 5) {
		return; //Limit the amount of times this is run to how many arrays need be output
	}
	else {
		outputRandom(caseCount + 1, RandomFileNumber + 1);
		int pickArray = caseCount; //This lets us choose what array we're pulling from to output
		long keyAmount = (long)pow(10, (caseCount + 1)); //Dynamic way of determining how many keys are in the array
		ofstream OutputFile(RandomOutFileNames[RandomFileNumber]);

		if (OutputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				OutputFile << selectArrays[pickArray][e] << '\n';
				//pickArray chooses the array that we're outputting to
			}//End for
			OutputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure the file exists or is not already opened! \n";
		}//End inner if-else

	}//End recursive if-else
}

void Populater::populateArrays(int inputConfig)
{
	if (inputConfig == 1) {
		populateAscending(0, 0);
	}
	else if (inputConfig == 2) {
		populateDescending(0, 0);
	}
	else {
		populateRandom(0, 0);
	}
}

void Populater::populateAscending(int caseCount, int AscFileNumber)
{
	if (caseCount > 5) {
		return; //Limit to the amount of arrays we need to populate
	}
	else {
		populateAscending(caseCount + 1, AscFileNumber + 1);
		int pickArray = caseCount; //Dynamic way of choosing what array to fill
		long keyAmount = (long)pow(10, (caseCount + 1)); //Because the arrays are each exponents of 10 in size we can just increase the exponent
		ifstream InputFile(AscInFileNames[AscFileNumber]);
		if (InputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				InputFile >> selectArrays[pickArray][e];
			}//End for
			InputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure file exists or isn't open already! \n";
		}//End inner if-else

	}//End outer if-else
}

void Populater::populateDescending(int caseCount, int DescFileNumber)
{
	if (caseCount > 5) {
		return; //Limit to the amount of arrays we need to populate
	}
	else {
		populateDescending(caseCount + 1, DescFileNumber + 1);
		int pickArray = caseCount; //Dynamic way of choosing what array to fill
		long keyAmount = (long)pow(10, (caseCount + 1)); //Because the arrays are each exponents of 10 in size we can just increase the exponent
		ifstream InputFile(DescInFileNames[DescFileNumber]);
		if (InputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				InputFile >> selectArrays[pickArray][e];
			}//End for
			InputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure file exists or isn't open already! \n";
		}//End inner if-else

	}//End outer if-else
}

void Populater::populateRandom(int caseCount, int RandomFileNumber)
{
	if (caseCount > 5) {
		return; //Limit to the amount of arrays we need to populate
	}
	else {
		populateRandom(caseCount + 1, RandomFileNumber + 1);
		int pickArray = caseCount; //Dynamic way of choosing what array to fill
		long keyAmount = (long)pow(10, (caseCount + 1)); //Because the arrays are each exponents of 10 in size we can just increase the exponent
		ifstream InputFile(RandomInFileNames[RandomFileNumber]);
		if (InputFile.is_open()) {
			for (long e = 0; e < keyAmount; e++) {
				InputFile >> selectArrays[pickArray][e];
			}//End for
			InputFile.close();
		}

		else {
			cout << "Unable to open file. \n Make sure file exists or isn't open already! \n";
		}//End inner if-else

	}//End outer if-else
}

void InsertSorter::InsertLongSort(long  array[], long  big) {
	for (long i = 1; i <= big; i++) {
		long  key = array[i];
		//Insert array[i] into sorted sequence
		long  j = i - 1;
		while (key < array[j] && j >= 0) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}


/*
* Merges two subarrays of Array[].
* Left subarray is Array[p...q].
* Right subarray is Array[q+1...r]
*/
void MergeSorter::MergeLong(long int Array[], long int p_index, long int middle, long int r_index) {
	long int n1 = middle - p_index + 1;
	long int n2 = r_index - middle;

	long int *LeftSubArray = new long int[n1];
	//Create left subarray, [p...q]
	long int *RightSubArray = new long int[n2];
	//Create right subarray [q+1...r]

	//The new keyword must be used so that the memory can be dynamically allocated
	//C++ does not let you declare arrays in static instances without a size.

	//Populate subarrays using values of passed indexes.
	for (long int i = 0; i < n1; i++) {
		LeftSubArray[i] = Array[p_index + i];
	}
	for (long int j = 0; j < n2; j++) {
		RightSubArray[j] = Array[middle + j + 1];
	}
	//Merge the temp arrays back into the original array [p...r]

	//Initial index of first subarray
	long int i = 0;

	//Initial index of second subarray
	long int j = 0;

	//Initial index of merged subarrray
	long int k = p_index;

	//Return merged subarray values back into the original array.

	while (i < n1 && j < n2) {
		if (LeftSubArray[i] <= RightSubArray[j]) {
			Array[k] = LeftSubArray[i];
			i++;
		}
		else {
			Array[k] = RightSubArray[j];
			j++;
		}
		k++;
	}

	//Copy anything remaining inside left[], if applicable
	while (i < n1) {
		Array[k] = LeftSubArray[i];
		i++;
		k++;
	}

	//Copy remaining elements of right[], if applicable
	while (j < n2) {
		Array[k] = RightSubArray[j];
		j++;
		k++;
	}

	//Delete temporary subarrays to free up space.
	delete[]LeftSubArray;
	delete[]RightSubArray;
}
/*
Divides an array into subsections.
Conquers using recursion to 'sort' through subarrays.
Combines subarrays into single sorted array, by calling MergeLong().
*/
void MergeSorter::MergeLongSort(long int Array[], long int starting, long int ending) {
	if (starting < ending)
	{ //Check for base case, is array divisible
		long int midpoint = starting + (ending - starting) / 2;
		//Divide. Find midpoint of original array A, to determine indexes of subarrays.
		MergeLongSort(Array, starting, midpoint);
		//Conquer. Recursively call Merge-Sort to sort subarray L
		MergeLongSort(Array, midpoint + 1, ending);
		//Conquer. Recursively call Merge-Sort to sort subarray R
		MergeLong(Array, starting, midpoint, ending);
		//Combine sorted subarrays into a single sorted subarray.
	}
	else {
		return;
	}
}

/*
Prints the values of an array passed into it.
Primarily used for debugging to verify sorting algorithms work.
*/
void Printer::PrintArray(int array[], int size) {
	for (int i = 0; i <= size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

void MergeSorter::TimedMergeSort(int arraysCompleted)
{
	if (arraysCompleted > 5) {
		return;
	}
	else {
		auto start_time = std::chrono::high_resolution_clock::now();
		MergeLongSort(selectArrays[arraysCompleted], 0, (long)pow(10, (arraysCompleted + 1)) - 1);
		auto finish_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_time = finish_time - start_time;
		cout << "Elapsed time for merge sorting " << pow(10, (arraysCompleted + 1)) << " keys: " << elapsed_time.count() << "s\n";

		TimedMergeSort(arraysCompleted + 1); //Recurr the timer function, so we don't have to waste lots of code lines with multiple timer variables.
		//NOTE: The reason this call is AFTER the sort is so that the smallest array size gets sorted and printed first.
	}
}

void InsertSorter::TimedInsertSort(int arraysCompleted)
{
	if (arraysCompleted > 5) {
		return;
	}
	else {
		auto start_time = std::chrono::high_resolution_clock::now();
		InsertLongSort(selectArrays[arraysCompleted], (long)pow(10, (arraysCompleted + 1)) - 1);
		auto finish_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_time = finish_time - start_time;
		cout << "Elapsed time for insertion sorting " << pow(10, (arraysCompleted + 1)) << " keys: " << elapsed_time.count() << "s\n";

		TimedInsertSort(arraysCompleted + 1); //Recurr the timer function, so we don't have to waste lots of code lines with multiple timer variables.
		//NOTE: The reason this call is AFTER the sort is so that the smallest array size gets sorted and printed first.
	}
}