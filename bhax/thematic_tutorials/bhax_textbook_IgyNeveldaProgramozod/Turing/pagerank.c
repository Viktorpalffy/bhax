#include "stdio.h"
#include <math.h>

double tavolsag(double* PR, double* PRv) {
		
	double tav = 0.0;
	double seged = 0.0;

	for(int i=0; i < sizeof(PR)/sizeof(double); i++) {
		if(PR[i] - PRv[i] < 0){
			seged = (PR[i] - PRv[i])*-1;
			tav += seged;
		}
		else{
		tav += PR[i] - PRv[i];
		}
	}
	

	return tav;
}

int main() {
	double L[4][4] = {						//
		{0.0, 0.0, 1.0 / 3.0, 0.0},
		{1.0, 1.0 / 2.0, 1.0 / 3.0, 1.0},
		{0.0, 1.0 / 2.0, 0.0, 0.0},
		{0.0, 0.0, 1.0 / 3.0, 0.0}
	};

	double PR[4];							//
	for(int i=0; i<sizeof(PR)/sizeof(double); i++) {
		PR[i]=0.0;
	}

	double PRv[4];							//
	for(int i=0; i<sizeof(PRv)/sizeof(double); i++) {
		PRv[i]=(1.0 / 4.0);
	}

	for(;;) {								//
		for( int i = 0; i< sizeof(PR)/sizeof(double); i++){
			PR[i] = PRv[i];
		}

		for(int i=0; i<sizeof(PR)/sizeof(double); i++) {				//
			double temp = 0.0;

			for(int j=0; j<sizeof(PRv)/sizeof(double); j++) {			//
				temp += L[i][j] * PR[j];			//
				PRv[i] = temp;					//
			}
		}

		if(tavolsag(PR, PRv) < 0.00001) {				//
			break;
		}
	}

	for( int i = 0; i< sizeof(PR)/sizeof(double); ++i){
		printf("Pagerank[ %d ]értéke: %f\n ", i, PR[i]);
	}								//
	return 0;
}
