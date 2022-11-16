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
    int ans[processes];
    
    // True if process is done
    bool done[processes];

    // Load the allocation and maximum information from JSON file into a 2D array
    for(int i = 0; i < processes; ++i){
        for(int j = 0; j < resources; ++j){
            allocation[i][j] = data["processes"][i]["allocation"][j];
            max[i][j] = data["processes"][i]["max"][j];

            // Using the allocation and max matrix calculate need
            // need = max - allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
        done[i] = false;
    }

    // Read in the available resources from the JSON file
    int available[resources];
    for(int i = 0; i < resources; ++i) {
        available[i] = data["resources"][i]["available"];
    }

    int sequencePos = 0;

    // The max number of runs for the algorithm is the same as the number of processes
    for(int maxPass = 0; maxPass < processes; ++maxPass) {
        // Loop for each process
        for(int j = 0;j < processes; ++j) {
            if(done[j] == false){
                bool valid = true;

                // Determine if need is not greater than work
                for(int i = 0; i < resources; ++i){
                    if(need[j][i] > available[i]) {
                        valid = false;
                        break;
                    }
                }

                // If need is not greater than work
                if(valid) {
                    // Update the processes index in the done array
                    ans[sequencePos] = j;
                    ++sequencePos;

                    // Update the number of resources available
                    // available = available + allocation
                    for(int i = 0; i < resources; ++i){
                        available[i] += allocation[j][i];
                    }

                    done[j] = true;
                }
            }
        }
    }
    

    // Determine if the sequence is safe
    // The done array will not have a -1
    // The done array stores the index when a process whould be performed
    bool isSafe = true;
    for(int i = 0; i < resources; ++i) {
        if(done[i] == false) {
            isSafe = false;
            break;
        }
    }

    if(isSafe) {

        // A safe sequence was found, output it.

        std::cout << "The following is the safe sequence:" << std::endl;
        for(int i = 0; i < processes; ++i) {
            if(i != 0)
                std::cout << " -> ";
            int temp = ans[i];
            std::cout << std::string(data["processes"][temp]["name"]);
            
        }
        std::cout << std::endl;
    } else {

        // A safe sequence was not provided output a message

        std::cout << "There is NO safe sequence" << std::endl;
    }
}