	In inceputul temei am definit tipurile necesare pentru rezolvarea cerintei. Am construit o serie de functii ajutatoare precum:
		-functia 'cod': calculeaza suma literelor unei key % M, returnand astfel intrarea in vectorul de liste;
		-functia 'IniTH': aloca memorie necesara pentru o tabela hash si pentru intreg vectorul de liste; 
		-functia 'AlocCel': aloca o celula de lista cu campurile urm si pre care pointeaza spre ea;
		-functia 'cmp': in catrul inserarii ordonate(setElem), functia cmp stabileste prin rezultatul furnizat de ea in urma compararii a doua informatii daca un element al listei este mai mare sau mai mic decat altul;
		-functia 'LungTLDI': calculeaza lungimea unei liste date ca parametru(lungimea = nr de elemente);
		-functia 'AfisareLDI': afiseaza campul 'value' al tuturor elementelor unei functii date ca parametru;
		-functia 'print': afiseaza pentru toate elementele toturor listelor campul 'value'
		-functia 'AlocElem': aloca spatiu si creeaza un element de tim TElem, cu informatiile transmise ca parametru;
		-functia 'freeElem': elibereaza campurile unui element de tipul TElem;
		-functia 'freeCel' elibereaza o celula a unei liste;
	Functiile care au dus efectiv la rezolvarea cerintelor sunt:
		-functia 'setElem': functia primeste ca parametru un element de tip TLDI si unul de tip TL. Se urmareste inserarea ordonata a elementului TLDI in TL si, daca este cazul, shimbarea adresei de inceput a elementului de tip TL. In cazul in care inserarea nu se efectueaza, se returneaza o;	
		-functia 'Elim': functia primeste ca parametru un element de tip TLDI si unul de tip TL. Functia cauta elementul de tip TlDI in lista declarata TL. In cazul in care elementul cautat este primul, acesta se elimina si se modifica inceputul liste. Altfel, inceputul ramane acelasi. In cazul in care eliminarea nu are lor, din cauza conditiei, se va returna 0;
		- functia 'get': functia 'get' are la baza functiile 'setElem' si 'Elim'. Functia cauta un element dat intr-o lista data. In cazul in care elementul este gasit, acesta se elimina si se introduce ordonat cu o frecventa mai mare cu 1.
	In 'main' ma folosesc de parametrii in linie de comanda pentru a deschide fisierele pentru citire, scriere si pentru a seta M. In cazul in care in cadrul functie set este nevoie de realocare, aloc un nou vector pentru tabela si inserez cu ajutorul functiei 'setElem' pe pozitii corespunzatoare in noul vector. La sfarsitul realocarii copiez vectorul nou creat. In cadrul celorlalte instructiuni apelez functiile mai sus create. 
Student: CAULEA Gheorghita
Grupa: 314 CB
Punctaj obtinut: 85/85
Masina virtuala: Ubuntu 15.10 32 bit
