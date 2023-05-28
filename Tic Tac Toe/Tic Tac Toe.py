import copy

def isFinalState(state, computerSymbol, userSymbol):
  if state[0][0] == state[0][1] == state[0][2] == userSymbol or state[1][0] == state[1][1] == state[1][2] == userSymbol or state[2][0] == state[2][1] == state[2][2] == userSymbol:
    return -1
  elif state[0][0] == state[1][0] == state[2][0] == userSymbol or state[0][1] == state[1][1] == state[2][1] == userSymbol or state[0][2] == state[1][2] == state[2][2] == userSymbol:
    return -1
  elif state[0][0] == state[1][1] == state[2][2] == userSymbol or state[0][2] == state[1][1] == state[2][0] == userSymbol:
    return -1
  elif state[0][0] == state[0][1] == state[0][2] == computerSymbol or state[1][0] == state[1][1] == state[1][2] == computerSymbol or state[2][0] == state[2][1] == state[2][2] == computerSymbol:
    return 1
  elif state[0][0] == state[1][0] == state[2][0] == computerSymbol or state[0][1] == state[1][1] == state[2][1] == computerSymbol or state[0][2] == state[1][2] == state[2][2] == computerSymbol:
    return 1
  elif state[0][0] == state[1][1] == state[2][2] == computerSymbol or state[0][2] == state[1][1] == state[2][0] == computerSymbol:
    return 1
  else:
    for i in range(len(state)):
      for j in range(len(state[0])):
        if state[i][j] == '-':
          return -2
    return 0

def isValidState(state, computerSymbol, userSymbol):
  numberOfUserSymbolsInTheState = 0
  numberOfComputerSymbolsInTheState = 0
  for i in range(len(state)):
    for j in range(len(state[0])):
      if state[i][j] == userSymbol:
        numberOfUserSymbolsInTheState += 1
      if state[i][j] == computerSymbol:
        numberOfComputerSymbolsInTheState += 1
  if numberOfUserSymbolsInTheState == numberOfComputerSymbolsInTheState + 1 or numberOfComputerSymbolsInTheState == numberOfUserSymbolsInTheState:
    return 1
  else:
    return 0

