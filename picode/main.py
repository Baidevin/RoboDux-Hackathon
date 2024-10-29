from turtle import goto
import cmdhandler
import mobility
import json

pathMode = True
curpath = []
isMoving = False

if __name__ == "__main__":
    networkingstuff = cmdhandler.cmdlink()
    networkingstuff.connect()
    mobilityHandler = mobility.Mobility()
    while True:
        if not isMoving:
            command = networkingstuff.handleMsg()
            if "pathmode" in command:
                pathMode = command["pathmode"]
                print(pathMode)
            elif "path" in command:
                waypoints = command["path"]
                for waypoint in waypoints:
                    curpath.append(waypoint)
                print(curpath)
            
            if len(curpath) > 0:
                isMoving = True
        else:
            if(len(curpath) > 0):
                for i in range(0, len(curpath), 5):
                    point = curpath[i]
                    while True:
                        mobilityHandler.goto(point)
                        if mobilityHandler.arrived():
                            break
                isMoving = False
                curpath = []
