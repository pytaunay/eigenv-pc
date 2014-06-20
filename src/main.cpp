#include <iostream>
#include <vector>
#include <thread>

#include <omp.h>

#include "folly/ProducerConsumerQueue.h"
#include "matrix.h"
#include "read_data.h"
#include "eigenvalues.h"

int main(int argc, char* argv[]) {


	double tic,toc;

	////////////////////////////////////////
	// SOLUTION 1: Using a lock free queue
	////////////////////////////////////////
	tic = omp_get_wtime();
	folly::ProducerConsumerQueue<matrix> queue(100);

	int maxLine = 1000000;
	std::string file = "./100MB";

	std::thread producer(read_data_to_queue, std::ref(queue), std::ref(file), std::ref(maxLine));

	// Eigenvalues and eigenvectors
	matrix M(6);
	std::vector<double> VM;
	std::vector<double> eigV;

	std::thread consumer([&queue,&M,&VM,&eigV,&maxLine] {
		for(int i = 0; i < maxLine; ++i) {
			//std::cout << i << std::endl;
			while(!queue.read(M)) {
				continue;
			}
			eigenvalues_3x3_sym(M.get_elems(),VM);
			eigenvector_3x3_sym(M.get_elems(),VM.back(),eigV);
		}
	});	

	// Wait for the two joins
	producer.join();
	consumer.join();

	toc = omp_get_wtime();

	// Time
	std::cout << "Lock-free queue timings (s) " << toc-tic << std::endl;

//	for(int i = 0; i < VM.size(); ++i) {
//		std::cout << i << " " << VM[i] << std::endl;
//		std::cout << eigV[3*i] << " " << eigV[3*i+1] << " " << eigV[3*i + 2] << std::endl;
//	}	
	////////////////////////////////////////
	// SOLUTION 2: Simple read and parse
	////////////////////////////////////////
	/*
	VM.clear();
	eigV.clear();

	// Read data
	std::vector<double> G;
	std::vector<double> POS;

	tic = omp_get_wtime();
	int ret = read_data(G,POS,maxLine);

	// Calculate the eigenvalues and eigenvectors
	for(int i = 0; i < maxLine; ++i) {
		eigenvalues_3x3_sym(&G[6*i],VM);
		eigenvector_3x3_sym(&G[6*i],VM.back(),eigV);
	}	
	
	toc = omp_get_wtime();

	std::cout << "Serial timing (s) " << toc-tic << std::endl;

//	for(int i = 0; i < VM.size(); ++i) {
//		std::cout << i << " " << VM[i] << std::endl;
//		std::cout << eigV[3*i] << " " << eigV[3*i+1] << " " << eigV[3*i + 2] << std::endl;
//	}	
*/
	return 0;

}
	
