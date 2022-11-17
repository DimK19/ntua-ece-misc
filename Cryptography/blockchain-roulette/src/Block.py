import json

class Block():
    def __init__(self, index, timestamp, transactions, proof, previous_hash):
        self.data = {}
        self.data.update({"index": index, "timestamp": timestamp, "transactions": transactions, "proof": proof, "previous_hash": previous_hash})

    def get(self, element):
        return self.data.get(element)

    def getAll(self):
        return self.data

    def getJSON(self):
        return json.dumps(self.data)
