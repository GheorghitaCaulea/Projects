#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS	100
#define BUFLEN 256

//Creez o structura de tipul 'CLIENT' pentru a putea retine toate detaliile clientilor;
typedef struct {
	char nume[13];
	char prenume[13];
	long numar_card;
	int pin;
	char parola_secrete[17];
	double sold;
	int open;
	int blocat;
	int try;
} CLIENT;

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    //Declar si initializez variabile de ajutor;
    int sockfd, newsockfd, portno, n, i, j, nr_clienti, clt_connect[250];
    socklen_t clilen;
    char buffer[BUFLEN], *portiune, *msg, *sold_chr;
    struct sockaddr_in serv_addr, cli_addr;
    CLIENT *clt;
    //Deschid fisierul in scopul citirii informatiilor despre clienti;
    FILE *f = fopen(argv[2], "rt");
    //Citesc numarul clientilor;
    fscanf(f, "%d", &nr_clienti);
    //Aloc un vector de clienti;
    clt = (CLIENT*)calloc(nr_clienti, sizeof(CLIENT));
    //Pentru fiecare client citesc din fisier campurile si le initializez;
    for(i = 0; i < nr_clienti; i ++) {
    	fscanf(f, "%s%s%ld%d%s%lf", clt[i].nume, clt[i].prenume, &clt[i].numar_card, &clt[i].pin, clt[i].parola_secrete, &clt[i].sold);
    	clt[i].open = 0;
    	clt[i].blocat = 0;
    	clt[i].try = 0;
    }
    for(i = 0; i < 250; i ++) {
    	clt_connect[i] = 0;
    }
    //Inchid fisierul;
    fclose(f);
    //Aloc variabile de tipul 'char*' ce ma vor ajuta mai departe la lucrul pe siruri de caractere;
    portiune = (char*)calloc(BUFLEN, sizeof(char));
    msg = (char*)calloc(BUFLEN, sizeof(char));
    sold_chr = (char*)calloc(BUFLEN, sizeof(char));
    //Declar multimea de citire si multimea folosita temporar;
    fd_set read_fds;
    fd_set tmp_fds;	
    int fdmax;	
    //Verific daca numarul argumentelor date este corect, in caz contrar afisez un mesaj de eroare;
    if (argc < 2) {
        fprintf(stderr,"Usage : %s port\n", argv[0]);
        exit(1);
    }

    //Golesc cele doua multimi;
    FD_ZERO(&read_fds);
    FD_ZERO(&tmp_fds);
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR opening socket");
     
    portno = atoi(argv[1]);

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;	
    serv_addr.sin_port = htons(portno);
     
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) < 0) 
        error("ERROR on binding");
     
    listen(sockfd, MAX_CLIENTS);

    //Adaug socketii in multimea de descriptori;
    FD_SET(0, &read_fds);
    FD_SET(sockfd, &read_fds);
    fdmax = sockfd;

	while (1) {
		tmp_fds = read_fds; 
		
		if (select(fdmax + 1, &tmp_fds, NULL, NULL, NULL) == -1) 
			error("ERROR in select");
	
		for(i = 1; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
			
				if (i == sockfd) {
					//A venit ceva pe socketul inactiv;
					clilen = sizeof(cli_addr);
					if ((newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) == -1) {
						error("ERROR in accept");
					} else {
						//Adaug noul socket la multimea descriptorilor de citire;
						//Adaug noul socket in vectorul de socketi activi pentru a sti ce socketi trebuie sa inchid la 'quit';
						clt_connect[newsockfd] = 1;
						FD_SET(newsockfd, &read_fds);
						if (newsockfd > fdmax) { 
							fdmax = newsockfd;
						}
					}
					printf("Noua conexiune de la %s, port %d, socket_client %d\n ", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), newsockfd);
				} else {
					//Am primit date pe unul din socketii cu care vorbesc cu clientii;
					memset(buffer, 0, BUFLEN);
					if ((n = recv(i, buffer, sizeof(buffer), 0)) <= 0) {
						if (n == 0) {
							//Conexiunea s-a inchis;
							printf("selectserver: socket %d hung up\n", i);
						} else {
							error("ERROR in recv");
						}
						//Scot socketul din multimea de citire;
						close(i); 
						FD_CLR(i, &read_fds); 
					} else {
						//Daca am primit ceva prin 'recv', parsez bufferul primit in vederea obtinerii comenzii primite;
						int sw = 0;
						portiune = strtok(buffer, " ");
						/*Daca am primit comanda 'login', parsez si numarul de card si pin-ul din buffer; */
						if(strcmp(portiune, "login") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							for(j = 0; j < nr_clienti; j ++) {
								if(clt[j].numar_card == nr_card && clt[j].blocat == 0 && clt[j].open == 0) {
									/*Daca reprezinta un set de credentiale corecte, marchez sesiunea clientului ca deschisa, 
									si numarul de incercari de introducere pin esuate ia valoarea din nou '0'; */
									//Voi transmite catre client un mesaj ce contine numele si prenumele clientului deschis;
									if(clt[j].pin == pin) {
										sw = 1;
										clt[j].try = 0;
										clt[j].open = 1;
										strcpy(msg, "Welcome ");
										strcat(msg, clt[j].nume);
										strcat(msg, " ");
										strcat(msg, clt[j].prenume);
										send(i, msg, strlen(msg), 0);
									} else {
										/*Daca credentialele nu sunt corecte si numarul de incercari actual este 2, marchez 
										numarul cardului ca blocat si retransmit un mesaj corespunzator; */
										if(clt[j].try == 2) {
											sw = 1;
											clt[j].blocat = 1;
											send(i, "-5 : Card blocat", 16, 0);
										/* Altfel inseamna ca am gresit pin-ul, cresc numarul de incercari esuate si retransmit un
										mesaj corespunzator; */
										} else {
											sw = 1;
											clt[j].try ++;
											send(i, "-3 : Pin gresit", 15, 0);
										}
									}
								} else {
									if(clt[j].numar_card == nr_card && clt[j].blocat == 1 && sw == 0) {
										sw = 1;
										send(i, "-5 : Card blocat", 16, 0);
										break;
									}
									/* Daca voi se incearca autentificarea pe un alt terminal iar sesiunea pentru respectivul client 
									este deja deschisa, se afiseaza un mesaj corespunzator; */
									if(clt[j].numar_card == nr_card && clt[j].open == 1 && sw == 0) {
										sw = 1;
										send(i, "-2 : Sesiune deja deschisa", 26, 0);
										break;
									}
								}
							}
							/*Daca nu s-a gasit in vectorul de clienti un client cu numarul de card transmis, se afiseaza un mesaj 
							corespunzator; */
							if(j == nr_clienti && sw == 0) {
								send(i, "-4 : Numar card inexistent", 26, 0);
							}
						}
						/* Daca se primeste o comanda 'quit', se verifica daca respectivul client a fost autentificat pana la acel
						moment, in caz pozitiv se 'delogheaza' din server, si i se va scoate descriptorul din lista de descriptori; */
						if(strcmp(portiune, "quit") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							for(j = 0; j < nr_clienti; j ++) {
								if(clt[j].numar_card == nr_card && clt[j].pin == pin && clt[j].open == 1) {
									clt[j].open = 0;
								}
							}
							clt_connect[i] = 0;
							FD_CLR(i, &read_fds);
							close(i); 
						}
						/* Daca se primeste o comanda 'logout', se cauta clientul in lista de clienti potrivit numarului de card
						si pin-ului si se declara sesiune inchisa pentru acel client. Se trimite un mesaj corespunzator; */
						if(strcmp(portiune, "logout") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							for(j = 0; j < nr_clienti; j ++) {
								if(clt[j].numar_card == nr_card && clt[j].pin == pin && clt[j].open == 1) {
									clt[j].open = 0;
									send(i, "ATM> Deconectare de la bancomat", 31, 0);
								}
							}		 
						}
						/* Daca se primeste o comanda 'listsold', se cauta clientul in lista de clienti, si se alcatuieste
						un mesaj ce urmeaza a fi transmis corespunzator tipului comenzii; */
						if(strcmp(portiune, "listsold") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							for(j = 0; j < nr_clienti; j ++) {
								if(clt[j].numar_card == nr_card && clt[j].pin == pin) {
									snprintf(sold_chr, BUFLEN, "%.2lf", clt[j].sold);
									strcpy(msg, "ATM> ");
									strcat(msg, sold_chr);
									send(i, msg, strlen(msg), 0);
								}
							}			
						}
						/*Daca se primeste o comanda 'getmoney', se cauta clientul in lista de clienti si se verifica daca
						operatiunea se poate sau nu efectua. Se raspunde cu un mesaj corespunzator; */
						if(strcmp(portiune, "getmoney") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							long suma = atol(strtok(NULL, " "));
							if(suma % 10 != 0){
								send(i, "ATM> -9 : Suma nu este multiplu de 10", 37, 0);
							} else {
								for(j = 0; j < nr_clienti; j ++) {
									if(clt[j].numar_card == nr_card && clt[j].pin == pin) {
										if(suma > clt[j].sold) {
											send(i, "ATM> -8 : Fonduri insuficiente", 30, 0);
										} else {
											clt[j].sold -= suma;
											snprintf(sold_chr, BUFLEN, "%ld", suma);
											strcpy(msg, "ATM> Suma ");
											strcat(msg, sold_chr);
											strcat(msg, " retrasa cu succes");
											send(i, msg, strlen(msg), 0);
										}
									}		
								}	
							}			
						}
						/*Daca se primeste o comanda 'putmoney', se cauta clientul in lista de clienti si se efectueaza
						operatiunea. Se raspunde cu un mesaj corespunzator; */
						if(strcmp(portiune, "putmoney") == 0) {
							long nr_card = atol(strtok(NULL, " "));
							int pin = atoi(strtok(NULL, " "));
							double suma = atof(strtok(NULL, " "));
							for(j = 0; j < nr_clienti; j ++) {
								if(clt[j].numar_card == nr_card && clt[j].pin == pin) {
									clt[j].sold += suma;
									send(i, "ATM > Suma depusa cu succes", 27, 0);
								}
							}
						}				
					}
				}
			}
		}
		/* Daca s-a citit de la tastatura o comanda pentru server(pe socketul cu descriptor '0' corespunzator
		stdin) se verifica daca acea comanda este 'quit'. In caz afirmativ, se trimite pe toti descriptorii
		valizi in acel moment un mesaj corespunzator, se extrag din lista de descriptori si se inchide conexiunea; */		
		if(FD_ISSET(0, &tmp_fds)) {
			memset(buffer, 0, BUFLEN);
            fgets(buffer, BUFLEN - 1, stdin); 
            if(strncmp(buffer, "quit", 4) == 0) {
            	for(j = 0; j < 250; j ++) {
            		if(clt_connect[j] == 1) {
            			send(j, "ATM> Serverul opreste conexiunea", 32, 0);
						FD_CLR(j, &read_fds);
						close(j);
            		}
            	}
            	close(sockfd);
    			return 0;
	    	}					
        }
    }
    close(sockfd);
    return 0; 
}