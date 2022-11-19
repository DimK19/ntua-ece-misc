import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;

public class ZPLFileReader
{

    public static LinkedList<Integer> readex1(String fileName)
    {
        try
        {
            BufferedReader in = new BufferedReader(new FileReader(fileName));
            String line = in.readLine(); // skip first line
            line = in.readLine();
            String[] strList = line.split(" ");
            LinkedList<Integer> res = new LinkedList<Integer>();
            for(String s: strList) res.add(Integer.valueOf(s));
            
            in.close();
            // System.out.println(res);
            return res;
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
        
        return null;
    }
    
    // testing
    /*
    public static void main(String[] args)
    {
        readex1("in.txt");
    }
    */
}
