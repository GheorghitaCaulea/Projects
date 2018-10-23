import java.util.LinkedList;

/* Am folosit clasa 'AddNod' pentru a retine existenta unui nod de tip adunare '+'. */

public class AddNod extends Nod {
    
    LinkedList<Nod> child = new LinkedList<>();
    
    public AddNod(Nod n1, Nod n2) {
        
        child.add(n1);
        child.add(n2);
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
