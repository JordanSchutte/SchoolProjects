#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

void CallProcedure(string pName){
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonSource");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param){
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonSource");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)){
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	} else{
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param){
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonSource");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)){
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	} else{
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void Menu(){
	bool programRun = true;
	bool correctInput;
	int userChoice;
	string groceryType;

	do {
		cout << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "|||                       Please Select an option                          |||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << "|||   1. Print List of All Purchased Items and How Many Were Purchased     |||" << endl;
		cout << "|||   2. Print Total Amount Purchased of a Specific Item                   |||" << endl;
		cout << "|||   3. Display Text Histogram                                            |||" << endl;
		cout << "|||   4. Exit The Program                                                  |||" << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		cout << endl;

		try {
			std::cin >> userChoice;
			cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
			cout << endl;

			while (std::cin.fail()){
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Unknown Entry. Please Try Again." << endl;

				cout << "Please enter 1, 2, 3, or 4." << endl;
				std::cin >> userChoice;
				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
				cout << endl;
			}
			if (userChoice >= 0){
				//Passes the try test
				//Makes sure the user entered a POSITIVE integer
				//exits the do-while
				correctInput = true;
			} else{ throw (userChoice); system("Color 03"); }
		} catch (...) { cout << "Please Enter 1, 2, 3, or 4." << endl; }


		if (userChoice == 1){
			//Prints the total amount of products that were purchased that day and stored in a file
			system("Color 0D");

			cout << endl;
			cout << "##############################################################################" << endl;
			cout << "#                         Total Produce Purchased Today                      #" << endl;
			cout << "##############################################################################" << endl;
			cout << endl;

			CallProcedure("read_File"); //reads the file in python


		} else if (userChoice == 2){
			system("Color 03");
			//ask user for a product
			string userString;
			cout << "Please Enter the Product you wish to look up: ";
			std::cin >> userString; //Grabs product the user wishes to look up

			int tot = callIntFunc("locate_Total_Product_Amount", userString); //Gets frequency of chosen user item product

			if (tot == -1) {
				cout << "The item could not be located within the data file. Make sure input is correct." << endl;
			} else{
				cout << "There were a total of " << tot << " " << userString << " sold today." << endl;
			}
		}
		else if (userChoice == 3) {
			system("Color 06");
			// Calls python function that will read a file, count and sort product amount
			CallProcedure("read_AND_Write_File");

		} else { programRun = false; system("Color 04"); } // Ends Program

	} while (programRun == true); //controls program flow
}

int main(){
	system("Color 03");
	//calls menu for main functionality of the program
	Menu();

	//Message when user exits program
	cout << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
	cout << "|||                      Program Shutting Down...                          |||" << endl;
	cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;

	return 0;
}
