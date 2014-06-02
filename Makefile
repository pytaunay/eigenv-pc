CXX=g++

EXEC=proc

CXXFLAGS=-std=c++0x -O3 -xHost -openmp 

INC=-I./inc -I/usr/global/intel-13/boost/1.54.0/include
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
	
