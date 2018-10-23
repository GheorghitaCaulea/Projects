import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;

public class Stropitori {
    //Metoda 'numara_stropitori' va returna numarul maxim de stropitori;
    public long numara_stropitori(long s[], long p[], long l){
        long count = 0;
        int last;
        //Daca numarul de stropitori este 0, intoarce 0;
        if(s.length == 0)
            return 0;
        //Daca exista o singura stropitoare si aceasta se poate aseza fie la stanga, fie la dreapta, intoarce 1;
        if(s.length == 1 && ((s[0] - p[0]) > 0 || (s[0] + p[0]) < l)) {
            return 1;
        }
        /*Am tratat special prima stropitoare.
        In continuare am folosit pentru 'last' 
        1 -> daca ultima stropitoarea a fost pusa la stanga
        0 -> daca ultima stropitoare a fost pusa la dreapta
        2 -> daca ultima stropitoare a fost blocata;
        */
        if(s[0] - p[0] >= 0) {
            last = 1;
            count ++;
        } else {
            if(s[0] + p[0] < s[1]){
                last = 0;
                count ++;
            } else {
                last = 2;
            }
        }
        
        for(int i = 1; i < s.length - 1; i ++) {
            int sw = 0;
            /*Daca ultima stropitoare a fost pusa la stanga sau blocata, verific daca stropitoarea curenta 
            se incadreaza pana la stropitoarea anterioara. In caz pozitiv o pun la stanga si incrementez contorul */
            if(last == 1 || last == 2) {
                if(s[i] - p[i] > s[i - 1]) {
                    last = 1;
                    count ++;
                    sw = 1;
                }
            }
            /* Daca ultima stropitoare a fost pusa la dreapta, verific daca stropitoarea curenta se incadreaza
            la stanga. In caz pozitiv o pun la stanga si incrementez contorul; */
            if(sw == 0 && last == 0) {
                if((s[i] - p[i]) > (s[i - 1] + p[i - 1])){
                    last = 1;
                    count ++;
                    sw = 1;
                }
            }
            /*Daca stropitoarea curenta nu a putut fi pusa la stanaga verific daca ar putea fi pusa la dreapta. In 
            caz pozitiv o pun l adreapta si incrementez contorul. In caz contrar o blochez; */
            if(sw == 0) {
                if(s[i] + p[i] < s[i + 1]) {
                    last = 0;
                    count ++;
                } else
                    last = 2;
            }
        }
        //Exectut aceiasi verificare si pentru ultima stropitoare;
        if(last == 0 && s[s.length - 1] - p[s.length - 1] > s[s.length - 2] + p[s.length - 2]) {
            count ++;
        } else {
            if((last == 1 || last == 2) && s[s.length - 1] - p[s.length - 1] > s[s.length - 2]) {
                count ++;
            } else {
                if(s[s.length - 1] + p[s.length - 1] <= l) {
                    count ++;
                }
            }   
        }
        return count;
    }
    
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Stropitori strop = new Stropitori();
        //Deschid fisierele pentru citire, respectiv scriere;
        MyScanner sc = new MyScanner("stropitori.in");
        File file_out = new File("stropitori.out");
        Writer write = new FileWriter(file_out);
        /*Citesc numele stadionului si numarul de stropitori si pregatesc doi vectori de dimensiunea
        numarului de stropitori, unul pentru pozitia fiecarei stropitori (s) si unul pentru puterea
        fiecarei stropitori(p); */
        String nume = sc.next_Line();
        int n = sc.next_int();
        long S = sc.next_Long();
        long s[] = new long[n];
        long p[] = new long[n];
        //Citesc din fisier pozitia fiecarei stropitori si puterea fiecarei stropitori;
        for(int i = 0; i < n; i ++) {
            s[i] = sc.next_Long();
        }
        
        for(int i = 0; i < n; i ++) {
            p[i] = sc.next_Long();
        }
        //Scriu rezultatul in fisier si inchid fisierul;
        long count = strop.numara_stropitori(s, p, S);
        write.write(Long.toString(count));
        write.close();
    }
    
}
