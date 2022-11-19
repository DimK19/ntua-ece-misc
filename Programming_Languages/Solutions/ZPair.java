import java.util.LinkedList;
import java.util.Objects;

public class ZPair
{
    private LinkedList<Integer> queue, stack;
    
    public ZPair(LinkedList<Integer> q, LinkedList<Integer> s)
    {
        this.queue = q;
        this.stack = s;
    }
    
    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        ZPair other = (ZPair) o;
        return queue.equals(other.queue) && stack.equals(other.stack);
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(queue, stack);
    }

    public LinkedList<Integer> getQueue()
    {
        return queue;
    }

    public LinkedList<Integer> getStack()
    {
        return stack;
    }
}
