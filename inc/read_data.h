#ifndef _READ_DATA_H
#define _READ_DATA_H

#include <string>
#include <vector>

#include "folly/ProducerConsumerQueue.h"
#include "matrix.h"

enum {PARSER_FAILED=0,PARSER_SUCCESS=1};


void read_data_to_queue(folly::ProducerConsumerQueue<matrix> &queue, const std::string &file, const int &maxLine); 




int read_data(std::vector<double> &G, std::vector<double> &POS,const int &maxLine); 
bool read_file(std::vector<double> &G, std::vector<double> &POS, std::string &file,const int &maxLine); 

#endif

