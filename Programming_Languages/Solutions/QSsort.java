import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class QSsort
{
    private static boolean isSorted(LinkedList<Integer> array)
    {
        for (int i = 0; i < array.size() - 1; ++i)
            if(array.get(i).compareTo(array.get(i + 1)) > 0) return false;

        return true;
    }

    public static void main(String[] args)
    {
        ZPLFileReader fr = new ZPLFileReader();
        LinkedList<Integer> queue;
        queue = fr.readex1(args[0]);
        //queue = fr.readex1("in.txt");
        int n = queue.size();
        LinkedList<Integer> stack = new LinkedList<Integer>();
        LinkedList<LinkedList<Integer>> QQ = new LinkedList<>();
        LinkedList<LinkedList<Integer>> SQ = new LinkedList<>();
        Queue<String> moves = new LinkedList<>();
        
        if(isSorted(queue)) System.out.println("empty");
        else
        {
            // ZPair p = new ZPair(queue, stack);
            QQ.add(queue);
            SQ.add(stack);
            moves.add("");
        }
        
        String winner = null, currentMove;
        
        while(!QQ.isEmpty())
        {
            //ZPair currentPair = Q.remove();
            //LinkedList<Integer> currentQueue = currentPair.getQueue();
            //LinkedList<Integer> currentStack = currentPair.getStack();
            
            LinkedList<Integer> currentQueue = QQ.remove();
            LinkedList<Integer> currentStack = SQ.remove();
            
            currentMove = moves.remove();
            
            // debug
            // System.out.println("examining " + currentMove + " : " + currentPair.getQueue() + " " + currentPair.getStack());
            
            if(currentQueue.size() == n)
                if(isSorted(currentQueue))
                {
                    winner = currentMove;
                    break;
                }
            
            if(currentQueue.size() > 0)
            {
                LinkedList<Integer> newStack = (LinkedList<Integer>) currentStack.clone();
                newStack.add(currentQueue.getFirst());
                LinkedList<Integer> newQueue = (LinkedList<Integer>) currentQueue.clone();
                int temp = newQueue.removeFirst();
                String m = "Q";
                while(newQueue.size() > 0 && temp == newQueue.getFirst())
                {
                    newStack.add(newQueue.getFirst());
                    temp = newQueue.removeFirst();
                    m += "Q";
                }
                // ZPair p = new ZPair(newQueue, newStack);

                QQ.add(newQueue);
                SQ.add(newStack);
                
                moves.add(currentMove + m);
            }
            if(currentStack.size() > 0)
            {
                LinkedList<Integer> newQueue = (LinkedList<Integer>) currentQueue.clone(); 
                newQueue.add(currentStack.getLast());
                LinkedList<Integer> newStack = (LinkedList<Integer>) currentStack.clone();
                
                int temp = newStack.removeLast();
                String m = "S";
                while(newStack.size() > 0 && temp == newStack.getLast())
                {
                    newQueue.add(newStack.getLast());
                    temp = newStack.removeLast();
                    m += "S";
                }
                // ZPair p = new ZPair(newQueue, newStack);
                
                QQ.add(newQueue);
                SQ.add(newStack);
                
                moves.add(currentMove + m);
            }
        }
        
        if(winner != null)
        {
            System.out.println(winner);
        }
    }

}
