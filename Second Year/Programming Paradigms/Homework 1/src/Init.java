
/*Am folosit clasa 'InitNod' pentru a crea un nod ce se foloseste pentru a retine initializarea unei variabile. Foloseam aceasta clasa pentru verificarea riguroasa de 'scope'. */

public class Init extends Nod {
    Nod nod;
    int value;
    
    public Init(Nod nod, int value){
        this.nod = nod;
        this.value = value;
    }
}
