
import static java.lang.Math.abs;

/**
 *Clasa Diamond este folosita pentru un obiect de tip romb.
 * @author Caulea Gheorghita
 */
public class Diamond extends GenericObjects {
    double x1, x2, x3, x4, y1, y2, y3, y4;
    int id;
    
    public Diamond(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, int id){
        this.x1 = x1;
        this.x2 = x2;
        this.x3 = x3;
        this.x4 = x4;
        this.y1 = y1;
        this.y2 = y2;
        this.y3 = y3;
        this.y4 = y4;
        this.id = id;
    }
    
    /**
     * Metoda getRectangle returneaza coordonatele dreptunghiului incadrator al cercului(x1,x2,y1,y2).
     * @param x1
     * @param x2
     * @param x3
     * @param x4
     * @param y1
     * @param y2
     * @param y3
     * @param y4
     * @return double[]
     */
    double[] getRectangle(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4){
         double points[] = new double[4];
         points[0] = x2;
         points[1] = x4;
         points[2] = y3;
         points[3] = y1;
         return points;
    }
    
    int getId(){
       return id; 
    }
    
    /**
     * Metoda getCheckPoint verifica daca un punct se afla in interiorul rombului si intoarce o valoare de adevar corespunzatoare.
     * Metoda imparte rombul in doua triunghiuri si foloseste ariile pentru a verifica daca punctul se gaseste in interior.
     * Pentru calcularea ariilor se folosesc formulele obtinute din determinanti.
     * @param x
     * @param y
     * @return boolean
     */
    boolean getCheckPoint(double x, double y){
        double A_tr = abs(x1*y2 + x2*y4 + x4*y1 - x4*y2 - x1*y4 - x2*y1);
        double A_tr1 = abs(x*y1 + x1*y2 + x2*y - x2*y1 - x*y2 - x1*y);
        double A_tr2 = abs(x*y2 + x2*y4 + x4*y - x4*y2 - x*y4 - x2*y);
        double A_tr3 = abs(x*y1 + x1*y4 + x4*y - x4*y1 - x*y4 - x1*y);
        double B_tr = abs(x2*y3 + x3*y4 + x4*y2 - x4*y3 - x2*y4 - x3*y2);
        double B_tr1 = abs(x*y2 + x2*y3 + x3*y - x3*y2 - x*y3 - x2*y);
        double B_tr2 = abs(x*y3 + x3*y4 + x4*y - x4*y3 - x*y4 - x3*y);
        double B_tr3 = abs(x*y2 + x2*y4 + x4*y - x4*y2 - x*y4 - x2*y);
        return A_tr == A_tr1 + A_tr2 + A_tr3 || B_tr == B_tr1 + B_tr2 + B_tr3;
    }
}

