import java.util.LinkedList;

/**
 *
 * @author Caulea Gheorghita
 */
public class Node {
    int name, number_of_neigh = 0;
    LinkedList<Node> neigh_list;
    
    public Node(int val){
        neigh_list = new LinkedList<>();
        name = val;
    }
    
    boolean check(Node n){
        return neigh_list.contains(n);
    }
    
    public void add(Node n){
        neigh_list.add(n);
        number_of_neigh++;
    }
    
    public void remove(Node n){
        neigh_list.remove(n);
        number_of_neigh--;
    }                
}
