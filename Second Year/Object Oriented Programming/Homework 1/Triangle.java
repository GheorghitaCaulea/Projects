

import static java.lang.Math.abs;

/**
 *Clasa Triangle este folosita pentru un obiect de tip triunghi.
 * @author Caulea Gheorghita
 */
public class Triangle extends GenericObjects {
    double x1, x2, x3, y1, y2, y3;
    int id;
    
    public Triangle(double x1, double x2, double x3, double y1, double y2, double y3, int id){
        this.x1 = x1;
        this.x2 = x2;
        this.x3 = x3;
        this.y1 = y1;
        this.y2 = y2;
        this.y3 = y3;
        this.id = id;
    }
    
    /**
     * Metoda getRectangle returneaza coordonatele dreptunghiului incadrator al trunghiului(x1,x2,y1,y2).
     * In cazul in care "varful triunghiului depaseste la stanga sau dreapta baza", metoda va incadra corespunzator.
     * @param x1
     * @param x2
     * @param x3
     * @param y1
     * @param y2
     * @param y3
     * @return double[]
     */
    double[] getRectangle(double x1, double x2, double x3, double y1, double y2, double y3){
        double points[] = new double[4];
        if(x1 < x2){
            points[0] = x1;
            points[1] = x3;
            points[2] = y2;
            points[3] = y1;
            return points;
        }
        
        if(x1 > x3){
            points[0] = x2;
            points[1] = x1;
            points[2] = y2;
            points[3] = y1;
            return points;
        }
        points[0] = x2;
        points[1] = x3;
        points[2] = y2;
        points[3] = y1;
        return points;
    }
    
    int getId(){
       return id; 
    }
    
    /**
     * Metoda getCheckPoint verifica daca un punct se afla in interiorul triunghiului si intoarce o valoare de adevar corespunzatoare.
     * Metoda foloseste o verificare pe baza de arii.
     * Pentru calcularea ariilor se folosesc formulele obtinute din determinanti.
     * @param x
     * @param y
     * @return boolean
     */
    boolean getCheckPoint(double x, double y){
        double A_tr = abs(x1*y2 + x2*y3 + x3*y1 - x3*y2 - x1*y3 - x2*y1);
        double A_tr1 = abs(x*y1 + x1*y2 + x2*y - x2*y1 - x*y2 - x1*y);
        double A_tr2 = abs(x*y2 + x2*y3 + x3*y - x3*y2 - x*y3 - x2*y);
        double A_tr3 = abs(x*y1 + x1*y3 + x3*y - x3*y1 - x*y3 - x1*y);
        return A_tr == A_tr1 + A_tr2 + A_tr3;         
    }
}

