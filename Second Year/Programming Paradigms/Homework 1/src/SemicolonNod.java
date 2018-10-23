import java.util.LinkedList;

/* Am folosit clasa 'SemicolonNod' pentru a retine existenta unui nod de tip ';'. */

public class SemicolonNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public SemicolonNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
