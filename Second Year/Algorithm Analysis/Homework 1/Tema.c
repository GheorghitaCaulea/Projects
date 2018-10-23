#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
//structura TS este folosita pentru a stoca toate starile
typedef struct{
  char* state;          
}TS;
//structura TSF este folosita pentru a stoca starile finale
typedef struct{
	char* final_state;
}TSF;
//structura TT este folosita pentru a stoca tranzitiile
typedef struct{
	char *current_state, *next_state;
 	char direction, read_symbol, write_symbol;
}TT;
int main(){
//se initializeaza variabilele
	char *banda, *initial;
	int nr_states, nr_fi_states, i, nr_tr, index = 1, indicator = 0;
//se aloca si se citeste banda din fisier
	banda = (char*)calloc(2000, sizeof(char));
	FILE *f = fopen("tape.in", "rt");
	fscanf(f, "%s ", banda);
	fclose(f);
//se deschide fisierul cu codificarea masinii si se citesc datele din el(se aloca memorie unde este cazul)
	FILE *g = fopen("tm.in", "rt");
	fscanf(g, "%d ", &nr_states);
	TS *states;
	states = (TS*)calloc(nr_states, sizeof(TS));	
	for(i = 0; i < nr_states; i++){
		states[i].state = (char*)calloc(10, sizeof(char));
		fscanf(g, "%s ", states[i].state); 	
	}	
	TSF *fi_states;
	fscanf(g, "%d ", &nr_fi_states);
	fi_states = (TSF*)calloc(nr_fi_states, sizeof(TSF));	
	for(i = 0; i < nr_fi_states; i++){
		fi_states[i].final_state = (char*)calloc(10, sizeof(char));
		fscanf(g, "%s", fi_states[i].final_state);
	}
//se initializeaza starea initiala
	initial = (char*)calloc(10, sizeof(char));
	fscanf(g, "%s ", initial);
	fscanf(g, "%d ", &nr_tr);
	TT *trans;
	trans = (TT*)calloc(nr_tr, sizeof(TT));
	for(i = 0 ; i < nr_tr; i ++){
		trans[i].current_state = (char*)calloc(10, sizeof(char));
		trans[i].next_state = (char*)calloc(10, sizeof(char));
		fscanf(g, "%s ", trans[i].current_state);
		fscanf(g, "%c ", &(trans[i].read_symbol));
		fscanf(g, "%s ", trans[i].next_state);
		fscanf(g, "%c ", &(trans[i].write_symbol));
		fscanf(g, "%c ", &(trans[i].direction));
	}
	FILE *h = fopen("tape.out", "wt");
	while(1){
//se verifica prin comparatie cu starea initiala daca s-a a ajuns intr-o stare finala
		for(i = 0; i < nr_fi_states; i ++){
			if(strcmp(initial, fi_states[i].final_state) == 0){
//in cazul in care s-a ajuns intr-o stare finala se scrie banda in fisier si se elibereaza memoria
				fprintf(h, "%s", banda);
				fclose(g);
				fclose(h);
				for(i = 0; i < nr_states; i++){
					free(states[i].state);
				}
				free(states);				
				for(i = 0; i < nr_fi_states; i++){
					free(fi_states[i].final_state);
				}
				free(fi_states);				
				for(i = 0 ; i < nr_tr; i ++){
					free(trans[i].current_state);
					free(trans[i].next_state);
				}
				free(trans);
				free(banda);
				free(initial);
				return 0;
			}
		}
//se parcurge vectorul de tranzitii, se misca si se scrie pe banda dupa cum este daca tranzitia respectiva
//se modifica starea initiala
		for(i = 0; i < nr_tr; i ++){
			if(strcmp(initial,trans[i].current_state) == 0 && banda[index] == trans[i].read_symbol){
				banda[index] = trans[i].write_symbol;
				strcpy(initial, trans[i].next_state);
				indicator = 1;
				if(banda[index + 1] == '\0')
						strcat(banda, "#");	
				if(trans[i].direction == 'R')		
					index ++;
				else{
					if(trans[i].direction == 'L')
						index --;
				}			
			if(indicator == 1)
				break;
			}
		}
//incazul in care nu se gaseste tranzitie se afiseaza un mesaj corespunzator
		if(indicator == 0){
			fprintf(h, "Se agata!");
			break;
		}
		indicator = 0;
	}
//se elibereaza memoria si se inchid fisierele
	fclose(g);
	fclose(h);
	for(i = 0; i < nr_states; i++){
		free(states[i].state);
	}
	free(states);
	for(i = 0; i < nr_fi_states; i++){
		free(fi_states[i].final_state);
	}
	free(fi_states);
	for(i = 0 ; i < nr_tr; i ++){
		free(trans[i].current_state);
		free(trans[i].next_state);
	}
	free(trans);
	free(banda);
	free(initial);
	return 0;
}	
		
