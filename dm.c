#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

char Miller_Rabin(mpz_t n, int k) {
	mpz_t r, t, y, a, a1, deux, un, zero, tmp, minus, mun;

	mpz_init(r);
	mpz_init(t);
	mpz_init(y);
	mpz_init(a);
	mpz_init(a1);
	mpz_init(tmp);
	mpz_init(minus);
	mpz_init(mun);
	mpz_init_set_str(deux, "2", 10);
	mpz_init_set_str(un, "1", 10);
	mpz_init_set_str(zero, "0", 10);
	mpz_set(minus, n);
	mpz_sub(minus, minus, un);
	mpz_init_set_str(mun, "-1", 10);

	mpz_set(t, n);
	mpz_sub(t, t, un);
	mpz_mod(r, t, deux);
	
	int s = 0;
	char str[100];

	srand(time(NULL));

	while(mpz_cmp(zero, r) == 0) {
		s++;
		mpz_cdiv_q(t, t, deux);
		mpz_mod(r, t, deux);
	}

	int i = 1;

	while( i <= k ) {
here:
		str[0] = '\0';
		sprintf(str, "%d", (int)(rand()));
		mpz_init_set_str(a, str, 10);
		mpz_mod(a, a, minus);
		mpz_add(a, a, un);


		mpz_mod(a, a, minus);
		mpz_add(a, a, un);

		mpz_set(a1, a);
	 	while(mpz_cmp(un, t) < 0) {
	 		mpz_mul(a, a, a1);
	 		mpz_sub(t, t, un);
	 	}

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
	mpz_clear(deux);
	mpz_clear(un);
	mpz_clear(zero);
	mpz_clear(minus);
	mpz_clear(mun);
	mpz_clear(tmp);

	return 'p';
}


int main() {
	mpz_t n;
	char str[4];

	str[0] = '\0';

	printf("MilLer-RaBin\n\n");

	for(int i = 2 ; i < 100 ; i++) {
		sprintf(str, "%d", i);
		mpz_init_set_str(n, str, 10);

		if(i%2 == 0) {
			printf("%d: c\n", i);
		}
		else {
			printf("%d: %c\n", i, Miller_Rabin(n, i));
		}	
		str[0] = '\0';
	}	
	mpz_clear(n);
	return 0;
}