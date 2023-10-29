/*A project from the summer before freshmen year of college that simulates the process of opening CS:GO cases in a simple console program*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

//All of the pre main function initializations.
void displayMenu(int &menuChoice);
void openFracture(fstream &inventory);
void openBrokenFang(fstream &inventory);
void openSnakebite(fstream &inventory);
void selectBlueFracture(string &skinResult);
void selectPurpleFracture(string &skinResult);
void selectPinkFracture(string &skinResult);
void selectRedFracture(string &skinResult);
void selectBlueBrokenFang(string &skinResult);
void selectPurpleBrokenFang(string &skinResult);
void selectPinkBrokenFang(string &skinResult);
void selectRedBrokenFang(string &skinResult);
void selectBlueSnakebite(string &skinResult);
void selectPurpleSnakebite(string &skinResult);
void selectPinkSnakebite(string &skinResult);
void selectRedSnakebite(string &skinResult);


int main() {
	int menuChoice = 0;
	cout << "Welcome to Skin To Win! A CSGO Skin Opening Sim. ";
	//Declaring the object for creating and writing to a file
	fstream inventory("inventory.txt");
	//Menu function that allows user to select the case they'd like to open.
	while(menuChoice != 4){
	displayMenu(menuChoice);
	//Seed generation for random number function
	srand(time(0));
	switch (menuChoice){
	case 1:
	{
		openFracture(inventory);
		break;
	}
	case 2:
	{
		openBrokenFang(inventory);
		break;
	}
	case 3:
	{
		openSnakebite(inventory);
		break;
	}
	case 4:
	{
	    cout << "Goodbye!";
	    break;
	}
	}
    
	}
	return 0;
}
//This function displays the menu with cases for the user to open and allows the user to enter their choice of case.
void displayMenu(int &menuChoice){
	cout << "\nPlease select the case you'd like to open below.\n";
	cout << " 1. Fracture Case\n 2. Operation Broken Fang Case\n 3. Snakebite Case\n 4. Quit\n";
	cin >> menuChoice;
}
//Function declaration of fracture case opening with different functions based 
//on the rarity determined by the random number generator
void openFracture(fstream &inventory){
	string skinResult;
	int randomNumber = rand() % 1000;
	if (randomNumber <= 799) {
		selectBlueFracture(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 959 && randomNumber > 799){
		selectPurpleFracture(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 991 && randomNumber > 959){
		selectPinkFracture(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 997 && randomNumber > 991) {
		selectRedFracture(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else {
		cout << "Congratulations!\nYou got a knife!!!";
	}
}
void selectBlueFracture(string &skinResult) {
	srand(time(0));
	int skinSelection = 1 + (rand() & 6);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "SG 553 | Ol' Rusty";
		break;
	}
	case 2:
	{
		skinResult = "P250 | Cassette";
		break;
	}
	case 3:
	{
		skinResult = "P90 | Freight";
		break;
	}
	case 4:
	{
		skinResult = "Negev | Ultralight";
		break;
	}
	case 5:
	{
		skinResult = "PP-Bizon | Runic";
		break;
	}
	case 6:
	{
		skinResult = "P2000 | Gnarled";
		break;
	}
	case 7:
	{
		skinResult = "SSG 08 | Mainframe 001";
		break;
	}
	}
}
void selectPurpleFracture(string &skinResult){
	int skinSelection = 1 + (rand() & 4);
	switch (skinSelection){
	case 1:
	{
		skinResult = "MP5-SD | Kitbash"; 
		break;
	}
	case 2:
	{
		skinResult = "Galil AR | Connexion";
		break;
	}
	case 3:
	{
		skinResult = "Tec-9 | Brother";
		break;
	}
	case 4:
	{
		skinResult = "MAC-10 | Allure";
		break;
	}
	case 5:
	{
		skinResult = "MAG-7 | Monster Call";
		break;
	}
	}
}
void selectPinkFracture(string &skinResult) {
	int skinSelection = 1 + (rand() & 2);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "XM1014 | Entombed";
		break;
	}
	case 2:
	{
		skinResult = "M4A4 | Tooth Fairy";
		break;
	}
	case 3:
	{
		skinResult = "Glock-18 | Vogue";
		break;
	}
	}
}
void selectRedFracture(string &skinResult) {
	int skinSelection = 1 + (rand() & 1);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "AK-47 | Legion of Anubis";
		break;
	}
	case 2:
	{
		skinResult = "Desert Eagle | Printstream";
		break;
	}
	}
}
//Function declaration of Broken Fang case opening with different function calls 
//Based on the rarity determined by the random number generator. 
void openBrokenFang(fstream &inventory) {
	string skinResult;
	int randomNumber = rand() % 1000;
	if (randomNumber <= 799) {
		selectBlueBrokenFang(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 959 && randomNumber > 799) {
		selectPurpleBrokenFang(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 991 && randomNumber > 959) {
		selectPinkBrokenFang(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 997 && randomNumber > 991) {
		selectRedBrokenFang(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else {
		cout << "Congratulations!\nYou got gloves!!!";
	}
}
void selectBlueBrokenFang(string& skinResult) {
	srand(time(0));
	int skinSelection = 1 + (rand() & 6);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "M249 | Deep Relief";
		break;
	}
	case 2:
	{
		skinResult = "P90 | Cocoa Rampage";
		break;
	}
	case 3:
	{
		skinResult = "CZ75-Auto | Vendetta";
		break;
	}
	case 4:
	{
		skinResult = "P250 | Contaminant";
		break;
	}
	case 5:
	{
		skinResult = "MP5-SD | Condition Zero";
		break;
	}
	case 6:
	{
		skinResult = "G3SG1 | Digital Mesh";
		break;
	}
	case 7:
	{
		skinResult = "Galil AR | Vandal";
		break;
	}
	}
}
void selectPurpleBrokenFang(string& skinResult) {
	int skinSelection = 1 + (rand() & 4);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "UMP-45 | Gold Bismuth";
		break;
	}
	case 2:
	{
		skinResult = "Dual Berettas | Dezastre";
		break;
	}
	case 3:
	{
		skinResult = "Nova | Clear Polymer";
		break;
	}
	case 4:
	{
		skinResult = "SSG 08 | Parallax";
		break;
	}
	case 5:
	{
		skinResult = "AWP | Exoskeleton";
		break;
	}
	}
}
void selectPinkBrokenFang(string& skinResult) {
	int skinSelection = 1 + (rand() & 2);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "M4A4 | Cyber Security";
		break;
	}
	case 2:
	{
		skinResult = "Five-SeveN | Fairy Tale";
		break;
	}
	case 3:
	{
		skinResult = "USP-S | Monster Mashup";
		break;
	}
	}
}
void selectRedBrokenFang(string& skinResult) {
	int skinSelection = 1 + (rand() & 1);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "Glock-18 | Neo-Noir";
		break;
	}
	case 2:
	{
		skinResult = "M4A1-S | Printstream";
		break;
	}
	}
}
void openSnakebite(fstream& inventory) {
	string skinResult;
	int randomNumber = rand() % 1000;
	if (randomNumber <= 799) {
		selectBlueSnakebite(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 959 && randomNumber > 799) {
		selectPurpleSnakebite(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 991 && randomNumber > 959) {
		selectPinkSnakebite(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else if (randomNumber <= 997 && randomNumber > 991) {
		selectRedSnakebite(skinResult);
		cout << "You got...\n" << skinResult;
		inventory << skinResult << endl;
		inventory.close();
	}
	else {
		cout << "Congratulations!\nYou got gloves!!!";
	}
}
void selectBlueSnakebite(string& skinResult) {
	srand(time(0));
	int skinSelection = 1 + (rand() & 6);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "M249 | O.S.I.P.R.";
		break;
	}
	case 2:
	{
		skinResult = "Nova | Windblown";
		break;
	}
	case 3:
	{
		skinResult = "UMP-45 | Oscillator";
		break;
	}
	case 4:
	{
		skinResult = "CZ75-Auto | Circaetus";
		break;
	}
	case 5:
	{
		skinResult = "R8 Revolver | Junk Yard";
		break;
	}
	case 6:
	{
		skinResult = "SG 553 | Heavy Metal";
		break;
	}
	case 7:
	{
		skinResult = "Glock-18 | Clear Polymer";
		break;
	}
	}
}
void selectPurpleSnakebite(string& skinResult) {
	int skinSelection = 1 + (rand() & 4);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "MAC-10 | Button Masher";
		break;
	}
	case 2:
	{
		skinResult = "Negev | dev_texture";
		break;
	}
	case 3:
	{
		skinResult = "P250 | Cyber Shell";
		break;
	}
	case 4:
	{
		skinResult = "Desert Eagle | Trigger Discipline";
		break;
	}
	case 5:
	{
		skinResult = "AK-47 | Slate";
		break;
	}
	}
}
void selectPinkSnakebite(string& skinResult) {
	int skinSelection = 1 + (rand() & 2);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "XM1014 | XOXO";
		break;
	}
	case 2:
	{
		skinResult = "MP9 | Food Chain";
		break;
	}
	case 3:
	{
		skinResult = "Galil AR | Chromatic Aberration";
		break;
	}
	}
}
void selectRedSnakebite(string& skinResult) {
	int skinSelection = 1 + (rand() & 1);
	switch (skinSelection) {
	case 1:
	{
		skinResult = "M4A4 | In Living Color";
		break;
	}
	case 2:
	{
		skinResult = "USP-S | The Traitor";
		break;
	}
	}
}
