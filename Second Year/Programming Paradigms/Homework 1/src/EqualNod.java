import java.util.LinkedList;

/* Am folosit clasa 'EqualNod' pentru a retine existenta unui nod de tip '=='. */

public class EqualNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public EqualNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
