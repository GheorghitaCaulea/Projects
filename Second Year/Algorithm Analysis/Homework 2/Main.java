import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author Caulea Gheorghita
 */
public class Main {
    
    public static void main(String[] args) {
        Graph g = new Graph();
        File file_in = new File("test.in");
        Scanner scan;
        FileWriter write;
        File file_out = new File("test.out");
        try{
            scan = new Scanner(file_in);
            try{
                write = new FileWriter(file_out);
                int nv, ne, k, n1, n2;
                nv = scan.nextInt();
                ne = scan.nextInt();
                k = scan.nextInt();
                while(scan.hasNext()){
                    n1 = scan.nextInt();
                    n2 = scan.nextInt();
                    g.add(n1, n2);
                }
                g.fine_reset(g);
                if(k > 1){
                    Node nd = g.reset(g);
                    write.write("(x" + nd.name );
                    for (Node neigh_list : nd.neigh_list) {
                        write.write("Vx" + neigh_list.name);
                    }
                    write.write(")");
                }
                for(int i = 0; i < k - 1; i ++){
                    if(g.nodes.size() == 0)
                        break;
                    Node nd = g.reset(g);
                    write.write("^(x" + nd.name );
                    for (Node neigh_list : nd.neigh_list) {
                        write.write("Vx" + neigh_list.name);
                    }
                    write.write(")");
                }
                scan.close();
                write.close();
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

