#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

/* Functia 'create_ker_from_payload' creeaza o structura de tip 'min_ker'(pachet) din 
payload-ul primit. */
min_ker create_ker_from_payload(char payload[]) {
    min_ker k;
    
    memcpy(&k.soh, payload, 1);
    memcpy(&k.len, payload + 1, 1);
    memcpy(&k.seq, payload + 2, 1);
    memcpy(&k.type, payload + 3, 1); 
    memcpy(k.data, payload + 4, k.len - 5);
    memcpy(&(k.check), payload + k.len - 1, 2);
    memcpy(&k.mark, payload + k.len + 1, 1);
   
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
    memcpy(buf + 4, k.data, k.len - 5);
    memcpy(buf + lg - 3, &k.check, 2);
    memcpy(buf + lg - 1, &k.mark, 1);
  
    return buf;
}

/*Functia 'create_buf_ak' creaza un vector de caractere din campurile unei structuri de 
tipul 'min_ker' ignorand campul 'data' al pachetului. */
char* create_buf_ak(min_ker k) {
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
    msg *r, t;
    min_ker k;
    char *buf; 
    int count = 0;
    //Initializez numarul de secventa 
    char nr_secv= 0x01;
    init(HOST, PORT);
    r = receive_message_timeout(5000);
    //Astept primirea unui mesaj de maxim trei ori.
    while(count < 3) {
        if(r == NULL) {
            count ++;
            r = receive_message_timeout(5000);
        //Daca mesajul nu e NULL, creez o structura de tip 'min_ker' din payload.
        } else {
            count = 0;
            k = create_ker_from_payload(r -> payload);
            //Daca pachetul e corupt, voi creea un pachet de tip 'N' cu numar de secventa actualizat si il voi trimite.
            if(k.check != crc16_ccitt(r -> payload, r -> len - 3)) {
                k.type = 'N';
                k.seq = nr_secv;
                nr_secv += 2;
                nr_secv %= 64;
                buf = create_buf_ak(k);
                t.len = 7;
                memcpy(t.payload, buf, t.len);
                send_message(&t);
                r = receive_message_timeout(5000); 
            } else {
                //Daca pachetul nu e corupt, voi creea un pachet de tip 'Y' cu numar de secventa actualizat si il voi trimite.
                k.type = 'Y';
                k.seq = nr_secv;
                nr_secv += 2;
                nr_secv %= 64;
                buf = create_buf(k);
                t.len = k.len + 2;
                memcpy(t.payload, buf, t.len);
                send_message(&t);
                break;
            }
        }
    }

    if(count == 3) {
        printf("S-a primit 3 x TIME-OUT via RECEIVER!\n");
        return -1;
    } 

    r = receive_message_timeout(5000);
    
    while(count < 3) {
        //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet. 
        if(r == NULL || (r -> payload[2] +1) % 64 != nr_secv) {
            if(r == NULL)
                count ++;
            else
                count = 0;
            send_message(&t);
            r = receive_message_timeout(5000);
        } else {
            //Daca mesajul nu e NULL, creez o structura de tip 'min_ker' din payload.
            count = 0;
            k = create_ker_from_payload(r -> payload);
            if(k.check != crc16_ccitt(r -> payload, r -> len - 3)) {
                //Daca pachetul e corupt, voi creea un pachet de tip 'N' cu numar de secventa actualizat si il voi trimite.
                k.type = 'N';
                k.seq = nr_secv;
                nr_secv += 2;
                nr_secv %= 64;
                buf = create_buf_ak(k);
                t.len = k.len + 2;
                memcpy(t.payload, buf, t.len);
                send_message(&t);
                r = receive_message_timeout(5000); 
            } else {
                //Daca pachetul nu e corupt, voi creea un pachet de tip 'Y' cu numar de secventa actualizat si il voi trimite.
                k.type = 'Y';
                k.seq = nr_secv;
                nr_secv += 2;
                nr_secv %= 64;
                buf = create_buf_ak(k);
                t.len = 7;
                memcpy(t.payload, buf, t.len);
                send_message(&t);
                break;
            }
        }
    }

    if(count == 3) {
        printf("S-a primit 3 x TIME-OUT via RECEIVER!\n");
        return -1;
    } 

    //Voi executa acest 'while' pentru fiecare fisier care trebuie trimis.
    while(1) {
        int fid;
        //Creez si deschid fisierul in care urmeaza sa scriu date.
        char file_out[250] = "recv_\0"; 
        strcat(file_out, k.data);
        fid = open(file_out, O_WRONLY | O_CREAT, 0644);
        
        if(fid < 0) {
            printf("A aparut o EROARE la deschiderea fisierului pentru scriere via RECEIVER!\n");
            return -1;
        }

        memset(r -> payload, 0, r -> len);
        r = receive_message_timeout(5000);
        int dim, zok = 0;
        while(1) {  
            while(count < 3) { 
            //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet.     
                if(r == NULL || (r -> payload[2] +1) % 64 != nr_secv) {
                    if(r == NULL)
                        count ++;
                    else
                        count = 0;
                    send_message(&t);
                    r = receive_message_timeout(5000);
                //Daca mesajul nu e NULL, creez o structura de tip 'min_ker' din payload.
                } else {       
                    count = 0;
                    memset(&k.data, 0, k.len - 5);
                    k = create_ker_from_payload(r -> payload);
                    //Daca pachetul e corupt, voi creea un pachet de tip 'N' cu numar de secventa actualizat si il voi trimite.
                    if(k.check != crc16_ccitt(r -> payload, r -> len - 3)) {
                        k.type = 'N';
                        k.seq = nr_secv;
                        nr_secv += 2;
                        nr_secv %= 64;
                        memset(buf, 0, 7);
                        buf = create_buf_ak(k);
                        memset(t.payload, 0, 7);
                        memcpy(t.payload, buf, 7);
                        send_message(&t);
                        r = receive_message_timeout(5000); 
                    } else {
                        //Daca tipul pachetului este 'Z' inseamna ca s-au transmis toate datele dintr-un fisier si il pot inchide.
                        if(k.type == 'Z') {
                            k.type = 'Y';
                            k.seq = nr_secv;
                            nr_secv += 2;
                            nr_secv %= 64;
                            memset(buf, 0, 7);
                            buf = create_buf_ak(k);
                            memset(t.payload, 0, 7);
                            memcpy(t.payload, buf, 7);
                            send_message(&t);
                            zok = 1;
                        
                            break;
                        }
                        /*Daca tipul pachetului este in continuare 'D', scriu datele in fisier si  creez un pachet 
                        de tip 'Y' cu numar de secventa actualizat si il trimit. */
                        dim = write(fid, k.data, k.len - 5);
                        
                        if(dim < 0)
                            printf("A aparut o EROARE la scrierea in fisier via RECEIVER!\n");
                        k.type = 'Y';
                        k.seq = nr_secv;
                        nr_secv += 2;
                        nr_secv %= 64;
                        memset(buf, 0, 7);
                        buf = create_buf_ak(k);
                        memset(t.payload, 0, 7);
                        memcpy(t.payload, buf, 7);
                        send_message(&t);
                        r = receive_message_timeout(5000);
                        break;

                    }
                }
            }
          
            if(count == 3) {
                printf("S-a primit 3 x TIME-OUT via RECEIVER!\n");
                close(fid);
                return -1;
            }

            if(zok == 1)
                break;
        }

        close(fid);
        int bok = 0;
        r = receive_message_timeout(5000);
    
        while(count < 3) {
            //Cat timp mesajul e NULL sau nu e cel asteptat(ca numar de secventa), retrimit ultimul pachet. 
            if(r == NULL || (r -> payload[2] +1) % 64 != nr_secv) {
                if(r == NULL)
                    count ++;
                else
                    count = 0;
                send_message(&t);
                r = receive_message_timeout(5000);
            //Daca mesajul nu e NULL, creez o structura de tip 'min_ker' din payload.   
            } else {
                count = 0;
                k = create_ker_from_payload(r -> payload);
                //Daca pachetul e corupt, voi creea un pachet de tip 'N' cu numar de secventa actualizat si il voi trimite.
                if(k.check != crc16_ccitt(r -> payload, r -> len - 3)){
                    k.type = 'N';
                    k.seq = nr_secv;
                    nr_secv += 2;
                    nr_secv %= 64;
                    buf = create_buf_ak(k);
                    t.len = k.len + 2;
                    memcpy(t.payload, buf, t.len);
                    send_message(&t);
                    r = receive_message_timeout(5000); 
                 /*Daca pachetul nu e corupt si are tipul 'B' voi marca acest lucru, voi crea un pachet de tipul 'Y' cu numar
                 de secventa actualizat si il voi trimite. Daca pachetul este de tip 'B' asta va insemna finalul transmisiei, 
                 in caz contrar va inseamna ca este pached de tip 'F' si voi relua operatiile de deschidere si scriere date in fisier. */   
                } else {
                    if(k.type == 'B')
                        bok = 1;
                    k.type = 'Y';
                    k.seq = nr_secv;
                    nr_secv += 2;
                    nr_secv %= 64;
                    buf = create_buf_ak(k);
                    t.len = 7;
                    memcpy(t.payload, buf, t.len);
                    send_message(&t);

                    break;
                }
            }
        }

        if(count == 3) {
            printf("S-a primit 3 x TIME-OUT via RECEIVER!\n");
            return -1;
        }
    
        if(bok == 1)
            break;
    }    

    printf("Inchid transmisia via RECEIVER!\n");
    return 0;    
          
}
