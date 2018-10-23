import java.util.LinkedList;

/**
 *Clasa Nod simuleaza comportamentul unui graf si contine metode specifice elementelor unui graf.
 * @author Caulea Gheorghita
 */
public class Nod {
    public LinkedList<Nod> ls = new LinkedList<>();
    int type_a, type_b, type_c;
    
    public Nod(int a, int b, int c){
        this.type_a = a;
        this.type_b = b;
        this.type_c = c;
    }
    public Nod(){
        
    }
    
    /**
     * Metoda 'get' cauta in graf un nod dupa 'name' si il intoarce.
     * @param ls
     * @param name
     * @return Nod 
     */
    public Nod get(LinkedList<Nod> ls, String name){
        int i;
        for(i = 0; i < ls.size(); i ++){
            if(ls.get(i) instanceof NodA1)
                if(((NodA1)((NodA)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodA2)
                if(((NodA2)((NodA)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodA3)
                if(((NodA3)((NodA)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodB1)
                if(((NodB1)((NodB)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodB2)
                if(((NodB2)((NodB)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodB3)
                if(((NodB3)((NodB)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodC1)
                if(((NodC1)((NodC)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodC2)
                if(((NodC2)((NodC)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
            if(ls.get(i) instanceof NodC3)
                if(((NodC3)((NodC)(ls.get(i)))).nume.equals(name))
                    return ls.get(i);
        }
        return null;
    }
    
    /**
     * Metoda 'add' aduga nodul cu numele 'nume2' in lista de vecini ai nodului cu numele 'nume1'.
     * De asemeni va adauga si in lista de vecini ai nodului cu numele 'nume2', nodul cu numele 'nume1'.
     * @param nume1
     * @param nume2 
     */
    public void add(String nume1, String nume2){
        Nod a, b;
        a = get(ls, nume1);
        b = get(ls, nume2);
        if(a == null || b == null || get_neighbours(a).contains(b))
            return;
        if(a instanceof NodA)
            ((NodA)(a)).add(a, b);
        if(a instanceof NodB)
            ((NodB)(a)).add(a, b);
        if(a instanceof NodC)
            ((NodC)(a)).add(a, b);
    }
    
    /**
     * Metoda 'add' aduga nodul cu numele 'nume2' in lista de vecini ai nodului cu numele 'nume1'. 
     * Reciproc nu.
     * @param nume1
     * @param nume2 
     */
    public void add_vecin(String nume1, String nume2){
        Nod a, b;
        a = get(ls, nume1);
        b = get(ls, nume2);
        if(a instanceof NodA)
            ((NodA)(a)).add_vecin_A(a, b);
        if(a instanceof NodB)
            ((NodB)(a)).add_vecin_B(a, b);
        if(a instanceof NodC)
            ((NodC)(a)).add_vecin_C(a, b);
    }
    
    /**
     * Metoda 'add_muchie' adauga o muchie intre nodul cu numele 'nume1' si nodul cu numele 'nume2'.
     * @param nume1
     * @param nume2 
     */
    public void add_muchie(String nume1, String nume2){
        add(nume1, nume2);
    }
    
    /**
     * Metoda 'initialization' initializeaza un nod al grafului dupa versiune, setare si nume.
     * @param ABC
     * @param nod
     * @param Type
     * @param nume
     * @return Nod 
     */
    public Nod initialization(String ABC, Nod nod, int Type, String nume){
        NodA a = new NodA();
        NodB b = new NodB();
        NodC c = new NodC();
        if(ABC.equals("NodA"))
            return a.initialization(nod, Type, nume);
        if(ABC.equals("NodB"))
            return b.initialization(nod, Type, nume);
        return c.initialization(nod, Type, nume);
    }
    
    /**
     * Metoda 'init_insert' initializeaza si adauga un nod in graf.
     * @param ABC
     * @param nod
     * @param Type
     * @param nume 
     */
    public void init_insert(String ABC, Nod nod, int Type, String nume){
        Nod nd = initialization(ABC, nod, Type, nume);
        ls.add(nd);
    }
    
    /**
     * Metoda 'remove' sterge nodul cu numele 'nume' din graf.
     * Toate aparitiile nodului cu numele 'nume' ca vecin al altor noduri, vor fi sterse. 
     * @param nume
     * @param Graph 
     */
    public void remove(String nume, Nod Graph){
        Nod nod1 = get(ls, nume);
        if(nod1 == null)
            return;
        if(nod1 instanceof NodA)
            ((NodA)(nod1)).remove_nod_A(((NodA)(nod1)), Graph);
        if(nod1 instanceof NodB)
            ((NodB)(nod1)).remove_nod_B(((NodB)nod1), Graph);
        if(nod1 instanceof NodC)
            ((NodC)(nod1)).remove_nod_C(((NodC)(nod1)), Graph);
        ls.remove(nod1);
    }
    
    /**
     * Metoda 'remove_muchie' sterge muchia dintre nodul cu numele 'nume1' si cel cu numele 'nume2'.
     * @param nume1
     * @param nume2 
     */
    public void remove_muchie(String nume1, String nume2){
        Nod a = get(ls, nume1);
        Nod b = get(ls, nume2);
        if(a == null || b == null)
            return;
        if(a instanceof NodA1)
            ((NodA1)((NodA)(a))).remove(b);
        if(a instanceof NodA2)
            ((NodA2)((NodA)(a))).remove(b);
        if(a instanceof NodA3)
            ((NodA3)((NodA)(a))).remove(b);
        if(a instanceof NodB1)
            ((NodB1)((NodB)(a))).remove(b);
        if(a instanceof NodB2)
            ((NodB2)((NodB)(a))).remove(b);
        if(a instanceof NodB3)
            ((NodB3)((NodB)(a))).remove(b);
        if(a instanceof NodC1)
            ((NodC1)((NodC)(a))).remove(b);
        if(a instanceof NodC2)
            ((NodC2)((NodC)(a))).remove(b);
        if(a instanceof NodC3)
            ((NodC3)((NodC)(a))).remove(b);
        if(b instanceof NodA1)
            ((NodA1)((NodA)(b))).remove(a);
        if(b instanceof NodA2)
            ((NodA2)((NodA)(b))).remove(a);
        if(b instanceof NodA3)
            ((NodA3)((NodA)(b))).remove(a);
        if(b instanceof NodB1)
            ((NodB1)((NodB)(b))).remove(a);
        if(b instanceof NodB2)
            ((NodB2)((NodB)(b))).remove(a);
        if(b instanceof NodB3)
            ((NodB3)((NodB)(b))).remove(a);
        if(b instanceof NodC1)
            ((NodC1)((NodC)(b))).remove(a);
        if(b instanceof NodC2)
            ((NodC2)((NodC)(b))).remove(a);
        if(b instanceof NodC3)
            ((NodC3)((NodC)(b))).remove(a);
    }
    
    /**
     * Metoda 'get_neighbours' returneaza o lista de vecini ai nodului 'nod'
     * @param nod
     * @return LinkedList Nod
     */
    public LinkedList<Nod> get_neighbours(Nod nod){
        LinkedList<Nod> lista = new LinkedList<>();
        if(nod instanceof NodA)
            lista = ((NodA)(nod)).get_neighbours_A((NodA)(nod));
        if(nod instanceof NodB)
            lista = ((NodB)(nod)).get_neighbours_B((NodB)(nod));
        if(nod instanceof NodC)
            lista = ((NodC)(nod)).get_neighbours_C((NodC)(nod));
        return lista;
    }
    
    /**
     * Metoda 'set_vizitat' seteaza starea de vizitat sau nu(true/false) a unui nod.
     * @param var
     * @param nod 
     */
    public void set_vizitat(boolean var, Nod nod){
        if(nod instanceof NodA)
            ((NodA)(nod)).set_vizitat_A(var,((NodA)(nod)));
        if(nod instanceof NodB)
            ((NodB)(nod)).set_vizitat_B(var,((NodB)(nod)));
        if(nod instanceof NodC)
            ((NodC)(nod)).set_vizitat_C(var,((NodC)(nod)));
    }
    
    /**
     * Metoda 'get_name' intoarce numele unui obiect de tip nod.
     * @param nod
     * @return String
     */
    public String get_name(Nod nod){
        if(nod instanceof NodA)
            return ((NodA)(nod)).get_name_A(((NodA)(nod)));
        if(nod instanceof NodB)
            return ((NodB)(nod)).get_name_B(((NodB)(nod)));
        return ((NodC)(nod)).get_name_C((NodC)(nod));
    }
    
    /**
     * Metoda 'get_version' intoarce veriunea unui nod.
     * @param nod
     * @return int
     */
    public int get_version(Nod nod){
        if(nod instanceof NodA)
            return ((NodA)(nod)).get_version_A((NodA)(nod));
        if(nod instanceof NodB)
            return ((NodB)(nod)).get_version_B((NodB)(nod));
        return ((NodC)(nod)).get_version_C((NodC)(nod));
    }
    
    /**
     * Metoda 'get_implentation' ne spune modul in care sunt mentinute nodurile adiacente ale unui nod.
     * @param nod
     * @return String 
     */
    public String get_implemantation(Nod nod){
        if(get_version(nod) == 1)
            return "LIST";
        if(get_version(nod) == 2)
            return "VECTOR";
        return "SET";
    }
    
    /**
     * Metoda 'get_vizitat' intoarce starea de vizitat a unui nod.
     * @param nod
     * @return boolean
     */
    public boolean get_vizitat(Nod nod){
        if(nod instanceof NodA)
            return ((NodA)(nod)).get_vizitat_A(((NodA)(nod)));
        if(nod instanceof NodB)
            return ((NodB)(nod)).get_vizitat_B(((NodB)(nod)));
        return ((NodC)(nod)).get_vizitat_C(((NodC)(nod)));
    }
    
    /**
     * Metoda 'get_class' intoarcea clasa unui nod.
     * @param nod
     * @return String
     */
    public String get_class(Nod nod){
        if(nod instanceof NodA)
            return "NodA";
        if(nod instanceof NodB)
            return "NodB";
        return "NodC";
    }
    
    /**
     * Metoda 'get_id' intoarce id-ul unui nod.
     * @param nod
     * @return int
     */
    public int get_id(Nod nod){
        if(nod instanceof NodA)
            return ((NodA)(nod)).get_id_A((NodA)(nod));
        if(nod instanceof NodB)
            return ((NodB)(nod)).get_id_B((NodB)(nod));
        return ((NodC)(nod)).get_id_C((NodC)(nod));
    }
    
    /**
     * Metoda 'set_id' seteaza id-ul unui nod.
     * @param nod
     * @param id 
     */
    public void set_id(Nod nod, int id){
        if(nod instanceof NodA)
            ((NodA)(nod)).set_id_A(((NodA)(nod)), id);
        if(nod instanceof NodC)
            ((NodC)(nod)).set_id_C(((NodC)(nod)), id);
        if(nod instanceof NodB)
            ((NodB)(nod)).set_id_B(((NodB)(nod)), id);
    }
}
