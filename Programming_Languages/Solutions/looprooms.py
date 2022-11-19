import sys

## f = open("fairmaze.in2", 'r')
f = open(sys.argv[1], 'r')

n, m = f.readline().split() # consumes line
n = int(n)
m = int(m)

adj = {}
escapeable = {}
visited = {}
exits = []

for i in range(n):
    directions = list(f.readline())
    for j in range(m):
        escapeable.update({(i, j) : False})
        visited.update({(i, j) : False})
        d = directions[j]
        isExit = False
        if(d == 'U'):
            if(i - 1 >= 0):
                if((i - 1, j) in adj.keys()): adj[i - 1, j].append((i, j))
                else: adj.update({(i - 1, j) : [(i, j)]})
            else: isExit = True
        elif(d == 'D'):
            if(i + 1 < n):
                if((i + 1, j) in adj.keys()): adj[i + 1, j].append((i, j))
                else: adj.update({(i + 1, j) : [(i, j)]})
            else: isExit = True
        elif(d == 'L'):
            if(j - 1 >= 0):
                if((i, j - 1) in adj.keys()): adj[i, j - 1].append((i, j))
                else: adj.update({(i, j - 1) : [(i, j)]})
            else: isExit = True
        elif(d == 'R'):
            if(j + 1 < m):
                if((i, j + 1) in adj.keys()): adj[i, j + 1].append((i, j))
                else: adj.update({(i, j + 1) : [(i, j)]})
            else: isExit = True
                        
        if(isExit):
            exits.append((i, j))
            escapeable.update({(i, j) : True})

while(exits):
    e = exits.pop()
    if(e not in adj.keys()): continue
    for v in adj[e]:
        if(not visited[v]): exits.append(v)
        visited.update({v : True})
        escapeable.update({v : True})
    
counter = 0
for i in range(n):
    for j in range(m):
        if(not escapeable[(i, j)]): counter += 1
        # print(1 if escapeable[(i, j)] else 0, end = '')
    # print()
        
print(counter)

f.close()
