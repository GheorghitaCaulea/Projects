import java.util.HashSet;


/**
 *Am implementat clasa 'SET' folosindu-ma de HashSet.
 *Metodele implementate(add, remove, get, lenght) va vor ajuta la realizarea operatiilor din graf. 
 * @author Caulea Gheorghita
 * @param <E>
 */
public class SET<E>{
    public HashSet<E> lhs;
    
    public SET(){
        lhs = new HashSet<>();
    }
    
    public void add(E nod){
        lhs.add(nod);
    }
    
    public void remove(E nod){
        lhs.remove(nod);
    }
    
    public int lenght(){
        return lhs.size();
    }
    
    public E get(int index){
        Object [] al;
        al = lhs.toArray();
        return (E)al[index];   
    }
}
