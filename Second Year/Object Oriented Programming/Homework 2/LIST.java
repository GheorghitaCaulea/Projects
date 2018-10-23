import java.util.LinkedList;

/**
 *Am implementat clasa LIST folosindu-ma de LinkedList.
 *Metodele implementate(add, remove, get, lenght) va vor ajuta la realizarea operatiilor din graf. 
 * @author Caulea Gheorghita
 * @param <E>
 */
public class LIST<E>{
    LinkedList<E> lsl;
    public LIST(){
      lsl = new LinkedList<>();  
    }
    
    public void add(E nod){
        lsl.add(nod);
    }
    
    public void remove(E nod){
        lsl.remove(nod);
    }
    
    public E get(int index){
       return lsl.get(index);
    }
    
    public int lenght(){
        return lsl.size();
    }
}
