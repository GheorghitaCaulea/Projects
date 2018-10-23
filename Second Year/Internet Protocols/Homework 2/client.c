#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

#define BUFLEN 256
//Aceasta functie scrie in fisier rezultatul intors de comanda 'login' in cazul in care aceasta esueaza;
void write_in_log_for_login_fail(FILE *f, long numar_card, int pin) {
    fprintf(f, "login %ld %d\n-2 : Sesiune deja deschisa\n", numar_card, pin);
    printf("-2 : Sesiune deja deschisa\n");
}
//Aceasta functie scrie in fisier rezultatul intors de comanda 'login' in cazul in care aceasta reuseste;
void write_in_log_for_login(FILE *f, long numar_card, int pin, char* buffer) {
    fprintf(f, "login %ld %d\nATM> %s\n", numar_card, pin, buffer);
    printf("ATM> %s\n", buffer);
}
//Aceasta functie scrie in fisier rezultatul intors de comanda 'logout' in cazul in care aceasta reuseste;
void write_in_log_for_logout(FILE *f, char * buffer) {
    fprintf(f, "logout\n%s\n", buffer);
    printf("%s\n", buffer);
}
//Aceasta functie scrie in fisier rezultatul intors de comanda 'listsold' in cazul in care aceasta reuseste;
void write_in_log_for_listsold(FILE *f, char * buffer) {
    fprintf(f, "listsold\n%s\n", buffer);
    printf("%s\n", buffer);
}
//Aceasta functie scrie in fisier rezultatul intors de comanda 'getmoney' in cazul in care aceasta reuseste;
void write_in_log_for_getmoney(FILE *f, char * buffer, char * suma) {
    fprintf(f, "getmoney %s\n%s\n", suma, buffer);
    printf("%s\n", buffer);
}
//Aceasta functie scrie in fisier rezultatul intors de comanda 'putmoney' in cazul in care aceasta reuseste;
void write_in_log_for_putmoney(FILE *f, char * buffer, char * suma) {
    fprintf(f, "putmoney %s\n%s\n", suma, buffer);
    printf("%s\n", buffer);
}

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    //Declar si initializez variabilele de ajutor;
    int sockfd, n, fdmax, sw = 0, pin, cod_comanda, pin_final, d;
    long numar_card, numar_card_final, suma_ceruta;
    char buffer[BUFLEN], *portiune, new_buffer[BUFLEN], file_name[20], id[20], pin_chr[20], nr_card_chr[20], suma[BUFLEN], suma_dep_chr[BUFLEN];
    double suma_depusa;
    struct sockaddr_in serv_addr;
    //Declar multimea de citire si multimea folosita temporar;
    fd_set read_fds;
    fd_set temp_fds;
    //Golesc cele doua multimi;
    FD_ZERO(&read_fds);
    FD_ZERO(&temp_fds);
  
    portiune = (char*)calloc(BUFLEN, sizeof(char));
    //Determin ID-ul procesului si creez numele fisierului de 'log' al clientului;
    d = getpid();
    strcpy(file_name, "client-");
    snprintf(id, BUFLEN, "%d", d);
    strcat(file_name, id);
    strcat(file_name, ".log");
    //Deschid fisierul in vederea scrierii;
    FILE *f = fopen(file_name, "wt");
    //Verific daca numarul argumentelor date este corect, in caz contrar afisez un mesaj de eroare;
    if (argc < 3) {
       fprintf(stderr,"Usage %s server_address server_port\n", argv[0]);
       exit(0);
    }  
    //Obtin descriptorul de fisier pentru TCP;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);

    if (connect(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");  
    //Adaug socketii in multimea de descriptori;
    FD_SET(sockfd, &read_fds);
    FD_SET(0, &read_fds);
    fdmax = sockfd;  
    
    while(1) {
        temp_fds = read_fds;

        if(select(fdmax + 1, &temp_fds, NULL, NULL, NULL) == -1)
            perror("ERROR");

        if(FD_ISSET(0, &temp_fds)) {
            //Setez variabila 'cod_comanda' ce reprezinta faptul ca momentan nu am nicio comanda activa;
            cod_comanda = -1;
            memset(buffer, 0, BUFLEN);
            memset(portiune, 0, BUFLEN);
            //Citesc de la tastarura;
            fgets(buffer, BUFLEN - 1, stdin);
            strcpy(new_buffer, buffer);
            //Parsez buffer-ul citit in vederea clarificarii comenzii primite;
            if(strncmp(buffer, "quit", 4) == 0) {
                strcpy(portiune, buffer);
            } else {
                portiune = strtok(buffer, " ");
            }
            //Daca am o comanda 'login' si am deja o sesiune deschisa, afisez un mesaj corespunzator;
            if(strcmp(portiune, "login") == 0) {
                if(sw == 1) { 
                    write_in_log_for_login_fail(f, numar_card, pin);
                } else {
                    /*Daca nu am nico sesiune deschisa deja, salvez numarul de card si pin-ul si trimit bufferul citit 
                    initial catre server;*/
                    cod_comanda = 1;
                    portiune = strtok(NULL, " ");
                    numar_card = atol(portiune);
                    portiune = strtok(NULL, " ");
                    pin = atoi(portiune);
                    n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                }    
            }
            /*Daca am o comanda 'quit', trimit serverului un mesaj prin care il anunt de inchidere, scriu in fisier mesajul
            corespunzator comenzii, inchid sochetul, inchid fisierul de 'log' si inchid programul; */
            if(strncmp(portiune, "quit", 4) == 0) {
                memset(new_buffer, 0, BUFLEN);
                snprintf(pin_chr, BUFLEN, "%d", pin_final);
                snprintf(nr_card_chr, BUFLEN, "%ld", numar_card_final);
                strcpy(new_buffer, "quit ");
                strcat(new_buffer, nr_card_chr);
                strcat(new_buffer, " ");
                strcat(new_buffer, pin_chr);
                n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                fprintf(f, "quit");
                close(sockfd);
                fclose(f);
                return 0;
            }
            //Daca am o comanda 'logout' si nu am nicio sesiune deschisa, scriu in fisier un mesaj corespunzator;
            if(strncmp(portiune, "logout", 6) == 0) {
                if(sw == 0) {
                    fprintf(f, "-1 : Clientul nu este autentificat\n");
                    printf("-1 : Clientul nu este autentificat\n");
                } else {
                    /*Daca exista o sesiune deschisa, setez codul comenzii si creez un mesaj corespunzator pe care
                    il trimit serverului, mesaj care va ajuta serverul la identificarea utilizatorului care doreste
                    aceasta comanda(atasez numarul cardului si pin-ul); */
                    sw = 0;
                    cod_comanda = 2;
                    memset(new_buffer, 0, BUFLEN);
                    snprintf(pin_chr, BUFLEN, "%d", pin_final);
                    snprintf(nr_card_chr, BUFLEN, "%ld", numar_card_final);
                    strcpy(new_buffer, "logout ");
                    strcat(new_buffer, nr_card_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, pin_chr);
                    n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                }            
            }
            //Daca am o comanda 'listsold' si nu am nicio sesiune deschisa, scriu in fisier un mesaj corespunzator;
            if(strncmp(portiune, "listsold", 8) == 0) {
                if(sw == 0){
                    fprintf(f, "-1 : Clientul nu este autentificat\n");
                    printf("-1 : Clientul nu este autentificat\n");
                } else {
                    /*Daca exista o sesiune deschisa, setez codul comenzii si creez un mesaj corespunzator pe care
                    il trimit serverului, mesaj care va ajuta serverul la identificarea utilizatorului care doreste
                    aceasta comanda(atasez numarul cardului si pin-ul); */
                    cod_comanda = 3;
                    memset(new_buffer, 0, BUFLEN);
                    snprintf(pin_chr, BUFLEN, "%d", pin_final);
                    snprintf(nr_card_chr, BUFLEN, "%ld", numar_card_final);
                    strcpy(new_buffer, "listsold ");
                    strcat(new_buffer, nr_card_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, pin_chr);
                    n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                }
            }
            //Daca am o comanda 'getmoney' si nu am nicio sesiune deschisa, scriu in fisier un mesaj corespunzator;
            if(strncmp(portiune, "getmoney", 8) == 0) {
                if(sw == 0) {
                    fprintf(f, "-1 : Clientul nu este autentificat\n");
                    printf("-1 : Clientul nu este autentificat\n");
                } else {
                    /*Daca exista o sesiune deschisa, setez codul comenzii si creez un mesaj corespunzator pe care
                    il trimit serverului, mesaj care va ajuta serverul la identificarea utilizatorului care doreste
                    aceasta comanda(atasez numarul cardului si pin-ul) si la aflarea sumei care se doreste a fi 
                    retrasa; */
                    cod_comanda = 4;
                    portiune = strtok(NULL, " ");
                    suma_ceruta = atol(portiune);
                    memset(new_buffer, 0, BUFLEN);
                    snprintf(pin_chr, BUFLEN, "%d", pin_final);
                    snprintf(nr_card_chr, BUFLEN, "%ld", numar_card_final);
                    strcpy(new_buffer, "getmoney ");
                    strcat(new_buffer, nr_card_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, pin_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, portiune);
                    n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                    if(n < 0) {
                        printf("ERROR\n");
                    }
                }
            }
            //Daca am o comanda 'getmoney' si nu am nicio sesiune deschisa, scriu in fisier un mesaj corespunzator;
            if(strcmp(portiune, "putmoney") == 0) {
                if(sw == 0) {
                    fprintf(f, "-1 : Clientul nu este autentificat\n");
                    printf("-1 : Clientul nu este autentificat\n");
                } else {
                    /*Daca exista o sesiune deschisa, setez codul comenzii si creez un mesaj corespunzator pe care
                    il trimit serverului, mesaj care va ajuta serverul la identificarea utilizatorului care doreste
                    aceasta comanda(atasez numarul cardului si pin-ul) si la aflarea sumei care se doreste a fi 
                    retrasa; */
                    cod_comanda = 5;
                    portiune = strtok(NULL, " ");
                    suma_depusa = atof(portiune);
                    memset(new_buffer, 0, BUFLEN);
                    snprintf(pin_chr, BUFLEN, "%d", pin_final);
                    snprintf(nr_card_chr, BUFLEN, "%ld", numar_card_final);
                    strcpy(new_buffer, "putmoney ");
                    strcat(new_buffer, nr_card_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, pin_chr);
                    strcat(new_buffer, " ");
                    strcat(new_buffer, portiune);
                    n = send(sockfd, new_buffer, strlen(new_buffer), 0);
                }    
            }
        } 
        //Tratez cazul in care primesc un mesaj pe socket;    
        if(FD_ISSET(sockfd, &temp_fds)) {
            memset(buffer, 0, BUFLEN);
            n = recv(sockfd, buffer, 255, 0);
            /*In cazul in care codul comenzii corespunde comenzii 'login', daca raspunsul serverului reprezinta
            faptul ca s-a reusit logarea, retin valorile pentru numar card si pin(valori valide corespunzatoare
            deschiderii sesiunii curente, valori pe care le folosesc pentru a le trimite catre server pentru restul
            comenzilor), scriu in fisier mesajul corespunzator si schimb codul comenzii; */
            if(cod_comanda == 1) {
                strcpy(new_buffer, buffer);
                portiune = strtok(new_buffer, " ");
                if(strcmp(portiune, "Welcome") == 0) {
                    numar_card_final = numar_card;
                    pin_final = pin;
                    sw = 1;
                }
                write_in_log_for_login(f, numar_card, pin, buffer);
                cod_comanda = -1;
            }
            //Daca mesajul reprezinta faptul ca serverul opreste conexiunea, inchid socketul, fisierul de 'log' si programul;
            if(strcmp(buffer, "ATM> Serverul opreste conexiunea") == 0) {
                close(sockfd);
                fclose(f);
                return 0;
            }
            /*In cazul in care codul comenzii corespunde comenzii 'logout', scriu in fisier raspunsul serverului si schimb
            codul comenzii; */
            if(cod_comanda == 2) {
                write_in_log_for_logout(f, buffer);
                cod_comanda = -1;
            } 
            /*In cazul in care codul comenzii corespunde comenzii 'listsold', scriu in fisier raspunsul serverului si schimb
            codul comenzii; */
            if(cod_comanda == 3) {
                write_in_log_for_listsold(f, buffer);
                cod_comanda = -1;
            } 
            /*In cazul in care codul comenzii corespunde comenzii 'getmoney', scriu in fisier raspunsul serverului si schimb
            codul comenzii; */
            if(cod_comanda == 4) {
                snprintf(suma, BUFLEN, "%ld", suma_ceruta);
                write_in_log_for_getmoney(f, buffer, suma);
                cod_comanda = -1;  
            }
            /*In cazul in care codul comenzii corespunde comenzii 'putmoney', scriu in fisier raspunsul serverului si schimb
            codul comenzii; */
            if(cod_comanda == 5) {
                snprintf(suma_dep_chr, BUFLEN, "%.2lf", suma_depusa);
                write_in_log_for_putmoney(f, buffer, suma_dep_chr);
                cod_comanda = -1; 
            }
        }
    }        
    fclose(f);    
    return 0;
}