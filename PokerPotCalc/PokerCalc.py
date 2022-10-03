class Pot:
    def __init__(self, value, players, prevMinStackPlayer=None):
        self._value = float(value)
        self._players = list(set(players))
        self._prevMinStackPlayer = prevMinStackPlayer
        assert(len(self._players) >= 2)
        assert(not prevMinStackPlayer in self._players)

    def isPlayerIn(self, player):
        return player in self._players

    def minStackPlayer(self):
        ret = self._players[0]
        for player in self._players:
            ret = player if player.value() < ret.value() else ret
        return ret

    def totalValue(self):
        n = self._prevMinStackPlayer.value() if self._prevMinStackPlayer else 0
        ret = self._value + (len(self._players) * (self.minStackPlayer().value() - n))
        return ret

    def nextPot(self, newValue=0):
        minStackPlayer = self.minStackPlayer()
        newPlayers = [p for p in self._players if p != minStackPlayer]
        ret = Pot(newValue, newPlayers, minStackPlayer)
        return ret

    def split(self, numWays):
        return self.totalValue() / int(numWays)

    def numPlayers(self):
        return len(self._players)

class Player:
    def __init__(self, name, value):
        self._name = name
        self._value = float(value)

    def value(self):
        return self._value

#result is a list, 0 is mainpot
def sidePotStart(players, mainPotValue, numWays, sidePotValues):
    ret = []
    mainPot = Pot(mainPotValue, players)
    ret.append(mainPot.split(numWays))
    pot = mainPot
    for sidePotValue in sidePotValues:
        sidePot = pot.nextPot(sidePotValue)
        ret.append(sidePot.split(numWays))
        pot = sidePot if sidePot.numPlayers() > 2 else None
    return ret

def main():
    players = []
    count = input("How many players?")
    for num in range(0, int(count)):
        name = input("Enter player name.")
        amount = input("Enter stack total.")
        newPlayer = Player(name, amount)
        players.append(newPlayer)
    mainPotValue = input("How much is currently in the pot?")
    numWays = input("How many times did you run the board?")
    sidePotValues = []
    while True:
        sidePotValue = input("Enter side pot value.")
        if not sidePotValue: break
        sidePotValues.append(float(sidePotValue))
    splits = sidePotStart(players, mainPotValue, numWays, sidePotValues)
    for i in range(len(splits)):
        split = splits[i]
        potStr = "main" if i == 0 else "side"
        print("Winners of the", potStr, "pot take", split)


if __name__ == "__main__":
    main()

#The basic algorithm is the dead chips (folds) + the minimum committed chips are distributed
#among the winners of the hand (main pot). If after this, there are still chips left in the pot,
#the process is repeated (for every side pot).
