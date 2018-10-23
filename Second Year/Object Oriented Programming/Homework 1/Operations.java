


import java.util.ArrayList;
import java.util.LinkedList;

/**
 *Clasa Operations este folosita pentru a executa operatii pe obiecte de tip QuadTree.
 * In aceasta clasa se realizeaza insearea si stergerea unui obiect generic.
 * @author Caulea Gheorghita
 */
public class Operations extends QuadTree{
    
    /**
     * Metoda SpecialInsertInQuadTree realizeaza inserarea unui obiect generic intr-un QuadTree.
     * In cazul in care trebuiesc divizate cadranele, se va realiza acest lucru.
     * Metoda este una recursiva.
     * In lst(lista de liste), se memoreaza o lista de QuadTree-uri corespunzatoare fiecarui id, al fiecarui obiect.
     * Avand un id, se stie unde anume se gaseste acesta in QuadTree.
     * @param tree
     * @param obj
     * @param lst 
     */
    static public void SpecialInsertInQuadTree(QuadTree tree, GenericObjects obj, ArrayList<LinkedList<QuadTree>> lst){
        int i;
        //Se verifica daca sunt in frunza si daca aceasta este fara obiecte;
        //In acest caz se insereaza obiectul;
        //In lista de liste, pe pozitia id, va aparea frunza in care s-a inserat obiectul;
        if(tree.child.length == 0 && tree.objects.isEmpty()){
            if(TestCollisionWithQuad(tree, obj) > 0){
                lst.get(obj.getIdforGenericObject(obj)).add(tree);
                tree.objects.add(obj);
                return;
            }
        }
        //Se verica daca sunt in frunza si daca aici se mai gasesc si alte obiecte;
        if(tree.child.length == 0  && !tree.objects.isEmpty() && TestCollisionWithQuad(tree, obj) > 0){
            for(i = 0; i < tree.objects.size(); i ++){
                if(TestCollision(obj ,tree.objects.get(i)) < 1)
                    break;
            }
            //Daca obiectul de inserat prezinta coliziune cu toate celelalte obiecte, se insereaza aici;
            //Se inseareaza si in lista;
            if(i == tree.objects.size()){
                lst.get(obj.getIdforGenericObject(obj)).add(tree);
                tree.objects.add(obj);
            }
            //In cazul in care nu prezinta coliziune cu toate obiectele;
            //Se creeaza copii;
            //Se muta copiii in fii, si se apeleaza recursiv metoda pentru inserarea obiectului;
            else{
                tree.child = makeChild(tree);
                for(int j = 0; j < 4; j ++){
                    for(i = 0; i < tree.objects.size(); i++){
                        if(TestCollisionWithQuad(tree.child[j], tree.objects.get(i)) > 0){
                            lst.get(obj.getIdforGenericObject(tree.objects.get(i))).remove(tree);
                            lst.get(obj.getIdforGenericObject(tree.objects.get(i))).add(tree.child[j]);
                            tree.child[j].objects.add(tree.objects.get(i));
                        }
                    }
                    if(TestCollisionWithQuad(tree.child[j], obj) > 0)
                        SpecialInsertInQuadTree(tree.child[j], obj, lst);
                }
                tree.objects.clear();
            }
            return;
        }
        //Se verifica acel caz in care nu sunt pe frunza;
        //In acest caz se apeleaza recursiv metoda pentru frunzele cu care am coliziune;
        if(tree.child.length != 0){
            for(int j = 0; j < 4; j ++){
                if(TestCollisionWithQuad(tree.child[j], obj) > 0){
                    SpecialInsertInQuadTree(tree.child[j], obj, lst);
                }
            }
        }
    }

    /**
     * Metoda RemoveFromTree sterge toate aparitiile unui id(obiect) dintr-un QuadTree.
     * @param tree
     * @param id 
     */
    public static void RemoveFromTree(QuadTree tree, int id){
        for(int i = 0; i < tree.objects.size(); i ++){
            if(tree.objects.get(i).getIdforGenericObject(tree.objects.get(i)) == id){
                tree.objects.remove(i);
            }
        }
    }    
    
