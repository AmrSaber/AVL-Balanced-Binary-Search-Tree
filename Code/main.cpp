#include <iostream>
#include <stdio.h>

using namespace std;
#include "BST.h"

int main (){
	
	//AVL Binary Search Tree instance
	BST<int, string> my_map;
	
	//vairalbles for the input
	int input, key;
	string value;
	
	//main loop of the program
	while(1){
		//inform the user of the options
		cout <<"Choose one of the following options to manipulate our BST " << endl;
		cout << "1- insert\t\t";
		cout << "2- modify\t\t";
		cout << "3- set\n";
		cout << "4- display\t\t";
		cout << "5- search\t\t";
		cout << "6- delete\n";
		cout << "7- get\t\t\t";
		cout << "8- exit\n";
		
		cin >> input;
		if (input == 1){ //insert new key to the tree
			cout <<"Enter an integer to be your key: ";
			cin >> key;
			cout << "Enter a string to be the value of the key: ";
			cin >> value;
			
			//try inserting the new key and catch potential exeption in case of duplicate key
			try{
				my_map.insert(key, value);
				printf("Inserted value %s, with key %d\n", value.c_str(), key);
			}catch(string ex){
				cout << ex << endl;
			}
		}else if(input == 2){ //modify old key and assign new value to it
			cout << "Enter a key to modify it's string value: ";
			cin >> key;
			cout << "Enter a string to modify the old one: ";
			cin >> value;
			
			//try modifying the given key and cath the potectial exception in case of key not found
			try{
				my_map.modify(key, value);
				printf("Modified key %d, to new value of %s\n", key, value.c_str());
			}catch(string ex){
				cout << ex << endl;
			}
		}else if(input == 3){	//set the given key to the given value
			cout << "Enter a key to set: ";
			cin >> key;
			cout << "Enter value for the given key: ";
			cin >> value;
			my_map.set(key, value);
			printf("Set key %d to value %s\n", key, value.c_str());
		}else if(input == 4){	//display the tree as in question
			my_map.display();
		}else if(input == 5){	//searches for a given key and check if it exists
			cout << "Enter a key to search for: ";
			cin >> key;
			if(my_map.containsKey(key)) printf("Key %d exists\n", key);
			else printf("Key %d does not exist\n", key);
		}else if(input == 6){	//delete the given key, throw error if it doesn't exist
			cout << "Enter a key to be deleted: ";
			cin >> key;
			
			//try removing the given key and catch exception in case key not found
			try{
				my_map.remove(key);
				printf("Key %d was removed\n", key);
			}catch(string ex){
				cout << ex << endl;
			}
		}else if(input == 7){	//gets the value of a given key
			cout << "Enter key to get it's value: ";
			cin >> key;
			
			//checks the value of the given key
			//catches the potential exception if the key is not found
			try{
				printf("Value of key %d, is %s\n", key, my_map.get(key).c_str());
			}catch(string ex){
				cout << ex << endl;
			}
		}else if(input == 8){	//exit, breaks the main loop and stops the program
			break;
		}else{	//in case of wrong input
			cout << "Wrong input, try again" << endl;
		}
		cout << endl;
	}
	
	return 0;
}
