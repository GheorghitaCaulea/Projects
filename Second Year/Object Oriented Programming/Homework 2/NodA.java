import java.util.LinkedList;

/**
 *Clasa 'NodA' este utilizata pentru mentinerea nodurile de tip 'NodA'.
 * @author Caulea Gheorghita
 */
public class NodA extends Nod {
    /**
     *Metoda 'add' aduga nodul 'nod_des' in lista de vecini ai nodului 'nod_source'.
     *De asemeni va adauga si in lista de vecini ai nodului 'nod_des', nodul 'nod_source'.
     * @param nod_des
     * @param nod_source 
     */
    public void add(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodA1){
            ((NodA1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodA2){
            ((NodA2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodA3){
            ((NodA3)(nod_des)).add(nod_source);
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
     * Metoda 'add_vecin_A' aduga nodul 'nod_source' in lista de vecini ai nodului 'nod_des'.
     * Reciproc nu.
     * @param nod_des
     * @param nod_source 
     */
    public void add_vecin_A(Nod nod_des, Nod nod_source){
        if(nod_des instanceof NodA1){
            ((NodA1)(nod_des)).add(nod_source);   
        }
        if(nod_des instanceof NodA2){
            ((NodA2)(nod_des)).add(nod_source);
        }
        if(nod_des instanceof NodA3){
            ((NodA3)(nod_des)).add(nod_source);
        }
    }
    
    /**
     * Metoda 'remove_A' sterge nodul 'nod_source' din lista de vecini ai nodului 'nod_des'.
     * @param nod_des
     * @param nod_source 
     */
    public void remove_A(Nod nod_des, Nod nod_source ){
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
     * Metoda 'remove_nod_A' sterge nodul 'nod' de tip 'NodA' din graful 'graph'.
     * Vor fi eliminate si toate aparitiile nodului 'nod' ca vecin.
     * @param nod
     * @param graph 
     */
    public void remove_nod_A(NodA nod, Nod graph){
        if(nod instanceof NodA1){
            for(int i = 0; i < ((NodA1)(nod)).lenght(); i ++)
                remove_A(((NodA1)(nod)).get(i), nod);
        }
        if(nod instanceof NodA2){
            for(int i = 0; i < ((NodA2)(nod)).lenght(); i ++)
                remove_A(((NodA2)(nod)).get(i), nod);
        }
        if(nod instanceof NodA3){
            for(int i = 0; i < ((NodA3)(nod)).lenght(); i ++)
                remove_A(((NodA3)(nod)).get(i), nod);
        }
    }
    
    /**
     * Metoda 'initialization' initializeaza un obiect de tip 'NodA' si iteratie 'type'.
     * @param graph
     * @param type
     * @param name
     * @return NodA
     */
    public NodA initialization(Nod graph, int type, String name){
        if(type == 1){
           return new NodA1(name);
        }
        if(type == 2){
            return new NodA2(name);
        }
        return new NodA3(name);
    }
    
    
    /**
     * Metoda 'get_neighbours_A', intoarce sub forma de lista vecinii nodului 'nod' de tip 'NodA'.
     * @param nod
     * @return LinkedList Nod
     */
    public LinkedList<Nod> get_neighbours_A(NodA nod){
        LinkedList<Nod> lista = new LinkedList<>();
        if(nod instanceof NodA1){
            for(int i = 0; i < ((NodA1)(nod)).lenght(); i ++)
                lista.add(((NodA1)(nod)).get(i));
        }
        if(nod instanceof NodA2){
            for(int i = 0; i < ((NodA2)(nod)).lenght(); i ++)
                lista.add(((NodA2)(nod)).get(i));
        }
        if(nod instanceof NodA3){
            for(int i = 0; i < ((NodA3)(nod)).lenght(); i ++)
                lista.add(((NodA3)(nod)).get(i));
        }
        return lista;
    }
    
    /**
     * Metoda 'set_vizitat_A' seteaza starea de vizitat sau nu(false/true) a unui nod 'nod' de tip 'NodA'.
     * @param var
     * @param nod 
     */
    public void set_vizitat_A(boolean var, NodA nod){
        if(nod instanceof NodA1)
            ((NodA1)(nod)).vizitat = var;
        if(nod instanceof NodA2)
            ((NodA2)(nod)).vizitat = var;
        if(nod instanceof NodA3)
            ((NodA3)(nod)).vizitat = var;
    }
    
    /**
     * Metoda 'get_name_A' intoarce numele unui nod 'nod' de tip 'NodA'.
     * @param nod
     * @return String
     */
    public String get_name_A(NodA nod){
        if(nod instanceof NodA1)
            return ((NodA1)nod).nume;
        if(nod instanceof NodA2)
            return ((NodA2)nod).nume;
        return ((NodA3)nod).nume;
    }
    
    /**
     * Metoda 'get_version_A' intoarce versiunea unui nod 'nod' de tip 'NodA'.
     * @param nod
     * @return int
     */
    public int get_version_A(NodA nod){
        if(nod instanceof NodA1)
            return 1;
        if(nod instanceof NodA2)
            return 2;
        return 3;
    }
    
    /**
     * Metoda 'get_vizitat_A' intoarce starea de vizitat a nodului 'nod' de tip 'NodA'.
     * @param nod
     * @return boolean
     */
    public boolean get_vizitat_A(NodA nod){
        if(nod instanceof NodA1)
            return ((NodA1)nod).vizitat;
        if(nod instanceof NodA2)
            return ((NodA2)nod).vizitat;
        return ((NodA3)nod).vizitat;
    }
    
    /**
     * Metoda 'get_id_A' intoarce id-ul unui nod 'nod' de tip 'NodA'.
     * @param nod
     * @return int
     */
    public int get_id_A(NodA nod){
        if(nod instanceof NodA1)
            return ((NodA1)nod).id;
        if(nod instanceof NodA2)
            return ((NodA2)nod).id;
        return ((NodA3)nod).id;
    }
    
    /**
     * Metoda 'set_id_A' seteaza id-ul unui nod 'nod' de tip 'NodA'
     * @param nod
     * @param id 
     */
    public void set_id_A(NodA nod, int id){
        if(nod instanceof NodA1)
            ((NodA1)(nod)).id = id;
        if(nod instanceof NodA2)
            ((NodA2)(nod)).id = id;
        if(nod instanceof NodA3)
            ((NodA3)(nod)).id = id;
    }
}
