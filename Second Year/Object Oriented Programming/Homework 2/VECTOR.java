import java.util.ArrayList;

/**
 *Am implementat clasa 'VECTOR' folosindu-ma de ArrayList.
 *Metodele implementate(add, remove, get, lenght) va vor ajuta la realizarea operatiilor din graf. 
 * @author Caulea Gheorghita
 * @param <E>
 */
public class VECTOR<E>{
    public ArrayList<E> als;
    
    public VECTOR(){
        als = new ArrayList<>();
    }
    
    public void add(E nod){
        als.add(nod);
    }
    
    public void remove(E nod){
        als.remove(nod);
    }
    
    public E get(int index){
        return als.get(index);
    }
    
    public int lenght(){
        return als.size();
    }
}
