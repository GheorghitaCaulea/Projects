
/**
 *Clasa GenericObjects 'trateaza' obiecte specifice ca obiecte generice. 
 * @author Caulea Gheorghita
 */
public class GenericObjects {
    
    /**
     * Metoda getRectangleforGenericObject returneaza coordonatele dreptunghiului incadrator al unui obiect generic.
     * Metoda verifica instanta obiectului si apeleaza metoda din clasa respectiva.
     * @param obj
     * @return double[]
     */
    double[] getRectangleforGenericObject(GenericObjects obj){
        if(obj instanceof Rectangle){
            return ((Rectangle)obj).getRectangle(((Rectangle)obj).x1, ((Rectangle)obj).x2, ((Rectangle)obj).y1, ((Rectangle)obj).y2);
        }
        if(obj instanceof Circle){
            return ((Circle)obj).getRectangle(((Circle)obj).r, ((Circle)obj).x, ((Circle)obj).y);
        }
        if(obj instanceof Triangle){
            return ((Triangle)obj).getRectangle(((Triangle)obj).x1, ((Triangle)obj).x2, ((Triangle)obj).x3, ((Triangle)obj).y1, ((Triangle)obj).y2, ((Triangle)obj).y3);
        }
        return ((Diamond)obj).getRectangle(((Diamond)obj).x1, ((Diamond)obj).x2, ((Diamond)obj).x3, ((Diamond)obj).x4, ((Diamond)obj).y1, ((Diamond)obj).y2, ((Diamond)obj).y3, ((Diamond)obj).y4);  
    }
    
    /**
     * Metoda getIdforGenericObject returneaza id-ul unui obiect generic.
     * Metoda verifica instanta obiectului si apeleaza metoda din clasa respectiva.
     * @param obj
     * @return int
     */
    int getIdforGenericObject(GenericObjects obj){
        if(obj instanceof Rectangle){
            return ((Rectangle)obj).getId();
        }
        if(obj instanceof Circle){
            return ((Circle)obj).getId();
        }
        if(obj instanceof Triangle){
            return ((Triangle)obj).getId();
        }
        return ((Diamond)obj).getId();  
    }
    
    /**
     * Metoda getCheckPoint verifica daca un punct apartine unui obiect generic.
     * Metoda verifica instanta obiectului si apeleaza metoda din clasa respectiva.
     * @param obj
     * @param p
     * @return boolean
     */
    boolean getCheckPoint(GenericObjects obj, Point p){
        if(obj instanceof Rectangle){
            return ((Rectangle)obj).getCheckPoint(p.x, p.y);
        }
        if(obj instanceof Circle){
            return ((Circle)obj).getCheckPoint(p.x, p.y);
        }
        if(obj instanceof Triangle){
            return ((Triangle)obj).getCheckPoint(p.x, p.y);
        }
        return ((Diamond)obj).getCheckPoint(p.x, p.y); 
    }
}
