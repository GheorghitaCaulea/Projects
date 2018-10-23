CAULEA Gheorghita
324 CB

1.Simulare Masina Turing
	In inceputul implementarii am creat 3 structuri folosite pentru a memora starile ce intra in alcatuirea masinii, starile finale si tranzitiile. Am initializat variabilele de ajutor. Deschid fisierul pentru citirea benzii, aloc memorie pentru banda si o citesc. Deschid fisierul unde se afla codificarea masinii. Citesc starile ce vor intra in alcatuirea masinii, starile finale si starea initiala, alocandu-le memorie. Pentru fiecare tranzitie aloc memorie si citesc componentele ce o alcatuiesc. Verific daca starea in care ma aflu este o stare finala. Daca se intampla acest lucru scriu banda in fisier, eliberez memoria si inchid fisierele. In caz contrar, parcurg vectorul de tranzitii si execut oparatiile necesare. In situatia in care nu se gaseste o tranzitie corespundatoare starii in care ma aflu, afisez mesajul "Se agata!", eliberez memoria si inchid fisierele. 

2. Adunare binara
	Am construit o masina care aduna doua numere in partea dreapta a spatiului gol('#') ce le separa. Plecand din partea stanga citesc primul caracter de pe banda, daca e diferit de '#', si il inlocuiesc cu '#'. Parcurg banda pana reusesc sa depasesc caracterul '#' ce separa numerele. Dupa ce am depasit acest caracter execut o adunare in binar. Am folosit scrierea pe banda a altor caractere in partea dreapta pentru a sti la fiecare pas unde trebuie sa adun. Daca aveam scris 'z', in momentul in care ajungeam acolo, scriam 0 si adunam dupa el. Daca aveam scris 'u', scriam 1, si adunam dupa el. Masina va relua procesul pana cand in partea stanga toate spatiile pe care initial se afla un numar devin '#'. La sfarsit, masina parcurge banda si daca va intalni unul din acele caractere speciale il va traduce. Va intalni maxim unul. 
	
