

import java.util.LinkedList;

/**
 *Clasa QuadTree este folosita pentru obiecte de tip quadtree.
 * Pentru a creea obiecte de acest tip am folosit ca argumente: 
 * -un vector de copii de tip quad tree(child);
 * -un parinte de tip quadtree(parent);
 * -o lista de obiecte generice care s-ar putea gasi in obiect(objects);
 * -coordonatele planului initial(x1, x2, y1, y2);
 * -nivelul pe care se afla obiectul(level)
 * @author Caulea Gheorghita
 */

public class QuadTree{
    QuadTree[] child;
    QuadTree parent;
    LinkedList<GenericObjects> objects;
    double x1, x2, y1, y2;
    int level;
   
    public QuadTree(double x1, double x2, double y1, double y2, QuadTree tree, int level){
        this.parent = tree;
        this.child = new QuadTree[0];
        this.objects = new LinkedList<>();
        this.x1 = x1;
        this.x2 = x2;
        this.y1 = y1;
        this.y2 = y2;
        this.level = level;
    }
    
    public QuadTree(){
    }
    
    /**
     * Metoda makeChild creeaza copii pentru un obiect de tip QuadTree.
     * Copiii vor avea coordonate specifice, vor avea parinte si un nivel mai mare decat parintele.
     * @param tree
     * @return QuadTree[]
     */
    static QuadTree[] makeChild(QuadTree tree){
        QuadTree qt[] = new QuadTree[4];
        qt[0] = new QuadTree((tree.x1 + tree.x2) / 2, tree.x2, (tree.y1 + tree.y2) / 2, tree.y2, tree, tree.level + 1); 
        qt[1] = new QuadTree(tree.x1, (tree.x1 + tree.x2) / 2, (tree.y1 + tree.y2) / 2, tree.y2, tree, tree.level + 1); 
        qt[2] = new QuadTree(tree.x1, (tree.x1 + tree.x2) / 2, tree.y1, (tree.y1 +tree.y2) / 2, tree, tree.level + 1);
        qt[3] = new QuadTree((tree.x2 + tree.x1) / 2, tree.x2, tree.y1, (tree.y1 + tree.y2)  / 2, tree, tree.level + 1);
        return qt;
    }
    
    /**
     * Metoda TestCollisionWithQuad testeaza coliziunea dintre un obiect generic si planul unui obiect de tip QuadTree.
     * Se verifica trei situatii posibile(se folosesc coordonatele dreptunghiului incadrator pentru obiectul generic):
     *  -se verifica daca obiectul generic nu apartine planului obiectului de tip QuadTree(se returneaza 0);
     *  -se verifica daca obiectul generic este inclus in planul obiectului de tip QuadTree(se returneaza 2);
     *  -se verifica daca obiectul generic include planul obiectului de tip QuadTree(se returneaza 2);
     *  -la final se returneaza 1, concluzia fiind aceea ca cele doua obiecte prezinta coliziune partiala;
     * @param tree
     * @param ob2
     * @return int
     */
    static public int TestCollisionWithQuad(QuadTree tree, GenericObjects ob2){
        double p1[] = new double[4];
        p1[0] = tree.x1;
        p1[1] = tree.x2;
        p1[2] = tree.y1;
        p1[3] = tree.y2;
        double p2[] = ob2.getRectangleforGenericObject(ob2);
        if(p2[2] > p1[3] || p2[3] < p1[2] || p2[1] < p1[0] || p2[0] > p1[1])
            return 0;
        if(p2[0] < p1[0] && p2[2] < p1[2] && p2[1] > p1[1] && p2[3] > p1[3])
            return 2;
        if(p1[0] < p2[0] && p1[2] < p2[2] && p1[1] > p2[1] && p1[3] > p2[3])
            return 2;
        return 1;
    }
    
    /**
     * Metoda TestCollison testeaza coliziunea dintre doua obiecte generice.
     * Se realizeaza o testare similara cu cea dintre un obiect generic si un obiect de tip QuadTree.
     * Testarea se bazeaza pe dreptunghiul incadrator al obiectelor generice.
     * @param ob1
     * @param ob2
     * @return int
     */
    static public int TestCollision(GenericObjects ob1, GenericObjects ob2){
        double p1[] = ob1.getRectangleforGenericObject(ob1);
        double p2[] = ob2.getRectangleforGenericObject(ob2);
        if(p2[2] > p1[3] || p2[3] < p1[2] || p2[1] < p1[0] || p2[0] > p1[1])
            return 0;
        if(p2[0] < p1[0] && p2[2] < p1[2] && p2[1] > p1[1] && p2[3] > p1[3])
            return 2;
        if(p1[0] < p2[0] && p1[2] < p2[2] && p1[1] > p2[1] && p1[3] > p2[3])
            return 2;
        return 1;
    }
    
