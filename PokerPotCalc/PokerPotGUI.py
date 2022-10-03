import sys
import PokerBot as PB
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class PokerPotGUI(QMainWindow):

    def __init__(self):
        super().__init__()
        self.title = 'Poker Pot GUI'
        self.pixmap = QPixmap('pokerTable.jpg')
        self.pixmap = self.pixmap.scaled(self.width(), self.height())
        self.setGeometry(self.height(), self.height(), self.width(), self.height())
        self.label = QLabel(self)
        self.label.setPixmap(self.pixmap)
        self.label.resize(self.width(), self.height())
        self.label.move(0, 0)
        self.widgets = []
        self.values = []
        self.initUI()

    def initUI(self):
        for i in range(1, 9):
            playerName = "Player" + " " + str(i)
            widget = QLineEdit(playerName, self)
            widget.move(60*i,30)
            widget.resize(60, 30)
            self.widgets.append(widget)
        mainPotWidget = QLineEdit("Pot: ", self)
        mainPotWidget.move(200, 200)
        mainPotWidget.resize(60,30)
        split = QLineEdit("times? ", self)
        split.move(200, 230)
        split.resize(60,30)
        self.button = QPushButton("Enter", self)
        self.button.move(200,260)
        self.button.clicked.connect(self.onClick)
        self.show()

    def onClick(self):
        QMessageBox.question(self, "", "MEMES " + self.widgets[1].text(), QMessageBox.Ok, QMessageBox.Ok)
        self.pokerPotCalc()

    def pokerPotCalc(self):
        players = []
        sidePotValues = []
        for w in self.widgets:
             name = w.text().split(" ",1)[0]
             amount = w.text().split(" ",1)[1]
             newPlayer = PB.Player(name, amount)
             players.append(newPlayer)
        while True:
            #QMessageBox(self, "", "Enter sidepots")
            sidePot = QLineEdit(self)
            if not sidePot: break
            sidePotValues.append(float(sidePot.text()))
        PB.sidePotStart()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = PokerPotGUI()
    w.show()
    sys.exit(app.exec_())
