import java.util.HashMap;
import java.util.LinkedList;
import java.util.Objects;

/* Am folosit clasa 'Evaluate' pentru a implementa metodele 'visit' folosite de Design Pattern-ul Visitor in evaluarea arborelui construit. */ 
public class Evaluate implements Visitor {
// Mapa 'hash' retine atat initializarile variabilelor cat si modificarile ce au loc pe parcursul evaluarii programului.
    HashMap<String, Integer> hash = new HashMap<>();
// Varibila 'sw_check' este folosita pentru a indica daca este respectata conditia de 'scope'.
    boolean sw_check = true;
//Lista 'return_object' retine obiectele de intors.
    LinkedList<Object> return_object = new LinkedList<>();
//Lista 'assert_value' retine valorile de adevar ale operatiilor de tip 'assert'.
    LinkedList<Boolean> assert_value = new LinkedList<>();
    

    @Override
    public Object visit(AddNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Integer op1, op2;
        
        if((n1.accept(this)) instanceof String){
            op1 = hash.get((String)(n1.accept(this)));
            
            if(op1 == null){
                op1 = 0;
                sw_check = false;
            }
        }        
        else
            op1 = ((Integer)n1.accept(this));
        
        
        if((n2.accept(this)) instanceof String){
            op2 = hash.get((String)(n2.accept(this)));
            
            if(op2 == null) {
                op2 = 0;
                sw_check = false;
            }
        }
        
        else
            op2 = ((Integer)n2.accept(this));
        
        return (op1 + op2);
    }

    @Override
    public Object visit(AssertNod a) {
        Nod n = a.child.get(0);
        assert_value.add((Boolean)n.accept(this));
        
        return null;
    } 

    @Override
    public Object visit(EqualNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Integer op1, op2;
        
        if(n1.accept(this) instanceof Boolean && n1.accept(this) instanceof Boolean)
            return (Objects.equals((Boolean)n1.accept(this), (Boolean)n2.accept(this)));
        
        else{
            if((n1.accept(this)) instanceof String){
                op1 = hash.get((String)(n1.accept(this)));
            
                if(op1 == null){
                    op1 = 0;
                    sw_check = false;
                }
            }        
            else
                op1 = ((Integer)n1.accept(this));
        
        
            if((n2.accept(this)) instanceof String){
                op2 = hash.get((String)(n2.accept(this)));
                
                if(op2 == null) {
                    op2 = 0;
                    sw_check = false;
                }
            }
        
            else
                op2 = ((Integer)n2.accept(this));
        }
        
        return (op1 == op2);
           
    }

    @Override
    public Object visit(AssignedNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        String k = ((String)n1.accept(this));
        Integer v;
        
        if(n2.accept(this) instanceof String){
            v = hash.get((String)(n2.accept(this)));
            
            if(v == null){
                v = 0;
                sw_check = false;
            }
        }
        else
            v = (Integer)n2.accept(this);
        hash.put(k, v);
        
        return null;
    }

    @Override
    public Object visit(ForNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Nod n3 = a.child.get(2);
        Nod n4 = a.child.get(3);
        n1.accept(this);
        
        while((Boolean)n2.accept(this)){
            n4.accept(this);
            n3.accept(this);
        }
        
        return null;
    }

    @Override
    public Object visit(IfNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Nod n3 = a.child.get(2);
        
        if((Boolean)n1.accept(this))
            n2.accept(this);
        else
            n3.accept(this);
        
        return null;
    }

    @Override
    public Object visit(MultiplyNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Integer op1, op2;
        
        if((n1.accept(this)) instanceof String){
            op1 = hash.get((String)(n1.accept(this)));
            
            if(op1 == null){
                op1 = 0;
                sw_check = false;
            }
        }        
        else
            op1 = ((Integer)n1.accept(this));
        
        
        if((n2.accept(this)) instanceof String){
            op2 = hash.get((String)(n2.accept(this)));
            if(op2 == null) {
                op2 = 0;
                sw_check = false;
            }
        }
        
        else
            op2 = ((Integer)n2.accept(this));
        
        return (op1 * op2);
    }

    @Override
    public Object visit(ReturnNod a) {
        Nod n1 = a.child.get(0);
        Integer op;
 
        
        if(n1.accept(this) instanceof Boolean)
            return_object.add(n1.accept(this));
        
        else{
            
            if(n1.accept(this) instanceof String){
                op = hash.get((String)(n1.accept(this)));
            
                if(op == null){
                    op = 0;
                    sw_check = false;
                }
            }        
            else
                op = ((Integer)n1.accept(this));
        
            return_object.add(op);
        }
        return null;
    }

    @Override
    public Object visit(SemicolonNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        n1.accept(this);
        n2.accept(this);
        
        return null;
    }

    @Override
    public Object visit(SmallerNod a) {
        Nod n1 = a.child.get(0);
        Nod n2 = a.child.get(1);
        Integer op1, op2;
        
        if((n1.accept(this)) instanceof String){
            op1 = hash.get((String)(n1.accept(this)));
            
            if(op1 == null){
                op1 = 0;
                sw_check = false;
            }
        }        
        else
            op1 = ((Integer)n1.accept(this));
        
        
        if((n2.accept(this)) instanceof String){
            op2 = hash.get((String)(n2.accept(this)));
            if(op2 == null) {
                op2 = 0;
                sw_check = false;
            }
        }
        
        else
            op2 = ((Integer)n2.accept(this));
        
        return (op1 < op2);
    }

    @Override
    public Object visit(SymbolNod a) {

        return a.symbol;
    }

    @Override
    public Object visit(ValueNod a) {
        
        return a.value;
    }

}
