// Include headers for reading from a file, populating data structure, etc.
#include <iostream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_COOKING_ORDER = 5;

// Define a function to simulate restaurant order state changes over time
// Parameters: map of cuisines, and number of time periods
void simulateCuisine(map<string, array<list<string>,3>> &cuisineMap, int timePeriods);
bool loadOrdersFromFile(map<string, array<list<string>,3>> &cuisineMap);

// Define main() function
int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed random number generator with current time

    // Initialize a map<string, array<list<string>,3>> called cuisineMap to store 
    // the information for the different cuisines, each associated with an array 
    // of lists for orders that are in the waiting phase, cooking phase, and 
    // completed phase
    map<string, array<list<string>,3>> cuisineMap;

    if (!loadOrdersFromFile(cuisineMap))
    {
        cout << "Error: could not open orders.txt" << endl;
        return 1;  // exit program with error code
    }

    // Call the simulateCuisine() function
    simulateCuisine(cuisineMap, 25);

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
            // Move 1 order from cooking [1] to completed [2] if list not empty
            // if cooking list not empty:
                // remove first order from cooking
                // add to completed list

            list<string> &waitingOrders = cuisine.second[0];
            list<string> &cookingOrders = cuisine.second[1];
            list<string> &completedOrders = cuisine.second[2];

            if (cookingOrders.size() > 0)
            {
                int randomCompletedOrders = rand() % cookingOrders.size() + 1;

                for (int cookingOrderIndex = 0; cookingOrderIndex < randomCompletedOrders; ++cookingOrderIndex)
                {
                    string cookingOrder = cookingOrders.front();
                    completedOrders.push_back(cookingOrder);
                    cookingOrders.pop_front();
                }
            }

            // Move 1 order from waiting [0] to cooking [1] if list not empty
            //if waiting list not empty:
                // remove first order from waiting
                // add to cooking list
            int waitingOrdersToBeMovedToCooking = MAX_COOKING_ORDER;
            if (waitingOrders.size() > 0)
            {
                if (cookingOrders.size() > 0)
                {
                    waitingOrdersToBeMovedToCooking -= cookingOrders.size();
                }

                for (int waitingOrderIndex = 0; waitingOrderIndex < waitingOrdersToBeMovedToCooking && waitingOrderIndex < waitingOrders.size(); ++waitingOrderIndex)
                {
                    string waitingOrder = waitingOrders.front();
                    cookingOrders.push_back(waitingOrder);
                    waitingOrders.pop_front();
                }
            }

            // Optionally, add a new dummy order to waiting list
            // add "OrderX-CuisineName" to waiting list
            int randomWaitingOrdersToAdd = rand() % 2;
            for (int randomWaitingOrderToAdd = 0; randomWaitingOrderToAdd < randomWaitingOrdersToAdd; ++randomWaitingOrderToAdd)
            {
                
            }

            // Print current number of orders in waiting, cooking, completed for this cuisine
            cout << "Simulating cuisine: " << cuisine.first << endl;
            cout << "Orders - Waiting: " << waitingOrders.size()
                    << ", Cooking: " << cookingOrders.size()
                    << ", Completed: " << completedOrders.size() << endl;

            // Wait or pause briefly to simulate passage of time                
        }
    }
}

bool loadOrdersFromFile(map<string, array<list<string>,3>> &cuisineMap)
{
    // Open and external file ("orders.txt") to populate the map from it
    ifstream inputFile("orders.txt");

    // Check if file is open successfully otherwise print an error and exit
    if (!inputFile) 
    {
        return false;
    }

    // Read data from file until the end of file is reached 
    string line;
    while (getline(inputFile, line)) 
    {
        // For each line, extract cuisine name and order data
        stringstream ss(line);
        string cuisineName;
        string order;

        // Insert into map (wireframe)
        // cuisineMap[cuisineName][0].push_back(order);
        if (getline(ss, cuisineName, ',') && getline(ss, order)) 
        {
            // Insert order into the appropriate list in the array for their cuisine
            cuisineMap[cuisineName][0].push_back(order);  // add to waiting list
        }
    }

    // Close the file
    inputFile.close();
    
    return true;
}