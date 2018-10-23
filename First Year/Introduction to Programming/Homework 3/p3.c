#include<stdio.h>
#include "bmp_header.h"
#include<string.h>
#include<stdlib.h>
int main(void){
        char num[30], num1[30];
        int i, j, p, a[100][100], m0[5][5], u = 0, v[100], vb[100][100],vg[100][100], vr[100][100];;
	int m1[5][5], m2[5][5], m3[5][5], m4[5][5], m5[5][5], m6[5][5], m7[5][5], m8[5][5], m9[5][5];
	int nr, sw, sw0, sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9, q, w, z, t;
	int cif, c1, c2, c3, v1[100], xi, sww, op = 0, vcb[100], vcg[100], vcr[100], sk = 0;        
	unsigned char b, g, r;
        struct bmp_fileheader x;
        struct bmp_infoheader y;
        FILE *f = fopen("input.txt", "rt");
//se declara variabilele si cele doua structuri
        fscanf(f, "%s", num);
        fscanf(f, "%d%d%d", &c1, &c2, &c3);
	while(fscanf(f, "%d", &cif)){
		v[u] = cif;
		u ++;
	}	
	FILE *gh = fopen(num, "rb");
      	strncpy(num1, num, strlen(num) - 4);
	strcat(num1, "_task3.bmp");
//se deschide fisierul pentru citirea datelor de imput, se creeaza numele fisierului de output
        fread(&x, sizeof(struct bmp_fileheader), 1, gh);
        fread(&y, sizeof(struct bmp_infoheader), 1, gh);
        fseek(gh, x.imageDataOffset, 0);
        FILE *h = fopen(num1, "wb");
	fwrite(&x, sizeof(struct bmp_fileheader), 1, h);
	fwrite(&y, sizeof(struct bmp_infoheader), 1, h);
	p = (y.width * 3) % 4;
//se citesc cele doua structuri din fisier, se sare in pozitia de inceput a imaginii, se deschide fisierul de output pentru scriere in el, dupa care se scriu cele doua structuri; se calculeaza paddingul
	for(i = 0; i < 100; i ++){
		for(j = 0; j < 100; j++){
			a[i][j] = 0;
			vb[i][j] = 255;
			vg[i][j] = 255;
			vr[i][j] = 255;
			vcb[i] = 0;
			vcg[i] = 0;
			vcr[i] = 0;
		}
	}
//se initializeaza o matrice ajutatoare de dimensiunea maxima a imaginii, cu 0 si o matrice ajutatoare de pixeli, doar cu pixeli albi si vectori care se vor folosi tot pentru memorarea culorilor; in continuare se vor construi matrici de dimensiunea 5x5 pentru fiecare cifra {0,1,2,3,4,5,6,7,8,9}, schitate cu 1 si 0;
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
		 
			vb[i][j] = b; 
			vg[i][j] = g;
			vr[i][j] = r; 
		}                		
		if(p != 0){
                        fseek(gh, (4 - p), 1);
                }
	}
