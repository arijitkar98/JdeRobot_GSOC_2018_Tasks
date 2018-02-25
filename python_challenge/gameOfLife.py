import sys
import time
import json
from collections import OrderedDict

def displayConfig(board, iteration, steps, size=None):
    # move to the top of the screen
    sys.stdout.write('\033[H')
    # clear the screen
    sys.stdout.write('\033[J')
    # step number
    print('step: ' + str(iteration) + ' of ' + str(steps))

    sizeX = sizeY = size or 0
    for x, y in board:
        if x > sizeX:
            sizeX = x
        if y > sizeY:
            sizeY = y
    for i in range(0, sizeX):
        for j in range(0, sizeY):
            if (i,j) in board:
                sys.stdout.write(' x ')
            else:
                sys.stdout.write(' . ')
        print()

def testDisplayConfig(board, size=None):
    sizeX = sizeY = size or 0
    for x, y in board:
        if x > sizeX:
            sizeX = x
        if y > sizeY:
            sizeY = y
    for i in range(0, sizeX):
        for j in range(0, sizeY):
            if (i,j) in board:
                sys.stdout.write(' x ')
            else:
                sys.stdout.write(' . ')
        print()

def getNeighbours(cell, distance=1):
    # Return the getNeighbours at specified distance
    x, y = cell
    r = range(0 - distance, 1 + distance)
    new = set()
    for i in r:
        for j in r:
            if not i == j == 0:
                new.add((x+i,y+j))
    return new

def getNextConfig(board):
    # Advance the board one generation and return it.
    nextBoard = set()
    for cell in board:
        cellNeighbours = getNeighbours(cell)
        # test if live cell dies
        if len(board & cellNeighbours) in [2, 3]:
            nextBoard.add(cell)
        # test dead getNeighbours to see if alive
        for new in cellNeighbours:
            if len(board & set(getNeighbours(new))) is 3:
                nextBoard.add(new)
    return nextBoard

def checkBoardSize(board, size):
    checkedBoard = set()
    for cell in board:
        if cell[0] <= size and cell[1] <= size:
            checkedBoard.add(cell)
    return checkedBoard;

def getJson(pathname):
    # to store the mentioned values
    yes = ['y', 'Y', '']
    no = ['n', 'N']

    # to store settings and points data
    dataSettings = []

    # open the config from the provided JSON file
    with open(pathname, 'r') as dataFile:
        data = json.load(dataFile)

    # to make the entries in data stay ordered
    data = OrderedDict(sorted(data.items()))

    print("Use the default settings? (Y/n)")
    choice_setting = input()

    if choice_setting in yes:
        steps = int(data['steps'])
        size = int(data['size'])
        timeInterval = float(data['timeInterval'])

    elif choice_setting in no:
        print("Enter the number steps/generations(integer) ")
        steps = int(input())
        print("Enter the size of square world(integer)")
        size = int(input())
        print("Enter the time interval between 2 steps (float)")
        timeInterval = float(input())

    else:
        print("Invalid choice")
        return

    # set new default settings or not
    if choice_setting in no:
        print("Use these as default settings? (Y/n)")
        default = input()

        if default in yes:
            # set the current supplied data settings as new default
            data["steps"] = steps
            data["size"] = size
            data["timeInterval"] = timeInterval
            # write the new default into the JSON file
            with open(pathname, "w") as jsonFile:
                json.dump(data, jsonFile, indent=4, separators=(', ', ': '))

    # for choices in data:
    print("Enter choice for the world between 1 and ", len(data.items()) - 3)
    choices = int(input()) - 1

    # set to store the yx coordinates
    jsonPoints = set()
    for y in data[str(choices)]:
        for x in data[str(choices)][y]:
            point = (int(y), int(x))
            jsonPoints.add(point)

    dataSettings.append(jsonPoints)
    dataSettings.append(steps)
    dataSettings.append(size)
    dataSettings.append(timeInterval)

    return dataSettings

def main(pathname="settings.json"):
    dataSettings = getJson(pathname)
    board = dataSettings[0]
    steps = dataSettings[1]
    size = dataSettings[2]
    timeInterval = dataSettings[3]
    for i in range(1, steps + 1):
        displayConfig(board, i, steps, size)
        time.sleep(timeInterval)
        nextBoard = getNextConfig(board)
        board = checkBoardSize(nextBoard, size)

if __name__ == '__main__':
    main()
