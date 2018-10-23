import java.util.LinkedList;

/* Am folosit clasa 'ReturnNod' pentru a retine existenta unui nod de tip 'return'. */

public class ReturnNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public ReturnNod(Nod n1) {
        
        child.add(n1);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
