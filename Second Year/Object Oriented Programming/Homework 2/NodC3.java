/**
 *CLasa 'NodC3' este folosita pentru noduri de tip 'NodC' la iteratia 3.
 * @author gicu
 */
public class NodC3 extends NodC {
    String nume;
    SET<Nod> s = new SET<>();
    boolean vizitat = false;
    int id = 0;
    
    /**
     * Constructor cu parametru numele.
     * @param nume 
     */
    public NodC3(String nume){
        this.nume = nume;
    }
    
    /**
     * Metoda 'add' adauga un element in Set-ul in care sunt retinuti vecinii.
     * @param nod 
     */
    public void add(Nod nod){
        s.add(nod);
    }
    
    /**
     * Metoda 'remove' sterge un element din Set-ul in care sunt retinuti vecinii.
     * @param nod 
     */
    public void remove(Nod nod){
        s.remove(nod);
    }
    
    /**
     * Metoda 'lenght' intoarce dimensiunea Set-ului in care sunt retinuti vecinii.
     * @return int
     */
    public int lenght(){
        return s.lenght();
    }
    
     /**
     * Metoda 'get' intoarce nodul de pe pozitia 'index' din Set-ul in care sunt retinuti vecinii.
     * @param index
     * @return Nod
     */
    public Nod get(int index){
        return s.get(index);
    }
}
