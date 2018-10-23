
/* Am folosit clasa 'SymbolNod' pentru a retine existenta unui nod de tip 'symbol'(nume de variabila). */

public class SymbolNod extends Nod {
    
    String symbol;
    
    public SymbolNod(String symbol) {
        
        this.symbol = symbol;
    
    }
    
    public Object accept(Visitor v) {
        
        return v.visit(this);
    
    }
    
}
