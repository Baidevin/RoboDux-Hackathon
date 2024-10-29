import turtle
import duxSerial
class Mobility():
    def __init__(self):
        self.pendown = True
        self.targetPos = [0,0]

        self.window = turtle.Screen()
        self.window.bgcolor("blue")
        self.window.setup(width=1000, height=800)
        self.window.title("Preview")
        self.window.listen()

        self.character = turtle.Turtle()
        self.character.shape("turtle")
        self.character.penup()
        self.character.goto(0, 0)
        # self.character.speed(1)
        
        self.duxSerial = duxSerial.DuxSerial()

    def arrived(self) -> bool:
        print(f"Arrived at x: {self.targetPos[0]} y: {self.targetPos[1]} pendown: {self.pendown}")
        return True

    def goto(self, pos):
        lastpos = self.targetPos
        self.targetPos = pos
        self.pendown = self.targetPos[2]
        print(f"Going to x: {self.targetPos[0]} y: {self.targetPos[1]} pendown: {self.pendown}")
        if self.pendown:
            self.character.pendown()
            self.duxSerial.sendPendown()
        else:
            self.duxSerial.sendPenup()
            self.character.penup()
        self.character.goto(pos[0] - 500, -pos[1] + 400)
        self.duxSerial.sendGoto(pos[0] - lastpos[0], pos[1] - lastpos[1])
        