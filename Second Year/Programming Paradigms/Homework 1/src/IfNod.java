import java.util.LinkedList;

/* Am folosit clasa 'IfNod' pentru a retine existenta unui nod de tip 'if'. */

public class IfNod extends Nod {
    
    Nod parent;
    LinkedList<Nod> child = new LinkedList<>();
    
    public IfNod(Nod n1, Nod n2, Nod n3) {
        
        child.add(n1);
        child.add(n2);
        child.add(n3);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
