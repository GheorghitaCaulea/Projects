import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.List;

public class Permutari {
    public static int comp_matrix(int[][] m_a, String f_word, String s_word) {
        char f_w[] = f_word.toCharArray();
        char s_w[] = s_word.toCharArray();
        int  min_l = Math.min(f_w.length, s_w.length), sw = 0;
		/* Completez pentru fiecare pereche de cuvinte matricea de adiacenta. */
        for(int i = 0; i < min_l; i ++) {
            if(f_w[i] != s_w[i]) {
                m_a[f_w[i] - 'a'][s_w[i] - 'a'] = 1;
                sw = 1;
                break;
            }
        }
		/* In cazul in care cuvintele sunt egale pana pe o pozitie 'i' si primul este mai lung, returnez esec. */
        if(sw == 0 && min_l == s_w.length){
            return -1;
        } else {
            return 1;
        }
    }
    /* Construiesc algoritmul de sortare topologica 'Kahn'. */
    public static int sort(int [][] m_a, List<Integer> list) {
        List<Integer> s_list = new ArrayList<>();
        int sw;
        for(int i = 0; i < 26 ; i++) {
            sw = 0;
            for(int j = 0; j < 26 ; j ++) {
                if(m_a[j][i] != 0) {
                    sw = 1;
                }
            }
			/* Adaug in 's_list' toate nodurile care nu au 'in-muchii'. */
            if(sw == 0) {
                s_list.add(i);
            }    
        }
        while(!s_list.isEmpty()) {
            int u = s_list.remove(s_list.size() - 1);
            list.add(u);
            for(int i = 0; i < 26 ; i++) {
                if(m_a[u][i] == 1) {
                    m_a[u][i] = 0;
                    sw = 0;
                    for(int j = 0; j < 26 ; j ++) {
                        if(m_a[j][i] != 0) {
                            sw = 1;
                        }
                    }
                    if(sw == 0) {
                        s_list.add(i);
                    }
                }  
            }
        }
		/* Verific daca in graf mai sunt muchii, in caz pozitiv returnez esec. */
        sw = 0;
        for(int i = 0; i < 26 ; i++) {
            for(int j = 0; j < 26 ; j ++) {
                if(m_a[i][j] != 0) {
                    sw = 1;
                }
            }
        }
        if(sw == 1) {
            return -1;
        } else {
            return 0;
        }
    }
    
    public static void main(String[] args) throws IOException {
		/* Initializez variabile si o matrice de adiacenta petru graful pe care urmeaza sa-l construiesc */        
		BufferedReader read;
        int N, m_a[][] = new int[26][26], sw = 0;
        String line, f_word, s_word;
        for(int i = 0; i < 26; i ++) {
            for(int j = 0; j < 26; j ++) {
                m_a[i][j] = 0;
            } 
        }
        File file_out = new File("permutari.out");
        Writer write = new FileWriter(file_out);
        FileReader file_in = new FileReader("permutari.in");
        try {
            read = new BufferedReader(file_in);
            line = read.readLine();
            N = Integer.parseInt(line);
			/* Citesc pe rand cuvintele si apelez functia ce imi completeaza matricea de adiacenta pentru fiecare pereche de cuvinte
			consecutive. */
            f_word = read.readLine();
            for(int i = 0; i < N - 1; i ++) {
				/* In cazul in care alfabetul nu se poate forma, scriu in fisier mesajul corespunzator si ma opresc. */ 
                s_word = read.readLine();
                if(comp_matrix(m_a, f_word, s_word) == -1) {
                    write.write("Imposibil");
                    sw = 1;
                    break;
                }
                f_word = s_word;
            }
        } catch(IOException e) {
            System.out.println(e);
        }
		/* In cazul in care completarea matricei de adiacenta a reusit, apelez sortarea topologica. */
        if(sw == 0) {
            List<Integer> list = new ArrayList<>();
            if(sort(m_a, list) == -1) {
                write.write("Imposibil");
            } else {
				/* Scriu in fisier sirul format. */
                for (Integer l : list) {
                    write.write('a' + l);
                }
            }
        }    
        write.close();
    }          
}   
    
