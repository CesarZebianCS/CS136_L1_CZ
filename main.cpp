// Cesar Zebian
// Lab #1 Files - Refresher F25
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const string INPUT_FILE = "inventory.txt";
const string ERROR_FILE = "errors.txt";
const int MAX_RECORDS = 100;

struct CarRecord {
    string carID;
    string model;
    int quantity;
    double price;
    string errorMessage;
};

int numValid = 0;
CarRecord validCars[MAX_RECORDS];
CarRecord invalidCars[MAX_RECORDS];
int numInvalid = 0;

// Function prototypes
void getData();
bool isValidRecord(const CarRecord& temp, string& errorMsg);
void printValidRecords();
void printInvalidRecords();

// Read file and validate records
void getData() {
    ifstream infile(INPUT_FILE);
    ofstream errorfile(ERROR_FILE);

    if (!infile) {
        cout << "Error opening input file.\n";
    }
    else if (!errorfile) {
        cout << "Error opening error file.\n";
    }
    else {
        CarRecord temp;
        while (infile >> temp.carID >> temp.model >> temp.quantity >> temp.price) {
            string errorMsg = "";
            if (isValidRecord(temp, errorMsg)) {
                if (numValid < MAX_RECORDS) {
                    validCars[numValid++] = temp;
                }
            }
            else {
                temp.errorMessage = errorMsg;
                if (numInvalid < MAX_RECORDS) {
                    invalidCars[numInvalid++] = temp;
                    errorfile << setw(10) << left << temp.carID
                              << setw(12) << left << temp.model
                              << setw(8) << right << temp.quantity
                              << setw(12) << right << fixed << setprecision(2) << temp.price
                              << "   " << temp.errorMessage << endl;
                }
            }
        }
    }

    infile.close();
    errorfile.close();
}

// Validate record
bool isValidRecord(const CarRecord& temp, string& errorMsg) {
    bool valid = true;

    if (temp.carID.length() != 10) {
        errorMsg += "Invalid ID length; ";
        valid = false;
    }
    if (temp.model.length() < 3) {
        errorMsg += "Model too short; ";
        valid = false;
    }
    if (temp.quantity <= 0) {
        errorMsg += "Quantity must be above 0; ";
        valid = false;
    }
    if (temp.price < 24995.0) {
        errorMsg += "Price must be above 24995.00; ";
        valid = false;
    }

    return valid;
}

// Print valid records
void printValidRecords() {
    cout << "\nValid Car Records:\n";
    cout << setw(10) << left << "CarID"
         << setw(12) << left << "Model"
         << setw(8) << right << "Quantity"
         << setw(12) << right << "Price" << endl;
    cout << "-------------------------------------------\n";

    for (int i = 0; i < numValid; i++) {
        cout << setw(10) << left << validCars[i].carID
             << setw(12) << left << validCars[i].model
             << setw(8) << right << validCars[i].quantity
             << setw(12) << right << fixed << setprecision(2) << validCars[i].price
             << endl;
    }
}

// Print invalid records
void printInvalidRecords() {
    cout << "\nInvalid Car Records:\n";

    if (numInvalid == 0) {
        cout << "No invalid records.\n";
    }
    else {
        cout << setw(10) << left << "CarID"
             << setw(12) << left << "Model"
             << setw(8) << right << "Quantity"
             << setw(12) << right << "Price"
             << "   Errors" << endl;
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < numInvalid; i++) {
            cout << setw(10) << left << invalidCars[i].carID
                 << setw(12) << left << invalidCars[i].model
                 << setw(8) << right << invalidCars[i].quantity
                 << setw(12) << right << fixed << setprecision(2) << invalidCars[i].price
                 << "   " << invalidCars[i].errorMessage << endl;
        }
    }
}

// Main program
int main() {
    getData();

    int choice = 0;
    while (choice != 3) {
        cout << "\nMenu:\n";
        cout << "1. Print all valid car records\n";
        cout << "2. Print invalid records\n";
        cout << "3. Quit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            printValidRecords();
        }
        else if (choice == 2) {
            printInvalidRecords();
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    /*

    return 0;
}


*/
