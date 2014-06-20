#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "readcsv.h"
#include "read_data.h"
#include "matrix.h"

#include "folly/ProducerConsumerQueue.h"

#define SIZE_POS 3
#define SIZE_G 6


void read_data_to_queue(folly::ProducerConsumerQueue<matrix> &queue, const std::string &file, const int &maxLine) {
	std::ifstream infile(file);

	if(!infile.is_open() ) {
		std::cout << "File " << file << " could not be opened" << std::endl;
		return;
	}	

	// Placeholder for all the parsed data
	std::vector<double> v; 
	std::vector<double>::iterator it = v.end();

	int nLine = 0;


	// Let's preallocate a matrix to fill
	matrix M; 

	// Temporary vector and string
	std::vector<double> tmp(SIZE_G);
	std::string str = "";

	// Parse the file
	while( getline(infile, str) && nLine < maxLine ) {
		if(!client::parse_numbers(str.begin(),str.end(),v) ) {
			std::cout << "Parsing failed " << std::endl;
			infile.close();
			return;
		}

		// Data was appended to v - get the last element
		it = v.end();

		// Copy the last 6 data members into the matrix
		std::copy(it-SIZE_POS-SIZE_G,it-SIZE_POS,tmp.begin());
		M.set_elems(tmp);

		// Add the matrix to the queue
		while(!queue.write(M)) {
			continue;
		}
		++nLine;
	}	
 
 	infile.close();
}



int read_data(std::vector<double> &G, std::vector<double> &POS,const int &maxLine) {

	std::string file = "";
	
	file = "./100MB";

//	std::cout << "Parsing data file at " << file << std::endl;
	if( read_file(G,POS,file,maxLine) ) {
	//	std::cout << "Success" << std::endl;
		return PARSER_SUCCESS;
	} else {
	//	std::cout << "Failed" << std::endl;
		return PARSER_FAILED;
	}	
	return PARSER_SUCCESS;
}		

bool read_file(std::vector<double> &G, std::vector<double> &POS, std::string &file, const int &maxLine) {

	std::ifstream infile(file);
	if (!infile.is_open()) {
		std::cout << "File " << file << " could not be opened" << std::endl;
		return false;
	}	


	std::string str = "";
	std::vector<double> v;
	std::vector<double>::iterator it = v.end();

	std::back_insert_iterator< std::vector<double> > b_it_g(G);
//	std::back_insert_iterator< std::vector<double> > b_it_pos(POS);

	int nLine = 0;

	while (getline(infile, str) && nLine < maxLine) {
		if (!client::parse_numbers(str.begin(), str.end(),v) ) {
			std::cout << "Parsing failed\n";
			infile.close(); 
			return false;
		}
		// Data was appended to V
		it = v.end();
		// Copy backward 3 elements and insert in POS
//		std::copy(it-SIZE_POS,it,b_it_pos);
		// Copy backward 6 additional elements and insert in G
		std::copy(it-SIZE_POS-SIZE_G,it-SIZE_POS,b_it_g);
		 
		// Increment number of records
		++nLine;
	}


	infile.close(); 
	return true;
}
