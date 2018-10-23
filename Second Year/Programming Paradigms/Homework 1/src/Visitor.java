public interface Visitor {
    
    public Object visit(AddNod a);
     
    public Object visit(AssertNod a);
    
    public Object visit(AssignedNod a);
    
    public Object visit(EqualNod a);
    
    public Object visit(ForNod a);
    
    public Object visit(IfNod a);
    
    public Object visit(MultiplyNod a);
    
    public Object visit(ReturnNod a);
    
    public Object visit(SemicolonNod a);
    
    public Object visit(SmallerNod a);
    
    public Object visit(SymbolNod a);
    
    public Object visit(ValueNod a);
    
}
