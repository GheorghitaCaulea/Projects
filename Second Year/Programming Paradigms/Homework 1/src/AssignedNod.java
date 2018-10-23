import java.util.LinkedList;

/* Am folosit clasa 'AssignedNod pentru a retine existenta unui nod de tip 'assignment'. */

public class AssignedNod  extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public AssignedNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    @Override
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
