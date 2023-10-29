/*This project involves implementing the mergesort sorting algorithm in a slightly
modified manner that utilizes a file of integers that specifiy what indicies of a 
digit or string to use for comparisions. For an int, index 0 represents the ones
place digit, index 1 represents the tens place digit, and so on. 
For a string, the index represents the traditional index of the string
This version of mergesort is stable and runs in O(n lg n). The data is outputted
fixed right with a column width of ten for integers, and on a newline separated list 
of values for strings.*/
#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

//Function Signature for Mergesort
void Merge(int numbers[], int i, int j, int k, int sortIndicies[], int sortArraySize);
void MergeSort(int numbers[], int i, int k, int sortIndicies[], int sortArraySize);
void Merge(string strings[], int i, int j, int k, int sortIndicies[], int sortArraySize);
void MergeSort(string strings[], int i, int k, int sortIndicies[], int sortArraySize);
int getDigit(int integer, int index);

int main(int argc, char *argv[]){

    if(argc != 5){
        cout << "Usage: ./a.out i|s sort_filename input_filename output_filename" << endl;
        return 1;
    }
    //Storing the datatype in a string, then checking that there is a valid number of 
    //arguments, and that the datatype is valid
    string datatype = argv[1];
    if(datatype != "i" && datatype != "s"){
        cout << "Invalid datatype \"" << datatype << "\" (must be \"i\" or \"s\")" << endl;
        return 1;
    }

    //Creating a file stream for the sort file, opening it, checking, creating the array to store data, and then
    //reading data into the array
    ifstream sortFile;
    sortFile.open(argv[2]);
    if(!sortFile){
        cout << "Unable to open sort file" << endl;
        return 1;
    }
    int sortIndicies[2001] = {-1};
    int i = 0;
    int currSort = 0;
    while(sortFile >> currSort){
        sortIndicies[i] = currSort;
        i++;
        
    }
    int sortArraySize = i;
    sortFile.close();

    //Creating an array to store the input file data based on the datatype
    int intArray[2001];
    string stringArray[2001];
    
    //Creating file stream for input file, opening it, checking it, then reading the data into the corresponding array
    ifstream inFile;
    inFile.open(argv[3]);
    int currValue = 0;
    string currString;
    if(!inFile.is_open()){
            cout << "Unable to open input file" << endl;
            return 1;
        }
    i = 0;
    int inputArrayCount;
    if(datatype == "i"){
        while(inFile >> currValue){
            intArray[i] = currValue;
            i++;
        }
        inputArrayCount = i;
    }
    else if(datatype == "s"){
        while(inFile >> currString){
            stringArray[i] = currString;
            i++;
        }
        inputArrayCount = i;
    }
    inFile.close();
    i = 0;

    //Creating the outputFile stream, checking that it's open, and calling mergesort
    //based on the datatype, and writing the output to the file
    ofstream outFile;
    outFile.open(argv[4]);

    if(!outFile){
        cout << "Unable to open output file" << endl;
        return 1;
    }

    // MERGESOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRRT
    if(datatype == "i"){
        MergeSort(intArray, 0, inputArrayCount - 1, sortIndicies, sortArraySize);
        for(int i = 0; i < inputArrayCount; i++){
            outFile << fixed << setw(10) << intArray[i] << endl;
        }
    }
    else if(datatype == "s"){
        MergeSort(stringArray, 0, inputArrayCount - 1, sortIndicies, sortArraySize);
        for(int i = 0; i < inputArrayCount; i++){
            outFile << stringArray[i] << endl;
        }
    }
    return 0;
}

//Function to extract a given digit from a number based on the index
int getDigit(int integer, int index){
    for(int j = 0; j < index; j++){
        integer /= 10;
    }
    return (integer % 10);
}
//MERGESOOOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRRRRRT FOR INTEGERS
void MergeSort(int numbers[], int i, int k, int sortIndicies[], int sortArraySize) {
   int j;
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j, sortIndicies, sortArraySize);
      MergeSort(numbers, j + 1, k, sortIndicies, sortArraySize);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, sortIndicies, sortArraySize);
   }
}
//Why not merge right?
void Merge(int numbers[], int i, int j, int k, int sortIndicies[], int sortArraySize) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
    int integer1, integer2;
   // Add smallest element from left or right partition to merged numbers
    while(leftPos <= j && rightPos <= k){
        //Assigning the current number from the number array to it's own variable so we can mutate it. 
        integer1 = numbers[leftPos];
        integer2 = numbers[rightPos];
            for(int p = 0; p < sortArraySize; p++){
                //Extracting the proper digits from the integer
                integer1 = getDigit(numbers[leftPos], sortIndicies[p]);
                integer2 = getDigit(numbers[rightPos], sortIndicies[p]);
                //If int 1 is less than int2, add int1
                if(integer1 < integer2){
                    mergedNumbers[mergePos] = numbers[leftPos];
                    mergePos++;
                    leftPos++;
                    break;
                }
                //If int 2 is less than int1, add int2
                else if(integer2 < integer1){
                    mergedNumbers[mergePos] = numbers[rightPos];
                    mergePos++;
                    rightPos++;
                    break;
                }
                //If int1 and int2 are equal and we've reached the end of the sort indexes, add both
                else if(integer1 == integer2 && p == (sortArraySize - 1)){
                    mergedNumbers[mergePos] = numbers[leftPos];
                    mergePos++;
                    leftPos++;
                    break;
                }
                
        }
}
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}
//MERGESOOOOOOOOOOOOOOOOOOOOOOOOOORRRRRRRRRRRRRRRRRRRRRRRRRT FOR STRINGS
void MergeSort(string strings[], int i, int k, int sortIndicies[], int sortArraySize) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(strings, i, j, sortIndicies, sortArraySize);
      MergeSort(strings, j + 1, k, sortIndicies, sortArraySize);
      
      // Merge left and right partition in sorted order
      Merge(strings, i, j, k, sortIndicies, sortArraySize);
   }
}

void Merge(string strings[], int i, int j, int k, int sortIndicies[], int sortArraySize) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int n;
   string *mergedStrings = nullptr;

   mergePos = 0;
   n = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedStrings = new string[mergedSize];    // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
     //Assigning string with the string in the left and right position
     string string1 = strings[leftPos];
     string string2 = strings[rightPos];
     char left;
     char right;
     for(int m = 0; m < sortArraySize; m++){
        left = string1[sortIndicies[n]];
        right = string2[sortIndicies[n]];
        //If the sort index is outside of the string, assign char with the null character
        if(sortIndicies[n] > string1.length()){
            left = '\0';
        }
        if(sortIndicies[n] > string2.length()){
            right = '\0';
        }
        //If left is less than right, add left to merged array
        if(left < right){
            mergedStrings[mergePos] = strings[leftPos];
            leftPos++;
            n = 0;
            mergePos++;
            break;
        }
        //If right is less than left, add right to merged array
        else if(left > right){
            mergedStrings[mergePos] = strings[rightPos];
            rightPos++;
            n = 0; 
            mergePos++;
            break;
        }
        //If left and right are equal, and we've checked all previous indexes 
        else if(left == right && m == (sortArraySize - 1)){
            mergedStrings[mergePos] = strings[leftPos];
            mergePos++;
            leftPos++;
            n = 0;
            break;
            
        }
        n++;
    }
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedStrings[mergePos] = strings[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedStrings[mergePos] = strings[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      strings[i + mergePos] = mergedStrings[mergePos];
   }
   delete[] mergedStrings;
}
