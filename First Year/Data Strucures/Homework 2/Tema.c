/*CAULEA Gheorghita 314CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
//se initializeaza structurile ce vor fi folosite
//se folosesc macrodefinitii pentru ajutor
typedef struct cel
{ 
  void* info;           /* adresa informatie */
  struct cel *urm;   /* adresa urmatoarei celule */
}TCel, *TLG, **ALG; /* tipurile Celula, Lista si Adresa_Lista */
typedef struct{
	int id;
	char *denumire;
	char *adresa;
	char *mod;
}TSwitch, *ASwitch;  
typedef struct
{ 
	size_t 	dime; 		/* dimensiunea unui element din coada  		*/
	TLG 	ic; 		/* adresa primului element din coada 		*/
	TLG 	sc; 		/* adresa de sfarsit a cozii 				*/
} TCoadaV, *AQV;
#define IC(a) 	(((AQV)(a))->ic)
#define SC(a) 	(((AQV)(a))->sc)
typedef struct
{ 
	size_t 	dime; 		/* dimensiunea unui element al stivei 			*/
	TLG 	vf; 		/* varful stivei 					*/
}TStiva, *ASt;
#define VF(a) 	(((ASt)(a))->vf)
//functia 'AlocCel' contruieste si aloca memorie pentru o structura de tip TLG
TLG AlocCel(void *ae){
	TLG a;
	a = (TLG)calloc(1, sizeof(TCel));
	if(!a)
		return NULL;
	a -> urm = NULL;
	a -> info = malloc(sizeof(TSwitch));
	if(!a -> info){
		free(a);
		return NULL;
	} 
	memcpy(a -> info, ae, sizeof(TSwitch));
	return a;
}
//functia 'InitS' initializeaza o stiva vida
void *InitS(size_t d){
	ASt s;
	s = (ASt)calloc(1, sizeof(TStiva));
	if(!s){
		printf("nu");
		return NULL;
	}
	s -> vf = NULL;
	s -> dime = d;
	return (void*)s;
}
//functia 'Push' adauga un element intr-o stiva
int Push(void *a, void *ae){
	TLG aux;
	aux = AlocCel(ae);
	if(VF(a) == NULL)
		VF(a) = aux;
	else{
		aux -> urm = VF(a);		
		VF(a) = aux;
	}
		return 1;
}
//functia 'Pop' scoate un element dintr-o stiva
int Pop(void *a, void *ae){
	TLG aux = VF(a);
	if(VF(a) != NULL){
		memcpy(ae, (VF(a)) -> info, sizeof(TSwitch));
		VF(a) = VF(a) -> urm;		
		free(aux);
		return 1;
	}
	else
		return 0;
}
//functia 'Rastoarna' rastoarna stiva 'as' peste stiva 'ad'
int Rastoarna(void* ad, void* as){
	TSwitch b;
	while(VF(as) != NULL){
		Pop(as, &b);
		Push(ad, &b);
	}
	return 1;
}
//functia 'Suprapune' suprapune stiva 'as' peste stiva 'ad'
int Suprapune(void *ad, void *as){
	void *aux;
	TSwitch b;
	aux = InitS(sizeof(TSwitch));
	while(VF(as) != NULL){
		Pop(as, &b);
		Push(aux, &b);
	}
	while(VF(aux) != NULL){
		Pop(aux, &b);
		Push(ad, &b);
	}
	return 1;
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
		memcpy(ae, (IC(a)) -> info, sizeof(TSwitch));
		IC(a) = IC(a) -> urm;
		free(aux);
		return 1;
	}
	return 0;
}
//functia 'InsOrdS' introduce ordonat un element intr-o stiva
void InsOrdS(void *a, void *ae){
	void *aux;
	aux = InitS(sizeof(TSwitch));
	TSwitch sw;
	while(VF(a) != NULL){ 
			if((((TSwitch*)(VF(a) -> info)) -> id) > ((TSwitch*)ae) -> id){
				Pop(a, &sw);
				Push(aux, &sw);
			}
			else
				break;
	}			
	Push(aux, ae);
	Rastoarna(a, aux);
}
//functia 'transform' tranforma o adresa IPv4 intr-un numar
unsigned long transform(char *a){
	int i = 0;
	unsigned long ip = 0, nr = 0;
	while(a[i] != '.' && a[i] != '\0'){
		nr = nr * 10 + (a[i] - '0');
		if(a[i + 1] == '.'){
			ip = (ip + nr) * 256;
			nr = 0;
			i ++;
		}
		else
			if(a[i + 1] == '\0')
				ip = ip + nr;
		i ++;
	}
	return ip;
}
//functia 'InsOrdQ' insereaza un element intr-o coada
void InsOrdQ(void *a, void  *ae){
	unsigned long ae_ipv, ipv;
	TSwitch b;
	void *aux;
	aux = InitQ(sizeof(TSwitch));
	ae_ipv = transform(((TSwitch*)ae) -> adresa);
	if(IC(a) != NULL){
		ipv = transform(((TSwitch*)(IC(a) -> info)) -> adresa);
		while(ipv < ae_ipv && IC(a) != NULL){
			ExtrQ(a, &b);
			IntrQ(aux, &b);
			if(IC(a) != NULL)
				ipv = transform(((TSwitch*)(IC(a) -> info)) -> adresa);
		}
	}
	IntrQ(aux, ae);
	while(IC(a) != NULL){
		ExtrQ(a, &b);
		IntrQ(aux, &b);
	}
	while(IC(aux) != NULL){
		ExtrQ(aux, &b);
		IntrQ(a, &b);
	}	
}
//functia 'addS' introduce un switch in retea, dupa cum este dat
/*x-1 pentru switch principal, 0-secundar*/
void addS(void *a, void *ae, int x){
		void *aux;
		TSwitch sw;
		aux = InitS(sizeof(TSwitch));
		if(VF(a) == NULL)
			Push(a, ae);
		else{
			if(x == 1){
				while(VF(a) != NULL){
					Pop(a, &sw);
					Push(aux, &sw);
				}
				Push(a, ae);
				Pop(aux, &sw);
				if(VF(aux) == NULL)
					Push(aux, &sw);
				else
					InsOrdS(aux, &sw);
				Rastoarna(a, aux);
			}
			else{
				if(x == 0){
					while(VF(a) -> urm != NULL){
						Pop(a, &sw);
						Push(aux, &sw);
					}
					if(VF(aux) == NULL)
						Push(aux, ae);
					else
						InsOrdS(aux, ae);
					Rastoarna(a, aux);
				}
			}
		}
}						
//functia 'dell_id' localizeaza si elimina un switch dintr-o retea sau dintr-o stiva
int dell_id(int nr_stive, void **s, void *c, int id_cautat, void *ae){
	void *aux1, *aux2;
	int i, sw = 0;
	TSwitch b;
	aux1 = InitQ(sizeof(TSwitch));
	aux2 = InitS(sizeof(TSwitch));	
	while(IC(c) != NULL && ((TSwitch*)IC(c) -> info) -> id != id_cautat){
		ExtrQ(c, &b);
		IntrQ(aux1, &b);
	}
	if(IC(c) != NULL){
		ExtrQ(c, &b);
		sw = 1;
		memcpy(ae, &b, sizeof(TSwitch));
		while(IC(c) != NULL){
			ExtrQ(c, &b);
			IntrQ(aux1, &b);
		}
	}
	else{
		while(IC(c) != NULL){
			ExtrQ(c, &b);
			IntrQ(aux1, &b);
		}
	}
	while(IC(aux1) != NULL){
		ExtrQ(aux1, &b);
		IntrQ(c, &b);
	}
	if(sw == 1)
		return 1;
	for(i = 0; i < nr_stive; i++){	
		while(VF(s[i]) != NULL && ((TSwitch*)VF(s[i]) -> info) -> id != id_cautat){
			Pop(s[i], &b);
			Push(aux2, &b);
		}
		if(VF(s[i]) != NULL){
			sw = 1;
			Pop(s[i], &b);
			memcpy(ae, &b, sizeof(TSwitch));
			while(VF(s[i]) != NULL){
				Pop(s[i], &b);
				Push(aux2, &b);
			}
		}
		else{
			while(VF(s[i]) != NULL){
				Pop(s[i], &b);
				Push(aux2, &b);
			}
		}
		Rastoarna(s[i], aux2);
		if(sw == 1)
			return 1;
	}
	return 0;
}					
//functia 'InitStive' initializeaza un vector de stive
void **InitStive(int nr){
	int i;
	void **a;
	a = (void**)calloc(nr, sizeof(void*));
	for(i = 0; i < nr; i ++){
		a[i] = InitS(sizeof(TSwitch));
	}
	return a;
}
//functia 'AfiElem' afiseaza toate campurile unui element de tip TSwitch
void AfiElem(void* a, FILE *g){
		fprintf(g, "%d ", ((TSwitch*)a) -> id);
		fprintf(g, "%s ", ((TSwitch*)a) -> adresa);
		fprintf(g, "%s", ((TSwitch*)a) -> denumire);
}
//functia 'showSQ' afiseaza coada si toate stivele din vectorul de stive
void showSQ(int x, void **s, void *q, FILE *g){
	TSwitch b;
	void *aux1, *aux2;
	aux1 = InitQ(sizeof(TSwitch));
	aux2 = InitS(sizeof(TSwitch));	
	int i;
	fprintf(g, "{");
	while(IC(q) != NULL){
		ExtrQ(q, &b);
		fprintf(g, "%d ", b.id);
		IntrQ(aux1, &b);
	}
	while(IC(aux1) != NULL){
		ExtrQ(aux1, &b);
		IntrQ(q, &b);
	}	
	fprintf(g, "}\n");
	for(i = 0; i < x; i ++){
		fprintf(g, "%d:\n", i);
		while(IC(s[i]) != NULL){
			Pop(s[i], &b);
			AfiElem(&b, g);
			Push(aux2, &b);
			fprintf(g, "\n");
		}
	Rastoarna(s[i], aux2);
	}
	fprintf(g, "\n");
}
//functia 'ip_min' determina cel mai mic ip transformat, dintr-o coada
void ip_min(void *c, FILE *g){
	unsigned long val;
	if(IC(c) == NULL)
		fprintf(g, "ipmin=0\n");
	else{
		val = transform(((TSwitch*)(IC(c) -> info)) -> adresa);
		fprintf(g, "ipmin=%lu\n", val);
	}
}
int main(int argc, char *argv[]){
//se initializeaza coada si vectorul de stive
	int nr_stive;
	void **s;
	void *c;	
	char *com;
	c = InitQ(sizeof(TSwitch));
	com = (char*)calloc(256, sizeof(char));
	if(!com)
		return 0;
//se deschid fisierele pentru citire, respectiv scriere
	FILE *f = fopen(argv[1], "rt");
	FILE *g = fopen(argv[2], "wt");
	fscanf(f, "%d", &nr_stive);
	s = InitStive(nr_stive);
	while(fscanf(f, "%s", com) != EOF){	
//daca instructiunea este 'add' se citesc din fisier campurile unui element de tip TSwitch si se introduce in functie de 'functionare' in stiva sau coada
		if(strcmp(com,"add") == 0){
			TSwitch b;
			char *den, *adr, *md;
			int idi;
			den = (char*)calloc(256, sizeof(char));
			if(!den){
				free(com);
				return 0;
			}				
			adr = (char*)calloc(256, sizeof(char));
			if(!adr){
				free(com);
				free(den);
				return 0;
			}
			md = (char*)calloc(256, sizeof(char));
			if(!md){
				free(com);
				free(den);
				free(adr);				
				return 0;
			}
			fscanf(f, "%d%s%s%s", &idi, den, adr, md);
			b.id = idi;
			b.denumire = strdup(den);
			b.adresa = strdup(adr);
			b.mod = strdup(md);
			if(strcmp(md, "SINGLE") == 0){
				InsOrdQ(c, &b);
			}
			else{
				char *principal;
				int id_stiva;
				principal = (char*)calloc(256, sizeof(char));
				if(!principal){
					free(com);
					free(den);
					free(adr);				
					free(principal);
					return 0;	
				}		
				fscanf(f, "%d%s", &id_stiva, principal);
				if(strcmp(principal, "BASE") == 0)
					addS(s[id_stiva], &b, 1);
				else
					addS(s[id_stiva], &b, 0); 
			}
		}
//daca intructiunea este 'show' se afiseaza intrg vectorul de stive si coada
		if(strcmp(com, "show") == 0){
			showSQ(nr_stive, s, c, g);
		}
//daca intructiunea este 'ipmin' se determina cel mai mic ip din coada
		if(strcmp(com, "ipmin") == 0){
			ip_min(c, g);
		}
//daca intructiunea este 'del' se scoate din retea, in caz ca exista, switch-ul dorit
		if(strcmp(com, "del") == 0){
			int id_cautat;
			TSwitch un_sw;
			fscanf(f, "%d", &id_cautat);
			dell_id(nr_stive, s, c, id_cautat, &un_sw);
		}
//daca intructiunea este 'set' se seteaza switch-ul prin stergerea acestuia si adaugarea in coada sau stiva data
		if(strcmp(com, "set") == 0){
			int idii;
			char *mod_func;
			TSwitch swit;
			mod_func = (char*)calloc(256, sizeof(char));
			if(!mod_func)
				return 0;
			fscanf(f, "%d%s", &idii, mod_func);
			if(dell_id(nr_stive, s, c, idii, &swit) == 1){
				if(strcmp(mod_func, "STACK") == 0){
					int id_stiva;	
					char *principal;
					principal = (char*)calloc(256, sizeof(char));
					if(!principal)
						return 0;
					fscanf(f, "%d%s", &id_stiva, principal);
					if(strcmp(principal, "BASE") == 0)
						addS(s[id_stiva], &swit, 1);
					else
						addS(s[id_stiva], &swit, 0);
				}
				else
					InsOrdQ(c, &swit);
			}
		}
	}	
//se inchid fisierele
	fclose(f);
	fclose(g);
	return 0;
}
	
