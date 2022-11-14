#include <iostream>
#include <fstream>
#include "json.hpp"
#include <cstring>

int main(int argc, char *argv[]) { 

    std::ifstream f;

    // Open the json data file
    if(argc == 1) {
        f.open("default.json");
    } else {
        f.open(argv[1]);
    }
    
    nlohmann::json data = nlohmann::json::parse(f);

    // Calculate the number of processes and resources
    int processes = data["processes"].size();
    int resources = data["resources"].size();
    
    // Create arrays for storage
    int allocation[processes][resources];
    int max[processes][resources];

    // Stores need for each of the process
    int need[processes][resources];

    // Saves the index for the order of process
    // [0]=1 - Process 0 should be processed second
    // [1]=0 - Process 1 should be processed first
    int done[processes];

    // Load the allocation and maximum information from JSON file into a 2D array
    for(int i = 0; i < processes; ++i){
        for(int j = 0; j < resources; ++j){
            allocation[i][j] = data["processes"][i]["allocation"][j];
            max[i][j] = data["processes"][i]["max"][j];

            // Using the allocation and max matrix calculate need
            // need = max - allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
        done[i] = -1;
    }

    // Read in the avalible resources from the JSON file
    int avalible[resources];
    for(int i = 0; i < resources; ++i) {
        avalible[i] = data["resources"][i]["avalible"];
    }

    int sequencePos = 0;
    int j = 0;
    bool onePass = true;
    while(j < processes) {
        if(done[j] == -1){
            bool valid = true;

            // Determine if need is not greater than avalibility
            for(int i = 0; i < resources; ++i){
                if(need[j][i] > avalible[i]) {
                    valid = false;
                    break;
                }
            }

            // If need is not greater than avalibility
            if(valid) {
                // Update the processes index in the done array
                done[j] = sequencePos;
                ++sequencePos;

                // Update the number of resources avalible
                // avalible = avalible + allocation
                for(int i = 0; i < resources; ++i){
                    avalible[i] += allocation[j][i];
                }
            }
        }
        ++j;
        if(j == processes && onePass){
            onePass = false;
            j = 0;
        }
    }
    

    // Determine if the sequence is safe
    // The done array will not have a -1
    // The done array stores the index when a process whould be performed
    bool isSafe = true;
    for(int i = 0; i < resources; ++i) {
        if(done[i] == -1) {
            isSafe = false;
            break;
        }
    }

    if(isSafe) {

        // A safe sequence was found, output it.

        std::cout << "The following is the safe sequence:" << std::endl;
        for(int count = 0; count < processes; ++count) {
            if(count != 0)
                std::cout << " -> ";
            for(int i = 0; i < processes && count < processes; ++i) {
                if(count == done[i]) {
                    std::cout << std::string(data["processes"][i]["name"]);
                    break;
                }
            }
            
        }
        std::cout << std::endl;
    } else {

        // A safe sequence was not provided output a message

        std::cout << "There is NO safe sequence" << std::endl;
    }
}