#include <iostream>
#include <iomanip>

using namespace std;

void displayMenu(int& menuChoice, float& USD);

int main() {
	
	int menuChoice = 0;
	char cont = 'Y';
	float USD;
	float EUR = 0.97;
	float JPY = 140.25;
	float GBP = 0.84;
	float CAD = 1.34;
	float BTC = 0.000062;
	float conversion;

	while (cont != 'N') {
		displayMenu(menuChoice, USD);
		cout << fixed << showpoint << setprecision(2);
		switch (menuChoice) {
		case 1:
		{
			conversion = USD * EUR;
			cout << "With ";
			cout << USD;
			cout << " USD, you have ";
			cout << conversion;
			cout << " EUR." << endl;
			break;
		}
		case 2:
		{
			conversion = USD * JPY;
			cout << "With ";
			cout << USD;
			cout << " USD, you have ";
			cout << conversion;
			cout << " JPY." << endl;
			break;
		}
		case 3:
		{
			conversion = USD * GBP;
			cout << "With ";
			cout << USD;
			cout << " USD, you have ";
			cout << conversion;
			cout << " GBP." << endl;
			break;
		}
		case 4:
		{
			conversion = USD * CAD;
			cout << "With ";
			cout << USD;
			cout << " USD, you have ";
			cout << conversion;
			cout << " CAD." << endl;
			break;
		}
		case 5:
		{
			conversion = USD * BTC;
			cout << "With ";
			cout << USD;
			cout << " USD, you have ";
			cout << conversion;
			cout << " BTC." << endl;
			break;
		}
		}
		cout << "Would you like to continue? (Y or N)" << endl;
		cin >> cont;
	}
	return 0;
}

void displayMenu(int& menuChoice, float& USD) {
	cout << "How much USD are you starting with?\n";
	cin >> USD;
	cout << "\nWhat currency would you like to convert to?\n";
	cout << "\n1. EUR \n2. JPY \n3. GBP \n4. CAD \n5. BTC\n";
	cin >> menuChoice;
}