#ifndef _EIGENVALUES_H_
#define _EIGENVALUES_H_

void eigenvalues_3x3_sym(const double *M, std::vector<double> &VM); 
void eigenvector_3x3_sym(const double *M, const double &eM, std::vector<double> &eigV); 
double determinant_3x3_sym(const double *M); 
double norm_3x1(const double *T);

#endif