//se parcurge imaginea iar acolo unde am pixel de alta culoare decat alb, se noteaza cu 1 in matricea ajutatoare iar in matricea de pixeli se noteaza culoarea pixelului respectiv; se ignora paddingul
	for(j = 0; j <y.width - 4; j ++){
		for(i = 0; i < y.height - 4; i ++){
			sw0 = 0, sw1 = 0; sw2 = 0; sw3 = 0; sw4 = 0;
			sw5 = 0; sw6 = 0; sw7 = 0; sw8 = 0; sw9 = 0;
			t = 0;	sw = 0; nr = 0;
//se parcurge matricea ajutatoare, pe coloane si se initializeaza ajutoare pentru identificarea matricii numar, eventual descoperite 
			for(z = i; z < i + 5; z ++){
				q = 0;
				for(w = j; w < j + 5; w ++){
//se parcurge matricea numar si se verifica daca vreo unul din pixeli difera fata de cei din matricea ajutatoare, in acest caz se incrementeaza ajutoarele
					if(a[z][w] != m0[t][q]){
						sw0 = 1; 
					}
					if((a[z][w] != m1[t][q]) || (a[i][j + 5] != 0)){
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
					q ++;
				}
				t ++;
			}
//se initialiseaza un ajutor general
			sw = 0; 
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
			sww = 0;
			if(sw == 1){								
				for(xi = 0; xi < u; xi ++){
					if(v[xi] == nr){
						sww = 1;

//daca se gaseste un numar, se verifica daca acesta se afla in vectorul de numere ce trebuie eliminate; in caz contrar, se introduce intr-un vector de numere ce trebuie pastrate si se memoreaza indicii de culoare	
					}
				}
				if(sww == 0){
					v1[op] = nr;
					vcb[op] = vb[i][j + 4];
					vcg[op] = vg[i][j + 4];
					vcr[op] = vr[i][j + 4];
					op ++;
				}
			}
		}			
	} 		
	int cv = 0, fi = 0; 	
	for(j = 0; j <y.width - 4; j ++){
		for(i = 0; i < y.height - 4; i ++){
			sw0 = 0, sw1 = 0; sw2 = 0; sw3 = 0; sw4 = 0;
			sw5 = 0; sw6 = 0; sw7 = 0; sw8 = 0; sw9 = 0;
			t = 0;	sw = 0; nr = 0;
//se parcurge din nou matricea ajutatoare
			for(z = i; z < i + 5; z ++){
				q = 0;
				for(w = j; w < j + 5; w ++){
					if(a[z][w] != m0[t][q]){
						sw0 = 1; 
					}
					if((a[z][w] != m1[t][q]) || (a[i][j + 5] != 0)){
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
					q ++;
				}
				t ++;
			}
			sw = 0; 
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
			sww = 0; 			
			if(sw == 1){								
//daca se gaseste un numar si acesta nu apare in vectorul de numere ce trebuiesc pastrate, se inlocuieste toata aria acestuia cu aria primului numar din vector; in caz contrar se merge mai departe in matricea ajutatoare si se trece la urmatorul numar din vector				
				for(xi = 0; xi < op; xi ++){
					if(v1[xi] == nr){						
						sww = 1;
					}
				}					
				if(cv < op){
					t = 0;						
					for(z = i; z < i + 5; z ++){
						q = 0;
						for(w = j; w < j + 5; w ++){
							if(v1[cv] == 0){
								if(m0[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}		
							}		
							if(v1[cv] == 1){
								if(m1[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 2){
								if(m2[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 3){
								if(m3[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 4){
								if(m4[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 5){
								if(m5[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 6){
								if(m6[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 7){
								if(m7[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							if(v1[cv] == 8){
								if(m8[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								};
							}
							if(v1[cv] == 9){
								if(m9[t][q] != 0){
									a[z][w] = 1 + fi;
								}
								else{
									a[z][w] = 0;
								}
							}
							q ++;
						}
						t++;
					}											
				
				} 
				cv ++; fi ++;
//fiecare numar va fi schitat cu un alt numar pentru a fi mai usor de stabilit pixelul culoare corespunzator; in cazul in care vectorul de numere ajunge la final, restul matricii ajutatoare devine 0;
				if(cv > op){
					for(z = i; z < i + 5; z ++){
						for(w = j; w < j + 5; w ++){	
							a[z][w] = 0;
						}
					}
				}
			}
		} 			
	}
	int pix = 255;
	p = (y.width * 3) % 4;	
	for(i = y.height - 1; i >= 0; i--){
		for(j = 0; j < y.width ; j++){
			if(a[i][j] == 0){
				fwrite(&pix, 1, 1, h);
				fwrite(&pix, 1, 1, h);
				fwrite(&pix, 1, 1, h);
			}
			else{
				fwrite(&vcb[a[i][j] - 1], 1, 1, h);
				fwrite(&vcg[a[i][j] - 1], 1, 1, h);
				fwrite(&vcr[a[i][j] - 1], 1, 1, h);
			}
		}
		if(p != 0){
			fseek(gh, (4 - p), 1);
			fwrite(&sk, 1, (4 - p), h);
		}		
	}
//se parcurge matricea ajutatoare nou formata; daca pe pozitia respectiva se afla 0, se scrie alb in output, altfel, se scrie pixelul culoare corespunzator
	fclose(f);
	fclose(h);
	fclose(gh);	
	return 0;
}