def isAllowed(state, userSymbol, userNumber):
  userRowNumber = (userNumber // 10) - 1
  userColumnNumber = (userNumber % 10) - 1
  if userRowNumber > len(state) or userColumnNumber > len(state[0]):
    return -1
  if state[userRowNumber][userColumnNumber] != '-':
    return 0
  else:
    state[userRowNumber][userColumnNumber] = userSymbol
    return 1

def argmax(childStateValues):
  maxValue = max(*childStateValues)
  for i in range(len(childStateValues)):
    if childStateValues[i] == maxValue:
      return i

def myNextMoves(state, symbol):
  if isFinalState(state, 'X', 'O') != -2:
    return None
  nextMoves = []
  for i in range(len(state)):
    for j in range(len(state[0])):
      if state[i][j] == '-':
        stateCopy = copy.deepcopy(state)
        stateCopy[i][j] = symbol
        nextMoves.append(stateCopy)
  return nextMoves

def myFirstChance(currentState, computerSymbol, userSymbol):
  computerSymbolsPlaced = []
  for i in range(len(currentState)):
    for j in range(len(currentState[0])):
      if currentState[i][j] == computerSymbol:
        computerSymbolsPlaced.append((i,j))
  if len(computerSymbolsPlaced) != 0:
    return False
  if currentState[1][1] == '-':
    currentState[1][1] = computerSymbol
  else:
    for i in range(len(currentState)):
      for j in range(len(currentState[0])):
        if i == 0 or i == len(currentState)-1:
          if j == 0 or j == len(currentState)-1:
            if currentState[i][j] != userSymbol:
              currentState[i][j] = computerSymbol
              computerSymbolsPlaced.clear()
              break
      if len(computerSymbolsPlaced) == 0:
        break
  return True

def mySecondChance(currentState, computerSymbol, userSymbol):
  userMoves = []
  computerMoves = []
  for i in range(len(currentState)):
    for j in range(len(currentState[0])):
      if currentState[i][j] == computerSymbol:
        computerMoves.append((i,j))
      elif currentState[i][j] == userSymbol:
        userMoves.append((i,j))
  if len(userMoves) == 1 and len(computerMoves) == 1:
    if currentState[0][0] != userSymbol:
      currentState[0][0] = computerSymbol
    elif currentState[0][2] != userSymbol:
      currentState[0][2] = computerSymbol
    elif currentState[2][0] != userSymbol:
      currentState[2][0] = computerSymbol
    elif currentState[2][2] != userSymbol:
      currentState[2][2] = computerSymbol
    return True
  return False

def ticTacToe(state, computerSymbol, userSymbol):
  if not isValidState(state, computerSymbol, userSymbol):
    return None
  if isFinalState(state, computerSymbol, userSymbol) != -2:
    return 'The game is finished. I cannot take any step.'
  numberOfSpacesLeft = []
  for i in range(len(state)):
    for j in range(len(state[0])):
      if state[i][j] == '-':
        numberOfSpacesLeft.append((i,j))
  if len(numberOfSpacesLeft) == 1:
    tmpState = copy.deepcopy(state)
    tmpState[numberOfSpacesLeft[0][0]][numberOfSpacesLeft[0][1]] = computerSymbol
    return tmpState
  queue = [[state, argmax, None, computerSymbol, None]]
  tree = []
  while True:
    if len(queue) == 0:
      break
    tree.append(queue.pop(0))
    currentState = tree[-1][0]
    currentAlgorithm = tree[-1][1]
    currentSymbol = tree[-1][3]
    nextFunctionToApplyMiniOrMax = min if currentAlgorithm == argmax or currentAlgorithm == max else max
    nextMoves = myNextMoves(currentState, currentSymbol)
    if not nextMoves:
        continue
    currentSymbol = computerSymbol if currentSymbol == userSymbol else userSymbol
    for nextState in nextMoves:
      if isFinalState(nextState, 'X', 'O') != -2:
        queue.append([nextState, None, len(tree)-1, None, isFinalState(nextState, computerSymbol, userSymbol)])
      else:
        queue.append([nextState, nextFunctionToApplyMiniOrMax, len(tree)-1, currentSymbol, None])
        

  parentNodesValueCalculated = []
  optimalNextMove = None
  while True:
    bottomStateValues = []
    parentNodeIndex = None
    
    for i in range(len(tree)-1, -1, -1):
      if tree[i][-1] != None and tree[i][2] not in parentNodesValueCalculated:
        if parentNodeIndex == None or parentNodeIndex == tree[i][2]:
          bottomStateValues.append(tree[i][-1])
        else:
          break
        if not parentNodeIndex:
          parentNodeIndex = tree[i][2]
    parentNodesValueCalculated.append(parentNodeIndex)
    minOrMaxFunction = tree[parentNodeIndex][1]
    tree[parentNodeIndex][-1] = minOrMaxFunction(bottomStateValues[::-1])
    if not parentNodeIndex:
      break
  optimalNextMove = tree[tree[0][-1]+1][0]
  return optimalNextMove

def beautifyState(state):
  for i in range(len(state)):
    for j in range(len(state[0])):
      print(f'{state[i][j]} ', end=' ')
    print()
  return

"""# Which is the most optimal move ?"""

inputState = [
         ['X', '-', '-'],
         ['X', '-', 'O'],
         ['O', 'X', '-']
]
print('Input State:\n')
beautifyState(inputState)

outputState = ticTacToe(inputState, 'O', 'X')

print('\n------------------------------\n')

if outputState:
  if type(outputState) == str:
    print(outputState)
  else:
    print('Output State:\n')
    beautifyState(outputState)
else:
  print('Invalid Input State')

inputState = [
         ['X', 'O', 'O'],
         ['X', 'X', 'O'],
         ['-', 'X', 'O']
]
print('Input State:\n')
beautifyState(inputState)

outputState = ticTacToe(inputState, 'O', 'X')

print('\n------------------------------\n')

if outputState:
  if type(outputState) == str:
    print(outputState)
  else:
    print('Output State:\n')
    beautifyState(outputState)
else:
  print('Invalid Input State')

"""# Play a Game with Computer"""

def playGame():
  print('WELCOME !!!  #UnBeatable\n')
  print('------------------------------\n')
  userSymbol = input("Which symbol will you continue with (X / O): ")
  computerSymbol = 'X' if userSymbol == 'O' else 'O'
  print(f'\nYour Symbol: {userSymbol}\nMy Symbol: {computerSymbol}\n')
  userOrComputerFirstChance = input("Who should take first chance ((U)ser / (C)omputer): ")
  currentChance = userOrComputerFirstChance
  currentState = [
                  ['-', '-', '-'],
                  ['-', '-', '-'],
                  ['-', '-', '-']
  ]
  print('\n')
  beautifyState(currentState)
  winner = None
  while True:
    print('\n------------------------------\n')
    finalState = isFinalState(currentState, computerSymbol, userSymbol)
    if finalState != -2:
      winner = finalState
      break
    if currentChance == 'U':
      while True:
        userNumber = int(input("Where should your symbol be placed (eg: 23 = row 2 and col 3): "))
        allowed = isAllowed(currentState, userSymbol, userNumber)
        if allowed == 0:
          print('That space is already filled')
        elif allowed == -1:
          print('Your input is invalid')
        else:
          print('\nYour Turn:- \n')
          beautifyState(currentState)
          break
      currentChance = 'C'
      continue
    if currentChance == 'C':
      print('\nMy Turn:- \n')
      isMyFirstChance = myFirstChance(currentState, computerSymbol, userSymbol)
      if not isMyFirstChance:
        if userOrComputerFirstChance == 'C':
          isMySecondChance = mySecondChance(currentState, computerSymbol, userSymbol)
          if not isMySecondChance:
            currentState = ticTacToe(currentState, computerSymbol, userSymbol)
        else:
          currentState = ticTacToe(currentState, computerSymbol, userSymbol)
      beautifyState(currentState)
      currentChance = 'U'
  if winner == -1:
    print('--------------------YOU WON 😢--------------------')
  elif winner == 1:
    print('--------------------I WON 😎--------------------')
  else:
    print('--------------------IT`S A TIE 🤝--------------------')

playGame()