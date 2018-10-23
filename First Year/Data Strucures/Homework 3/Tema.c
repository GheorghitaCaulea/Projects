/*CAULEA Gheorghita 314CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
//se initializeaza structurile ce vor fi folosite
//se folosesc macrodefinitii pentru ajutor
typedef struct nod {
	char cod, caracter;
	struct nod **fii, *parinte;
	int nr_fii;
} TNod, *TArb;
typedef struct cel
{ 
  void* info;           
  struct cel *urm;   
}TCel, *TLG, **ALG; 
typedef struct
{ 
	size_t 	dime; 	
	TLG 	ic; 		
	TLG 	sc; 		
} TCoadaV, *AQV;
#define IC(a) 	(((AQV)(a))->ic)
#define SC(a) 	(((AQV)(a))->sc)
//functia 'AlocCel' contruieste si aloca memorie pentru o structura de tip TLG
TLG AlocCel(void *ae){
	TLG a;
	a = (TLG)calloc(1, sizeof(TCel));
	if(!a)
		return NULL;
	a -> urm = NULL;
	a -> info = malloc(sizeof(TArb));
	if(!a -> info){
		free(a);
		return NULL;
	} 
	memcpy(a -> info, ae, sizeof(TArb));
	return a;
}
//functia 'InitQ' initializeaza o coada cu dimensiune data
void *InitQ(size_t d){
	AQV c;
	c = (AQV)calloc(1, sizeof(TCoadaV));
	if(!c){
		return NULL;
	}
	c -> ic = NULL;
	c -> sc = NULL;
	c -> dime = d;
	return (void*)c;
}
//functia 'IntrQ' introduce un element intr-o coada
int IntrQ(void *a, void *ae){
	TLG aux;
	aux = AlocCel(ae);
	if(IC(a) == NULL){
		IC(a) = aux;
		SC(a) = aux;
	}
	else{
		SC(a) -> urm = aux;		
		SC(a) = aux;
	}
		return 1;
}
//functia 'ExtrQ' extrage un element dintr-o coada
int ExtrQ(void *a, void *ae){
	TLG aux = IC(a);
	if(IC(a) != NULL){
		memcpy(ae, (IC(a)) -> info, sizeof(TArb));
		IC(a) = IC(a) -> urm;
		free(aux -> info);
		free(aux);
		return 1;
	}
	return 0;
}
//functia 'ConstrFr' contruieste un nod pentru arbore, cu 'litera' si 'codificare' date
TArb ConstrFr(char litera, char codificare){
	TArb a;
	a = (TArb)calloc(1, sizeof(TNod));
	if(!a)
		return NULL;
	a -> fii = NULL;
	a -> parinte = NULL;
	a -> nr_fii = 0;
	a -> cod = codificare;
	a -> caracter = litera;
	return a;
}
//functia 'add' adauga o codificare in arbore
int add(char *calea, char litera, TArb a){
	char s;
	int i = 0, j;
//se verica situatiile de adaugare sau nu a unei frunze
	while(calea[i] != '\0' && calea[i + 1] != '\0'){
		s = calea[i];
		if(a -> nr_fii == 0){
			a -> fii = (TArb*)calloc(1, sizeof(TArb));
			if(!a -> fii)
				return 0;
			a -> fii[0] = ConstrFr('\0', s);
			
			a -> nr_fii = 1;
			a -> fii[0] -> parinte = a;
			a = a -> fii[0];
		}
		else{				
			for(j = 0; j < a -> nr_fii; j ++){
				if(a -> fii[j] -> cod == s){
					a = a -> fii[j];
					j =-10;
					break;
				}
			}
			if(j == a -> nr_fii){
				a -> fii = realloc(a -> fii,(a -> nr_fii + 1)*sizeof(TArb));
				a -> nr_fii = a -> nr_fii + 1;
				a -> fii[a -> nr_fii - 1] = ConstrFr('\0', s);
				a -> fii[a -> nr_fii - 1] -> parinte = a;
				a = a -> fii[a -> nr_fii - 1];
			}
		}
		i ++;
	}	
//se verica situatiile de adaugare sau nu a unei frunze, cu ultimul caracter din codificare si 'litera' specificata' 
	if(a -> nr_fii == 0){
		a -> fii = (TArb*)calloc(1, sizeof(TArb));
		if(!a -> fii)
			return 0;
		a -> fii[0] = ConstrFr(litera, calea[i]);
		a -> nr_fii = 1;
		a -> fii[0] -> parinte = a;
		a = a -> fii[0];
	}
	else{				
		for(j = 0; j < a -> nr_fii; j ++){
			if(a -> fii[j] -> cod == calea[i]){
				a = a -> fii[j];
				a -> caracter = litera;
				return 1;
			}
		}
		if(j == a -> nr_fii){
			a -> fii = realloc(a -> fii,(a -> nr_fii + 1)*sizeof(TArb));
			a -> nr_fii = a -> nr_fii + 1;
			a -> fii[a -> nr_fii - 1] = ConstrFr(litera, calea[i]);
			a -> fii[a -> nr_fii - 1] -> parinte = a;
			a = a -> fii[a -> nr_fii - 1];
		}
	}
	return 1;
}
//functia 'InitArb' initializeza un arbore
TArb InitArb(){
	TArb a;
	a = (TArb)calloc(1, sizeof(TNod));
	if(! a)
		return NULL;
	a -> cod = '\0';
	a -> caracter = '\0';
	a -> fii = NULL;
	a -> parinte = NULL;
	a -> nr_fii = 0;
	return a;
}		
//functia 'AfiArb' afiseaza un arbore pe nivele	
void AfiArb(TArb a, FILE *g){
	int i, j, suma_fii = 0, suma_fii2 = 0;
	void *c;
	TArb aux;
//se foloseste o coada pentru o mai buna prelucrare a fiilor
	c = InitQ(sizeof(TArb));
	for(i = 0; i < a -> nr_fii; i ++){
		IntrQ(c, &(a -> fii[i]));
		suma_fii = suma_fii + 1;
	}
	fprintf(g, "(:)\n");
	while(IC(c) != NULL){		
		for(i = 0; i < suma_fii; i ++){
			ExtrQ(c, &aux);
			for(j = 0; j < aux -> nr_fii; j ++){
				IntrQ(c, &(aux -> fii[j]));
				suma_fii2 += 1;
			}
//se afiseaza 'cod' si 'caracter'
			if(aux -> caracter == '\0')
				fprintf(g, "(%c:)", aux -> cod);			
			else		
				fprintf(g, "(%c:%c)", aux -> cod, aux -> caracter);
		}	
		suma_fii = suma_fii2;
		suma_fii2 = 0;		
		fprintf(g, "\n");
	}
	free(c);
}
//functia 'delete' realizeaza stergerea unei codificari din arbore
int delete(TArb a, char litera){
	int i, j, suma_fii = 0, suma_fii2 = 0, h;	
	void *c;
	TArb aux, copie = NULL, aux2;
//cu ajutorul unei cozi se cauta printre fiii fiecarui nod, caracterul de interes
	c = InitQ(sizeof(TArb));
	for(i = 0; i < a -> nr_fii; i ++){
		IntrQ(c, &(a -> fii[i]));
		suma_fii = suma_fii + 1;
	}
	while(IC(c) != NULL){		
		for(i = 0; i < suma_fii; i ++){
			ExtrQ(c, &aux);
			for(j = 0; j < aux -> nr_fii; j ++){
				IntrQ(c, &(aux -> fii[j]));
				suma_fii2 += 1;
			}
//fiind gasit, nodul este memorat
			if(aux -> caracter == litera)
				copie = aux;
		}	
		suma_fii = suma_fii2;
		suma_fii2 = 0;		
	}
	free(c);
//se urca in arbore verificandu-se situatiile in care ne putem afla
	if(copie == NULL){
		return 0;
	}
	if(copie -> nr_fii > 0){
		copie -> caracter = '\0';
		return 1;
	}
	while(copie -> parinte != NULL && copie -> parinte -> nr_fii == 1){
		if(copie -> parinte -> caracter != '\0'){
			free(copie);
			return 1;
		}
		else{
			aux2 = copie;
			copie = copie -> parinte;
			copie -> nr_fii --;
			free(aux2);
		}
	}				
	if(copie -> parinte == NULL){
		return 1;
	}		
	copie = copie -> parinte;
	for(h = 0; h < copie -> nr_fii; h++){
		if((copie -> fii[h] -> nr_fii == 0 && copie -> fii[h] -> caracter == '\0') || copie -> fii[h] -> caracter == litera)
			break;
	}
	if(h == copie -> nr_fii - 1){
		free(copie -> fii[h]);
		copie -> fii = realloc(copie -> fii,(copie -> nr_fii - 1)*sizeof(TArb));
		copie -> nr_fii --;			
		return 1;
	}	
	if(h < copie -> nr_fii - 1){
		for(i = h + 1; i < copie -> nr_fii; i ++){
			copie -> fii[i - 1] = copie -> fii[i];
		}
		copie -> fii = realloc(copie -> fii,(copie -> nr_fii - 1)*sizeof(TArb));
		copie -> nr_fii --;
	}	
	return 1;
} 
//functia 'decodificare' realizeaza cautarea in arbore a unui 'caracter' dupa 'calea' data
char decodificare(char *calea, TArb a){
	int i = 0, j;
	char s, litera;
	while(calea[i] != '\0'){
		s = calea[i];	
		for(j = 0; j < a -> nr_fii; j ++){
			if(a -> fii[j] -> cod == s){
				a = a -> fii[j];
				litera = a -> caracter;
				break;
			}
		}
		i ++;
	}	
	return litera;
}
int main(int argc, char *argv[]){
//se aloca memorie pentru variabilele ce urmeaza a fi folosite si se verifica alocarea
	int nr_coduri, i, nr_com;
	char *litera, *cod, *cha, *com, *sep, o_litera, *fraza;
	TArb a;
	cod = (char*)calloc(20, sizeof(char));
	if(!cod)
		return 0;
	litera = (char*)calloc(2, sizeof(char));
	if(!litera){
		free(cod);
		return 0;
	}	
	com = (char*)calloc(20, sizeof(char));
	if(!litera){
		free(cod);
		free(litera);
		return 0;	
	}
	cha = (char*)calloc(20, sizeof(char));
	if(!litera){
		free(cod);
		free(litera);
		free(com);
		return 0;	
	}
	sep = (char*)calloc(20, sizeof(char));
	if(!litera){
		free(cod);
		free(litera);
		free(com);
		free(cha);
		return 0;	
	}
	fraza = (char*)calloc(10000, sizeof(char));
	if(!fraza){
		free(sep);
		free(cod);
		free(litera);
		free(com);
		free(cha);
	}
//se initializeaza arborele si se deschid fisierele pentru citire si scriere
	a = InitArb();
	FILE *f = fopen(argv[1], "rt");
	FILE *f1 = fopen(argv[2], "rt");
	FILE *g = fopen(argv[3], "wt");
	FILE *g1 = fopen(argv[4], "wt");
	fscanf(f, "%d", &nr_coduri);
//se parcurg codurile si se adauga in arbore
	for(i = 0; i < nr_coduri; i ++){
		fscanf(f, "%s%s", litera, cod);
		add(cod, *litera, a);
	}
	AfiArb(a, g);
	fscanf(f, "%s", sep);
	fscanf(f, "%d", &nr_com);
//se citesc intructiunile
	for(i = 0; i < nr_com; i ++){
		fscanf(f, "%s", com);
		if(strcmp(com, "add") == 0){
//daca intructiunea este 'add' se citeste calea si caracterul si se adauga respectiva codificare in arbore
			fscanf(f, "%s%s", cha, cod);
			add(cod, *cha, a);
		}
		if(strcmp(com, "delete") == 0){
//daca intructiunea este 'delete' se citeste caracterul si se elimina respectiva codificare in arbore
			fscanf(f, "%s", cha);
			delete(a, *cha);
		}
		AfiArb(a, g);
	}
//se citesc frazele pentru decodificat
	while(fgets(fraza, 10000, f1) != NULL){
//cu ajutorul functiei 'strtok' se sparge fraza in cai pentru descifrarea caracterelor
		cod = strtok(fraza, sep);
		while(cod){
			if(cod[0] == ' '){
				fprintf(g1, "%c", cod[0]);
				cod ++;
			}
			if(cod[0] == '\n'){
				fprintf(g1, "%c", cod[0]);
				cod++;	
			}
			if(cod[0] != '\0'){
				o_litera = decodificare(cod, a);
				fprintf(g1, "%c", o_litera);
				}
			cod = strtok(NULL, sep);
		}
	}
//se inchid fisierele si se elibereaza memoria
	fclose(f);
	fclose(g);
	fclose(f1);
	fclose(g1);
	free(sep);
	free(cod);
	free(litera);
	free(com);
	free(cha);
	free(fraza);
	return 0;
}
	
	





















