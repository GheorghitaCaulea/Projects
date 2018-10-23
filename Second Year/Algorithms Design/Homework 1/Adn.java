import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.LinkedList;
import java.util.List;

public class Adn {
    
    //Metoda 'fortwo' va trata cazul cu doua siruri;
    public boolean fortwo(String s1, String s2, String rez) {
        int n = s1.length();
        int m = s2.length();
        //Creez un vector de char-uri pentru fiecare sir, inclusiv pentru sirul rezultat;
        char [] s11 = s1.toCharArray();
        char [] s22 = s2.toCharArray();
        char [] rez1 = rez.toCharArray();
        //Creez o matrice de boolean pentru memoizare;
        boolean a[][] = new boolean[n + 1][m + 1];
        
        /*Pe pozitia '[n][m]'' voi pune in matrice 'true' daca lungimea sirului rezultat este  egala cu suma 
        lungimilor celor doua siruri, in caz contrat ma opresc; */
        if((n + m) == rez.length()) 
            a[n][m] = true;
        
        else
            return false;
        
        //Marcurg matricea pe coloane descrescator si pe linii descrescator;
        for(int j = m; j >= 0; j--) {
            for(int i = n; i >= 0; i --) {
                //Verific daca nu sunt pe pozitia '[n][m]', pozitie deja initializata;
                if(i != n || j != m) {
                    //Verific daca sunt in cazul in care i si j nu sunt pe ultima linie, respectiv coloana;
                    if((i + 1) <= n && (j + 1) <= m) {
                        /*Valoarea lui a[i][j] reprezinta faptul ca sirul rezultat a putut fi format pana la momentul anterior
                        si ca la momentul respentiv caracterul de pe pozitia 'i' al primului sir este identic
                        cu caracterul din sirul rezultat de pe pozitia 'i + j' SAU caracterul de pe pozitia 'j' al celui de-al 
                        doilea sir este identic cu caracterul din sirul rezultat de pe pozitia 'i + j'; */
                        a[i][j] = (a[i + 1][j] && s11[i] == rez1[i + j]) || (a[i][j + 1] && s22[j] == rez1[i + j]);
                    } else {
                        //In cazul in care unul din indici se afla pe 'rama' matricii se va verifica doar una dintre conditii;
                        if((i + 1) > n) {
                            a[i][j] = a[i][j + 1] && s22[j] == rez1[i + j];
                        } else {
                            a[i][j] = a[i + 1][j] && s11[i] == rez1[i + j];
                        }
                    }  
                }
            }
        }
        /*Valoarea de adevar de pe pozitia a[0][0] va reprezenta faptul ca sirul rezultat a putut fi creat prin intrepatrunderea
        celor doua siruri; */       
        return a[0][0];    
    }
    //Metoda 'forthree' va trata cazul cu trei siruri;
    public boolean forthree(String s1, String s2, String s3, String rez) {
        int n = s1.length();
        int m = s2.length();
        int o = s3.length();
        //Creez un vector de char-uri pentru fiecare sir, inclusiv pentru sirul rezultat;
        char [] s11 = s1.toCharArray();
        char [] s22 = s2.toCharArray();
        char [] s33 = s3.toCharArray();
        char [] rez1 = rez.toCharArray();
        //Creez o matrice de boolean pentru memoizare;
        boolean a[][][] = new boolean[n + 1][m + 1][o + 1];
        /*Pe pozitia '[n][m][o]'' voi pune in matrice 'true' daca lungimea sirului rezultat este  egala cu suma 
        lungimilor celor trei siruri, in caz contrat ma opresc; */
        if((o + n + m) == rez.length()) {
            a[n][m][o] = true;
        } else {
            return false;
        }
        //Parcurg matricea;
        for(int k = o ; k >= 0; k --) {
            for(int j = m; j >= 0; j--) {
                for(int i = n; i >= 0; i --) {
                    //Verific daca nu sunt pe pozitia '[n][m][o]', pozitie deja initializata;
                    if(i != n || j != m || k != o) {
                        /*Valoarea lui a[i][j][k] reprezinta faptul ca sirul rezultat a putut fi format pana la momentul anterior
                        si ca la momentul respentiv caracterul de pe pozitia 'i' al primului sir este identic
                        cu caracterul din sirul rezultat de pe pozitia 'i + j + k' SAU caracterul de pe pozitia 'j' al celui de-al 
                        doilea sir este identic cu caracterul din sirul rezultat de pe pozitia 'i + j + k' SAU caracterul de pe 
                        pozitia 'k' al celui de-al treilea sir este identic cu caracterul din sirul rezultat de pe pozitia 'i + j + k'; */

                        /* In cazul in care sunt pe 'rama' matricii voi verifica doar pentru situatiile in care nu voi depasi matricea; */
                        if((i + 1) <= n && (j + 1) <= m && (k + 1) <= o) {
                            a[i][j][k] = (a[i + 1][j][k] && s11[i] == rez1[i + j + k]) || 
                            (a[i][j + 1][k] && s22[j] == rez1[i + j + k]) || 
                            (a[i][j][k + 1] && s33[k] == rez1[i + j + k]);
                        }
                        
                        if((i + 1) > n && (j + 1) <= m && (k + 1) <= o) {
                            a[i][j][k] = (a[i][j + 1][k] && s22[j] == rez1[i + j + k]) || 
                            (a[i][j][k + 1] && s33[k] == rez1[i + j + k]);
                        }
                        
                        if((i + 1) > n && (j + 1) > m && (k + 1) <= o) {
                            a[i][j][k] = a[i][j][k + 1] && s33[k] == rez1[i + j + k];
                        }
                        
                        if((i + 1) > n && (j + 1) <= m && (k + 1) > o) {
                            a[i][j][k] = a[i][j + 1][k] && s22[j] == rez1[i + j + k];
                        }
                        
                        if((i + 1) <= n && (j + 1) > m && (k + 1) > o) {
                            a[i][j][k] = a[i + 1][j][k] && s11[i] == rez1[i + j + k];
                        }
                        
                        if((i + 1) <= n && (j + 1) > m && (k + 1) <= o) {
                            a[i][j][k] = (a[i + 1][j][k] && s11[i] == rez1[i + j + k]) || 
                            (a[i][j][k + 1] && s33[k] == rez1[i + j + k]);
                        }
                        
                        if((i + 1) <= n && (j + 1) <= m && (k + 1) > o) {
                            a[i][j][k] = (a[i + 1][j][k] && s11[i] == rez1[i + j + k]) || 
                            (a[i][j + 1][k] && s22[j] == rez1[i + j + k]);
                        }
                    }
                }
            }
        }
        /*Valoarea de adevar de pe pozitia a[0][0][0] va reprezenta faptul ca sirul rezultat a putut fi creat prin intrepatrunderea
        celor trei siruri; */   
        return a[0][0][0];      
    }
    
