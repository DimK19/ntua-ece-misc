from random import randint

class Player():
    def __init__(self, name = "Player"):
        self.balance = 1000
        self.name = name
        self.bet = (-1, 0)
        self.request = True

    def makeRequest(self):
        return self.request

    def placeBet(self):
        number = randint(0, 36)
        self.balance -= 100
        self.bet = (number, 100)
        return (number, 100)

    def getName(self):
        return self.name

    def publishRequestToChain(self, blockchain):
        blockchain.push_participant(self, self.request)

    def publishBetToChain(self, blockchain):
        blockchain.push_bet(self, self.bet)
