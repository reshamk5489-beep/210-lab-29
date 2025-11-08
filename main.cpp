// Include headers for reading from a file, populating data structure, etc.
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Define a function to simulate restaurant order state changes over time
// Parameters: map of cuisines, and number of time periods
void simulateCuisine(map<string, array<list<string>,3>> &cuisineMap, int timePeriods);
void loadOrdersFromFile(map<string, array<list<string>,3>> &cuisineMap);

// Define main() function
int main()
{
    // Initialize a map<string, array<list<string>,3>> called cuisineMap to store 
    // the information for the different cuisines, each associated with an array 
    // of lists for orders that are in the waiting phase, cooking phase, and 
    // completed phase
    map<string, array<list<string>,3>> cuisineMap;

    // Open and external file ("orders.txt") to populate the map from it
    ifstream inputFile("orders.txt");

    // Check if file is open successfully otherwise print an error and exit
    if (!inputFile) 
    {
        cout << "Error: could not open orders.txt" << endl;
        return 1;  // exit program with error code
    }

    loadOrdersFromFile(cuisineMap);

    // Call the simulateCuisine() function
    simulateCuisine(cuisineMap, 1);

    return 0;
}

// simulateCuisine function logic
void simulateCuisine(map<string, array<list<string>,3>> &cuisineMap, int timePeriods)
{
    cout << endl << endl << "simulateCuisine() called with " << cuisineMap.size() << " cuisines." << endl;
    
    // for each time period (1 to 25):
    for (int i = 1; i <= timePeriods; ++i)
    {
        // for each cuisine in the map:
        for (auto& cuisine : cuisineMap)
        {
            // Move 1 order from waiting [0] to cooking [1] if list not empty
            //if waiting list not empty:
                // remove first order from waiting
                //add to cooking list

            // Move 1 order from cooking [1] to completed [2] if list not empty
            // if cooking list not empty:
                // remove first order from cooking
                // add to completed list

            // Optionally, add a new dummy order to waiting list
            // add "OrderX-CuisineName" to waiting list

            // Print current number of orders in waiting, cooking, completed for this cuisine
            cout << "Simulating cuisine: " << cuisine.first << endl;
            cout << "Orders - Waiting: " << cuisine.second[0].size()
                    << ", Cooking: " << cuisine.second[1].size()
                    << ", Completed: " << cuisine.second[2].size() << endl;

            // Wait or pause briefly to simulate passage of time                
        }
    }
}

void loadOrdersFromFile(map<string, array<list<string>,3>> &cuisineMap)
{
    // Read data from file until the end of file is reached 
    string line;
    while (getline(inputFile, line)) 
    {
        // line contains one order from the file
        cout << "Read line: " << line << endl;

        // For each line, extract cuisine name and order data
        stringstream ss(line);
        string cuisineName;
        string order;

        // Insert into map (wireframe)
        // cuisineMap[cuisineName][0].push_back(order);
        if (getline(ss, cuisineName, ',') && getline(ss, order)) 
        {
            cout << "Cuisine: " << cuisineName << " order: " << order << endl;
            // Insert order into the appropriate list in the array for their cuisine
            cuisineMap[cuisineName][0].push_back(order);  // add to waiting list
        }
    }

    // Close the file
    inputFile.close();
}