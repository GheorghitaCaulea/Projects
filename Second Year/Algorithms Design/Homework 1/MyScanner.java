import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class MyScanner {
    BufferedReader br;
    StringTokenizer st;
    
    public MyScanner(String file_name) throws FileNotFoundException {
        br = new BufferedReader(new FileReader(new File(file_name)));
    }
    
    String next_String() {
        while(st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }
    
    int next_int() {
        return Integer.parseInt(next_String());
    }
    
    long next_Long() {
        return Long.parseLong(next_String());
    }
    
    double next_double() {
        return Double.parseDouble(next_String());
    }
    
    String next_Line() {
        String str = "";
        try {
            str = br.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }
}
