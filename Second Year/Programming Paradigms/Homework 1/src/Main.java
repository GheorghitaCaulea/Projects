import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
            
    
    public static void main(String[] args) {
        StringBuilder str = new StringBuilder();
        String line;
        Evaluate eva;
        File file_in = new File(args[0]);
        Scanner scan;
        File file_out = new File(args[1]);
        FileWriter write;
        try{
			//Deschid fisierul pentru citire.
            scan = new Scanner(file_in);
            try{
				//Deschid fisierul pentru scriere.
                write = new FileWriter(file_out);
                
				//Cat timp am ce citi, citesc si construiesc un string cu toate liniile citite.
                while(scan.hasNextLine())
                    str.append(scan.nextLine());
                
                line = str.toString();
                ConstructTree construct = new ConstructTree();
				//Folosesc metoda 'create_string' pentru a modifica stringul citit si a-l aduce la forma utila construirii arborelui.
                String work[] = construct.create_string(line);
				//Construiesc arborele.
                Nod root = construct.create_tree(work);
				eva = new Evaluate();
				//Evaluez arborele.
                root.accept(eva);
				//Verific erorile in ordinea prioritatilor si afisez eroare respectiva sau valoare evaluarii programului.
				if(!eva.sw_check){
					write.write("Check failed");
				} else {
					if(construct.sw_return == 0) {
                      	write.write("Missing return");
					} else {
						if(eva.assert_value.contains(false)) 
                      		write.write("Assert failed");
						else
							write.write(eva.return_object.getFirst().toString());
					}
				}
				//Inchid fisierele.
                scan.close();
                write.close();
            } catch(IOException ioe) {
                System.out.println(ioe);
            }
        } catch(FileNotFoundException fnfe){
            System.out.println(fnfe);
        }
    }           
    
}    
