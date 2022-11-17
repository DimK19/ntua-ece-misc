import sys
import math
from string import ascii_uppercase
from cryptoex1 import vig_decrypt, caesar_decrypt
import itertools

def IC(text):
    n = len(text)
    Itext = 0 ## index of coincidence
    for l in ascii_uppercase:
        fi = text.count(l)
        Itext += (fi * (fi - 1)) / (n * (n - 1))
    return Itext
    
def getColumns(text, r):
    res = []
    for column in range(r):
        column_text = ''.join([text[column + i * r] for i in range(math.floor(len(text) / r))])
        res.append(column_text)
    return res
    
try:
    f = open(sys.argv[1], 'r')
    encrypted_text = f.read().replace('\n', '')
except:
    sys.exit()

Ieng = 0.065
Irand = 0.038 
ic = IC(encrypted_text)
rest = (Ieng - Irand) / (ic - Irand) ## estimation for key length, result 6.980961454529971

candidates_list = []
## Εξετάζουμε εύρος τιμών γύρω από την εκτίμηση Friedman
for r in range(math.ceil(rest) - 2, math.ceil(rest) + 3):
    for column_text in getColumns(encrypted_text, r):
        if(IC(column_text) < 0.05):
            print("key length %d rejected" % r)
            break

        ## για μια στήλη με αποδεκτό δείκτη συμπτώσεως, δοκιμάζουμε όλες τις δυνατές μεταθέσεις και 
        ## αποθηκεύουμε τις αποδεκτές σε string
        ## assume most frequent letters in the english language are EAI, least frequent XZQ
        candidates = ''
        for k in ascii_uppercase:
            flag = True
            candidate_text = caesar_decrypt(column_text, ord(k) - ord('A'))
            for (i, j) in itertools.product("EAI", "XZQ"):
                if(candidate_text.count(i) < candidate_text.count(j)):
                    flag = False
            if(flag): candidates += k
            
        candidates_list.append(candidates)

## όλοι οι δυνατοί συνδυασμοί των αποδεκτών γραμμάτων για κάθε στήλη
potential_keys = [''.join(k) for k in itertools.product(*candidates_list)]

for pk in potential_keys:
    print("Key: ", pk)
    print(vig_decrypt(encrypted_text, pk))
    print()
