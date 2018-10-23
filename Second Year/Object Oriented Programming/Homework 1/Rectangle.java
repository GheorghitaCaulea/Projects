
/**
 *Clasa Rectangle este folosita pentru un obiect de tip rectangle.
 * @author Caulea Gheorghita
 */
public class Rectangle extends GenericObjects {
    double x1, x2, y1, y2;
    int id;
    
    public Rectangle(double x1, double x2, double y1, double y2, int id){
        this.x1 = x1;
        this.x2 = x2;
        this.y1 = y1;
        this.y2 = y2;
        this.id = id;
    }
    
    /**
     * Metoda getRectangle returneaza coordonatele dreptunghiului incadrator al dreptunghiului(x1,x2,y1,y2).
     * In cazul dreptunghiului, coordonatele vor coincide cu cele ale obiectului.
     * @param x1
     * @param x2
     * @param y1
     * @param y2
     * @return double[]
     */
    double[] getRectangle(double x1, double x2, double y1, double y2){
        double points[] = new double[4];
        points[0] = x1;
        points[1] = x2;
        points[2] = y1;
        points[3] = y2;
        return points;
    }
    
    int getId(){
       return id; 
    }
    
    /**
     * Metoda getCheckPoint verifica daca un punct de afla in interiorul dreptunghiului si intoarce o valoare de adevar corespunzatoare.
     * Metoda compara coordonatele punctului cu coordonatele dreptunghiului.
     * @param x
     * @param y
     * @return boolean
     */
    boolean getCheckPoint(double x, double y){
        return (x >= x1) && (x <= x2) && (y <= y2) && (y >= y1);
    }
}
