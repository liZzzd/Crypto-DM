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


void test_de_fermat(mpz_t n , int k){

    mpz_t  a ,m, n1 ;//n1 == n-1
    int i;
  
    mpz_init(a);
    mpz_t max , tmp; 
   
    mpz_init(max);
    mpz_init(tmp); //tmp est l'entier aléatoire dans a^n-1 mod n qui est compris en 1 et n-1
   
    mpz_init_set(n1, n); //  n-1
	mpz_sub_ui(n1, n1, 1);

    mpz_init_set(max, n); //On initialise la max à n-2 pour pouvoir générer un nombre aléatoire 1 < a < n-1
	mpz_sub_ui(max,max,2);

    gmp_randstate_t state; //pour générer l entier aleatoire 
	gmp_randinit_default(state);
    
   /**
	* vérification que l entier entrée 
	* si il est pair donc forcément composé
	**/

   if(mpz_divisible_ui_p(n,2)){
		printf(" Composé ! c'est un nombre pair\n");
		return ;
	}

	/**
	 * "1" n'est pas premier
	 * */

    if(mpz_cmp_ui(n,1) == 0){
		printf(" '1' n'est pas  premier\n");
		return ;
	}

  /**
   * Boucle for de 1 a k 
   * Choisir aleatoirement "a" tel que 1 < a < n − 1 ;
		si a^n−1 ≡ 1 mod n alors "il est composé" , sinon "il est premier "
	*/

    for(i = 1 ; i < k; i++){
        //Generation de l'entier aleatoirement entre 0 < a < n-2
		mpz_urandomm(a, state, max);
        //meme chose mais  entre 1 < a < n-1
		mpz_add_ui(a, a, 1); 
		  
		SnM(a, n, n1); // la fonction qui effectue a^n-1 mod n 
		mpz_set(tmp , snm);

		if(mpz_cmp_ui(tmp, 1) != 0){ // verifie si le resultat est different de 1 mod n
			printf("Composé !\n");
			mpz_clears(max, tmp, a, n1, state, NULL);
			
			return;
		}else {
          printf("premier !\n");	
    	  mpz_clears(max, tmp, a, n1, state, NULL);
	      return ;
		}
	}   
}


char Miller_Rabin(mpz_t n, int k) {
	mpz_t r, t, y, a, tmp, minus, mun;
	gmp_randstate_t state;

	mpz_init(r);
	mpz_init(t);
	mpz_init(y);
	mpz_init(a);
	mpz_init(tmp);
	mpz_init(minus);
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
	 		
	 	mpz_clear(r);
		mpz_clear(t);
		mpz_clear(y);
		mpz_clear(a);
		mpz_clear(minus);
		mpz_clear(mun);
		mpz_clear(tmp);
		gmp_randclear(state);

	  	return 'c';
	}
	 	

there:
	mpz_clear(r);
	mpz_clear(t);
	mpz_clear(y);
	mpz_clear(a);
	mpz_clear(minus);
	mpz_clear(mun);
	mpz_clear(tmp);
	gmp_randclear(state);

	return 'p';
}


int main() {
	mpz_t n, t, neuf, ss;

	mpz_init_set_str(deux, "2", 10);
	mpz_init_set_str(un, "1", 10);
	mpz_init_set_str(zero, "0", 10);
	mpz_init_set_str(t, "7", 10);
	mpz_init_set_str(neuf, "3", 10);
	mpz_init_set_str(ss, "77", 10);
	mpz_init(snm);

	char str[10];
	str[0] = '\0';

	printf("MilLer-RaBin\n\n");

	for(int i = 1153 ; i < 1205 ; i++) {
		if(i%2 == 0) {
			printf("%d: c\n", i);
		}
		else {
			sprintf(str, "%d", i);
			mpz_init_set_str(n, str, 10);
			printf("%d: %c\n%d: ", i, Miller_Rabin(n, i), i);

			test_de_fermat(n, i);
			mpz_clear(n);
		}	
		str[0] = '\0';
	}


	mpz_clear(t);
	mpz_clear(neuf);
	mpz_clear(ss);
	mpz_clear(snm);
	mpz_clear(zero);
	mpz_clear(un);
	mpz_clear(deux);

	return 0;
}