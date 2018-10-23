#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

/* Functia 'create_ker' creaza un pachet de tip 'min_ker'(structura pachetului e definata
in 'lib.h').*/
min_ker create_ker(unsigned char ln, char sq, char tp, char da[], unsigned short ch) {
    min_ker k; 
    char sh = 0x01;
    char mk = 0x0d;
    memcpy(&k.soh, &sh, 1);
    memcpy(&k.len, &ln, 1);
    memcpy(&k.type, &tp, 1);
    memcpy(&k.seq, &sq, 1);
    memcpy(k.data, da, (k.len - 5));
    memcpy(&k.check, &ch, 2);
    memcpy(&k.mark, &mk, 1);
   
    return k;
}

/* Functia 'create_buf' creaza un vector de caractere plecand de la campurile unei structuri
de tip 'min_ker'. */
char* create_buf(min_ker k) {
    int lg = k.len + 2;
    char * buf = (char*)calloc(lg, sizeof(char));
    memcpy(buf, &k.soh, 1);
    memcpy(buf + 1, &k.len, 1);
    memcpy(buf + 2, &k.seq, 1);
    memcpy(buf + 3, &k.type, 1);
    memcpy(buf + 4, &k.data, k.len - 5);
    memcpy(buf + 4 + k.len - 5, &(k.check), 2);
    memcpy(buf + lg - 1, &k.mark, 1);
   
    return buf;
}

/* Functia 'get_crc' creaza un vector de caractere din parametrii primiti si pentru acest
vector calculeaza suma de control. */
unsigned short get_crc(unsigned char a, char b, char c, char d[]) {
    int lg = a - 1;
    char * buf = (char*)calloc(lg, sizeof(char));
    char unu = 0x01;
    memcpy(buf, &unu, 1);
    memcpy(buf + 1, &a, 1);
    memcpy(buf + 2, &b, 1);
    memcpy(buf + 3, &c, 1);
    memcpy(buf + 4, d, a - 5);

    return crc16_ccitt(buf, lg);   

}

/* Functia 'create_data_s' creaza un vector de caractere din parametrii primiti, vector
ce simbolizeaza structura unui pachet de tip 'S'. */
char* create_data_s(char mx, char tm) {
    char* data = (char*)calloc(11, sizeof(char));
    char z = 0x00;
    char d = 0x0d;
    memcpy(data, &mx, 1);
    memcpy(data + 1, &tm, 1);
    memcpy(data + 2, &z, 1);
    memcpy(data + 3, &z, 1);
    memcpy(data + 4, &d, 1);
    memcpy(data + 5, &z, 1);
    memcpy(data + 6, &z, 1);
    memcpy(data + 7, &z, 1);
    memcpy(data + 8, &z, 1);
    memcpy(data + 9, &z, 1);
    memcpy(data + 10, &z, 1);


    return data;
}

/*Functia 'create_buf_vid' creaza un vector de caractere din campurile unei structuri de 
tipul 'min_ker' ignorand campul 'data' al pachetului. */
char* create_buf_vid(min_ker k) {
    char * buf = (char*)calloc(7, sizeof(char));
    memcpy(buf, &k.soh, 1);
    memcpy(buf + 1, &k.len, 1);
    memcpy(buf + 2, &k.seq, 1);
    memcpy(buf + 3, &k.type, 1);
    memcpy(buf + 4, &k.check, 2);
    memcpy(buf + 6, &k.mark, 1);
   
    return buf;
}

