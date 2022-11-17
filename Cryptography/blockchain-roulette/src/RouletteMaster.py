class RouletteMaster():
    def __init__(self, players):
        self.playerCount = len(players)
        self.players = players
        self.requests = []
        self.bets = []

    def receiveRequests(self, requests):
        self.requests = requests

    def publishParticipantsToChain(self, blockchain):
        for r, p in zip(self.requests, self.players):
            if(r): blockchain.push_participant(p, r)

    def receiveBets(self, bets):
        for p, r, b in zip(self.players, self.requests, bets):
            if(r): self.bets.append(b)
            else: self.bets.append((-1, 0))

    def publishBetsToChain(self, blockchain):
        for r, p, b in zip(self.requests, self.players, self.bets):
            if(r): blockchain.push_bet(p, b)

    def tallyResults(self, winner, blockchain, proof):
        print(f"Ball landed on {winner}")
        totalAmount = 0
        winnersAmount = 0
        winners = []
        for player, bet in zip(self.players, self.bets):
            betNumber, betAmount = bet
            totalAmount += betAmount
            if(betNumber == winner):
                winnersAmount += betAmount
                winners.append((player, betAmount))


        if(len(winners) == 0):
            print(f"The house wins {totalAmount}€")
            for p, b in zip(self.players, self.bets):
                blockchain.new_transaction(sender = p.getName(), recipient = "house", amount = b[1])
        else:
            for p, b in winners:
                winnings = (b / winnersAmount) * totalAmount
                print(f"{p.getName()} wins {winnings}€")
                blockchain.new_transaction(sender = "house", recipient = p.getName(), amount = winnings)
