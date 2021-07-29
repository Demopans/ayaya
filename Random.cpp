#include "Random.h"

double next_exp(double lambda, int upper_bound) {
	
	double r = drand48();
	double x = -log(r) / lambda;
	while(x > upper_bound) {
		r = drand48();
		x = -log(r) / lambda;
	}
	return x;
}
