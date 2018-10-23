#include<stdio.h>
#include "bmp_header.h"
#include<string.h>
#include<stdlib.h>
int main(void){
	char num[30], num1[30];
	int i, j, b1, g1, r1, p, sk = 0;
	unsigned char b, g, r;
	struct bmp_fileheader x;
	struct bmp_infoheader y;
//se declara variabilele si cele doua structuri
	FILE *f = fopen("input.txt", "rt");
	fscanf(f, "%s", num);
	fscanf(f, "%d%d%d", &b1, &g1, &r1);	
	FILE *gh = fopen(num, "rb");
	strncpy(num1, num, strlen(num) - 4);
	strcat(num1, "_task1.bmp");
//se deschide fisierul pentru citirea datelor de imput, se creeaza numele fisierului de output 
	fread(&x, sizeof(struct bmp_fileheader), 1, gh);
	fread(&y, sizeof(struct bmp_infoheader), 1, gh);
	fseek(gh, x.imageDataOffset, 0);
	FILE *h = fopen(num1, "wb");
	fwrite(&x, sizeof(struct bmp_fileheader), 1, h);
	fwrite(&y, sizeof(struct bmp_infoheader), 1, h);	
	p = (y.width * 3) % 4;
//se citesc cele doua structuri din fisier, se sare in pozitia de inceput a imaginii, se deschide fisierul de output pentru scriere in el, dupa care se scriu cele doua structuri; se calculeaza paddingul
	for(i = 0; i < y.height; i++){
		for(j = 0; j < y.width ; j++){
			fread(&b, 1, 1, gh);
			fread(&g, 1, 1, gh);
			fread(&r, 1, 1, gh);
//se parcurge imaginea ca o matrice si se citesc culorile pixelilor
			if(b != 255 || g != 255 || r != 255){
				b = b1;
				g = g1;
				r = r1;
			}
			fwrite(&b, 1, 1, h);
			fwrite(&g, 1, 1, h);
			fwrite(&r, 1, 1, h);
		}
//daca o culoare este diferita de alb, se schimba cu acea culoare data la imput
		if(p != 0){
			fseek(gh, (4 - p), 1);
			fwrite(&sk, 1, (4 - p), h);
//se ignora paddingul la citire dar se scrie in noul fisier
		}				 
	}
	fclose(f);
	fclose(gh);
	fclose(h);
	return 0;
}