    /**
     * Metoda TestCollisionwithPoint testeaza coliziunea dintre planul unui obiect de tip QuadTree si un obiect de tip Point.
     * @param tree
     * @param p
     * @return int
     */
    static public int TestCollisionwithPoint(QuadTree tree, Point p){
        if((p.x >= tree.x1) && (p.x <= tree.x2) && (p.y <= tree.y2) && (p.y >= tree.y1)){
            return 1;
        }
        else
            return 0;
    }       
    
    /**
     * Metoda searchInQuadTree realizeaza o cautare recursiva a unui obiect generic intr-un obiect de tip QuadTree.
     * Metoda se bazeaza pe coliziuni.
     * In cazul in care am ajuns la locul potrivit in obiectul de tip QuadTree, se testeaza coliunea obiectului generic cu obiectele continute de acel obiect.
     * In cazul in care exista coliziune cu acele obiecte, id-ul obiectelor se va memora prin inserarea lui intr-o lista de intregi.
     * @param tree
     * @param obj
     * @param id 
     */
    
    static public void searchInQuadTree(QuadTree tree, GenericObjects obj, LinkedList<Integer> id){
        int i;
        //Se verifica daca am ajuns in frunza si nu am obiecte;
        if(tree.child.length == 0 && tree.objects.size() == 0){
            return;
        }
        //Se verifica daca am ajuns in frunza si am obiecte; 
        if(tree.child.length == 0  && tree.objects.size() != 0 && TestCollisionWithQuad(tree, obj) > 0){
            for(i = 0; i < tree.objects.size(); i ++){
                //Se testeaza coliziunea cu toate obiectele si se introduc in lista id-urile.
                if(TestCollision(obj ,tree.objects.get(i)) > 0){
                   if(!id.contains(tree.objects.get(i).getIdforGenericObject(tree.objects.get(i))))
                        id.add(tree.objects.get(i).getIdforGenericObject(tree.objects.get(i)));   
                }
            }
        return;
        }
        //Se verifica daca nu sunt in frunza si se apeleaza recursiv metoda pentru fiii cu care obiectul generic prezinta coliziune;    
        if(tree.child.length != 0){
            for(int j = 0; j < 4; j ++){
                if(TestCollisionWithQuad(tree.child[j], obj) > 0){
                    searchInQuadTree(tree.child[j], obj, id); 
                } 
            }
        } 
    }
    
    /**
     * Metoda searchInQuadTreeforPoint realizeaza o cautare recursiva asemanatoare cu cea a metodei searchInQuadTree.
     * Diferenta dintre metode este ca in cazul acesteia se verifica o coliziune a unui obiect generic in sine(nu dupa dreptunghiul incadrator), cu un punct.
     * Se va returna o lista de id-uri corespunzatoare obiectelor generice cu care punctul face coliziune.
     * @param tree
     * @param p
     * @param id 
     */
    static public void searchInQuadTreeforPoint(QuadTree tree, Point p, LinkedList<Integer> id){
        int i;
        //Se verifica daca ama juns in lista si nu am obiecte;
        if(tree.child.length == 0 && tree.objects.isEmpty()){
          return;
        }
        //Se verica daca sunt in frunza si am obiecte;
        if(tree.child.length == 0  && !tree.objects.isEmpty() && TestCollisionwithPoint(tree, p) > 0){
            for(i = 0; i < tree.objects.size(); i ++){
                //In cazul in care am obiecte in frunza, verific daca punctul apartine obiectelor;
                //Daca punctul apartine obiectelor, adaug id-urile obiectelor in lista de intregi;
                if(tree.objects.get(i).getCheckPoint(tree.objects.get(i), p)){
                    if(!id.contains(tree.objects.get(i).getIdforGenericObject(tree.objects.get(i))))
                        id.add(tree.objects.get(i).getIdforGenericObject(tree.objects.get(i)));
                }
            }
        return;
        }
        //Se verifica daca nu sunt in frunza si se apeleaza recursiv metoda pentru fiul cu care punctul prezinta coliziune;    
        if(tree.child.length != 0){
            for(int j = 0; j < 4; j ++){
                if(TestCollisionwithPoint(tree.child[j], p) > 0){
                    searchInQuadTreeforPoint(tree.child[j], p, id);
                } 
            }    
        } 
    }
}
