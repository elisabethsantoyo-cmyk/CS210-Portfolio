#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void LoadItemsFromFile(const string& inputFile) {
        ifstream inFS(inputFile);
        string itemName;

        if (!inFS.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return;
        }

        while (inFS >> itemName) {
            itemFrequency[itemName]++;
        }

        inFS.close();
    }

    void SaveFrequencyFile(const string& outputFile) {
        ofstream outFS(outputFile);

        for (const auto& pair : itemFrequency) {
            outFS << pair.first << " " << pair.second << endl;
        }

        outFS.close();
    }

    int GetItemFrequency(const string& itemName) const {
        auto it = itemFrequency.find(itemName);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void PrintHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

int main() {
    GroceryTracker tracker;
    int userChoice = 0;
    string itemToSearch;

    tracker.LoadItemsFromFile("CS210_Project_Three_Input_File.txt");
    tracker.SaveFrequencyFile("frequency.dat");

    do {
        cout << endl;
        cout << "Corner Grocer Menu" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print all item frequencies" << endl;
        cout << "3. Print histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        while (cin.fail() || userChoice < 1 || userChoice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Try again: ";
            cin >> userChoice;
        }

        if (userChoice == 1) {
            cout << "Enter item name: ";
            cin >> itemToSearch;
            cout << itemToSearch << " was purchased "
                << tracker.GetItemFrequency(itemToSearch)
                << " time(s)." << endl;
        }
        else if (userChoice == 2) {
            tracker.PrintAllFrequencies();
        }
        else if (userChoice == 3) {
            tracker.PrintHistogram();
        }

    } while (userChoice != 4);

    cout << "Goodbye!" << endl;

    return 0;
}