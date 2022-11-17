from Player import Player
from RouletteMaster import RouletteMaster
from Blockchain import Blockchain

from random import randint
import pickle
import os

## initialize a new Blockchain obect if the file has not been created yet
if(os.path.exists("blockchain.pkl")):
    with open("blockchain.pkl", 'rb') as f:
        bc = pickle.load(f)
else:
    bc = Blockchain()

proof = bc.proof_of_work(bc.getLatestProof())

players = []
requests = []
bets = []
for i in range(15):
    p = Player(f"Player {i + 1}")
    players.append(p)
    r = p.makeRequest()
    p.publishRequestToChain(bc)
    requests.append(r)
    if(r): bets.append(p.placeBet())
    else: bets.append((-1, 0))
    p.publishBetToChain(bc)
    ## if !request, the default bet value signifying no bet will be sent

rm = RouletteMaster(players)

rm.receiveRequests(requests)
rm.publishParticipantsToChain(bc)
rm.receiveBets(bets)
rm.publishBetsToChain(bc)

result = randint(0, 36)

rm.tallyResults(winner = result, blockchain = bc, proof = proof)

bc.new_block(proof)

bc.writeChainToFile()

with open("blockchain.pkl", 'wb') as f:
    pickle.dump(bc, f)
