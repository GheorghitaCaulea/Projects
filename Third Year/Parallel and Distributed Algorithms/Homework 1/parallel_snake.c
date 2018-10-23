#include <stdio.h>
#include <stdlib.h>
#include "main.h"
/*Aceasta functie construieste o celula din corpul unui sarpe, celula ce este reprezentata printr-o lista dublu inlantuita 
necirculara avand un singur element.*/
TLDI ConsBodySeg(int line, int col) {
	TLDI seg;
	seg = (TLDI)calloc(1, sizeof(TCel));
	if(!seg)
		return NULL;
	seg -> pre = NULL;
	seg -> urm = NULL;
	seg -> lc.line = line;
	seg -> lc.col = col;
	return seg;
}

/*Aceasta functie adauga la corpul unui sarpe, care este reprezentat de o lista dublu inlantuita necirculara, o celula reprezentata
de o lista dubla inlantuita necirculara cu un singur element. */
void ConsBody(TLDI body, TLDI seg) {
	body -> urm = seg;
	seg -> pre = body;
}

/*Aceasta functie returneaza index-ul liniei sau al coloanei calculand daca indexul depaseste dimensiunile matricii.
ex. Daca sunt pe o celula in Nordul hartii si indexul liniei scade cu o unitate, functia imi va returna indexul corespunzator
celei mai Sudice linii.*/
int get_index(int index, int max_lim) {
	if(index > max_lim - 1) {
		return (index - max_lim);
	} 
	else if (index < 0) {
		return (index + max_lim);
	}
	return index;
}
/*Aceasta functie va construi corpul unui sarpe(lista coordonatelor fiecarei celule din sarpe) si totodata va retine
si ultima celula din sarpe, celula ce reprezinta coada sarpelui.*/
TLDI FindSnakes(struct snake s, int ** m, int num_lines, int num_cols, TL last) {
	int line = s.head.line;
	int col = s.head.col;
	int sw = 0;
	TLDI init_snake = ConsBodySeg(line, col);
	TLDI iter = init_snake;
	*last = init_snake;
	TLDI aux_snake;
	while(1) {
		/*Daca sw == 0, caut vecinii head-ului. */
		if (sw == 0) {
			/*Verific daca am vecin in Sud.*/
			if(m[get_index(line + 1, num_lines)][col] == s.encoding) {
				line = get_index(line + 1, num_lines);
				sw = 1;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm;
				*last = aux_snake;
			}
			/*Verific daca am vecin in Nord.*/
			else if(m[get_index(line - 1, num_lines)][col] == s.encoding) {
				line = get_index(line - 1, num_lines);
				sw = 2;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Vest.*/
			else if(m[line][get_index(col - 1, num_cols)] == s.encoding) {
				col = get_index(col - 1, num_cols);
				sw = 3;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Est.*/
			else if(m[line][get_index(col + 1, num_cols)] == s.encoding) {
				col = get_index(col + 1, num_cols);
				sw = 4;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			else 
				break;
		}
		/*Daca sw == 1, inseamna ca vin din N spre S.*/
		else if(sw == 1) {
			/*Verific daca am vecin in Sud.*/
			if(m[get_index(line + 1, num_lines)][col] == s.encoding) {
				line = get_index(line + 1, num_lines);
				sw = 1;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Vest.*/
			else if(m[line][get_index(col - 1, num_cols)] == s.encoding) {
				col = get_index(col - 1, num_cols);
				sw = 3;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Est.*/
			else if(m[line][get_index(col + 1, num_cols)] == s.encoding) {
				col = get_index(col + 1, num_cols);
				sw = 4;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			else 
				break;
		}
		/*Daca sw == 2 inseamna ca vin din S spre N. */
		else if(sw == 2) {
			/*Verific daca am vecin in Nord.*/
			if(m[get_index(line - 1, num_lines)][col] == s.encoding) {
				line = get_index(line - 1, num_lines);
				sw = 2;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Vest.*/
			else if(m[line][get_index(col - 1, num_cols)] == s.encoding) {
				col = get_index(col - 1, num_cols);
				sw = 3;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Est.*/
			else if(m[line][get_index(col + 1, num_cols)] == s.encoding) {
				col = get_index(col + 1, num_cols);
				sw = 4;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			else 
				break;
		}
		/*Daca sw == 3, inseamna ca vin din E spre V. */
		else if(sw == 3) {
			/*Verific daca am vecin in Sud.*/
			if(m[get_index(line + 1, num_lines)][col] == s.encoding) {
				line = get_index(line + 1, num_lines);
				sw = 1;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Nord.*/
			else if(m[get_index(line - 1, num_lines)][col] == s.encoding) {
				line = get_index(line - 1, num_lines);
				sw = 2;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Vest.*/
			else if(m[line][get_index(col - 1, num_cols)] == s.encoding) {
				col = get_index(col - 1, num_cols);
				sw = 3;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			else 
				break;
		}
		/*Daca sw == 4 inseamna ca vin din V spre E.*/
		else if(sw == 4) {
			/*Verific daca am vecin in Sud.*/
			if(m[get_index(line + 1, num_lines)][col] == s.encoding) {
				line = get_index(line + 1, num_lines);
				sw = 1;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Nord.*/
			else if(m[get_index(line - 1, num_lines)][col] == s.encoding) {
				line = get_index(line - 1, num_lines);
				sw = 2;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			/*Verific daca am vecin in Est.*/
			else if(m[line][get_index(col + 1, num_cols)] == s.encoding) {
				col = get_index(col + 1, num_cols);
				sw = 4;
				aux_snake = ConsBodySeg(line, col);
				ConsBody(iter, aux_snake);
				iter = iter -> urm; 
				*last = aux_snake;
			}
			else 
				break;
		}
	}	
	return init_snake;
}

/*Aceasta functie realizeaza mutarea cozii sarpelui prin mutare tuturor informatiilor din lista ce tine corpul sarpelui.
Mutarea va incepe de la coada sarpelui si se incheie cand se ajunge pe capul acestuia(aux -> pre == NULL). */
void moveTail(struct snake *s) {

	TLDI aux = s -> last;
	s -> col_old_tail = (s -> last -> lc).col;
	s -> line_old_tail = (s -> last -> lc).line;

	while(aux -> pre != NULL) {
		(aux -> lc).line = (aux -> pre -> lc).line;
		(aux -> lc).col = (aux -> pre -> lc).col;		
		aux = aux -> pre;
		
	}
}

/* Aceasta functie realizeaza mutarea capului fiecarui sarpe. Mutarea are loc daca celula in care urmeaza sa se mute capul este
goala sau daca matricea auxiliara(aux_world2) indica faptul ca acea celula este coada unui sarpe deci se poate muta acolo  si 
daca matricea auxiliara(aux_world) nu indica faptul ca pe acea celula se gaseste capul unui alt sarpe.
In cazul in care nu se poate efectua o mutare, se detecteaza eveniment de tip coliziune si functia va returna valoarea 1.*/
int moveHead(struct snake *s, int ** world, int num_lines, int num_cols, int **aux_world, int ** aux_world2) {
	
	if(s -> direction == 'S' && (world[get_index((s -> body -> lc).line + 1, num_lines)][(s -> body -> lc).col] == 0 ||
	aux_world2[get_index((s -> body -> lc).line + 1, num_lines)][(s -> body -> lc).col] == 1) &&
	aux_world[get_index((s -> body -> lc).line + 1, num_lines)][(s -> body -> lc).col] != 1) {
		aux_world[(s -> body -> lc).line][(s -> body -> lc).col] = 0;
		aux_world[get_index((s -> body -> lc).line + 1, num_lines)][(s ->body -> lc).col] = 1;
		(s -> body -> lc).line = get_index((s -> body -> lc).line + 1, num_lines);
		return 0;
	
	} else if ( s -> direction == 'N' && (world[get_index((s -> body -> lc).line - 1, num_lines)][(s -> body -> lc).col] == 0 || 
	aux_world2[get_index((s -> body -> lc).line - 1, num_lines)][(s -> body -> lc).col] == 1) &&
	aux_world[get_index((s -> body -> lc).line - 1, num_lines)][(s -> body -> lc).col] != 1) {
		aux_world[(s -> body -> lc).line][(s ->body -> lc).col] = 0;
		aux_world[get_index((s -> body -> lc).line - 1, num_lines)][(s -> body -> lc).col] = 1;
		(s -> body -> lc).line = get_index((s -> body -> lc).line - 1, num_lines);
		return 0;
	
	} else if( s -> direction == 'V' && (world[(s -> body -> lc).line][get_index((s -> body -> lc).col - 1, num_cols)] == 0 ||
	aux_world2[(s -> body -> lc).line][get_index((s -> body -> lc).col - 1, num_cols)] == 1) &&
	aux_world[(s -> body -> lc).line][get_index((s -> body -> lc).col - 1, num_cols)] != 1) {
		aux_world[(s -> body -> lc).line][(s -> body -> lc).col] = 0;
		aux_world[(s -> body -> lc).line][get_index((s -> body -> lc).col - 1, num_cols)] = 1;
		(s -> body -> lc).col = get_index((s -> body -> lc).col - 1, num_cols);
		return 0;
	
	} else if( s -> direction == 'E' && (world[(s -> body -> lc).line][get_index((s -> body -> lc).col + 1, num_cols)] == 0 ||
	aux_world2[(s -> body -> lc).line][get_index((s -> body -> lc).col + 1, num_cols)] == 1) &&
	aux_world[(s -> body -> lc).line][get_index((s -> body -> lc).col + 1, num_cols)] != 1) {
		aux_world[(s -> body -> lc).line][(s ->body -> lc).col] = 0;
		aux_world[(s -> body -> lc).line][get_index((s -> body -> lc).col + 1, num_cols)] = 1;
		(s -> body -> lc).col = get_index((s -> body -> lc).col + 1, num_cols);
		return 0;
	} else {
		return 1;
	}
	
}

/*Aceast functie este apelata pentru a face update-ul hartii de joc in cazul in care nu a avut loc o coliziune.
Mut capul sarpelui pe noile coordonate si in cazul in care nu a ajuns un alt sarpe pe vechea coada voi pune 0 pe harta.
Actualizez si harta auxiliara(aux_world2) in vederea mutarii sarpelui.*/
void update(int **world, int ** aux_world, struct snake *s, int **aux_world2) {
	
	world[(s -> body -> lc).line][(s -> body -> lc).col] = s -> encoding;
	
	if(aux_world[s -> line_old_tail][s -> col_old_tail] != 1)
		world[s -> line_old_tail][s -> col_old_tail] = 0;
	(s -> head).line = (s -> body -> lc).line;
	(s -> head).col = (s -> body -> lc).col; 
	aux_world2[s -> line_old_tail][s -> col_old_tail] = 0;
	aux_world2[(s -> last -> lc).line][(s -> last -> lc).col] = 1;

}

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name) {
	int i, j, k, sum = 0;
	int **aux_world;
	/*Initializez prima harta auxiliara care va tine 1 pe pozitiile capetelor tuturor serpilor.*/
	aux_world = (int **)malloc(num_lines * sizeof(int *));
	
	for (i = 0; i < num_lines; i++)
		aux_world[i] = (int *)calloc(num_cols, sizeof(int));
	
	for(i = 0; i < num_lines; i ++) {
	
		for(j = 0; j < num_cols; j ++) {
			aux_world[i][j] = 0;
		}
	}
	/*Initializez cea de-a doua harta auxiliara care va tine 1 pe pozitiile cozilor tuturor serpilor.*/
	int **aux_world2;
	aux_world2 = (int **)malloc(num_lines * sizeof(int *));
	for (i = 0; i < num_lines; i++)
		aux_world2[i] = (int *)calloc(num_cols, sizeof(int));
	for(i = 0; i < num_lines; i ++) {
		for(j = 0; j < num_cols; j ++) {
			aux_world2[i][j] = 0;
		}
	}
	/*Construiesc lista pentru fiecare sarpe si initializez cele doua matrici auxiliare.*/
	for(i = 0; i < num_snakes; i ++) {
		snakes[i].body = FindSnakes(snakes[i], world, num_lines, num_cols, &(snakes[i].last));
		aux_world[snakes[i].head.line][snakes[i].head.col] = 1;
		aux_world2[(snakes[i].last -> lc).line][(snakes[i].last -> lc).col] = 1;
	}
	
	/*Pentru fiecare tura voi muta in paralel coada serpilor.
	Mut capetele lor pentru a reusi sa verific toate cazurile de coliziune.
	Fac update la harta in mod paralel, asigurandu-ma ca nu am avut coliziune.*/
	for(j = 0; j < step_count; j ++) {

		#pragma omp parallel for
		for(i = 0; i < num_snakes; i ++) {
			moveTail(&snakes[i]);

		}

		for(i = 0; i < num_snakes; i ++) {
			sum += moveHead(&snakes[i], world, num_lines, num_cols, aux_world, aux_world2);
		}

		if(sum != 0) {
			break;
		}
		else {
			#pragma omp parallel for
			for(k = 0; k < num_snakes; k ++) {
				update(world, aux_world, &snakes[k], aux_world2);
			}	
		}	
	}	
}