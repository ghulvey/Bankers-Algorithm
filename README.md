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

# Sample Input and Output
## Input File

`default.json`

```
{
    "resources": [{
            "name": "a",
            "instances": 10,
            "avalible": 3
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

# Libraries Used
https://github.com/nlohmann/json - For JSON Parsing