    //Metoda 'forfour' va trata cazul cu patru siruri;
    public boolean forfour(String s1, String s2, String s3, String s4, String rez) {
        int n = s1.length();
        int m = s2.length();
        int o = s3.length();
        int p = s4.length();
        //Creez un vector de char-uri pentru fiecare sir, inclusiv pentru sirul rezultat;
        char [] s11 = s1.toCharArray();
        char [] s22 = s2.toCharArray();
        char [] s33 = s3.toCharArray();
        char [] s44 = s4.toCharArray();
        char [] rez1 = rez.toCharArray();
        //Creez o matrice de boolean pentru memoizare;
        boolean a[][][][] = new boolean[n + 1][m + 1][o + 1][p + 1];
        /*Pe pozitia '[n][m][o][p]'' voi pune in matrice 'true' daca lungimea sirului rezultat este  egala cu suma 
        lungimilor celor patru siruri, in caz contrat ma opresc; */
        if((p + o + n + m) == rez.length()) {
            a[n][m][o][p] = true;
        } else {
            return false;
        }
        //Parcurg matricea;
        for(int h = p; h >= 0; h --) {
            for(int k = o ; k >= 0; k --) {
                for(int j = m; j >= 0; j--) {
                    for(int i = n; i >= 0; i --) {
                        //Verific daca nu sunt pe pozitia '[n][m][o][p]', pozitie deja initializata;
                        if(i != n || j != m || k != o || h != p) {
                            /*Valoarea lui a[i][j][k][h] reprezinta faptul ca sirul rezultat a putut fi format pana la momentul anterior
                        si ca la momentul respectiv caracterul de pe pozitia 'i' al primului sir este identic cu caracterul din sirul 
                        rezultat de pe pozitia 'i + j + k + h' SAU caracterul de pe pozitia 'j' al celui de-al doilea sir este identic cu 
                        caracterul din sirul rezultat de pe pozitia 'i + j + k + h' SAU caracterul de pe pozitia 'k' al celui de-al treilea 
                        sir este identic cu caracterul din sirul rezultat de pe pozitia 'i + j + k + h' SAU caracterul de pe pozitia 'h' 
                        al celui de-al patrulea sir este identic cu caracterul din sirul rezultat de pe pozitia 'i + j + k + h'; */

                        /* In cazul in care sunt pe 'rama' matricii voi verifica doar pentru situatiile in care nu voi depasi matricea; */
                            if((i + 1) <= n && (j + 1) <= m && (k + 1) <= o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k +1 ][h] && s33[k] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }
                        
                            if((i + 1) <= n && (j + 1) > m && (k + 1) > o && (h + 1) > p) {
                                a[i][j][k][h] = a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h];
                            }

                            if((i + 1) <= n && (j + 1) > m && (k + 1) > o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }

                            if((i + 1) <= n && (j + 1) > m && (k + 1) <= o && (h + 1) > p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j][k + 1][h] && s33[k] == rez1[i + j + k + h]);
                            }

                            if((i + 1) <= n && (j + 1) > m && (k + 1) <= o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j][k +1 ][h] && s33[k] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }

                            if((i + 1) <= n && (j + 1) <= m && (k + 1) > o && (h + 1) > p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]);
                            }

                            if((i + 1) <= n && (j + 1) <= m && (k + 1) > o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }

                            if((i + 1) <= n && (j + 1) <= m && (k + 1) <= o && (h + 1) > p) {
                                a[i][j][k][h] = (a[i + 1][j][k][h] && s11[i] == rez1[i + j + k + h]) || 
                                (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k +1 ][h] && s33[k] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) > m && (k + 1) > o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) > m && (k + 1) <= o && (h + 1) > p) {
                                a[i][j][k][h] = (a[i][j][k + 1][h] && s33[k] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) > m && (k + 1) <= o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]) || 
                                (a[i][j][k + 1][h] && s33[k] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) <= m && (k + 1) > o && (h + 1) > p) {
                                a[i][j][k][h] = a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h];
                            }

                            if((i + 1) > n && (j + 1) <= m && (k + 1) > o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) <= m && (k + 1) <= o && (h + 1) > p) {
                                a[i][j][k][h] = (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k + 1][h] && s33[k] == rez1[i + j + k + h]);
                            }

                            if((i + 1) > n && (j + 1) <= m && (k + 1) <= o && (h + 1) <= p) {
                                a[i][j][k][h] = (a[i][j + 1][k][h] && s22[j] == rez1[i + j + k + h]) || 
                                (a[i][j][k + 1][h] && s33[k] == rez1[i + j + k + h]) || 
                                (a[i][j][k][h + 1] && s44[h] == rez1[i + j + k + h]) ;
                            }
                        }
                    }
                }
            }
        }
        /*Valoarea de adevar de pe pozitia a[0][0][0][0] va reprezenta faptul ca sirul rezultat a putut fi creat prin intrepatrunderea
        celor patru siruri; */
        return a[0][0][0][0];
    }
    
    
    
    public static void main(String[] args) throws IOException {
        Adn adn = new Adn();
        int T, N;
        //Deschid fisierele pentru citire, respectiv scriere;
        File file_out = new File("adn.out");
        Writer write = new FileWriter(file_out);
        MyScanner sc = new MyScanner("adn.in");
        try {
            T = sc.next_int();
            /*Petru fiecare test, verific tipul testului, dupa care apelez metoda corespunzatoare si scriu in fisier rezultatul; */
            for(int i = 0; i < T; i ++) {
                boolean val;
                N = sc.next_int();
                if(N == 1) {

                    val = sc.next_String().equals(sc.next_String());
                    if(val)
                        write.write("1\n");
                    else
                        write.write("0\n");
                }
                if(N == 2) {
                    val = adn.fortwo(sc.next_String(), sc.next_String(), sc.next_String());
                    if(val)
                        write.write("1\n");
                    else
                        write.write("0\n");
                }
                
                if(N == 3) {
                    val = adn.forthree(sc.next_String(), sc.next_String(), sc.next_String(), sc.next_String());
                    if(val)
                        write.write("1\n");
                    else
                        write.write("0\n");
                }
                
                if(N == 4) {
                    val = adn.forfour(sc.next_String(), sc.next_String(), sc.next_String(), sc.next_String(), sc.next_String());
                    if(val)
                        write.write("1\n");
                    else
                        write.write("0\n");
                }
            }            
        }
        catch(IOException e) {
            System.out.println(e);
        }
        write.close();
    }
}
