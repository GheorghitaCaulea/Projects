import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;

/**
 *Clasa Main contine metoda main.
 * @author Caulea Gheorghita
 */
public class Main{
    public static void main(String[] args) {
        Operation operation = new Operation();            
        int type_a, type_b, type_c;
        File file_in = new File(args[0]);
        Scanner scan;
        FileWriter write;
        try{
            scan = new Scanner(file_in);
            try{
                //Consider ca prima linie contine un Setting si citesc setarile curente
                String line = scan.nextLine();
                String [] com = line.split(" ");
                type_a = Integer.parseInt(com[1]);
                type_b = Integer.parseInt(com[2]);
                type_c = Integer.parseInt(com[3]);
                //Construiesc un graf gol cu setarile curente ale versiunilor
                Nod Graph = new Nod(type_a, type_b, type_c);
                while(scan.hasNextLine()){
                    //Citesc fiecare linie
                    line = scan.nextLine();
                    com = line.split(" ");
                    if(com[0].equals("Add")){
                        //In cazul in care comanda este 'Add', initializez nodul si il adaug in graf
                        if(com[1].equals("NodA"))
                            Graph.init_insert(com[1], Graph, type_a, com[2]);
                        if(com[1].equals("NodB"))
                            Graph.init_insert(com[1], Graph, type_b, com[2]);    
                        if(com[1].equals("NodC"))
                            Graph.init_insert(com[1], Graph, type_c, com[2]);
                        //Pe fiecare nod valid, dat dupa cel de initializare, il voi adauga ca vecin al acestuia
                        for(int i = 3; i < com.length; i++)
                            Graph.add(com[2], com[i]);
                    }
                    if(com[0].equals("Del")){
                        //In cazul in care comanda este 'Del', voi sterge nodul din graf, si niciun alt nod nu il va mai avea ca vecin
                        Graph.remove(com[2], Graph);
                    }
                    if(com[0].equals("AddM")){
                        //In cazul in care comanda este 'AddM', voi adauga o muchie intre nodurile specificate
                        Graph.add_muchie(com[1], com[2]);
                    }
                    if(com[0].equals("DelM")){
                        //In cazul in care comanda este 'DelM', voi sterge muchia dintre nodurile specificate
                        Graph.remove_muchie(com[1], com[2]);
                    }
                    if(com[0].equals("Serialize")){
                        //In cazul in care comanda este 'Serialize', se va face serializarea grafului
                        Nod start = Graph.get(Graph.ls, com[1]);
                        File file_out = new File(com[2]);
                        write = new FileWriter(file_out);
                        write.write("Serialize " + com[1] + "\n");
                        operation.Serialize(start, Graph, write);
                        write.close();
                    }
                    if(com[0].equals("Settings")){
                        //In cazul in care comanda este 'Settings', se actualizeaza setarile curente
                        type_a = Integer.parseInt(com[1]);
                        type_b = Integer.parseInt(com[2]);
                        type_c = Integer.parseInt(com[3]);
                    }
                    if(com[0].equals("Deserialize")){
                        //In cazul in care comanda este 'Deserialize', se distruge graful vechi, construindu-se unul nou prin deserializare 
                        File file_out_des = new File(com[1]);
                        Scanner scan2 = new Scanner(file_out_des);
                        Graph = operation.Deserialize(type_a, type_b, type_c, scan2, com[1]);
                    }
                }
            scan.close();     
            }
            catch(IOException ioe){
                System.out.println(ioe);
            }
        }
        catch(FileNotFoundException fnfe){
            System.out.println(fnfe);
        } 
        
    }
    
}
