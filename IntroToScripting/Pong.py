import turtle #Jordan Schutte 10/7/2021, Pong operational, room movement working
import os
import random as rand

def pong():
    def player1UP():
        y = player1.ycor()
        y += 20
        player1.sety(y)

    def player1DOWN():
        y = player1.ycor()
        y -= 20
        player1.sety(y)

    def player2UP():
        y = player2.ycor()
        y += 20
        player2.sety(y)

    def player2DOWN():
        y = player2.ycor()
        y -= 20
        player2.sety(y)
    scoreP1 = 0
    scoreP2 = 0
    name = "Player1"
    botname = "Player2"
    pong = turtle.Screen()
    pong.title("Pong")
    pong.bgcolor("black")
    pong.setup(width=800, height=600)
    pong.tracer(0)
#player1
    player1 = turtle.Turtle()
    player1.speed(0)
    player1.shape("square")
    player1.color("white")
    player1.shapesize(4, 1)
    player1.penup()
    player1.goto(-325, 0)
#player2
    player2 = turtle.Turtle()
    player2.speed(0)
    player2.shape("square")
    player2.color("white")
    player2.shapesize(4, 1)
    player2.penup()
    player2.goto(330, 0)
#ball
    ball = turtle.Turtle()
    ball.speed(0)
    ball.shape("circle")
    ball.color("white")
    ball.penup()
    ball.goto(0, 0)
#ball delta
    ball.dx = .2
    ball.dy = .2
#pen
    pen = turtle.Turtle()
    pen.speed(0)
    pen.shape("square")
    pen.color("white")
    pen.penup()
    pen.hideturtle()
    pen.goto(0, 260)
    pen.write("{}: {}   {}: {}".format(name, scoreP1, botname, scoreP2), align="center", font=("Cooper Black", 16, "normal"))
#Controls
    pong.listen()
    pong.onkeypress(player1UP, "w" or "W")
    pong.onkeypress(player1DOWN, "s" or "S")
#gameloop
    while scoreP1 + scoreP2 < 5:
        pong.update()
        ball.setx(ball.xcor() + ball.dx)
        ball.sety(ball.ycor() + ball.dy)
    #Boundaries
        if ball.ycor() > 290:
            ball.sety(290)
            ball.dy *= -1

        if ball.ycor() < -290:
            ball.sety(-290)
            ball.dy *= -1
    #Scoring
        if ball.xcor() > 390:
            scoreP1 += 1
            pen.clear()
            pen.write("{}: {} {}: {}".format(name, scoreP1, botname, scoreP2), align="center", font=("Cooper Black", 16, "normal"))
            ball.goto(0, 0)
            ball.dx *= -1

        if ball.xcor() < -390:
            scoreP2 += 1
            pen.clear()
            pen.write("{}: {} {}: {}".format(name, scoreP1, botname, scoreP2), align="center", font=("Cooper Black", 16, "normal"))
            ball.goto(0, 0)
            ball.dx *= -1

        #paddle + ball collision
        if ball.xcor() < -330 and ball.ycor() < player1.ycor() + 50 and ball.ycor() > player1.ycor() - 50:
            ball.dx *= -1

        elif ball.xcor() > 330 and ball.ycor() < player2.ycor() + 50 and ball.ycor() > player2.ycor() - 50:
            ball.dx *= -1

    else:
        pong.bye()

if __name__ == '__main__':
    pong()
