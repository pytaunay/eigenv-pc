CXX=g++

EXEC=proc

#CXXFLAGS=-std=c++0x -O3 -xHost -openmp 
CXXFLAGS=-std=c++11 -O3 -pthread -fopenmp -march=corei7-avx 

INC=-I./inc -I/usr/global/intel-13/boost/1.54.0
#LIB=-L/usr/global/intel-13/boost/1.54.0/lib -lboost_thread -lboost_system
LIB=


SRC:=$(wildcard src/*.cpp)
OBJ:=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))

all: $(EXEC)
	mv $< bin/

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIB)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ 

clean:
	rm  $(OBJ) 
	rm bin/$(EXEC) 
	
