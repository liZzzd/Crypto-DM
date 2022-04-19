#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "dm.h"

void SnM(mpz_t a, mpz_t n, mpz_t h) {
	mpz_t i, hi, tmp, r;
	mpz_init(i); 
	mpz_init(hi); 
	mpz_init(tmp);
	mpz_init(r);

	mpz_set(r, a);

	mpz_cdiv_q(h, h, deux);
	mpz_sub(tmp, h, un);
	mpz_set(i, tmp);

	while(mpz_cmp(i, zero) >= 0) {
		mpz_mul(r, r, r);
		mpz_mod(r, r, n);

		mpz_mod(tmp, h, deux);
		if((mpz_cmp(h, zero) != 0) && (mpz_cmp(tmp, zero) == 0)) {
			mpz_cdiv_q(h, h, deux);
			mpz_mul(r, r, a);
			mpz_mod(r, r, n);
		}
		mpz_sub(i, i, un);
	}
	mpz_set(snm, r);

	mpz_clear(i);
	mpz_clear(hi);
	mpz_clear(tmp);
	mpz_clear(r);
	
	return;
}


char Miller_Rabin(mpz_t n, int k) {
	mpz_t r, t, y, a, a1, tmp, minus, mun;
	gmp_randstate_t state;

	mpz_init(r);
	mpz_init(t);
	mpz_init(y);
	mpz_init(a);
	mpz_init(a1);
	mpz_init(tmp);
	mpz_init(minus);
	mpz_init(mun);
	mpz_set(minus, n);
	mpz_sub(minus, minus, un);
	mpz_init_set_str(mun, "-1", 10);
	gmp_randinit_mt(state); 

	mpz_set(t, n);
	mpz_sub(t, t, un);
	mpz_mod(r, t, deux);
	
	int s = 0;

	while(mpz_cmp(zero, r) == 0) {
		s++;
		mpz_cdiv_q(t, t, deux);
		mpz_mod(r, t, deux);
	}

	int i = 1;

	while( i <= k ) {
here:
		mpz_set(tmp, n);
		mpz_sub(tmp, tmp, un);
		mpz_urandomm(a, state, tmp);
		mpz_add(a, a, un);


		mpz_mod(a, a, minus);
		mpz_add(a, a, un);

		/*mpz_set(a1, a);
	 	while(mpz_cmp(un, t) < 0) {
	 		mpz_mul(a, a, a1);
	 		mpz_sub(t, t, un);
	 	}*/
		SnM(a, n, t);
	 	mpz_set(a, snm);

	 	mpz_mod(y, a, n);

	 	while(mpz_cmp(y, n) >= 0) {
	 		mpz_mod(y, y, n);	
	 	}
	 	mpz_mod(tmp, y, n);

	 	if( (mpz_cmp(tmp, un) != 0) && ((mpz_cmp(tmp, minus) != 0) || (mpz_cmp(tmp, mun) != 0)) ) {
	 		for(int j = 1 ; j < s ; j++) {
	 			mpz_mul(y, y, y);
	 			mpz_mod(y, y, n);
	 			mpz_mod(tmp, y, n);

	 			if(mpz_cmp(tmp, un) == 0) {
	 				return 'c';
	 			}
	 			if((mpz_cmp(tmp, minus) == 0) || (mpz_cmp(tmp, mun) == 0)) {
	 				i++;

	 				if(i <= k) {
	 					goto here;
	 				}
	 				else {
	 					goto there;
	 				}
	 			}
	 		}
	 	
	 		return 'c';
	 	}
	 	i++;
	}

there:
	mpz_clear(r);
	mpz_clear(t);
	mpz_clear(y);
	mpz_clear(a);
	mpz_clear(a1);
	mpz_clear(minus);
	mpz_clear(mun);
	mpz_clear(tmp);

	return 'p';
}


int main() {
	mpz_t n, t;

	mpz_init_set_str(deux, "2", 10);
	mpz_init_set_str(un, "1", 10);
	mpz_init_set_str(zero, "0", 10);
	mpz_init_set_str(n, "3", 10);
	mpz_init_set_str(t, "3", 10);
	mpz_init(snm);

	char str[4];
	str[0] = '\0';

	printf("MilLer-RaBin\n\n");

	for(int i = 2 ; i < 100 ; i++) {
		if(i%2 == 0) {
			printf("%d: c\n", i);
		}
		else {
			sprintf(str, "%d", i);
			mpz_init_set_str(n, str, 10);
			printf("%d: %c\n", i, Miller_Rabin(n, i/4));
		}	
		str[0] = '\0';
	}
	/*SnM(deux, n, t);

	mpz_out_str(stdout, 10, snm);*/

	mpz_clear(n);
	mpz_clear(t);
	mpz_clear(snm);
	mpz_clear(zero);
	mpz_clear(un);
	mpz_clear(deux);

	return 0;
}