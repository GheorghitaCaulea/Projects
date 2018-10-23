
/* Am folosit clasa 'ValueNod' pentru a retine existenta unui nod de tip 'value'(valoare numerica). */

public class ValueNod extends Nod {
    
    int value;
    
    public ValueNod(int value) {
        
        this.value = value;
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
