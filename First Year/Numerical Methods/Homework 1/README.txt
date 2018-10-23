TASK1
	Pentru inceput am creeat matricea rgb pentru o imagine data ca parametru. Pentru fiecare culoare am creat un vector separat. Vectorii r1, r2, r3, nou creati, au fost impatiti la o valoare val(255/count_bins).In urma impartirii am obtinut in cei trei vectori indicii din vectorii histograma pe care ii creez(indicii decremantati cu o unitate in urma folosirii floor). Parcurg vectorii cautand indicii si incrementez in vectorii histograma creati. Concatenez cei trei vectori.

TASK2
	Pentru inceput am creeat matricea rgb pentru o imagine data ca parametru. Pentru fiecare culoare am creat un vector separat. Vectorii r, g, b, nou creati, au fost impatiti la o valoare val(255/count_bins). Incep aplicarea algoritmului dat prin crearea a trei vectori:cmax, cmin, delta(cmax(i) = maxim(r(i), g(i), b(i)), in mod identic cmin si delta). Odata obtinuti vectorii h, s si v ii prelucrez astfel: ii impart la o valoare val(101/count_bins). In mod asemanator TASK-ului 1, creez histogramele cerute si le concatenez.  

TASK3
	In functia 'preprocess' imi creez caile de acces catre cele doua directoare de interes. Pentru prima cale, procesez fiecare imagine din acel director, punand pe fiecare linie a lui x, histograma hsv sau rgb dupa caz. In vectorul t pun 1 pentru directorul'/cats' si -1 in caz contrar. Fac aceleasi operatii si pentru cea de-a doua cale, creandu-mi astfel matricea x si vectorul t doriti.
	In functia 'learn' evit apricarea unui algoritm de inversa si astfel mut acea inmultirea de matrice la putere negativa in partea stanga, puterea devenind pozitiva. Imi voi crea un A care va fi egal cu inmultirea celor doua matrice si un b corespunzator, Sistemul va fi de forma Ax = b. Aplic Givens pentru descompunerea Q R b. Dupa aplicarea Givens, rezolv sistemul superior triunghiular creat si returnez vectorul.

TASK 4
	Imi creez caile de acces catre cele doua directoare. Initializez un vector x, de lungime 3 * count_bins cu o valoare de 1 pe ultima pozitie. Parcurg cele doua directoare, verific pentru fiicare imagine conditia data si in cazul in care imaginea corespunde maresc nr_cats sau nr_ncats, dupa caz, in functie de vectorul in care ma situez. Calculez procentul obtinut.	 	 

