import sys
from collections import deque

def isSorted(l):
    return all(l[i] <= l[i + 1] for i in range(len(l) - 1))
      
## f = open("qsin3.txt", 'r')
f = open(sys.argv[1], 'r')

n = f.readline() # consumes line
n = int(n)
queue = f.readline().rstrip('\n').split(' ') ## list
queue = [int(i) for i in queue]

stack = list()
seen = set() ## apparently visited was not necessary
Q = deque()

if(isSorted(queue)):
    print("empty")
else:
    Q.append((queue, stack))
    parent = {hash((tuple(queue), tuple(stack))) : ''}
    seen.add(hash((tuple(queue), tuple(stack))))
    
winner = None

while(Q):
    pair = Q.popleft()
    q, s = pair
    
    if(len(q) == n):
        if(isSorted(q)):
            winner = pair
            break
        
    if(len(q) > 0):
        newS = s.copy()
        newS.append(q[0])
        if(hash((tuple(q[1:]), tuple(newS))) not in seen):
            parent.update({hash((tuple(q[1:]), tuple(newS))) : parent[hash((tuple(q), tuple(s)))] + 'Q'})
            seen.add(hash((tuple(q[1:]), tuple(newS))))
            Q.append((q[1:], newS))
            del newS
    if(len(s) > 0):
        newQ = q[:]
        newQ.append(s[-1])
        if(hash((tuple(newQ), tuple(s[:-1]))) not in seen):
            parent.update({hash((tuple(newQ), tuple(s[:-1]))) : parent[hash((tuple(q), tuple(s)))] + 'S'})
            seen.add(hash((tuple(newQ), tuple(s[:-1]))))
            Q.append((newQ, s[:-1]))
            del newQ

    ## if visited leave
    ## else add to visited
    ## check if sorted
    ## if yes answer found
    ## if no add Q and S to the queue
    

if(winner is not None): 
    q, s = winner
    ans = parent[hash((tuple(q), tuple(s)))]
    print(ans)
    
f.close()
