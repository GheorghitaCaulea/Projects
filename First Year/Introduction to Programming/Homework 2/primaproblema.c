#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1000
char *strdel(char *sd, long poz, long n){
        long i, j;
        for(j = 0; j < n; j ++){
                i = 0;
                while(*(sd + poz + i + 1) != '\0'){
                        *(sd + poz + i) = *(sd + poz + i + 1);
                        i ++;
                }
                *(sd + poz + i) ='\0';
        }
        return sd;
}
//functia strdel sterge n caractere din sirul sd, incepand de pe pozitia poz, la dreapta
int str_length(char *s){
        long nr = 0, i = 0;
        while(*(s + i) != '\0'){
                nr = nr + 1;
                i ++;
        }
        return nr;
}
//functia str_length calculeaza lungimea unui sir de caractele, asemanator functiei strlen
char * strins(char *s1, long pos, char *s2){
        long a, b, i, j;
        a = str_length(s1);
        b = str_length(s2);
        for(i = 0; i < a; i ++){
                for(j = b - 1 ; j >= pos; j --){
                        *(s2 + j + i + 1) = *(s2 + i + j);
                }
        }
        for(i = 0; i < a; i++){
                *(s2 + pos + i) = *(s1 + i);
        }
        return s2;
}
//functia strins insereaza sirul s1 in sirul s2, pe pozitia pos
long f1(char *f, char *c){
        long i = 0, j, ap = 0;
        char separator[]="\"\n',?! ";
        while(f[i] != '\0'){
                if(((i == 0) && (strchr(separator, f[i]) == NULL)) || ((i > 0) && (strchr(separator,f[i -1]) != NULL) && (strchr(separator, f[i]) == NULL))){
                        if(f[i] == c[0]){
                                j = 0;
                                while((f[j + i] != '\0') && (c[j] != '\0') && (f[j + i] == c[j])) {
                                        j ++;
                                }
                        
                                if((c[j] == '\0') && ((f[i + j] == '\0') || (strchr(separator, f[i + j]) != NULL))){
                                        ap ++;
                                        i = i + j - 1;
                                }
			}
                }
                i ++;
        }
        return ap;
}
//functia f1 verifica daca o secventa din fraza delimitata de separatori este identica cu un anume cuvant dat
char *f2(char *s3, char *c1, char *c2){
        long l = 0, k;
        char sepa[]="\"\n', ?!";
        while(s3[l] != '\0'){
                if(((l == 0) && (strchr(sepa, s3[l]) == NULL)) || ((l > 0) && (strchr(sepa, s3[l -1]) != NULL) && (strchr(sepa, s3[l]) == NULL))) {
                        if(s3[l] == c1[0]){
                                k = 0;
                                while((s3[l + k] != '\0') && (c1[k] != '\0') && (s3[l + k] == c1[k])){
                                        k ++;
                                }
                                if((c1[k] =='\0') && ((s3[l + k] == '\0') || (strchr(sepa, s3[l + k]) != NULL))){
                                        strins(c2, l, s3);
                                        strdel(s3, l + str_length(c2), str_length(c1));
                                        l = l + str_length(c2) - 1;
                                        }
                        }
                }
                l ++;
        }
        return s3;
}
//functia f2, cauta in sirul s3 cuvantul c1, daca acesta se gaseste, fiecare aparitie a sa fiind inlocuita de cuvantul c2
char *f3(char *s5, long y){
        char sep[] ="\"\n,'? !";
        char ch;
        char aux;
        long k, i, e, j = 0, l;
        while(*(s5 + j) !='\0'){
                ch = *(s5 + j);
                if(strchr(sep, ch) == NULL){
                        i = 0;
                        ch = *(s5 + i + j);
                        while(strchr(sep, ch) == NULL){
                                i ++;
                                ch = *(s5 + j + i);
                        }
                        if( i > 1){
                                k = y % i;
                                for(e = 1; e <= k; e ++){
                                        aux = *(s5 + j + i - 1);
                                        for(l = j + i -2 ; l >= j ; l --){
                                                *(s5 + l + 1) = *(s5 + l);
                                        }
                                        *(s5 + j) = aux;
                                }
                                j = j + i - 1;
                        }

                }
                j ++;
        }
        return s5;
}
//functia f3 identifica secvente pe care le asociaza cu un cuvant, dupa care se executa rotirea secventei la dreapta de k % numarul de litere al cuvantului, pentru optimizare
int main(void){
	char **fr, *aj1, *aj2, *aj3;
	long lf1, lfr, laj2, laj3, n, m, x, z, num = 0, i, h;
	scanf("%ld", &n);
	getchar();
	fr = (char**)calloc(n, sizeof(char*));
	aj1 = (char*)calloc(N, sizeof(char));
	aj2 = (char*)calloc(N, sizeof(char));
	aj3 = (char*)calloc(N, sizeof(char));
	for(i = 0; i < n; i ++){
		fr[i] = (char*)calloc(12 * N, sizeof(char));
	}
	for(i = 0; i < n; i ++){
   		fgets(fr[i], 12 * N, stdin);	
	}
//se aloca memorie pentru argumentele folosite la operatia 1 si 2, si pentru intreg tabloul de siruri
	scanf("%ld", &m);
	getchar();
	for(i = 0; i < m; i ++){
		scanf("%ld", &x);
		getchar();
		if(x == 1){
			scanf("%s", aj1);
			for(h = 0; h < n; h ++){
				num = num + f1(fr[h], aj1);
			}
			printf("%ld\n", num);
			num = 0;
		}
		if(x == 2){
			scanf("%s %s", aj2, aj3);
				for(h = 0; h < n; h++){
					laj2 = str_length(aj2);
					laj3 = str_length(aj3);
					if(laj3 > laj2){
						lfr = str_length(fr[h]);
						lf1 = f1(fr[h], aj2);	
						if(lfr + (lf1 * (laj3 - laj2)) > 12000){
							fr[h] = realloc(fr[h], (lfr + (lf1 * (laj3 -laj2))) * sizeof(char));							}
					}
				}
//in cazul in care in urma inlocuirii secventei se risca depasirea valorii de 12000, vom realoca memorie
			for(h = 0; h < n; h ++){
				f2(fr[h], aj2, aj3);
				printf("%s", fr[h]);
			}
		}
		if(x == 3){
			scanf("%ld", &z);
			getchar();
			for(h = 0; h < n; h ++){
				f3(fr[h], z);	
				printf("%s", fr[h]);
			}
		}
	}
	free(aj1);
	free(aj2);
	free(aj3);
	return 0;
}
			


