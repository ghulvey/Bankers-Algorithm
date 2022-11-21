# Banker's Algorithm
**CS 33211** - Programming Assignment 2

**Author:** Gavin Hulvey

[![Compile and Test with Make](https://github.com/ghulvey/Bankers-Algorithm/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/ghulvey/Bankers-Algorithm/actions/workflows/c-cpp.yml)

# Run Instructions

This project can be downloaded using git. The program can be loaded via make or clang.
## Cloning the Repository

Run the following commands after changing to your desired directory to store the repository. Note: the name `Bankers-Algorithm` can be changed to any name of your choosing, this will be the folder where the repository will be contained.

```
git clone https://github.com/ghulvey/Bankers-Algorithm.git Bankers-Algorithm
cd Bankers-Algorithm
```

## Running with Make

Run one of the following commands based on your use case

- `make` output a list of commands
- `make compile` generate the executable file `./bankers-algo`
  - Then run `./banker-algo file.json` replace `file.json` with a file of your choosing. If the file field if not provided `default.json` will be loaded
- `make default` compile and run the program using `default.json` (can output a safe sequence)
- `make invalid` compile and run the program using `invalid.json` (can NOT output a safe sequence)
- `make clean` remove object files and deletes executables

## Compile with clang

```
clang++ main.cpp -o banker-algo
./banker-algo default.json
```

`default.json` contains the data provided in the assignment, this file can be repalced with any correctly formatted file of your choosing. If no file name is provided `default.json` will be loaded.

## Video Demo

https://user-images.githubusercontent.com/19355415/202058727-4285d13b-7763-49ad-b238-fea1a7d93fc5.mp4

# Sample Input and Output
## Input File

`default.json`

```
{
    "resources": [{
            "name": "a",
            "instances": 10,
            "available": 3
        },
        ...
    ],
    "processes": [{
            "name": "p0",
            "allocation": [0, 1, 0],
            "max": [7, 5, 3]
        },
        ...

    ]
}
```

## Program Output

With `default.json`

```
./banker-algo default.json
The following is the safe sequence:
p1 -> p3 -> p4 -> p0 -> p2
```

With `invalid.json`, no safe sequence is possible
```
./banker-algo invalid.json
There is NO safe sequence
```

# Implementation
## File Input

For my file I elected to use JSON as a file format. There are two main objects in the file, `resources` and `processes`. The resources object contains an array of objects each with a name, the number of instances, and the number available. The processes object contains an array of objects that specify the name, an array corresponding to allocation, and another array corresponding to the maximum for each of the resources.

[A sample JSON file, using the data provided for this assignment](default.json)

## Data Storage

The data from the JSON files are loaded into a 2D array, or a regular array using a for loop. Allocation and maximum use 2D arrays, while available resources uses a regular array.

While data is being converted from JSON to arrays, the need for each process is also calculated. Using the following code:

```
need[i][j] = max[i][j] - allocation[i][j];
```

## Algorithm

I created a two separate arrays each with the same number of elements as the same number of process. The done array stores true is a process has been allocated. The ans array stores the process index in the order they were allocated. If p0 was allocated second `ans[1]=0`

The algorithm uses a two for loops which will not execute more than the number of processes, in the case where there is no safe sequence.

A nested for loop is used to determine if work (available) is less less than or equal to need

```
for(int i = 0; i < resources; ++i){
    if(need[j][i] > available[i]) {
        valid = false;
        break;
    }
}
```

If the process is less than equal to work the following loop is ran to update work.

```
for(int i = 0; i < resources; ++i){
     available[i] += allocation[j][i];
}
```


The process id is stored within the answer array, and the process is marked done (true) in the done array

```
ans[sequencePos] = j; // j process index
++sequencePos;

done[j] = true;
```

The algorithm loop will continue until a safe sequence has been established or it is found that there is no safe sequence.

## Determining if a Sequence is Safe

The done array is looped through to check all process has a non negative index. If a negative index is present this means their is no safe sequence

```
bool isSafe = true;
for(int i = 0; i < resources; ++i) {
    if(done[i] == false) {
        isSafe = false;
        break;
    }
}
```

## Outputting the Result

If there is no safe sequence an error message is outputted to the user sating `There is safe sequence`. Otherwise, the processes in the answer array are outputted using the process names specified in the JSON file:

```
The following is the safe sequence:
p1 -> p3 -> p4 -> p0 -> p2
```

# Libraries Used
https://github.com/nlohmann/json - For JSON Parsing
