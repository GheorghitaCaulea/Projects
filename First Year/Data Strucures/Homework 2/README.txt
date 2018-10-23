Student: CAULEA Gheorghita
Grupa: 314 CB
Punctaj obtinut: 85/85
Masina virtuala: Ubuntu 15.10 32 bit

	In inceputul temei am definit tipurile necesare pentru rezolvarea cerintei si cateva macrodefinitii. Am construit o serie de functii de baza: AlocCel, InitS, Pop, Push, Rastoarna, Suprapune, InitQ, IntrQ, ExtrQ, functii care au ajutat la lucrul cu stive si cozi. Functiile secundare pe care le am contruit sunt:
	-'InsOrdS': introduce ordonat un element intr-o stiva folosint combinatii de functii de baza;
	-'InsOrdQ': introduce ordonat un element intr-o coada folosind combinatii de functii de baza;
	-'transform': transfoma o adresa IPv4 intr-un numar de tip unsigned;
	-'InitStive': initializeaza un vector de stive;
	-'AfiElem': ajuta la afisarea tuturor campurilor unei structuri de tip TSwitch;
	Functiile principale pe care le-am construit cu rol in rezolvarea temei sunt:
	-'addS': aceasta functie introduce un switch in una din stivelele din vectorul de stive ori in coada. Daca switch-ul trebuie adaugat in vectorul de stive i se va specifica si id-ul stivei in care trebuie adaugat dar si modul;
	-'showSQ': aceasta functia afiseaza cu ajutorul functiei 'AfiElem' toate id-urile switch-urilor din coada si informatiile(id, denumire, adresa) switch-urilor din vectorul de stive;
	-'dell_id': aceasta functia cauta un switch in coada si in vectorul de stive, un switch cu un id dat. Daca switch-ul este gasit acesta este eliminat si este intors prin efect lateral in functie; 
	-'ip_min': aceasta functie afiseaza ip-ul minim din coada. Fiind o coada ordonata crescator se va afisa ip-ul elementului de la inceputul cozii;
	In main am declarat variabilele, am initializat coada si vectorul de stive si deschis cele doua fisiere pentru citire, respectiv scriere. Cat timp exista intructiuni in fisier, citesc intructiunea si apelez functiile principale specifice intructiunii. Pentru 'set' am folosit functiile 'addS', 'dell_id' si 'InsOrdQ'. In cazul in care functia 'dell_id' anunta gasirea si stergea id-ului respectiv, inseram in coada sau in stiva, elementul intors prin efect lateral.
