

/**
 *Aceasta clasa e folosita pentru un obiect de tip cerc.
 * @author Caulea Gheorghita
 */
public class Circle extends GenericObjects {
    double r, x, y;
    int id;
    
    public Circle(double r, double x, double y, int id){
        this.r = r;
        this.y = y;
        this.x = x;
        this.id = id;
    }
    
    /**
     *Metoda getRectangle returneaza coordonatele dreptunghiului incadrator al cercului(x1,x2,y1,y2).
     *In cazul cercului dreptunghiul este de fapt un patrat. 
     * @param r
     * @param x
     * @param y
     */
    double[] getRectangle(double r, double x, double y){
        double points[] = new double[4];
        points[0] = x - r;
        points[1] = x + r;
        points[2] = y - r;
        points[3] = y + r;
        return points;
    }
   
    int getId(){
       return id; 
    }
    
    /**
     * Metoda getCheckPoint verifica daca un punct de afla in interiorul cercului si intoarce o valoare de adevar corespunzatoare.
     * Metoda verifica daca distanta dintre punct si centrul cercului este mai mica sau egala cu raza.
     * @param x1
     * @param y1
     * @return boolean
     */
    boolean getCheckPoint(double x1, double y1){
        return (x1 - x)*(x1 - x) + (y1 - y)*(y1 - y) <= r*r;
    }
    
}
