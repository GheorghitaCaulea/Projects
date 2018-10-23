/**
 *CLasa 'NodB2' este folosita pentru noduri de tip 'NodB' la iteratia 2.
 * @author Caulea Gheorghita
 */
public class NodB2 extends NodB{
    String nume;
    VECTOR<Nod> v = new VECTOR();
    boolean vizitat = false;
    int id = 0;
    
    /**
     * Constructor cu parametru numele.
     * @param nume 
     */
    public NodB2(String nume){
        this.nume = nume;
    }
    
    /**
     * Metoda 'add' adauga un element in vectorul in care sunt retinuti vecinii.
     * @param nod 
     */
    public void add(Nod nod){
        v.add(nod);
    }
    
    /**
     * Metoda 'remove' sterge un element din vectorul in care sunt retinuti vecinii.
     * @param nod 
     */
    public void remove(Nod nod){
        v.remove(nod);
    }
    
    /**
     * Metoda 'lenght' intoarce lungimea vectorului in care sunt retinuti vecinii.
     * @return int
     */
    public int lenght(){
        return v.lenght();
    }
    
    /**
     * Metoda 'get' intoarce nodul de pe pozitia 'index' vectorul in care sunt retinuti vecinii.
     * @param index
     * @return Nod
     */
    public Nod get(int index){
        return v.get(index);
    }
}
