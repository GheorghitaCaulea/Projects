Student: CAULEA Gheorghita
Grupa: 314 CB
Punctaj obtinut: 85/85
Masina virtuala: Ubuntu 15.10 32 bit

	In inceputul temei am definit tipurile necesare pentru rezolvarea cerintei si cateva macrodefinitii. Am construit o serie de functii de baza: AlocCel, InitQ, IntrQ, ExtrQ, functii care au ajutat la lucrul cu cozi. Functiile secundare pe care le am contruit sunt:
	-'ConstrFr': contruieste o frunza pentru un arbore cu calea si caracterul date.
	-'InitArb': initializeaza un arbore.
	-'AfiArb': afiseaza un arbore pe nivele. Pentru a putea accesa nivelurile unui arbore am folosit o coada in care am introdus initial fiii radacinei; extragand pe rand din coaza acei fii, si adugand la momentul respectiv fiii fiilor, am putut accesa in intregime arborele.
	-'decodificare': decodifica o cale intorcand caracterul de la capatul acelei cai.
	Functiile principale care au dus la rezolvarea cerintei sunt:
	-'add': se da ca parametru calea, caracterul si arborele. Veric daca mai exista pana la acel moment in arbore un nod cu acea cale, in caz contrar contruiesc o frunza noua si realoc vectorul de fii pentru nodul parinte.
	-'delete': se da ca parametru caracterul si arborele. Cu ajutorul accesului pe care coada il ofera(identic cu ce se face la afisare), identific nodul cu caracterul de interes. Dupa identificare merg in sus in arbore, din parinte in parinte si eliberez sau realoc memoria.
	In main aloc memorie pentru variabilele cu urmeaza a fi folosite, initializez arborele si deschid cele patru fisiere. Construiesc arborele initial iar apoi aplic in functie de ce se afla in fisier, respectivele operatii. Scriu arborele intr-un fisier. Pentru decodificare citesc frazele din fisierul de intrare si le sparg in cai de acces catre caractere cu ajutorul functiei 'strtok'. Decodific caile si le scriu in fisier. Eliberez memoria alocata si inchid fisierele 
