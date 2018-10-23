/**
 *CLasa 'NodB1' este folosita pentru noduri de tip 'NodB' la iteratia 1.
 * @author Caulea Gheorghita
 */
public class NodB1 extends NodB {
    String nume;
    LIST<Nod> lst = new LIST<>();
    boolean vizitat = false;
    int id = 0;
    
    /**
     * Constructor cu parametru numele.
     * @param nume 
     */
    public NodB1(String nume){
        this.nume = nume;
    }
    
    /**
     * Metoda 'add' adauga un element in lista in care sunt retinuti vecinii.
     * @param nod 
     */
    public void add(Nod nod){
        lst.add(nod);
    }
    
    /**
     * Metoda 'remove' sterge un element din lista in care sunt retinuti vecinii.
     * @param nod 
     */
    public void remove(Nod nod){
        lst.remove(nod);
    }
    
    /**
     * Metoda 'get' intoarce nodul de pe pozitia 'index' din lista in care sunt retinuti vecinii.
     * @param index
     * @return Nod
     */
    public Nod get(int index){
        return lst.get(index);
    }
    
    /**
     * Metoda 'lenght' intoarce lungimea listei in care sunt retinuti vecinii.
     * @return int
     */
    public int lenght(){
        return lst.lenght();
    }
}