    /**
     * Metoda ArrangeQuadTree "aranjeaza" in mod recursiv arborele dupa eliminarea unui obiect;
     * Metoda este recusiva si parcurge arborele de la frunza spre radacina.
     * @param qtree
     * @param lst 
     */
    static public void ArrangeQuadTree(QuadTree qtree, ArrayList<LinkedList<QuadTree>> lst){
        int i, j, sw = 0;
        QuadTree tree;
        LinkedList<GenericObjects> ls = new LinkedList<>();
        LinkedList<QuadTree> ls_quad = new LinkedList<>();
        //Se verifica daca nu sunt in radacina;
        if(qtree.parent != null && qtree.parent.child.length == 4){
            tree = qtree.parent;
        //Ma mut in parinte si incep sa fac verificari de acolo;
            for(i = 0; i < 4; i ++){
                if(tree.child[i].child.length != 0)
                    return;   
            }
            //Introduc toate obiectele copiilor intr-o alta lista de obiecte(obiecte unice);
            for(i = 0; i < 4; i ++){
                if(tree.child[i].objects.size() != 0)
                    for (GenericObjects object : tree.child[i].objects) {
                        if(!ls.contains(object)){
                            ls_quad.add(tree.child[i]);
                            ls.add(object);
                        }
                    }    
            }
            //Verific coliziunea obiectelor din noua lista;
            for(i = 0; i < ls.size(); i ++){
                for(j = 0; j < ls.size(); j ++){
                    if(TestCollision(ls.get(i), ls.get(j)) < 1)
                        sw = 1;
                }
            }
            //In cazul in care obiectele nu prezinta toate coliziune intre ele le las pe pozitia lor;
            //In caz contrar, folosesc metoda de inserare pentru obiecte si parinte;
            if(sw != 1){
                tree.child= new QuadTree[0];
                for(i = 0; i < ls.size(); i++){
                    lst.get(ls.get(i).getIdforGenericObject(ls.get(i))).remove(ls_quad.get(i));
                    SpecialInsertInQuadTree(tree, ls.get(i), lst);
                }
                //Apelez recursiv metoda de rearanjare pentru parinte;
                ArrangeQuadTree(tree, lst);
            }
        }
    } 
    
    /**
     * Metoda SpecialRemove, sterge toate aparitiile unui obiect(dat ca id) si rearanjeaza recursiv arborele.
     * @param id
     * @param lst 
     */
    static public void SpecialRemove(int id, ArrayList<LinkedList<QuadTree>> lst){
        LinkedList<QuadTree> ls = lst.get(id);
        LinkedList<QuadTree> ls_sort = new LinkedList<>();
        LinkedList<QuadTree> ls_sort_unique = new LinkedList<>();
        int i, j;
        //Se sterg din arbore toate aparitiile unui obiect;
        for (QuadTree l : ls) 
            RemoveFromTree(l, id);
        //Se creeaza o lista sortata descrescator dupa nivele, cu toate frunzele pe care s-a aflat obiectul respectiv;
        if(ls.size() != 0){
            for(i = 10000; i >= 0; i--){
                for (QuadTree l : ls) {
                    if (l.level == i) 
                        ls_sort.add(l);
                }
            }
        }
        //Se creeaza o lista unica de frunze in sensul ca sunt pastrate doar frunzele cu parinti diferiti;
        //Se face rearanjearea doar pentru un singur fiu al aceluias parinte;
        if(ls_sort.size() != 0)
            ls_sort_unique.add(ls_sort.get(0));
        for(i = 1; i < ls_sort.size(); i++){
            if(ls_sort.get(i - 1).parent != ls_sort.get(i ).parent)
                ls_sort_unique.add(ls_sort.get(i));
        }
        ls_sort = new LinkedList<>();
        for(i = 0; i < ls_sort_unique.size(); i++){
            for(j = 0; j < ls_sort_unique.size(); j++){
                if(i != j && ls_sort_unique.get(i).parent == ls_sort_unique.get(j).parent){
                    ls_sort.add(ls_sort_unique.get(i));
                }
            }
        }
        for(i = 0; i < ls_sort.size(); i++){
            ls_sort_unique.remove(ls_sort.get(i));
        }
        //Se apeleaza metoda recursiva de rearanjare pentru fiecare frunza de unde a fost eliminat obiectul;
        for(i = 0; i < ls_sort_unique.size(); i++){
            ArrangeQuadTree(ls_sort_unique.get(i), lst);
        }
        //Se sterg din list toate frunzele pe care se afla obiectul respectiv(id-ul respectiv);
        lst.get(id).removeAll(ls);
    }
}
