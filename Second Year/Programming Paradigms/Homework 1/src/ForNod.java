import java.util.LinkedList;

/* Am folosit clasa 'ForNod' pentru a retine existenta unui nod de tip 'for'. */

public class ForNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public ForNod(Nod n1, Nod n2, Nod n3, Nod n4) {
        
        child.add(n1);
        child.add(n2);
        child.add(n3);
        child.add(n4);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
