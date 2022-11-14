CPP  = clang++
OPTS = -g -Werror -W -Wunused -Wuninitialized -Wshadow -std=c++11

output:
	@echo 'make compile: produces ./banker-algo executable'
	@echo './banker-algo file.json: Run with custom JSON file'
	@echo 'make default: Compiles and runs program with a working safe json file'
	@echo 'make unsafe: Compiles and runs program with a un-safe json file'
	@echo 'make clean: Removes objects and executable'

compile:
	$(CPP) $(OPTS) -c main.cpp 
	$(CPP) $(OPTS) -o banker-algo main.o

default:
	$(CPP) $(OPTS) -c main.cpp 
	$(CPP) $(OPTS) -o banker-algo main.o
	./banker-algo

unsafe:
	$(CPP) $(OPTS) -c main.cpp 
	$(CPP) $(OPTS) -o banker-algo main.o
	./banker-algo invalid.json

clean:
	rm -f *.o banker-algo