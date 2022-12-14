from Block import Block

import hashlib
import json
from time import time

class Blockchain():
    def __init__(self):
        self.current_transactions = []
        self.chain = []

        # Create the genesis block
        self.new_block(previous_hash = 1, proof = 100)

    def new_block(self, proof, previous_hash = None):
        """
        Create a new Block in the Blockchain
        :param proof: <int> The proof given by the Proof of Work algorithm
        :param previous_hash: (Optional) <str> Hash of previous Block
        :return: <dict> New Block
        """

        block = Block(
            index = len(self.chain) + 1,
            timestamp = time(),
            transactions = self.current_transactions,
            proof = proof,
            previous_hash = previous_hash or self.hash(self.chain[-1])
        )

        # Reset the current list of transactions
        self.current_transactions = []

        self.chain.append(block)

    def push_participant(self, participant, request):
        self.current_transactions.append({"type": "participant", "data": {
            'name': participant.getName(),
            "participation": "YES" if request else "NO"
        }})

    def push_bet(self, player, bet):
        self.current_transactions.append({"type": "bet", "data": {
            "player": player.getName(),
            "number": bet[0],
            "amount": bet[1]
        }})

    def new_transaction(self, sender, recipient, amount):
        """
        Creates a new transaction to go into the next mined Block
        :param sender: <str> Address of the Sender
        :param recipient: <str> Address of the Recipient
        :param amount: <int> Amount
        :return: <int> The index of the Block that will hold this transaction
        """
        self.current_transactions.append({"type": "transaction", "data": {
            'sender': sender,
            'recipient': recipient,
            'amount': amount,
        }})

        return self.last_block.get('index') + 1

    @property
    def last_block(self):
        return self.chain[-1]

    @staticmethod
    def hash(block):
        """
        Creates a SHA-256 hash of a Block
        :param block: <object> Block
        :return: <str>
        """

        # We must make sure that the Dictionary is Ordered, or we'll have inconsistent hashes
        block_string = json.dumps(block.getAll(), sort_keys = True).encode()
        return hashlib.sha256(block_string).hexdigest()

    def proof_of_work(self, last_proof):
        """
        Simple Proof of Work Algorithm:
         - Find a number p' such that hash(pp') contains leading 4 zeroes, where p is the previous p'
         - p is the previous proof, and p' is the new proof
        :param last_proof: <int>
        :return: <int>
        """

        proof = 0
        while not self.valid_proof(last_proof, proof):
            proof += 1

        return proof

    @staticmethod
    def valid_proof(last_proof, proof):
        """
        Validates the Proof: Does hash(last_proof, proof) contain 4 leading zeroes?
        :param last_proof: <int> Previous Proof
        :param proof: <int> Current Proof
        :return: <bool> True if correct, False if not.
        """

        guess = f'{last_proof}{proof}'.encode()
        guess_hash = hashlib.sha256(guess).hexdigest()
        return guess_hash[:4] == "0000"

    def getFullChain(self):
        return self.chain

    def getLatestProof(self):
        if(not self.chain): return ''
        return self.chain[-1].get("proof")

    def writeChainToFile(self):
        printableChain = [b.getJSON() for b in self.chain]
        with open("chain.txt", 'w') as f:
            for b in printableChain:
                f.write(b)
                f.write('\n')
