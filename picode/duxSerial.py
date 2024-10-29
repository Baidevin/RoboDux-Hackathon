import serial
import threading
from time import sleep

class DuxSerial():
    def __init__(self) -> None:
        self.cmdQueue = []
        self.waiting = False
        self.acknowledge = False
        
        self.ser = serial.Serial('/dev/ttyUSB0', 9600)
        sleep(1)
        self.ser.write(b"!S")
        # self.ser.open()
        # self.ser.flush()
        
        self.recvThread = SerialRecvThread(self)
        self.recvThread.start()
        
        self.sendThread = threading.Thread(target=self.cmdLoop)
        self.sendThread.start()
    
    
    def sendCmd(self, cmd: str) -> None:
        print(f"Sending {cmd}")
        if not self.ser.isOpen():
            self.ser.open()
        self.ser.write(f"{cmd}\n".encode())
        
    def cmdLoop(self) -> None:
        while True:
            if self.waiting:
                sleep(0.1)
            else:
                self.acknowledge = False
                if len(self.cmdQueue) > 0:
                    cmd = self.cmdQueue.pop(0)
                    self.sendCmd(cmd)
                    # self.acknowledge = True # Assume Acknowledged
                    sleep(0.1)
                    while not self.acknowledge:
                        sleep(0.5)
                        self.sendCmd(cmd)
    
    def sendPenup(self) -> None:
        cmd = "!U"
        self.cmdQueue.append(cmd)
        
    def sendPendown(self) -> None:
        cmd = "!D"
        self.cmdQueue.append(cmd)
        
    def sendGoto(self, x: int, y: int) -> None:
        cmd = f"!M{x/10},{y/10}"
        self.cmdQueue.append(cmd)
        
    def sendStop(self) -> None:
        print("Sending Stop")
        cmd = "!S"
        self.acknolwedge = False
        self.cmdQueue = []
        while not self.acknolwedge:
            sleep(0.5)
            self.sendCmd(cmd)
            print("Sent Stop Packet")
        
    def handleMsg(self, msg: str) -> None:
        print(f"Received: {msg}")
        if not msg.startswith("$"):
            print("Invalid Message Received")
            return
        
        if msg.startswith("$A"):
            print("Cmd Queue Accepting")
            self.waiting = False
            if len(self.cmdQueue) == 0:
                # self.sendStop()
                pass
            return
        
        if msg.startswith("$R"):
            print("Cmd Queue Rejecting")
            self.waiting = True
            return
        
        if msg.startswith("$C"):
            print("Cmd Acknowledged")
            self.acknowledge = True
            return
        
class SerialRecvThread(threading.Thread):
    def __init__(self, duxSerial: DuxSerial) -> None:
        threading.Thread.__init__(self)
        self.duxSerial = duxSerial
        
    def run(self) -> None:
        while True:
            if self.duxSerial.ser.isOpen() and self.duxSerial.ser.in_waiting:
                msg = self.duxSerial.ser.readline().decode()
                self.duxSerial.handleMsg(msg)
            sleep(0.1)
            
if __name__ == "__main__":
    duxSerial = DuxSerial()
    duxSerial.sendPenup()
    duxSerial.sendPendown()
    duxSerial.sendGoto(700, 23)
    # duxSerial.sendGoto(-100, 0)
    # duxSerial.sendStop()
    # duxSerial.sendGoto(0, 100)
    # duxSerial.sendGoto(0, -100)
    # duxSerial.sendGoto(100, 100)
    # duxSerial.sendGoto(-100, -100)
    # duxSerial.sendGoto(100, -100)
    # duxSerial.sendGoto(-100, 100)
    
    
    