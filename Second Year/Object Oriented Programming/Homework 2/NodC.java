import java.util.LinkedList;


/**
 *Clasa 'NodC' este utilizata pentru mentinerea nodurile de tip 'NodC'.
 * @author Caulea Gheorghita
 */
public class NodC extends Nod{
    
    /**
     *Metoda 'add' aduga nodul 'nod_des' in lista de vecini ai nodului 'nod_source'.
     *De asemeni va adauga si in lista de vecini ai nodului 'nod_des', nodul 'nod_source'.
     * @param nod_des
     * @param nod_source 
     */
    public void add(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodC1){
            ((NodC1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodC2){
            ((NodC2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodC3){
            ((NodC3)(nod_des)).add(nod_source);
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
        if(nod_source instanceof NodA1){
            ((NodA1)(nod_source)).add(nod_des);     
        }
        if(nod_source instanceof NodA2){
            ((NodA2)(nod_source)).add(nod_des);
        }
        if(nod_source instanceof NodA3){
            ((NodA3)(nod_source)).add(nod_des);
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
    }
    
    /**
     * Metoda 'add_vecin_C' aduga nodul 'nod_source' in lista de vecini ai nodului 'nod_des'.
     * Reciproc nu.
     * @param nod_des
     * @param nod_source 
     */
    public void add_vecin_C(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodC1){
            ((NodC1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodC2){
            ((NodC2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodC3){
            ((NodC3)(nod_des)).add(nod_source);
        }
    }
    
    /**
     * Metoda 'remove_C' sterge nodul 'nod_source' din lista de vecini ai nodului 'nod_des'.
     * @param nod_des
     * @param nod_source 
     */
    public void remove_C(Nod nod_des, Nod nod_source ){
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
     * Metoda 'remove_nod_C' sterge nodul 'nod' de tip 'NodC' din graful 'graph'.
     * Vor fi eliminate si toate aparitiile nodului 'nod' ca vecin.
     * @param nod
     * @param graph 
     */
    public void remove_nod_C(NodC nod, Nod graph){
        if(nod instanceof NodC1){
            for(int i = 0; i < ((NodC1)(nod)).lenght(); i ++)
                remove_C(((NodC1)(nod)).get(i), nod);
        }
        if(nod instanceof NodC2){
            for(int i = 0; i < ((NodC2)(nod)).lenght(); i ++)
                remove_C(((NodC2)(nod)).get(i), nod);
        }
        if(nod instanceof NodC3){
            for(int i = 0; i < ((NodC3)(nod)).lenght(); i ++)
                remove_C(((NodC3)(nod)).get(i), nod);
        }
    }
    
    /**
     * Metoda 'initialization' initializeaza un obiect de tip 'NodC' si iteratie 'type'.
     * @param graph
     * @param type
     * @param name
     * @return NodC
     */
    public NodC initialization(Nod graph, int type, String name){
        if(type == 1){
           return new NodC1(name);
        }
        if(type == 2){
            return new NodC2(name);
        }
        return new NodC3(name);
    }
    
    /**
     * Metoda 'get_neighbours_C', intoarce sub forma de lista vecinii nodului 'nod' de tip 'NodC'.
     * @param nod
     * @return LinkedList Nod
     */
    public LinkedList<Nod> get_neighbours_C(NodC nod){
        LinkedList<Nod> lista = new LinkedList<>();
        if(nod instanceof NodC1){
            for(int i = 0; i < ((NodC1)(nod)).lenght(); i ++)
                lista.add(((NodC1)(nod)).get(i));
        }
        if(nod instanceof NodC2){
            for(int i = 0; i < ((NodC2)(nod)).lenght(); i ++)
                lista.add(((NodC2)(nod)).get(i));
        }
        if(nod instanceof NodC3){
            for(int i = 0; i < ((NodC3)(nod)).lenght(); i ++)
                lista.add(((NodC3)(nod)).get(i));
        }
        return lista;
    }
    
    /**
     * Metoda 'set_vizitat_C' seteaza starea de vizitat sau nu(false/true) a unui nod 'nod' de tip 'NodC'.
     * @param var
     * @param nod 
     */
    public void set_vizitat_C(boolean var, NodC nod){
        if(nod instanceof NodC1)
            ((NodC1)(nod)).vizitat = var;
        if(nod instanceof NodC2)
            ((NodC2)(nod)).vizitat = var;
        if(nod instanceof NodC3)
            ((NodC3)(nod)).vizitat = var;
    }
    
    /**
     * Metoda 'get_name_C' intoarce numele unui nod 'nod' de tip 'NodC'.
     * @param nod
     * @return String
     */
    public String get_name_C(NodC nod){
        if(nod instanceof NodC1)
            return ((NodC1)(nod)).nume;
        if(nod instanceof NodC2)
            return ((NodC2)(nod)).nume;
        return ((NodC3)(nod)).nume;
    }
    
     /**
     * Metoda 'get_version_C' intoarce versiunea unui nod 'nod' de tip 'NodC'.
     * @param nod
     * @return int
     */
    public int get_version_C(NodC nod){
        if(nod instanceof NodC1)
            return 1;
        if(nod instanceof NodC2)
            return 2;
        return 3;
    }
    
    /**
     * Metoda 'get_vizitat_C' intoarce starea de vizitat a nodului 'nod' de tip 'NodC'.
     * @param nod
     * @return boolean
     */
    public boolean get_vizitat_C(NodC nod){
        if(nod instanceof NodC1)
            return ((NodC1)(nod)).vizitat;
        if(nod instanceof NodC2)
            return ((NodC2)(nod)).vizitat;
        return ((NodC3)(nod)).vizitat;
    }
    
    /**
     * Metoda 'get_id_C' intoarce id-ul unui nod 'nod' de tip 'NodC'.
     * @param nod
     * @return int
     */
    public int get_id_C(NodC nod){
        if(nod instanceof NodC1)
            return ((NodC1)(nod)).id;
        if(nod instanceof NodC2)
            return ((NodC2)(nod)).id;
        return ((NodC3)(nod)).id;
    }
    
    /**
     * Metoda 'set_id_C' seteaza id-ul unui nod 'nod' de tip 'NodC'
     * @param nod
     * @param id 
     */
    public void set_id_C(NodC nod, int id){
        if(nod instanceof NodC1)
            ((NodC1)(nod)).id = id;
        if(nod instanceof NodC2)
            ((NodC2)(nod)).id = id;
        if(nod instanceof NodC3)
            ((NodC3)(nod)).id = id;
    }
}
