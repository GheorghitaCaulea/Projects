/*CAULEA Gheorghita 314CB*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
//se definesc tipurile folosite in rezolvarea temei
typedef int (*TFHash)(void*, int);
typedef struct cel{
	struct cel *pre, *urm;                        
	void *info;              
}TCel, *TLDI, **TL;
typedef struct{
	char * key, * value;
	int frequency;
}TEL, *TElem;
typedef struct{
	int M;
	TFHash fh;
	TLDI *v;

} TH;
//functia cod va genera intrarea in fiecare lista
int cod(void *a, int M)
{
	int sum = 0, i = 0;
	char *p=((char*)a);
	while(*(p + i) != '\0'){
		sum = sum + *(p + i);
		i ++;
	}	
	return sum % M;	
}
//functia IniTH va initializa o tabela hash cu un vector de liste cu o dimensiune data
TH* IniTH(int M, TFHash fh){
	TH * h = (TH*)calloc(1, sizeof(TH));
	if (!h){ 	
		printf("eroare alocare hash\n");
		return NULL;
	}
	h -> v = (TLDI*)calloc(M, sizeof(TLDI));
	if(! h -> v){
		printf("eroare alocare vector de pointeri TLDI in hash\n");
		free(h);
		return NULL;
	}
	h -> M = M;
	h -> fh = fh;
	return h;
}
//functia AlocCel aloca o lista circulara cu un singur element cu campurile urm si pre ce pointeaza spre ea
TLDI AlocCel(void *x){
	TLDI a;
	a = (TLDI)calloc(1, sizeof(TCel));
	if(!a)
		return NULL;
	a -> pre = a; 
	a -> urm = a;
	a -> info = (TElem)calloc(1, sizeof(TEL));
	if(!a -> info){
		free(a);
		return NULL;
	}
	memcpy(a -> info, x, sizeof(TEL));
	return a;
}
//functia cmp compara doua informatii, returnand un mesaj corespunzator
int cmp(void *a, void *b){
	char *x, *y;
	int z, t;
	x = ((TEL*)a) -> key;
	z = ((TEL*)a) -> frequency;
	y = ((TEL*)b) -> key;
	t = ((TEL*)b) -> frequency;	
	if(z == t){
		if(strcmp(x, y) == 0)
			return 0;
		else
			return strcmp(x, y);
	}	
	else
		if(strcmp(x, y) == 0)
			return 0;	
	return t - z;
}
//functia LungTLDI returneaza rungimea unei liste date ca parametru
int LungTLDI(TLDI a){
	TLDI b = a;
	int i = 1;
	if(a == NULL)
		return 0;	
	if(a != NULL && a == a -> urm)
		return 1;
	a = a -> urm;
	while(a != b){
		a = a -> urm;
		i ++;
	}
	return i;
}
//functia InsInainte insereaza o celula inaintea altei celule
void InsInainte(TLDI a, TLDI b){
	b -> urm = a; 
	b -> pre = a -> pre; 
	a -> pre -> urm = b; 
	a -> pre = b;
}
//functia setElem insereaza ordonat un element intr-o lista, schimband inceputul listei daca este cazul
int setElem(TL t, TLDI b){
	int i = 0;
	TLDI a = *t;
	if(*t == NULL){
		*t = b;
		return 1;	
	}
	if(cmp((*t) -> info, b -> info) > 0){
			b -> urm = *t; 
			(*t) -> pre -> urm = b; 
			b -> pre = (*t) -> pre; 
			b -> urm -> pre = b;
			*t = b;			
			return 14;
	}
	for(i = 0; i < LungTLDI(*t); i++){ 
		if(cmp(a -> info, b -> info) > 0){
			InsInainte(a, b);
			return 1;
		}			
		else
			if(cmp(a -> info, b -> info) == 0){
				return 0; 
			}
			else	
				a = a -> urm;	
	}
	if(i == LungTLDI(*t) && cmp(a -> info, b -> info) < 0){
		InsInainte(*t, b); 
		return 1;
	}		
	return 0;
}
//functia AfisareLDI afiseaza toate valorile din campul 'value' al unei liste
void AfisareLDI(TLDI s, FILE *g){
	int i;	
	for(i = 0; i < LungTLDI(s); i ++){
		fprintf(g, " (%s)", ((TElem)(s -> info)) -> value);
		s = s -> urm;
	}
	fprintf(g, "\n");
}
//functia print afiseaza toate valorile 'value' al vectorului de liste dat ca parametru
void print(TH *t, FILE *g){
	int i;
	for(i = 0; i < t -> M; i ++)
		if(t -> v[i] != NULL){
			fprintf(g, "%d:", i);	
			AfisareLDI(t -> v[i], g);
		}
}
//functia AlocElem aloca un element cu toate informatiile, date ca parametru
TElem AlocElem(char *k, char *v, int f){
	TElem s; 	
	s = (TElem)calloc(1, sizeof(TEL));
	if(!s)
		return 0;
	s -> key = (char*)calloc(120, sizeof(char));
	if(! s -> key){
		free(s);
		return 0;
	}
	strcpy(s -> key, k);
	s -> value = (char*)calloc(120, sizeof(char));
	if(! s -> value){
		free(s);
		free(s -> key);		
		return 0;
	}
	strcpy(s -> value, v);
	s -> frequency = f;
	return s;
}		
//functia freeElem elibereaza memoria alocata unui element
void freeElem(TElem x){
	free(x -> key);
	free(x -> value);
	free(x);
}
//functia freeCel elibereaza memoria alocata unei celule
void freeCel(TLDI x){
	freeElem((TElem)(x -> info));
	free(x);
}
//functia Elim elimina un element dintr-o lista returnand: 1 - s-a gasit si s-a eliminat; 0 - nu s-a gasit 
int Elim(TL a, TLDI b){
	TLDI aux;
	int i;
	
	if(strcmp(((TElem)(*a) -> info) -> key, ((TElem)(b -> info)) -> key) == 0){
		if((*a) -> urm == (*a)){			
			freeCel(*a);
			*a = NULL;
			return 1;
		}
		else{
			aux = *a;
			aux -> pre -> urm = aux -> urm;
			aux -> urm -> pre = aux -> pre;
			*a = aux -> urm;
			freeCel(aux);
			return 1;
		}
	}
	else
		for(i = 0; i < LungTLDI(*a); i++)
			if(strcmp(((TElem)(*a) -> info) -> key, ((TElem)(b -> info)) -> key) == 0){
				aux = *a;
				aux -> pre -> urm = aux -> urm;
				aux -> urm -> pre = aux -> pre;
				freeCel(aux);
				return 1;
			}
			else
				a = &(*a) -> urm;
	return 0;
}
//functia get creste valoarea campului 'frequency' al unui element si reordoneaza lista in care s-a facut incrementarea
//get este o combinatia a functiilor Elim si setElem
int get(TL a, TLDI b, FILE *g){
	int i;
	TLDI aux = *a;
	for(i = 0; i < LungTLDI(*a); i++)
		if(strcmp(((TElem)aux -> info) -> key, ((TElem)(b -> info)) -> key) == 0){				
			strcpy(((TElem)(b -> info)) -> value, ((TElem)aux -> info) -> value);
			((TElem)(b -> info)) -> frequency = ((TElem)aux -> info) -> frequency + 1;
			Elim(a, b);
			fprintf(g, "%s\n", ((TElem)(b -> info)) -> value);			
			setElem(a, b);	
			return 1;
		}
		else
			aux = aux -> urm;
	fprintf(g, "NULL\n");
	return 0;
}					
int main(int argc, char *argv[]){
//ise initializeaza si se aloca o tabela hash
	TH *t;
	int i, nr_el_total = 0, ki, j, lung;
	int M = atoi(argv[1]);
	t = IniTH(M, cod);
	char *com;
	com = (char*)calloc(20, sizeof(char));
//se deschid fisierele pentru citire, respectiv scriere
	FILE *f = fopen(argv[2], "rt");
	FILE *g = fopen(argv[3], "wt");
//cat timp sunt intructiuni in fisier
	while(fscanf(f, "%s", com) != EOF){
//daca intructiunea este set, se verifica daca trebuie realocata memorie
//daca trebuie alocata memorie, se aloca un nou vector de liste, se copiaza listele in noul vector pe pozitii corespunzatoare, se ataseaza noul vector tabelei hash
		if(strcmp(com, "set") == 0){						
			if(nr_el_total > 2 * (t -> M)){
				TL vec;
				TLDI aux;
				vec = (TL)calloc(2 * (t -> M), sizeof(TLDI));
				for(i = 0; i < t -> M; i ++){
					lung = LungTLDI(t -> v[i]);
					for(j = 0; j < lung; j ++){
						ki = t -> fh(((TElem)(t -> v[i]) -> info) -> key, 2 * (t -> M));
						aux = AlocCel(t -> v[i] -> info);
						t -> v[i] = t -> v[i] -> urm;
						setElem(&(vec[ki]), aux);
					}
				}
				t -> M = 2 * (t -> M);
				t -> v = vec;
			}
			TLDI b;
			TElem s;
			char *v, *k;
			v = (char*)calloc(120, sizeof(char));
			k = (char*)calloc(120, sizeof(char));			
			fscanf(f, "%s%s", k ,v);
			s = AlocElem(k, v, 0);
			b = AlocCel(s);
			i = t -> fh(k, t -> M);
//se verifica acea conditie de lungime a listei si se fac operatiile necesare
			if(LungTLDI(t -> v[i]) == t -> M){		
				TLDI CEL;
				CEL = t -> v[i];
				if(Elim(&(t -> v[i]), CEL -> pre) > 0)
					nr_el_total--;
			}
//se insereaza ordonat elementul
			if(setElem(&(t -> v[i]), b) > 0)
				nr_el_total ++;
		}		
//daca instructiunea este 'print' se asiseaza vectorul de liste
		if(strcmp(com, "print") == 0)
			print(t, g);
//daca intructiunea este 'print_list' se afiseaza lista cu indicele cerul
		if(strcmp(com, "print_list") == 0){
			int index;
			fscanf(f, "%d", &index);
			if(index >= 0 && index < t -> M){			
				if(t -> v[index] == NULL)
					fprintf(g, "%d: VIDA\n", index);
				else{
					fprintf(g, "%d:", index);
					AfisareLDI(t -> v[index], g);
				}
			}
		}
//daca intructiunea este 'remove' se elimina elementul dat, fiind cautat in lista dupa 'key'
		if(strcmp(com, "remove") == 0){
			char *k, *v;
			int j;
			k = (char*)calloc(120, sizeof(char));
			fscanf(f, "%s", k);
			v = (char*)calloc(120, sizeof(char));
			strcpy(v, "03");
			j = t -> fh(k, t -> M);
			if(t -> v[j] != NULL){
				TElem s;
				TLDI b;				
				s = AlocElem(k, v, 0);
				b = AlocCel(s);
				if(Elim(&(t->v[j]), b) > 0)
					nr_el_total--;
			}
		}				
//daca intructiunea este 'get' si respectiva 'key' exista, se elimina din lista si se introduce ordonat o noua celula cu acelasi 'key' si 'frequency' mai mare cu 1
		if(strcmp(com, "get") == 0){
			TLDI a;
			TElem s;
			char *k, *v;
			int j;
			k = (char*)calloc(120, sizeof(char));
			fscanf(f, "%s", k);
			v = (char*)calloc(120, sizeof(char));
			strcpy(v, "03");
			j = t -> fh(k, t -> M);
			if(t -> v[j] == NULL)
				fprintf(g, "NULL\n");
			else{
				s = AlocElem(k, v, 0);
				a = AlocCel(s);
				get(&(t -> v[j]), a, g);	
			}
		}										
	}		
//se inchid fisierele
	fclose(f);
	fclose(g);
	return 0;
}

	
