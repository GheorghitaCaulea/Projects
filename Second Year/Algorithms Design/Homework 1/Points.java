import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Points {
    
    public static void main(String[] args) throws IOException {
        BufferedReader read;
        int N, M;
        String line, tokens[];
        //Am creeat o lista de puncte;
        List<Integer> Puncte = new ArrayList<>();
        //Am creeat o lista de intervale(clasa Interval are doua atribute:capatul din stanga(x) si capatul din dreapta(y));
        List<Interval> list = new ArrayList<>();
        //Deschid fisierele pentru citire;
        File file_out = new File("points.out");
        Writer write = new FileWriter(file_out);
        FileReader file_in = new FileReader("points.in");
        try {
            //Citesc si retin numarul de puncte si intervale;
            read = new BufferedReader(file_in);
            line = read.readLine();
            tokens = line.split(" ");
            N = Integer.parseInt(tokens[0]);
            M = Integer.parseInt(tokens[1]);
            
            line = read.readLine();
            tokens = line.split(" ");
            
            //Citesc fiecare punct si il introduc in lista corespunzatoare;
            for(int i = 0; i < N; i++) {
                Puncte.add(Integer.parseInt(tokens[i]));
            }
            
            //Citesc fiecare interval si il introduc in lista corespunzatoare;
            for(int i = 0; i < M; i ++) {
                line = read.readLine();
                tokens = line.split(" ");
                list.add(new Interval(Integer.parseInt(tokens[0]), Integer.parseInt(tokens[1])));
            }
        }
        catch(IOException e) {
            System.out.println(e);
        }
        
        //Sortez lista de intervale dupa capatul stanga(x);
        Collections.sort(list, new Comparator<Interval>() {

            @Override
            public int compare(Interval o1, Interval o2) {
                if(o1.x > o2.x)
                    return 1;
                else
                    if(o1.x == o2.x)
                        return 0;
                return -1;
            }
        });

        int count = 0;
        //Folosesc cele doua variabile pentru a itera peste lista de intervale, puncte;
        int iterate_inteval = 0;
        int iterate_points = 0;
        //Aleg un interval cu capetele minime;
        Interval inter = new Interval(Integer.MIN_VALUE, Integer.MIN_VALUE);
        
        while(iterate_points < Puncte.size()) {
            
            inter.y = Integer.MIN_VALUE;
            //Cat timp punctul curent nu se afla in intervalul curent, iterez peste intervale;
            while(iterate_inteval < list.size() && ((list.get(iterate_inteval).x > Puncte.get(iterate_points) 
            || list.get(iterate_inteval).y < Puncte.get(iterate_points)))) {
                iterate_inteval ++;   
            }
           	
           	//Caut intervalul cu cel mai mare capat dreapta inca care se poate afla punctul; 
            while(iterate_inteval < list.size() && list.get(iterate_inteval).x <= Puncte.get(iterate_points)) {
                
                if(list.get(iterate_inteval).y > inter.y) {
                    inter = list.get(iterate_inteval);
                }
                iterate_inteval ++;
            }

            //Iterez peste toate punctele care se incadreaza in intervalul gasit;
            while(iterate_points < Puncte.size()) {
                if(Puncte.get(iterate_points) >= inter.x && Puncte.get(iterate_points) <= inter.y) {
                    iterate_points ++;
                } else {
                    break;
                }
            }
            //Numar intervalele;
            count++;
        }
       write.write(Integer.toString(count));
       write.close();
    }  
}
