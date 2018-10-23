#include<stdio.h>
#include "bmp_header.h"
#include<string.h>
#include<stdlib.h>
int main(void){
        char num[30], num1[30];
        int i, j, p, a[100][100], m0[5][5], m1[5][5], m2[5][5], u = 0, v[100];
	int m3[5][5], m4[5][5], m5[5][5], m6[5][5], m7[5][5], m8[5][5], m9[5][5];
	int nr, sw, sw0, sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, q, w, z, t;
        unsigned char b, g, r;
        struct bmp_fileheader x;
        struct bmp_infoheader y;
//se declara variabilele si cele doua structuri
        FILE *f = fopen("input.txt", "rt");
        fscanf(f, "%s", num);
        FILE *gh = fopen(num, "rb");
        strncpy(num1, num, strlen(num) - 4);
	strcat(num1, "_task2.txt");
//se deschide fisierul pentru citirea datelor de imput, se creeaza numele fisierului de output 
        fread(&x, sizeof(struct bmp_fileheader), 1, gh);
        fread(&y, sizeof(struct bmp_infoheader), 1, gh);
        fseek(gh, x.imageDataOffset, 0);
        FILE *h = fopen(num1, "wt");
	p = (y.width * 3) % 4;
//se citesc cele doua structuri din fisier, se sare in pozitia de inceput a imaginii, se deschide fisierul de output pentru scriere in el, dupa care se scriu cele doua structuri; se calculeaza paddingul
	for(i = 0; i < 100; i ++){
		for(j = 0; j < 100; j++){
			a[i][j] = 0;
		}
	}
//se initializeaza o matrice ajutatoare de dimensiunea maxima a imaginii, cu 0; in continuare se vor construi matrici de dimensiunea 5x5 pentru fiecare cifra {0,1,2,3,4,5,6,7,8,9}, schitate cu 1 si 0;
	for(i = 0; i < 5; i ++){
		for(j = 0; j < 5; j ++){
			m0[i][j] = 0;
		}
	}
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m1[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m2[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m3[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m4[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m5[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m6[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m7[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m8[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        m9[i][j] = 0;
                }
        }
	for(i = 0; i < 5; i ++){
		for(j = 0; j < 5; j ++){
			if(i == 0 || i == 4 || j == 0 || j == 4){
				m0[i][j] = 1;
			}
		}
	}
	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        if(j == 4){
				m1[i][j] = 1;
			}
                }
        }
 	for(i = 0; i < 5; i ++){
                for(j = 0; j < 5; j ++){
                        if(i == 0 || i == 2 || i == 4){
				m2[i][j] = 1;
				m3[i][j] = 1;
				m5[i][j] = 1;
				m6[i][j] = 1;
				m8[i][j] = 1;
				m9[i][j] = 1;
			}
		}
	}
	m2[1][4] = 1;
	m2[3][0] = 1;
	m3[1][4] = 1;
	m3[3][4] = 1;
	m5[1][0] = 1;
	m5[3][4] = 1;
	m6[1][0] = 1;
	m6[3][0] = 1;
	m6[3][4] = 1;
	m8[1][0] = 1;
	m8[1][4] = 1;
	m8[3][0] = 1;
	m8[3][4] = 1;
	m9[1][0] = 1;
	m9[1][4] = 1;
	m9[3][4] = 1;
	for(i = 0; i < 5; i ++){
		for(j = 0; j < 5; j ++){
			if(i == 2 || j == 4){
				m4[i][j] = 1;
			}
			if(i == 0 || j == 4){
				m7[i][j] = 1;
			}
		}
	}
	m4[0][0] = 1;
	m4[1][0] = 1;
	m4[0][4] = 1;
	m4[1][4] = 1;
//au fost construite matricele pentru cele 10 cifre
	for(i = y.height - 1; i >= 0; i--){
                for(j = 0; j < y.width ; j++){
                        fread(&b, 1, 1, gh);
                        fread(&g, 1, 1, gh);
                        fread(&r, 1, 1, gh);
                        if(b != 255 || g != 255 || r != 255){
                                a[i][j] = 1;
                        }
                }
                if(p != 0){
                        fseek(gh, (4 - p), 1);
                }
	}
//se parcurge imaginea iar acolo unde am pixel de alta culoare decat alb, voi nota cu 1, in caz contrar va ramane 0; se ignora paddingul
	for(j = y.width - 1; j >= 4; j --){
		for(i = 0; i < y.height - 4; i ++){
			sw0 = 0, sw1 = 0; sw2 = 0; sw3 = 0; sw4 = 0;
			sw5 = 0; sw6 = 0; sw7 = 0; sw8 = 0; sw9 = 0;
			t = 0;	sw = 0; nr = 0;
//se parcurge matricea ajutatoare, pe coloane si se initializeaza ajutoare pentru identificarea matricii numar, eventual descoperite 
			for(z = i; z < i + 5; z ++){
				q = 4;
				for(w = j; w > j - 5; w --){
//se parcurge matricea numar si se verifica daca vreo unul din pixeli difera fata de cei din matricea ajutatoare, in acest caz se incrementeaza ajutoarele
					if(a[z][w] != m0[t][q]){
						sw0 = 1; 
					}
					if((a[z][w] != m1[t][q]) || (a[i][j + 1] != 0)){
                                                sw1 = 1;
                                        }
					if(a[z][w] != m2[t][q]){
                                                sw2 = 1;
                                        }
					if(a[z][w] != m3[t][q]){
                                                sw3 = 1;
                                        }
					if(a[z][w] != m4[t][q]){
                                                sw4 = 1;
                                        }
					if(a[z][w] != m5[t][q]){
                                                sw5 = 1;
                                        }
					if(a[z][w] != m6[t][q]){
                                                sw6 = 1;
                                        }	
					if(a[z][w] != m7[t][q]){
                                                sw7 = 1;
                                        }
					if(a[z][w] != m8[t][q]){
                                                sw8 = 1;
                                        }
					if(a[z][w] != m9[t][q]){
                                                sw9 = 1;
                                        }
					q --;
				}
				t ++;
			}
			sw = 0; 
//se initialiseaza un ajutor general
			if(sw0 == 0){
				nr = 0;
				sw = 1;
			}
			if(sw1 == 0){
	                        nr = 1;
				sw = 1;
	                }
			if(sw2 == 0){
	                        nr = 2;
				sw = 1;
	                }
			if(sw3 == 0){
       		               	nr = 3;
				sw = 1;
      	          	}
			if(sw4 == 0){
                        	nr = 4;
				sw = 1;
                	}
			if(sw5 == 0){
                        	nr = 5;
				sw = 1;
                	}
			if(sw6 == 0){
                        	nr = 6;
				sw = 1;
                	}
			if(sw7 == 0){
                        	nr = 7;
				sw = 1;
                	}
			if(sw8 == 0){
                     		nr = 8;
				sw = 1;
                	}
  			if(sw9 == 0){
                        	nr = 9;
				sw = 1;
			}
//in cazul in care ajutorul general devine 1, adica s-a gasit o secventa din matricea ajutatoare identica cu o matrice numar, numarul corespunzator matricii este introdus intr-un vector
			if(sw == 1){
				v[u] = nr;
				u ++;
			}
		}
	}		
	for(i = u - 1; i >= 0 ; i --){
		fprintf(h, "%d", v[i]);
	}
	fclose(f);
	fclose(gh);
	fclose(h);
//numerele gasite se scriu in ordine inversa in fiserul text output si se inchid fiserele
	return 0;
}
    
