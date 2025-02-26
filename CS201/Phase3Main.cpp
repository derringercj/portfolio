#include <iostream>
using namespace std;
#include "BHeap.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " passed (Key:imeidj)" << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1(Key:kdjoum)" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors " << endl;
	}
}

int main(){
	string A[20] = {"AD","AB","AA","A","B","C","D","E","F","H","I","J","K","L","M","O","Q","R","S","T"};
	BHeap<string> Z(A,20), Y;
	Z.printKey();
    //B2: A AA AB AD\n B4: B C D E F H I J K L M O Q R S T 

	cout << Z.extractMin() << endl;       //A

	Z.printKey();
	//B0:AA\n B1:AB AD\n B4:B C D E F H I J K L M O Q R S T
	
	Y.insert("p"); 
	Y.insert("h");
	Y.insert("a");
	Y.insert("s");
	Y.insert("e");
	Y.insert("3");
	Y.printKey();
	//B0: 3\n B0: a\n B0: p\n B0: h\n B0: s\n B0: e\n
	
	Y.merge(Z);
    
	Y.printKey();
    //B0: AA\n B1:AB AD\n B4:B C D E F H I J K L M O Q R S T\n B0: 3\n B0: a\n B0: p\n B0: h\n B0: s\n B0: e\n
    
	cout << Y.peekKey() << endl;		//AA
	cout << Y.extractMin() << endl;       //AA
	Y.printKey();
	//B2: AB AD a p\n B4:B C D E F H I J K L M O Q R S T\n B0: e\n  B1: h s\n
	
	BHeap<int> X;
	for(int i = 0; i < 100000; i++){
		X.insert(i);
	}
	Node<int>* currentNode = X.min;
	int peakKey=0;
	int extractMin=0;
	for(int i = 0; i < 100000; i++){
		if(X.peekKey() != i) peakKey++;
		if(X.extractMin() != i) extractMin++;
	}
	//peakkey passed (Key:imeidj)
	printErrors("peakKey",peakKey);
	//extractMin passed (Key:imeidj)
	printErrors("extractMin",extractMin);		
	
	BHeap<int> C,D;
	for(int i = 0; i < 100000; i++){
		C.insert(i);
		D.insert(100000+i);
	}
	C.merge(D);
	peakKey=0;
	extractMin=0;
	for(int i = 0; i < 199999; i++){
		if(C.peekKey() != i) peakKey++;
		if(C.extractMin() != i) extractMin++;
	}
	//peakkey passed (Key:imeidj)
	printErrors("peakKey",peakKey);
	//extractMin passed (Key:imeidj)
	printErrors("extractMin",extractMin);
	return 0;
}
