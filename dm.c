#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include "dm.h"

void SnM(mpz_t a, mpz_t n, mpz_t h) {
	mpz_t r;

	mpz_init(r);

	mpz_set(r, a);

	char* str = mpz_get_str(NULL, 2, h);

	for(int t = 1 ; t <= strlen(str)-1 ; t++) {
		mpz_mul(r, r, r);
		mpz_mod(r, r, n);

		if(str[t] == '1') {
			mpz_mul(r, r, a);
			mpz_mod(r, r, n);
		}
	}
	mpz_set(snm, r);

	mpz_clear(r);
	free(str);
	
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

	while((mpz_cmp(zero, t) != 0) && (mpz_cmp(zero, r) == 0)) {
		s++;
		mpz_tdiv_q(t, t, deux);
		mpz_mod(r, t, deux);
	}

	int i = 1;

	while( i <= k ) {
here:
		mpz_set(tmp, n);
		mpz_sub(tmp, tmp, deux);
		mpz_sub(tmp, tmp, deux);
		mpz_urandomm(a, state, tmp);
		mpz_add(a, a, deux);

		SnM(a, n, t);
	 	mpz_set(y, snm);
	 	mpz_set(tmp, y);

	 	if( (mpz_cmp(tmp, un) == 0) || (mpz_cmp(tmp, minus) == 0) ) {
	 		i++;

	 		if(i <= k) {
	 			goto here;
	 		}
	 		else {
	 			goto there;
	 		}
	 	}	
	 	
	 	for(int j = 1 ; j < s ; j++) {
	 		SnM(y, n, deux);
	 		mpz_set(y, snm);

	 		if(mpz_cmp(y, minus) == 0) {
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
	mpz_t n, t, neuf, ss;

	mpz_init_set_str(deux, "2", 10);
	mpz_init_set_str(un, "1", 10);
	mpz_init_set_str(zero, "0", 10);
	mpz_init_set_str(n, "3", 10);
	mpz_init_set_str(t, "7", 10);
	mpz_init_set_str(neuf, "3", 10);
	mpz_init_set_str(ss, "77", 10);
	mpz_init(snm);

	char str[4];
	str[0] = '\0';

	printf("MilLer-RaBin\n\n");

	for(int i = 1223 ; i < 1224 ; i++) {
		if(i%2 == 0) {
			printf("%d: c\n", i);
		}
		else {
			sprintf(str, "%d", i);
			mpz_init_set_str(n, str, 10);
			printf("%d: %c\n", i, Miller_Rabin(n, i));
		}	
		str[0] = '\0';
	}
	//SnM(neuf, ss, t);

	//mpz_out_str(stdout, 10, snm);

	mpz_clear(n);
	mpz_clear(t);
	mpz_clear(neuf);
	mpz_clear(ss);
	mpz_clear(snm);
	mpz_clear(zero);
	mpz_clear(un);
	mpz_clear(deux);

	return 0;
}