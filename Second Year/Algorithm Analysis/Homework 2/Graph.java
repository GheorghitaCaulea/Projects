import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;

/**
 *
 * @author Caulea Gheorghita
 */
public class Graph {
    LinkedList<Node> nodes = new LinkedList<>();
    LinkedList<Integer> check_node = new LinkedList<>();
    
    public void add(int n1, int n2){
        Node node1, node2;
        
        if(!check_node.contains(n1)){ 
            node1 = new Node(n1);
            check_node.add(n1);
        }
        else
            node1 = nodes.get(check_node.indexOf(n1));
        
        if(!check_node.contains(n2)){
            node2 = new Node(n2);
            check_node.add(n2);
        }
        else
            node2 = nodes.get(check_node.indexOf(n2));
        
        if(!nodes.contains(node1))
            nodes.add(node1);
       
        if(!nodes.contains(node2))
            nodes.add(node2);
        
        node2.add(node1);
        node1.add(node2);
    }
    
    public Node reset(Graph g){
        Node node_to_return;
        node_to_return = g.nodes.removeFirst();
        g.check_node.removeFirstOccurrence(node_to_return.name);
        for(Node n1:g.nodes){
            if(n1.check(node_to_return))
                n1.remove(node_to_return);
        }
        
        Collections.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                if(o1.number_of_neigh < o2.number_of_neigh)
                    return 1;
                if(o1.number_of_neigh > o2.number_of_neigh)
                    return -1;
                return 0;
            }
        });
        
        return node_to_return;
    }
    
    public void fine_reset(Graph g){

        Collections.sort(nodes, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                if(o1.number_of_neigh < o2.number_of_neigh)
                    return 1;
                if(o1.number_of_neigh > o2.number_of_neigh)
                    return -1;
                return 0;
            }
        });
    }
    
}
