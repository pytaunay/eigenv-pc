#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

#include "utils.h"
#include "eigenvalues.h"

#define DEL 1e-10
#define EPS 1e-8


// Calculates the eigenvalues of a 3x3 symmetric matrix, stored in a row-major format
// [ a b c ]
// [ b d e ]
// [ c e f ]
void eigenvalues_3x3_sym(const double *M, std::vector<double> &VM) {

	double a,b,c,d,e,f;

	a = M[0]; 
	b = M[1];
	c = M[2];

	d = M[3];
	e = M[4]; 
	f = M[5];

	// Characteristic polynomial of M:
	// X^3 + 3*alpha*X^2 + 3*beta*X + gam = 0
	double alpha = -1.0/3.0 * (a + d + f);
	double beta = 1.0/3.0 * ( (a*d-b*b) + (a*f-c*c) + (d*f - e*e) );
	double gam = -1.0 * (a*d*f + 2.0*b*c*e - b*b*f - c*c*d - e*e*a);

	//// Find X = v + (u-v) / 1+del^(1/3) -- contains all solutions 
	//// where del = - (alpha + u)/(alpha + v), and
	//// u,v solutions of (alpha^2 - beta) Y^2 + (alpha*beta - gam ) * Y + (beta^2 - alpha*gam) = 0
	
	double b2 = (alpha * beta - gam);
	double f_ac = 4.0*(beta*beta - alpha*gam)*(alpha*alpha - beta);
	double den = 2.0*(alpha*alpha - beta);

	std::complex<double> u,v;
	std::complex<double> tmp(b2*b2 - f_ac, 0.0);


	u = sqrt(tmp);
	u.real( ( -1.0*b2 + u.real() ) / den );
	u.imag( u.imag()/den );


	v = sqrt(tmp);
	v.real( ( -1.0*b2 - v.real() ) / den );
	v.imag( -v.imag()/den );

	// del = - (alpha + u)/(alpha + v)
	std::complex<double> del_num( alpha + u.real(), u.imag()); 
	std::complex<double> del_den( alpha + v.real(), v.imag()); 

	std::complex<double> del = del_num/del_den;
	del.real(-1.0*del.real());;
	del.imag(-1.0*del.imag());;

	// del^1/3 : three roots
	double r = powf(abs(del),1.0/3.0);
	double th = arg(del)/3.0;

	std::complex<double> r1 = std::polar( r , th + 2.0*0.0*M_PI/3.0 ); 
	std::complex<double> r2 = std::polar( r , th + 2.0*1.0*M_PI/3.0 ); 
	std::complex<double> r3 = std::polar( r , th + 2.0*2.0*M_PI/3.0 ); 

	// Eigenvalues: v + (u-v)/(1 + del^1/3)
	double e1,e2,e3;
	std::complex<double> one( 1.0, 0.0);

	e1 = std::real( v + (u-v)/(one + r1));
	e2 = std::real( v + (u-v)/(one + r2));
	e3 = std::real( v + (u-v)/(one + r3));


//	std::cout << e1 <<" "<< e2 <<" "<< e3 << std::endl;

	// Largest eigenvalue
	VM.push_back(max(max(e1,e2),e3)); 
}	


// Find corresponding eigenvector of eM in matrix M 
void eigenvector_3x3_sym(const double *M, const double &eM, std::vector<double> &eigV) {

	double sig = eM + DEL;

	double T[3] = {0.0};
	double Tn[3] = {1.0/sqrt(3.0)};

	// Cofactors
	double c11, c12, c13, c22, c23, c33 = 0.0;

	//// S-sig I
	// Initialize S to the original matrix
	double S[6] = {0.0};
	for(int i = 0; i < 6; ++i) {
		S[i] = M[i];
	}	

	// Determinant
	double det = 0.0;
	S[0] -= sig;
	S[3] -= sig;
	S[5] -= sig;

	det = determinant_3x3_sym(S);

	double a,b,c,d,e,f;

	a = S[0]; 
	b = S[1];
	c = S[2];

	d = S[3];
	e = S[4]; 
	f = S[5];

	// Inverse of a general matrix given by
	// A^-1 = t(com(A))/det(A), where com(A) is comatrix: matrix made of co-factors of A
	// For a symmetric 3x3, com(A) is symmetric and given by
	// [d*f - e^2, e*c-b*f, b*e-c*d ]
	// [ ------  , a*f-c^2, b*c-a*e ]
	// [ ------  , -------, a*d-b^2 ]
	c11 = (d*f-e*e)/det;
	c12 = (e*c-b*f)/det;
	c13 = (b*e-c*d)/det;

	c22 = (a*f-c*c)/det;
	c23 = (b*c-a*e)/det;

	c33 = (a*d-b*b)/det;
	
	double nrm = 0.0;
	double crit = 1.0;
	double Tcrit[3] = {0.0};

	while (crit > EPS) { 
		for(int i = 0; i < 3; ++i ) {
			T[i] = Tn[i];
		}

		Tn[0] = c11*T[0] + c12*T[1] + c13*T[2];
		Tn[1] = c12*T[0] + c22*T[1] + c23*T[2];
		Tn[2] = c13*T[0] + c23*T[1] + c33*T[2];

		nrm = norm_3x1(Tn);
		
		for(int i = 0; i < 3; ++i ) {
			Tn[i] /= nrm;
		}

		// Stopping criterion: crit = norm(|Tn| - |T|)
		crit = 0.0;
		for(int i = 0; i<3;++i) {
			Tcrit[i] = abs(Tn[i])-abs(T[i]);
		}
		crit = norm_3x1(Tcrit);
	}	

	// Tn is an eigen vector
	for(int i = 0; i<3; ++i) {
		eigV.push_back(Tn[i]);
	}	
}
		
double determinant_3x3_sym(const double *M) {		

	double a,b,c,d,e,f;

	a = M[0]; 
	b = M[1];
	c = M[2];

	d = M[3];
	e = M[4]; 
	f = M[5];

	return (a*d*f + 2.0*b*e*c - b*b*f - e*e*a - c*c*d);
}

double norm_3x1(const double *T) {
	double nrm = 0.0;

	for(int i = 0; i < 3; ++i) {
		nrm += T[i]*T[i];
	}

	return ( sqrt(nrm) );
}	
