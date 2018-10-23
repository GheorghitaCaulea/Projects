import java.util.LinkedList;

/* Am folosit clasa 'MultiplyNod' pentru a retine existenta unui nod de tip '*'. */

public class MultiplyNod extends Nod {
    
    Nod parent;
    LinkedList<Nod> child = new LinkedList<>();
    
    public MultiplyNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
