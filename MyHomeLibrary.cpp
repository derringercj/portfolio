/*Casey Derringer
November 10, 2021
My Home Library
This program acts as a home library tracker for the user. They can add books to their library, remove books, calculate statistics, display their current library,
all while saving their library to a text document that lists their books as well as their lengths.*/

//Header files needed for the program as well as namespace.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;
//Function definition sincec readData is one of the first things to happen in the program.
void readData(vector<string>& bookTitles, vector<int>& pageNumbers)
{
    ifstream inputFile;
    inputFile.open("library.txt");

    string inputTitle;
    int inputPages;
    //While loop that reads the file and assigns titles of books and their page lengths to their corresponding vectors.
    while (getline(inputFile, inputTitle))
    {
        inputFile >> inputPages;
        inputFile.ignore();
        bookTitles.push_back(inputTitle);
        pageNumbers.push_back(inputPages);
    }
}
//Function prototypes in which vectors are passed to the functions.
void addBook(vector<string>&, vector<int>&);
void removeBook(vector<string>&, vector<int>&);
void calculateStats(vector<string>, vector<int>);
void displayLibrary(vector<string>, vector<int>);
void writeData(vector<string>, vector<int>);

int main()
{
    //Declaration of vectors as well as the int variable for the user's menu choice. 
    vector<string> bookTitles;
    vector<int> pageNumbers;
    int menuChoice;
    //Calling readData function.
    readData(bookTitles, pageNumbers);
    //Introductory statement of the program prompting them to use the menu. 
    cout << "Welcome to My Home Library!" << endl;
    cout << "Please enter the number of the task you would like to carry out." << endl << endl;
    //Do-while loop that displays the menu and reads the users choice.
    do
    {
        cout << "Add a book to your library:                                1" << endl;
        cout << "Remove a book from your library:                           2" << endl;
        cout << "Calculate statistics regarding the titles in your library: 3" << endl;
        cout << "Display your current library:                              4" << endl;
        cout << "Quit:                                                      5" << endl;

        cin >> menuChoice;
        cin.ignore();
        //Switch statement that validates the users input and calls the correct function based on the users input. 
        switch (menuChoice)
        {
        case 1:
        {
            addBook(bookTitles, pageNumbers);
            break;
        }
        case 2:
        {
            removeBook(bookTitles, pageNumbers);
            break;
        }
        case 3:
        {
            calculateStats(bookTitles, pageNumbers);
            break;
        }
        case 4:
        {
            displayLibrary(bookTitles, pageNumbers);
            break;
        }
        case 5:
        {
            writeData(bookTitles, pageNumbers);
            cout << "Thank you for choosing My Home Library, happy reading!";
            break;
        }
        default:
        {
            cout << "Please enter a valid menu choice!" << endl;
        }
        }
    } while (menuChoice != 5);

    return 0;
}
//Function definition for adding a book.
void addBook(vector<string>& bookTitles, vector<int>& pageNumbers)
{
    string bookTitle;
    int length;
    //Statements that get the book the user would like to add to their library and adding it to the end of the vector.
    cout << "What is the title of the book you'd like to add?" << endl;
    getline(cin, bookTitle);
    cout << "And how many pages is the book?" << endl;
    cin >> length;

    bookTitles.push_back(bookTitle);
    pageNumbers.push_back(length);
}
//Function definition for removing a book.
void removeBook(vector<string>& bookTitles, vector<int>& pageNumbers)
{
    string removedBook;
    cout << "What book would you like to remove?" << endl;
    getline(cin, removedBook);
    for (int count = 0; count < bookTitles.size(); count++)
    {
        //If statement that removes the entered book if it matches one inside the vector.
        if (removedBook == bookTitles.at(count))
        {
            bookTitles.erase(bookTitles.begin() + count);
            pageNumbers.erase(pageNumbers.begin() + count);
            cout << "Book succesfully removed." << endl;
            break;
        }
    }
}
//Function definition for calculating stats of a user's library.
void calculateStats(vector<string> bookTitles, vector<int> pageNumbers)
{
    int count, longest;
    int total = 0;
    double average;
    //Two loops that accumulate the total of all of the books lengths and find the longest book respectively.
    for (count = 0; count < pageNumbers.size(); count++)
    {
        total += pageNumbers.at(count);
    }
    //Math for calculating the average as well as defining the longest book to start. 
    average = total / pageNumbers.size();
    longest = pageNumbers.at(0);
    for (count = 0; count < pageNumbers.size(); count++)
    {
        if (longest < pageNumbers.at(count))
        {
            longest = pageNumbers.at(count);
        }
    }
    round(average);
    cout << fixed << setprecision(0) << "The average page length of books in your library is " << average << " pages.";
    cout << endl << "The longest book you have in your library is " << longest << " pages." << endl;
}
//Function definition to display the user's current library. 
void displayLibrary(vector<string> bookTitles, vector<int> pageNumbers)
{
    int count = 0;
    while (count < bookTitles.size())
    {
        cout << bookTitles.at(count) << endl << pageNumbers.at(count) << endl;
        count++;
    }
}
//Function definition to write the user's library to the library.txt file. 
void writeData(vector<string> bookTitles, vector<int> pageNumbers)
{
    ofstream fileOutput;
    fileOutput.open("library.txt");
    for (int count = 0; count < bookTitles.size(); count++)
    {
        fileOutput << bookTitles.at(count) << endl << pageNumbers.at(count) << endl;
    }
}
