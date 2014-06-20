#ifndef _MATRIX_H_
#define _MATRIX_H_

#define NELEM 6
#define NMATS 10


class matrix {
	protected:
		double *elems;
		int nelem;

	public:
		// Ctor's
		matrix() {
		//	std::cout << "Call ctor" << std::endl;
			elems = new double[NELEM];
			this->nelem = NELEM;

			for(int i = 0; i < nelem; ++i) 
				elems[i] = 0.0;
		}	

		matrix(int nelem) {
			elems = new double[nelem];
			this->nelem = nelem;

			for(int i = 0; i < nelem; ++i) 
				elems[i] = 0.0;
		}	

		// Copy assignment
		matrix& operator=(const matrix& rhs) {
			this->nelem = rhs.nelem;

			for(int i = 0; i < NELEM; ++i) {
				this->elems[i] = rhs.elems[i];
			}	
			return *this;
		}

		// Setter for the elements
		void set_elems(const std::vector<double> &rhs) {
			assert(this->nelem == rhs.size());

			int i = 0;
			for(auto it = rhs.begin(); it != rhs.end(); ++it) {
				this->elems[i] = *it;
				++i;
			}
		}	
	
		double* const& get_elems() const {
			return this->elems;

		}


		// Destructor
		~matrix() {
		//	std::cout << "Call dtor" << std::endl;
			delete [] elems;
		}

		// Print elements
		void print() {
			for(int i = 0; i < NELEM; ++i) {
				std::cout << elems[i] << std::endl;
			}
		}	
};



#endif
