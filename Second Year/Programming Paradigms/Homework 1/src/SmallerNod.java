import java.util.LinkedList;

/* Am folosit clasa 'SmallerNod' pentru a retine existenta unui nod de tip '<'. */

public class SmallerNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public SmallerNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
