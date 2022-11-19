import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;

public class Round
{

	public static void main(String[] args) throws FileNotFoundException, IOException
	{
		BufferedReader in = new BufferedReader(new FileReader(args[0]));
        String line = in.readLine();
        String[] strList = line.split(" ");
        int N, K;
        N = Integer.parseInt(strList[0]);
        K = Integer.parseInt(strList[1]);
        
        line = in.readLine();
        strList = line.split(" ");
        ArrayList<Integer> arr = new ArrayList<Integer>();
        for(String s: strList) arr.add(Integer.valueOf(s));
        
        in.close();

        int bestIndex = 0;
        int bestSum = Integer.MAX_VALUE;
        for(int i = 0; i < N; ++i)
        {
        	ArrayList<Integer> temp = (ArrayList<Integer>) arr.clone();
        	for(int j = 0; j < K; ++j)
        		if(temp.get(j) <= i) temp.set(j, i - temp.get(j));
        		else temp.set(j, N - (temp.get(j) - i));
			// System.out.println(temp);	
        	if(getArraySum(temp) + 1 >= 2 * getMax(temp))
        		if(getArraySum(temp) < bestSum)
        		{
        			bestSum = getArraySum(temp);
        			bestIndex = i;
        		}
        }
		
		System.out.println(bestSum + " " + bestIndex);
        
	}
	
	public static int getMax(ArrayList<Integer> arr)
	{
		int m = arr.get(0);
		for(int i = 1; i < arr.size(); ++i) if(arr.get(i) > m) m = arr.get(i);
		
		return m;
	}
	
	public static int getArraySum(ArrayList<Integer> arr)
	{
		int s = 0;
		for(int i = 0; i < arr.size(); ++i) s += arr.get(i);
		
		return s;
	}

}
