#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
long nr_cuv(char *fraza){
        char *sep = "\"\n ?,!'";
        long nr = 0, i = 0;
        while(fraza[i] != '\0'){
                if(((i == 0) && (strchr(sep, fraza[i]) == NULL)) || ((i > 0) && (strchr(sep, fraza[i - 1]) != NULL) && (strchr(sep, fraza[i]) == NULL))){
                        nr ++;
                }
                i ++;
        }
        return nr;
}
//functia nr_cuv numara cate cuvinte sunt intr-o fraza
long dist(char *c5, char*c6){
	long d = 0, i = 0;
	while((c5[i] != '\0') && (c6[i] != '\0')){
		d = d + abs(c5[i] - c6[i]);
		i ++;
	}
	if(c5[i] != '\0'){
		while(c5[i] != '\0'){
			d = d + (int)c5[i]; 
			i ++;
		}
	}
	else{
		if(c6[i] != '\0'){
               		while(c6[i] != '\0'){
                        	d = d + (int)c6[i];
                        	i ++;
                	}
		}
	}	
	return d;
}
//functia dist calculeaza distanta dintre doua cuvinte; in cazul in care au lungimi diferite, diferenta se face cu '\0'
int main(void){
	char **tx1, **tx2, **v1, **v2, *p, *caux;
	long h, f, g, n, m, aux, sum = 0, *vi1, *vi2, i, j, num1 = 0, num2 = 0;
	int sw;
	scanf("%ld", &n);
	getchar();
	caux = (char*)calloc(1000, sizeof(char));
	p = (char*)calloc(1000, sizeof(char));
	tx1 = (char**)calloc(n, sizeof(char*));
	for(i = 0; i < n; i++){
		tx1[i] = (char*)calloc(12000, sizeof(char));
	}
	for(i = 0; i < n; i++){
		fgets(tx1[i], 12000, stdin);
		num1 = num1 + nr_cuv(tx1[i]);
	}
	scanf("%ld", &m);
	getchar();
	tx2 = (char**)calloc(m, sizeof(char*));
	for(i = 0; i < m; i ++){
		tx2[i] = (char*)calloc(12000, sizeof(char));
	}
	for(i = 0; i < m; i ++){
		fgets(tx2[i], 12000, stdin);
		num2 = num2 + nr_cuv(tx2[i]);
	}
	vi1 = (long*)calloc(num1, sizeof(long));
        vi2 = (long*)calloc(num2, sizeof(long));
	v1 = (char**)calloc(num1, sizeof(char*));
	v2 = (char**)calloc(num2, sizeof(char*));
	for(i = 0; i < num1; i ++){
		v1[i] = (char*)calloc(1000, sizeof(char));
	}
	for(i = 0; i < num2; i ++){
		v2[i] = (char*)calloc(1000, sizeof(char));
	}
//aloc memorie pentro tot ce voi folosi pe parcursul programului, obtinand un numar total de cuvinte
	g = 0;
	for(i = 0; i < n; i ++){
		p = strtok(tx1[i], "\n\" ,'?!");
		while(p != NULL){
			sw = 0;
			for(h = 0; h < g; h++){
				if(strcmp(v1[h], p) == 0){
					vi1[h] = vi1[h] + 1;
					sw = 1;
				}
			}
			if(sw == 0){
				strcpy(v1[g], p);
				vi1[g] = 1;
				g ++;
			}
			p = strtok(NULL, "\"\n ,'?!");
		}
	}
//scot cuvintele din fraza, daca nu au fost introduse le adaug in lista de cuvinte, in caz contrar maresc numarul aparitiilor
	f = 0;
	for(i = 0; i < m; i++){
		p = strtok(tx2[i], "\n\" ,'?!");
		while(p != NULL){
			sw = 0;
			for(h = 0; h < f; h ++){
				if(strcmp(v2[h], p) == 0){
					vi2[h] = vi2[h] + 1;
					sw = 1;
				}
			}
			if(sw == 0){
				strcpy(v2[f], p);
				vi2[h] = 1;
				f ++;	
			}
			p = strtok(NULL, "\n\" ,'?!");
		}
	}
//identic cu formarea primei liste de cuvinte; valabila pentru cea de-a doua lista
	do{
		sw = 0;
		for(i = 0; i < g - 1; i++){
			if(vi1[i] < vi1[i + 1]){
				aux = vi1[i];
				vi1[i] = vi1[i + 1];
				vi1[i + 1] = aux;	
				strcpy(caux, v1[i]);
                                strcpy(v1[i], v1[i + 1]);
                                strcpy(v1[i + 1], caux);		
				sw = 1;
			}
			else{
				if((vi1[i] == vi1[i + 1]) && (strcmp(v1[i], v1[i + 1]) > 0)){
					strcpy(caux, v1[i]);
					strcpy(v1[i], v1[i + 1]);
					strcpy(v1[i + 1], caux);
					sw = 1;
				}
			}	
		}
	}while( sw == 1);
//realizez o sortare a cuvintelor folosind bubble sort
	do{
                sw = 0;
                for(i = 0; i < f - 1; i++){
        		 if(vi2[i] < vi2[i + 1]){
                               	aux = vi2[i];
                                vi2[i] = vi2[i + 1];
                            	vi2[i + 1] = aux;
                                strcpy(caux, v2[i]);
                                strcpy(v2[i], v2[i + 1]);
                                strcpy(v2[i + 1], caux);      
				sw = 1;
                      	}
                         else{
                              if((vi2[i] == vi2[i + 1]) && (strcmp(v2[i], v2[i + 1]) > 0)){
                                strcpy(caux, v2[i]);
                                strcpy(v2[i], v2[i + 1]);
                                strcpy(v2[i + 1], caux);
                                sw = 1;
                                }
                         }
                }
        }while( sw == 1);
//realizez o sortarea a celei de-a doua lista, folosind tot bubble sort
	if(g > f){
		j = f;
	}
	else{
		j = g;
	}
	sum = 0;
	for(i = 0; i < j; i ++){	
		sum = sum + (vi1[i] + vi2[i]) * dist(v1[i], v2[i]);
	}	
	j = abs(g - f);
	j = j * 100 + sum;
	printf("%ld", j);
	for(i = 0; i < n; i++){
		free(tx1[i]);
	}
	for(i = 0; i < m; i ++){
		free(tx2[i]);
	}
//parcurg listele pana la minimul dimensiunii lor, calculand distanta dupa formula
	free(tx1);
	free(tx2);
	free(caux);
	free(p);
	for(i = 0; i < num1; i++){
		free(v1[i]);
	}
	for(i = 0; i < num2; i++){
		free(v2[i]);
	}
	free(v1);
	free(v2);
	free(vi1);
	free(vi2);
//eliberez memoria alocata
	return 0;
}
