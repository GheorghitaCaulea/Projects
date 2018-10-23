import java.util.HashMap;
import java.util.LinkedList;
import java.util.Stack;

/* Am folosit clasa 'ConstructTree' pentru a defini mai multe metode ce ajuta la constructia arborelui. */ 

public class ConstructTree {
    
    Stack<Nod> check = new Stack<>();
    int sw_return = 0, count_ret = 0;
    HashMap<String, Integer> hash = new HashMap<>();
    LinkedList<String> all_symbols = new LinkedList<>();
    
/* Metoda 'check_failed' era folosita pentru o verificare 'riguroasa' a variabilelor nedeclarate insa nu verifica si cazul in care o variabila era declarata intr-o structura de tip 'for' si din aceasta cauza am renuntat sa o mai folosesc, alegand sa implementez varianta 'greedy'. */

    boolean check_failed(){
        
        LinkedList<String> list = new LinkedList<>();
        Nod n;
        
        while(!check.isEmpty()){
            n = check.pop();
            System.out.println(n.getClass());
            
            if(n instanceof Init){
                list.add(((SymbolNod)((Init)n).nod).symbol);
                hash.put(((SymbolNod)((Init)n).nod).symbol, ((Init)n).value);
            }
            
            else
                if(!list.contains(((SymbolNod)n).symbol))
                    return false;
        }
        return true;   
    }

/* Metoda 'check_return' verifica existenta unui 'return' pe o pozitie corecta. */    

    boolean check_return() {
        
        return sw_return == 1 && count_ret == 0;
}

/*Metoda 'create_string' creeaza un vector de stringuri dintr-un string dat prin eliminarea parantezelor de tipul '][' cat si a tuturor whitespace-urilor. */

    String[] create_string(String line){
        String new_s[],v,c,n;
        v = line.replaceAll("]", "");
        c=  v.replaceAll("\\[", "");
        n = c.replaceAll("\\s+", " ");
        new_s = n.split(" ");
        return new_s;
    }
    
/* Metoda 'create_tree' construieste un arbore parcurgand de la dreapta la stanga vectorul de stringuri creat de metoda 'create_string', arbore in care 'frunzele' sunt reprezentate de noduri de tip 'ValueNod' sau 'SymbolNod' iar parintii reprezinta noduri de tip 'expresie', 'operatie', 'assignment' sau 'program'. */

    Nod create_tree(String[] s){
        Nod tree;
		/*In constructia arborelui am folosit o stiva in care pun nodurile create iar pentru fiecare nod intalnit stiu cate noduri 'copil' trebuie sa scot de pe stiva si sa i le atribui drept copii folosind Decoratorul. */ 
        Stack<Nod> stack = new Stack<>();

        for(int i = s.length - 1; i >= 0; i --){

            int sw = 0;
            if(s[i].equals("+") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                AddNod addn = new AddNod(n1, n2);
                stack.push(addn);
                sw = 1;
            }
            
            if(s[i].equals("*") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                MultiplyNod muln = new MultiplyNod(n1, n2);
                stack.push(muln);
                sw = 1;
            }
            
            if(s[i].equals("==") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                EqualNod eqln = new EqualNod(n1, n2);
                stack.push(eqln);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("<") &&  sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                SmallerNod smln = new SmallerNod(n1, n2);
                stack.push(smln);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("=") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                
				if(all_symbols.getLast().equals(((SymbolNod)n1).symbol))
                    all_symbols.remove(((SymbolNod)n1).symbol);
                
				if(n2 instanceof ValueNod)
                    check.push(new Init(n1, ((ValueNod)n2).value));
                else {
                    if(all_symbols.contains(((SymbolNod)n1).symbol)) {
                        check.push(n1);
                        all_symbols = new LinkedList<>();
                    }
                    else
                        check.push(new Init(n1, 0));
                }
                all_symbols = new LinkedList<>();        
                AssignedNod asgn = new AssignedNod(n1, n2);
                stack.push(asgn);
                sw = 1;
            }
            
            if(s[i].equals(";") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                SemicolonNod smn = new SemicolonNod(n1, n2);
                stack.push(smn);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("if") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                Nod n3 = stack.pop();
                if(n2 instanceof ReturnNod || n3 instanceof ReturnNod)
                    count_ret --;
                IfNod ifn = new IfNod(n1, n2, n3);
                stack.push(ifn);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("for") && sw == 0){
                Nod n1 = stack.pop();
                Nod n2 = stack.pop();
                Nod n3 = stack.pop();
                Nod n4 = stack.pop();
                if(n4 instanceof ReturnNod)
                    count_ret--;
                ForNod forn = new ForNod(n1, n2, n3, n4);
                stack.push(forn);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("assert") && sw == 0){
                Nod n1 = stack.pop();
                if(n1 instanceof SymbolNod)
                    check.push(n1);
                AssertNod asn = new AssertNod(n1);
                stack.push(asn);
                sw = 1;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].equals("return") && sw == 0){
                Nod n1 = stack.pop();
                ReturnNod retn = new ReturnNod(n1);
                stack.push(retn);
                sw = 1;
                sw_return = 1;
                count_ret ++;
                all_symbols = new LinkedList<>();
            }
            
            if(s[i].matches("\\d+") && sw == 0) {
                ValueNod valn = new ValueNod(Integer.parseInt(s[i]));
                stack.push(valn);
                sw = 1;
            
            }
            
            if(!s[i].matches("\\d+") && sw == 0){
                    SymbolNod symn = new SymbolNod(s[i]);
                    all_symbols.add(s[i]);
                    check.push(symn);
                    stack.push(symn);
            }
        }
       /* La sfarsitul metodei returnez ultimul Nod ramas pe stiva, nod ce va reprezenta radacina. */ 
        return (Nod)stack.pop();
    }
    
}
    
    
            
            
            
            
 
