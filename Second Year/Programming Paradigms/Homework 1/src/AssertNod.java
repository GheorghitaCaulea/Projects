import java.util.LinkedList;

/* Am folosit clasa 'AsserNod' pentru a retine existenta unui nod de tip 'assert'. */

public class AssertNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public AssertNod(Nod n1) {
        
        child.add(n1);
    
    }
    
    @Override
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }

}
