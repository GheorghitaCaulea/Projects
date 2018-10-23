

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;

/**
 *Clasa Main este folosita pentru citirea, scrierea in fisier si executarea operatiilor;
 * @author Caulea Gheorghita
 */
public class Main extends Operations{
    
    public static void main(String[] args) {
        File file1 = new File("quadtree.in");
        Scanner scan;
        File file2 = new File("quadtree.out");
        FileWriter write;
        //Se deschid fisierele pentru citire, respectiv scriere;
        try{
            scan = new Scanner(file1);
            try{
                write = new FileWriter(file2);
                double x1_t, x2_t, y1_t, y2_t;
                //Se citesc coordonatele planului initial;
                x1_t = Double.parseDouble(scan.next().trim());
                y1_t = Double.parseDouble(scan.next().trim());
                x2_t = Double.parseDouble(scan.next().trim());
                y2_t = Double.parseDouble(scan.next().trim());
                int op, fig, id, i;
                double x1, x2, x3, x4, y1, y2, y3, y4, r;
                String s;
                Rectangle rec;
                Triangle tr;
                Circle cir;
                Diamond dia;
                Point p;
                QuadTree tree = new QuadTree(x1_t, x2_t, y1_t, y2_t, null, 0);
                ArrayList<LinkedList<QuadTree>> lst = new ArrayList<>(100000);
                for(i = 0; i < 100000; i++)
                    lst.add(new LinkedList<QuadTree>());
                LinkedList<Integer> id_list;
                while(scan.hasNext()){
                    //Se citeste operatia;
                    op = scan.nextInt();
                    //Pentru fiecare operatie se citesc elementele corespunzatoare si se apeleaza metoda;
                    if(op == 11){
                        fig = scan.nextInt();
                        if(fig == 1){
                            id = scan.nextInt();
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            rec = new Rectangle(x1, x2, y1, y2, id);
                            SpecialInsertInQuadTree(tree, rec, lst);
                        }
                        if(fig == 2){
                            id = scan.nextInt();
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            x3 = Double.parseDouble(scan.next().trim());
                            y3 = Double.parseDouble(scan.next().trim());
                            tr = new Triangle(x1, x2, x3, y1, y2, y3, id);
                            SpecialInsertInQuadTree(tree, tr, lst);
                        }
                        if(fig == 3){
                            id = scan.nextInt();
                            r = Double.parseDouble(scan.next().trim());
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            cir = new Circle(r, x1, y1, id);
                            SpecialInsertInQuadTree(tree, cir, lst);
                        }
                        if(fig == 4){
                            id = scan.nextInt();
                            x3 = Double.parseDouble(scan.next().trim());
                            y3 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x4 = Double.parseDouble(scan.next().trim());
                            y4 = Double.parseDouble(scan.next().trim());
                            dia = new Diamond(x1, x2, x3, x4, y1, y2, y3, y4, id);
                            SpecialInsertInQuadTree(tree, dia, lst);
                        }  
                    }
                    if(op == 22){
                        id = scan.nextInt();
                        SpecialRemove(id, lst);
                    }
                    if(op == 33){
                        x1 = Double.parseDouble(scan.next().trim());
                        y1 = Double.parseDouble(scan.next().trim());
                        p = new Point(x1, y1);
                        id_list = new LinkedList<>();
                        searchInQuadTreeforPoint(tree, p, id_list);
                        if(id_list.size() == 0)
                            write.write("NIL\n");
                        else{
                            Collections.sort(id_list);
                            for(i = 0; i < id_list.size() - 1; i ++){
                                s = Integer.toString(id_list.get(i));
                                write.write(s);
                                write.write(" ");
                            }
                            s = Integer.toString(id_list.get(i));
                            write.write(s);
                            write.write("\n");
                        }
                    }
                    if(op == 44){
                        fig = scan.nextInt();
                        id_list = new LinkedList<>();
                        if(fig == 1){
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            rec = new Rectangle(x1, x2, y1, y2, 0);
                            searchInQuadTree(tree, rec, id_list);
                        }
                        if(fig == 2){
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            x3 = Double.parseDouble(scan.next().trim());
                            y3 = Double.parseDouble(scan.next().trim());
                            tr = new Triangle(x1, x2, x3, y1, y2, y3, 0);
                            searchInQuadTree(tree, tr, id_list);
                        }
                        if(fig == 3){
                            r = Double.parseDouble(scan.next().trim());
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            cir = new Circle(r, x1, y1, 0);
                            searchInQuadTree(tree, cir, id_list);
                        }
                        if(fig == 4){
                            x3 = Double.parseDouble(scan.next().trim());
                            y3 = Double.parseDouble(scan.next().trim());
                            x2 = Double.parseDouble(scan.next().trim());
                            y2 = Double.parseDouble(scan.next().trim());
                            x1 = Double.parseDouble(scan.next().trim());
                            y1 = Double.parseDouble(scan.next().trim());
                            x4 = Double.parseDouble(scan.next().trim());
                            y4 = Double.parseDouble(scan.next().trim());
                            dia = new Diamond(x1, x2, x3, x4, y1, y2, y3, y4, 0);
                            searchInQuadTree(tree, dia, id_list);
                        }
                        if(id_list.size() == 0)
                            write.write("NIL\n");
                        else{
                            Collections.sort(id_list);
                            for(i = 0; i < id_list.size() - 1; i ++){
                                s = Integer.toString(id_list.get(i));
                                write.write(s);
                                write.write(" ");
                            }
                            s = Integer.toString(id_list.get(i));
                            write.write(s);
                            write.write("\n");
                        }
                    }     
                }
                //Se inchid fisierele;
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
