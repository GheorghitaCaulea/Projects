import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Scanner;

/**
 *Clasa 'Operation' contine cele doua operatii importante: serializarea si deserializarea.
 * @author gicu
 */
public class Operation{
    
    /**
     * Metoda 'Serialize' executa scrierea grafului in fisier, in formatul dorit.
     * Se parcurge graful in latime.
     * Se foloseste o lista in locul unui cozi.
     * @param stt
     * @param graph
     * @param write
     * @throws IOException 
     */
    public void Serialize(Nod stt, Nod graph, FileWriter write) throws IOException{
        Nod start;
        LinkedList<String> l_string = new LinkedList<>();
        int i, id = 1;
        //Imi formez String-uri necesare scrierii in fisier
        String tab_0 = "", tab_1 = "\t", tab_2 = "\t\t", tab_3 ="\t\t\t" ;
        LinkedList<Nod> li_nod = new LinkedList<>();
        LinkedList<Nod> li_neigh;
        //Adaug nodul de start, dat ca parametru in lista
        li_nod.add(stt);
        while(!li_nod.isEmpty()){
            start = li_nod.getFirst();
            li_nod.remove(0);
            //Scot si sterg nodul din lista
            if(start.get_vizitat(start) == false){
                write.write(tab_0 + "<Object class=\"" + start.get_class(start) + "\" Version=\"" + start.get_version(start) + "\" id=\"" + start.get_id(start) + "\">\n");
                start.set_vizitat(true, start);
                write.write(tab_1 + "<Nume>" + start.get_name(start) + "</Nume>\n");
                write.write(tab_1 + "<" + start.get_implemantation(start) + ">\n");
                li_neigh = start.get_neighbours(start);
                //Daca nodul nu a fost vizitat se scrie in fisier in formatul dorit si i se introduc vecinii in coada
                for(i = 0; i < li_neigh.size(); i ++){
                    if(li_neigh.get(i).get_vizitat(li_neigh.get(i)) == false){
                        //Daca vecinii nu au fost vizitati, li se seteaza id-ul si se afiseaza cu 'Object'
                        if(!(li_nod.contains(li_neigh.get(i)))){
                            li_neigh.get(i).set_id(li_neigh.get(i), id);
                            id ++;
                            li_nod.add(li_neigh.get(i));
                        }    
                        write.write(tab_2 + "<Object class=\"" + li_neigh.get(i).get_class(li_neigh.get(i)) + "\" Version=\"" + li_neigh.get(i).get_version(li_neigh.get(i)) + "\" id=\"" + li_neigh.get(i).get_id(li_neigh.get(i)) + "\">\n");
                        write.write(tab_3 + "<Nume>" + li_neigh.get(i).get_name(li_neigh.get(i)) + "</Nume>\n");
                        write.write(tab_2 + "</Object>\n");
                    }
                    else{
                        //Altfel se afiseaza cu 'Reference'
                        write.write(tab_2 + "<Reference class=\"" + li_neigh.get(i).get_class(li_neigh.get(i)) + "\" Version=\"" + li_neigh.get(i).get_version(li_neigh.get(i)) + "\" id=\"" + li_neigh.get(i).get_id(li_neigh.get(i)) +"\">\n");
                    }
                }
                write.write(tab_1 + "</" + start.get_implemantation(start) + ">\n");
                write.write(tab_0 + "</Object>\n");
            }
        }
    }
    