int main(int argc, char** argv) {
    msg t;
    init(HOST, PORT);
    int count = 0; 
    //Initializez numarul de secventa.
    char nr_secv = 0x00;
    //Creez un pachet de tip 'S'.
    min_ker s = create_ker(0x10, 0x00, 'S', create_data_s(0xfa, 0x5), get_crc(0x10, 0x00, 'S', create_data_s(0xfa, 0x5)));
    //Creez un vector de caractere din campurile pachetului.
    char * b = create_buf(s);
    t.len = s.len + 2;
    memcpy(t.payload, b, t.len);
    send_message(&t);

    msg *y = receive_message_timeout(5000);
    
    while(count < 3) {
        //Cat timp mesajul este NULL retrimit pachetul.
        if(y == NULL) {
            count ++;        
            send_message(&t);
            y = receive_message_timeout(5000);
        } else {
            //Daca mesajul nu e NULL si pachetul asteptat are tipul 'N', retrimit ultimul pachet cu numarul de secventa actualizat.
            if(y -> payload[3] == 'N'){
                nr_secv += 2;
                nr_secv %= 64;
                min_ker s = create_ker(0x10, nr_secv, 'S', create_data_s(0xfa, 0x5), get_crc(0x10, nr_secv, 'S', create_data_s(0xfa, 0x5)));
                b = create_buf(s);
                t.len = s.len + 2;
                memcpy(t.payload, b, t.len);
                count = 0;       
                send_message(&t);
                y = receive_message_timeout(5000);
            //Daca mesajul nu e NULL si pachetul asteptat are tipul 'Y' actualizez numarul de secventa.
            } else {
                nr_secv += 2;
                nr_secv %= 64;
                count = 0;
                break;
            }
        }
    }

    if(count == 3) {
        printf("S-a primit 3 x TIME-OUT via SENDER!\n");
        return -1;
    }

    int i;
    //Pentru fiecare fisier voi executa urmatoarele operatii.
    for(i = 1; i < argc; i ++) {
        char * nume = argv[i];
        int fl;
        fl = open(nume, O_RDONLY);
        
        if(fl < 0) {
            printf("A aparut o EROARE la deschiderea fisierului pentru citire via SENDER!\n");
            return -1;
        }     
        //Creez un pachet de tip 'F' cu campul data setat cu numele fisierului.
        s = create_ker(5 + strlen(nume), nr_secv, 'F', nume, get_crc(5 + strlen(nume), nr_secv, 'F', nume));
        //Creez un vector de caractere cu campurile structurii respective.
        b = create_buf(s);
        t.len = s.len + 2;
        memcpy(t.payload, b, t.len);
        send_message(&t); 

        y = receive_message_timeout(5000);
    
        while(count < 3) {
            //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet. 
            if(y == NULL || (y -> payload[2] + 1) % 64 == nr_secv) {

                if(y == NULL)
                    count ++;
                else
                    count = 0;        
                send_message(&t);
                y = receive_message_timeout(5000);
            } else { 
                //Daca mesajul nu e NULL si pachetul asteptat are tipul 'N' retrimit ultimul pachet cu numar de secventa actualizat.     
                if(y -> payload[3] == 'N') {
                    nr_secv += 2;
                    nr_secv %= 64;
                    s = create_ker(5 + strlen(nume), nr_secv, 'F', nume, get_crc(5 + strlen(nume), nr_secv, 'F', nume));
                    b = create_buf(s);
                    t.len = s.len + 2;
                    memcpy(t.payload, b, t.len);
            
                    count = 0; 
       
                    send_message(&t);
                    y = receive_message_timeout(5000);
                //Daca mesajul nu e NULL si pachetul asteptat are tipul 'Y' actualizez numarul de secventa.    
                } else{
                    nr_secv += 2;
                    nr_secv %= 64;
                    count = 0;
                    break;
                }
            }
        }

        if(count == 3) {
            printf("S-a primit 3 x TIME-OUT via SENDER!\n");
            return -1;
        } 
            
        //Initializez un vector de caractere in care voi citi din fisier cu 250(dimensiunea data de maxl).
        char buf[250];
        unsigned char dim;
        memset(buf, 0, sizeof(buf));
        //Citesc din fisier.
        int p = read(fl, buf, sizeof(buf));
        //In cazul in care nu am ce citi sau din anumite motive nu se poate executa citirea, afisez un mesaj corespunzator.
        if(p <= 0)
            printf("A aparut o EROARE la citirea din fisier via SENDER!\n");

        dim = (unsigned char)p;
        memset(s.data, 0, s.len - 5);
        //Creez un pachet de tip 'D' cu campul data setat cu vectorul de caractere citit anterior.
        s = create_ker((unsigned char)(dim + 5), nr_secv, 'D', buf, get_crc((unsigned char)(dim + 5), nr_secv, 'D', buf));
        memset(b, 0, t.len);
        //Creez un vector de caractere cu campurile structurii anterioare.
        b = create_buf(s);
        t.len = (unsigned char)s.len + 2;
        memset(t.payload, 0, t.len);
        memcpy(t.payload, b, t.len);
        
        send_message(&t);
        y = receive_message_timeout(5000);
        //Voi executa acest 'while' cat timp se poate citi din fisier.
        while(1) {

            while(count < 3) {
                //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet.
                if(y == NULL || (y -> payload[2] + 1) % 64 == nr_secv){

                    if(y == NULL)
                        count ++;
                  else
                        count = 0;
                    
                    send_message(&t);  
                    y = receive_message_timeout(5000);
                } else {
                     //Daca mesajul nu e NULL si pachetul asteptat are tipul 'N' retrimit ultimul pachet cu numar de secventa actualizat.
                    if(y -> payload[3] == 'N'){
                        count = 0; 
                        nr_secv += 2;
                        nr_secv %= 64;
                        memset(s.data, 0, s.len - 5);
                        s = create_ker(5 + dim, nr_secv, 'D', buf, get_crc(5 + dim, nr_secv, 'D', buf));
                        memset(b, 0, t.len);
                        b = create_buf(s);
                        t.len = (unsigned char)s.len + 2; 
                        memset(t.payload, 0, t.len);
                        memcpy(t.payload, b, t.len);     
                        send_message(&t);
                        y = receive_message_timeout(5000);
                    } else {
                        /*Daca mesajul nu e NULL si pachetul asteptat are tipul 'Y' actualizez numarul de secventa, citesc
                        din fisier urmatorul vector de caracter si creez un nou pached de tip 'D' pe care il trimit. */
                        nr_secv += 2;
                        nr_secv %= 64;
                        count = 0;
                        memset(buf, 0, p);
                        p = read(fl, buf, sizeof(buf));
                        
                        if(p <= 0)
                            break;
                        
                        dim = (unsigned char)p;
                        memset(s.data, 0, s.len - 5);
                        s = create_ker(5 + dim, nr_secv, 'D', buf, get_crc(5 + dim, nr_secv, 'D', buf));
                        memset(b, 0, t.len);
                        b = create_buf(s);
                        t.len = (unsigned char)s.len + 2;
                        memset(t.payload, 0, t.len);
                        memcpy(t.payload, b, t.len);
                        send_message(&t); 
                        y = receive_message_timeout(5000);
                
                    }
                }
            }

            if(count == 3) {
                printf("S-a primit 3 x TIME-OUT via SENDER!\n");
                close(fl);
                return -1;
            } else {
                break;
            }
        }
        
        //Creez un pachet de tipul 'Z'.
        s = create_ker(5, nr_secv, 'Z', "", get_crc(5, nr_secv, 'Z', ""));
        //Creez un vector de caractere cu campurile pachetului creat anterior(campul data este vid).
        b = create_buf_vid(s);
        t.len = 7;
        memcpy(t.payload, b, t.len);
        send_message(&t); 
        y = receive_message_timeout(5000);
        //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet. 
        while(count < 3) {
            if(y == NULL || (y -> payload[2] + 1) % 64 == nr_secv){
                if(y == NULL)
                    count ++;
                else
                    count = 0;        
                send_message(&t);
                y = receive_message_timeout(5000);
            } else {  
                //Daca mesajul nu e NULL si pachetul asteptat are tipul 'N' retrimit ultimul pachet cu numar de secventa actualizat.
                if(y -> payload[3] == 'N') {
                    nr_secv += 2;
                    nr_secv %= 64;
                    s = create_ker(5, nr_secv, 'Z', "", get_crc(5, nr_secv, 'Z', ""));
                    b = create_buf_vid(s);
                    t.len = 7;
                    memcpy(t.payload, b, t.len);
                    send_message(&t); 
                    count = 0; 
                    send_message(&t);
                    y = receive_message_timeout(5000);
                //Daca mesajul nu e NULL si pachetul asteptat are tipul 'Y' actualizez numarul de secventa.   
                } else {
                    nr_secv += 2;
                    nr_secv %= 64;
                    count = 0;
                    break;
                }
            }
        }

        if(count == 3) {
            printf("S-a primit 3 x TIME-OUT via SENDER!\n");
            return -1;
        } 
        //Inchid fisierul din care am citit.
        close(fl);
    }    
    //Creez un pachet de tip 'B'.
    s = create_ker(5, nr_secv, 'B', "", get_crc(5, nr_secv, 'B', ""));
    //Creez un vector de caractere cu campurile pachetului anterior.
    b = create_buf_vid(s);
    t.len = 7;
    memcpy(t.payload, b, t.len);
    send_message(&t); 
    y = receive_message_timeout(5000);
    //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet. 
    while(count < 3){
        if(y == NULL || (y -> payload[2] + 1) % 64 == nr_secv){
            if(y == NULL)
                count ++;
            else
                count = 0;        
            send_message(&t);
            y = receive_message_timeout(5000);
            //Daca mesajul nu e NULL si pachetul asteptat are tipul 'N' retrimit ultimul pachet cu numar de secventa actualizat.
        } else {      
            if(y -> payload[3] == 'N') {
                nr_secv += 2;
                nr_secv %= 64;
                s = create_ker(5, nr_secv, 'B', "", get_crc(5, nr_secv, 'B', ""));
                b = create_buf_vid(s);
                t.len = 7;
                memcpy(t.payload, b, t.len);
                send_message(&t); 
                count = 0; 
                send_message(&t);
                y = receive_message_timeout(5000);
            //Daca mesajul nu e NULL si pachetul asteptat are tipul 'Y' actualizez numarul de secventa.     
            } else{
                printf("Inchid transmisia via SENDER!\n");
                fflush(stdout);
                return 0;
            }
        }
    }

    if(count == 3) {
            printf("S-a primit 3 x TIME-OUT via SENDER!\n");
            return -1;
        } 

    return 0;
   
}
