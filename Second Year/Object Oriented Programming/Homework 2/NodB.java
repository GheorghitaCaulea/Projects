import java.util.LinkedList;


/**
 *Clasa 'NodB' este utilizata pentru mentinerea nodurile de tip 'NodB'.
 * @author Caulea Gheorghita
 */
public class NodB extends Nod {
    /**
     *Metoda 'add' aduga nodul 'nod_des' in lista de vecini ai nodului 'nod_source'.
     *De asemeni va adauga si in lista de vecini ai nodului 'nod_des', nodul 'nod_source'.
     * @param nod_des
     * @param nod_source 
     */
    public void add(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodB1){
            ((NodB1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodB2){
            ((NodB2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodB3){
            ((NodB3)(nod_des)).add(nod_source);
        }
        if(nod_source instanceof NodB1){
            ((NodB1)(nod_source)).add(nod_des);   
        }
        if(nod_source instanceof NodB2){
            ((NodB2)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodB3){
            ((NodB3)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodA1){
            ((NodA1)(nod_source)).add(nod_des);     
        }
        if(nod_source instanceof NodA2){
            ((NodA2)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodA3){
            ((NodA3)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodC1){
            ((NodC1)(nod_source)).add(nod_des);     
        }
        if(nod_source instanceof NodC2){
            ((NodC2)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodC3){
            ((NodC3)(nod_source)).add(nod_des);
        } 
    }
    
    /**
     * Metoda 'add_vecin_B' aduga nodul 'nod_source' in lista de vecini ai nodului 'nod_des'.
     * Reciproc nu.
     * @param nod_des
     * @param nod_source 
     */
    public void add_vecin_B(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodB1){
            ((NodB1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodB2){
            ((NodB2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodB3){
            ((NodB3)(nod_des)).add(nod_source);
        }
    }
    
    /**
     * Metoda 'remove_B' sterge nodul 'nod_source' din lista de vecini ai nodului 'nod_des'.
     * @param nod_des
     * @param nod_source 
     */
    public void remove_B(Nod nod_des, Nod nod_source ){
        if(nod_des instanceof NodA1){
            ((NodA1)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodA2){
            ((NodA2)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodA3){
            ((NodA3)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodB1){
            ((NodB1)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodB2){
            ((NodB2)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodB3){
            ((NodB3)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodC1){
            ((NodC1)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodC2){
            ((NodC2)(nod_des)).remove(nod_source);
        }
        if(nod_des instanceof NodC3){
            ((NodC3)(nod_des)).remove(nod_source);
        }
    }
    
    /**
     * Metoda 'remove_nod_B' sterge nodul 'nod' de tip 'NodB' din graful 'graph'.
     * Vor fi eliminate si toate aparitiile nodului 'nod' ca vecin.
     * @param nod
     * @param graph 
     */
    public void remove_nod_B(NodB nod, Nod graph){
        if(nod instanceof NodB1){
            for(int i = 0; i < ((NodB1)(nod)).lenght(); i ++)
                remove_B(((NodB1)(nod)).get(i), nod);
        }
        if(nod instanceof NodB2){
            for(int i = 0; i < ((NodB2)(nod)).lenght(); i ++)
                remove_B(((NodB2)(nod)).get(i), nod);
        }
        if(nod instanceof NodB3){
            for(int i = 0; i < ((NodB3)(nod)).lenght(); i ++)
                remove_B(((NodB3)(nod)).get(i), nod);
        }
    }
    
    /**
     * Metoda 'initialization' initializeaza un obiect de tip 'NodB' si iteratie 'type'.
     * @param graph
     * @param type
     * @param name
     * @return NodB
     */
    public NodB initialization(Nod graph, int type, String name){
        if(type == 1){
           return new NodB1(name);
        }
        if(type == 2){
            return new NodB2(name);
        }
        return new NodB3(name);
    }
    
    /**
     * Metoda 'get_neighbours_B', intoarce sub forma de lista vecinii nodului 'nod' de tip 'NodB'.
     * @param nod
     * @return LinkedList Nod
     */
    public LinkedList<Nod> get_neighbours_B(NodB nod){
        LinkedList<Nod> lista = new LinkedList<>();
        if(nod instanceof NodB1){
            for(int i = 0; i < ((NodB1)(nod)).lenght(); i ++)
                lista.add(((NodB1)(nod)).get(i));
        }
        if(nod instanceof NodB2){
            for(int i = 0; i < ((NodB2)(nod)).lenght(); i ++)
                lista.add(((NodB2)(nod)).get(i));
        }
        if(nod instanceof NodB3){
            for(int i = 0; i < ((NodB3)(nod)).lenght(); i ++)
                lista.add(((NodB3)(nod)).get(i));
        }
        return lista;
    }
    
    /**
     * Metoda 'set_vizitat_B' seteaza starea de vizitat sau nu(false/true) a unui nod 'nod' de tip 'NodB'.
     * @param var
     * @param nod 
     */
    public void set_vizitat_B(boolean var, NodB nod){
        if(nod instanceof NodB1)
            ((NodB1)(nod)).vizitat = var;
        if(nod instanceof NodB2)
            ((NodB2)(nod)).vizitat = var;
        if(nod instanceof NodB3)
            ((NodB3)(nod)).vizitat = var;
    }
    
    /**
     * Metoda 'get_name_B' intoarce numele unui nod 'nod' de tip 'NodB'.
     * @param nod
     * @return String
     */
    public String get_name_B(NodB nod){
        if(nod instanceof NodB1)
            return ((NodB1)(nod)).nume;
        if(nod instanceof NodB2)
            return ((NodB2)(nod)).nume;
        return ((NodB3)(nod)).nume;
    }
    
    /**
     * Metoda 'get_version_B' intoarce versiunea unui nod 'nod' de tip 'NodB'.
     * @param nod
     * @return int
     */
    public int get_version_B(NodB nod){
        if(nod instanceof NodB1)
            return 1;
        if(nod instanceof NodB2)
            return 2;
        return 3;
    }
    
    /**
     * Metoda 'get_vizitat_B' intoarce starea de vizitat a nodului 'nod' de tip 'NodB'.
     * @param nod
     * @return boolean
     */
    public boolean get_vizitat_B(NodB nod){
        if(nod instanceof NodB1)
            return ((NodB1)(nod)).vizitat;
        if(nod instanceof NodB2)
            return ((NodB2)(nod)).vizitat;
        return ((NodB3)(nod)).vizitat;
    }
    
    /**
     * Metoda 'get_id_B' intoarce id-ul unui nod 'nod' de tip 'NodB'.
     * @param nod
     * @return int
     */
    public int get_id_B(NodB nod){
        if(nod instanceof NodB1)
            return ((NodB1)(nod)).id;
        if(nod instanceof NodB2)
            return ((NodB2)(nod)).id;
        return ((NodB3)(nod)).id;
    }
    
    /**
     * Metoda 'set_id_B' seteaza id-ul unui nod 'nod' de tip 'NodB'
     * @param nod
     * @param id 
     */
    public void set_id_B(NodB nod, int id){
        if(nod instanceof NodB1)
            ((NodB1)(nod)).id = id;
        if(nod instanceof NodB2)
            ((NodB2)(nod)).id = id;
        if(nod instanceof NodB3)
            ((NodB3)(nod)).id = id;
    }
}