    /**
     * Metoda 'Deserialize' executa constructia unui graf scris in fisier.
     * Metoda va afisa si rezultatele cast-urilor.
     * @param type_a
     * @param type_b
     * @param type_c
     * @param scan
     * @param file_cast
     * @return Nod
     * @throws IOException 
     */
    public Nod Deserialize(int type_a, int type_b, int type_c, Scanner scan, String file_cast) throws IOException{
        //Se creeaza numele fisierului in care se vor scrie rezultatele cast-urilor.
        String point[];
        String file_cast_out = "Deserialize_";
        point = file_cast.split("\\.");
        file_cast_out = file_cast_out.concat(point[0]);
        file_cast_out = file_cast_out.concat("_CAST.log");
        File file = new File(file_cast_out);
        FileWriter wr = new FileWriter(file);
        int type = 0, version;
        Nod graph = new Nod();
        LinkedList<String> lst = new LinkedList<>();
        String line; 
        String tab[], versiune_nod, nume_nod, stare, nume_vecin;
        String space[];
        String open[];
        String close[];
        String comma[];
        line = scan.nextLine();
        line = scan.nextLine();
        while(scan.hasNextLine()){
            //Se citeste linie cu linie
            tab = line.split("\t");
            if(tab.length == 1 && tab[0].length() > 10){
                comma = tab[tab.length - 1].split("\"");
                versiune_nod = comma[1]; 
                line = scan.nextLine();
                tab = line.split("\t");
                close = tab[tab.length - 1].split(">");
                open = close[1].split("<");
                nume_nod = open[0];
                version = Integer.parseInt(comma[3]);
                //Se citeste pentru fiecare nod, din fisier, numele, versiunea si iteratia
                if(versiune_nod.equals("NodA"))
                    type = type_a;
                if(versiune_nod.equals("NodB"))
                    type = type_b;
                if(versiune_nod.equals("NodC"))
                    type = type_c;
                if(!lst.contains(nume_nod)){
                    //Se verifica daca nodul este deja in graf
                    lst.add(nume_nod);
                    //Se verifica acele conditii de cast si se scriu in fisier mesaje corespunzatoare
                    if(version < type){
                        wr.write("OK cast " + versiune_nod + " " + nume_nod + " from Version=\"" + version + "\" to Version=\"" + type + "\"\n" );
                    }
                    if(version > type){
                        wr.write("Fail cast " + versiune_nod + " " + nume_nod + " from Version=\"" + version + "\" to Version=\"" + type + "\"\n" );
                    }
                    //Se initializeaza si se adauga nodul in graf
                    graph.init_insert(versiune_nod, graph, type, nume_nod);
                }
                line = scan.nextLine();
                tab = line.split("\t");
                //Se vor identifica toti vecii nodului
                while(tab.length > 1){ 
                    if(tab.length == 3 && tab[tab.length - 1].length() > 10){
                        open = tab[tab.length - 1].split("<");
                        space = open[1].split(" ");
                        stare = space[0];
                        if(stare.equals("Object")){
                            comma = tab[tab.length - 1].split("\"");
                            versiune_nod = comma[1]; 
                            line = scan.nextLine();
                            tab = line.split("\t");
                            close = tab[tab.length - 1].split(">");
                            open = close[1].split("<");
                            nume_vecin = open[0];
                            version = Integer.parseInt(comma[3]);
                            if(versiune_nod.equals("NodA"))
                                type = type_a;
                            if(versiune_nod.equals("NodB"))
                                type = type_b;
                            if(versiune_nod.equals("NodC"))
                                type = type_c;
                            if(!lst.contains(nume_vecin)){
                                lst.add(nume_vecin);
                                if(version < type){
                                    wr.write("OK cast " + versiune_nod + " " + nume_vecin + " from Version=\"" + version + "\" to Version=\"" + type + "\"\n" );
                                }
                                if(version > type){
                                    wr.write("Fail cast " + versiune_nod + " " + nume_vecin + " from Version=\"" + version + "\" to Version=\"" + type + "\"\n" );
                                }
                                graph.init_insert(versiune_nod, graph, type, nume_vecin);
                            }

                            graph.add_vecin(nume_nod, nume_vecin);
                            //Daca un vecin apare cu 'Object' prima operatie este de initializare si adugare in graf
                            //A doua operatie este de adaugare ca vecin
                        }
                        else{
                            //In caz contrar este adugat decat ca vecin
                            //Numele i se va lua dintr-o lista de string-uri ce simuleaza graf-ul
                            comma = tab[tab.length - 1].split("\"");
                            int id = Integer.parseInt(comma[5]);
                            graph.add_vecin(nume_nod, lst.get(id));
                        }
                    }
                    line = scan.nextLine();
                    tab = line.split("\t");
                }
            }
                if(scan.hasNextLine()){    
                     line = scan.nextLine(); 
                }
                else
                    break;
        }
        wr.close();
        return graph;
            
    }
}
