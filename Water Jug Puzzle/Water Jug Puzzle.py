def waterJugProblem(jugsLimit, quantityToBeMeasured):
  machinePath = []
  userUnderstandablePath = []
  queue = []
  visitedStates = []
  currentState = tuple([0 for i in range(len(jugsLimit))])
  queue.append(currentState)
  userUnderstandablePath.append((currentState, None, 'Initially all jugs are empty'))
  jugNames = {i: f'{chr(65+i)}' for i in range(len(jugsLimit))}

  isInvalid = True
  for i in jugsLimit:
    if quantityToBeMeasured > i:
      isInvalid = isInvalid and True
    else:
      isInvalid = isInvalid and False
  if isInvalid:
    return None, None, None, None

  while True:
    currentState = queue.pop(0) if len(queue) else False
    if currentState == False:
      return None, None, None, None
    finalState = [0 for i in range(len(jugsLimit))]
    finalState[0] = quantityToBeMeasured
    if set(currentState) == set(finalState):
      machinePath.append(currentState)
      break
    if currentState in visitedStates or set(currentState) == set([i for i in jugsLimit]):
      continue
    for i in range(len(jugsLimit)):
      pourState = []
      throwState = []
      for j in range(len(jugsLimit)):
        if j == i:
          pourState.append(jugsLimit[j])
          throwState.append(0)
        else:
          pourState.append(currentState[j])
          throwState.append(currentState[j])
      queue.append(tuple(pourState))
      queue.append(tuple(throwState))
      userUnderstandablePath.append((tuple(pourState), currentState, f'Fill the whole jug {jugNames[i]}'))
      userUnderstandablePath.append((tuple(throwState), currentState, f'Empty jug {jugNames[i]}'))
      step = ''
      for j in range(len(jugsLimit)):
        if j != i:
          if jugsLimit[j] != currentState[j]:
            newStateOfj, newStateOfi = None, None
            if (currentState[j] + currentState[i]) <= jugsLimit[j]:
              newStateOfj = currentState[j] + currentState[i]
              newStateOfi = 0
              step = f'Transfer {currentState[i]} ltr from jug {jugNames[i]} to jug {jugNames[j]}'
            else:
              newStateOfj = jugsLimit[j]
              newStateOfi = currentState[j] + currentState[i] - jugsLimit[j]
              step = f'Transfer {jugsLimit[j]-currentState[j]} ltr from jug {jugNames[i]} to jug {jugNames[j]}'
            newState = []
            for k in range(len(jugsLimit)):
              if k == j:
                newState.append(newStateOfj)
              elif k == i:
                newState.append(newStateOfi)
              else:
                newState.append(currentState[k])
            queue.append(tuple(newState))
            userUnderstandablePath.append((tuple(newState), currentState, step))
    visitedStates.append(currentState)
    machinePath.append(currentState)
  buildingPerfectPath = []
  currentState = machinePath[-1]
  for i in userUnderstandablePath:
    if i[0] == currentState:
      currentState = i
      break
  buildingPerfectPath.append(currentState)
  while True:
    parentState = currentState[1]
    if parentState == None:
      break
    for i in userUnderstandablePath:
      if i[0] == parentState:
        buildingPerfectPath.append(i)
        currentState = i
        break
  jugNamesString = ''
  for i in jugNames:
    jugNamesString += f'Jug {jugNames[i]}: {jugsLimit[i]} ltr\n'
  return jugNames, jugNamesString, buildingPerfectPath[::-1], machinePath

"""# User Interface"""

print('WATER JUG PROBLEM:-\n==========================\n')

numberOfJugs = int(input("How many jugs do you want? "))
print("\n")
jugsLimit = []
for i in range(numberOfJugs):
  jugsLimit.append(int(input(f"Enter the limit of jug {i+1}: " )))
quantityToBeMeasured = int(input("\nHow much Quantity do you want to measure? "))

print("\n")

jugNames, jugNamesString, userUnderstablePerfectPath, machinePath = waterJugProblem(jugsLimit, quantityToBeMeasured)
if machinePath != None:
  print(f'Jug Names:-\n\n{jugNamesString}')
  print("State:- (", end='')
  for i in jugNames:
    print(jugNames[i], end=",") if i != len(jugNames)-1 else print(jugNames[i]+')')
  print('\n==========================\n')
  print(f"User Understandable Path:- (Solved in {len(userUnderstablePerfectPath)-1} Steps)\n\n")
  for i in userUnderstablePerfectPath:
    print(i[-1])
    print(f'\t\tResult:- {i[0]}\n')
    if i == userUnderstablePerfectPath[0]:
      print('--------------------------\n')
  print('\n=============BRAVO 😎=============\n')
else:
  print('\n=============NOT POSSIBLE 😡=============\n')

print('WATER JUG PROBLEM:-\n==========================\n')

numberOfJugs = int(input("How many jugs do you want? "))
print("\n")
jugsLimit = []
for i in range(numberOfJugs):
  jugsLimit.append(int(input(f"Enter the limit of jug {i+1}: " )))
quantityToBeMeasured = int(input("\nHow much Quantity do you want to measure? "))

print("\n")

jugNames, jugNamesString, userUnderstablePerfectPath, machinePath = waterJugProblem(jugsLimit, quantityToBeMeasured)
if machinePath != None:
  print(f'Jug Names:-\n\n{jugNamesString}')
  print("State:- (", end='')
  for i in jugNames:
    print(jugNames[i], end=",") if i != len(jugNames)-1 else print(jugNames[i]+')')
  print('\n==========================\n')
  print(f"User Understandable Path:- (Solved in {len(userUnderstablePerfectPath)-1} Steps)\n\n")
  for i in userUnderstablePerfectPath:
    print(i[-1])
    print(f'\t\tResult:- {i[0]}\n')
    if i == userUnderstablePerfectPath[0]:
      print('--------------------------\n')
  print('\n=============BRAVO 😎=============\n')
else:
  print('\n=============NOT POSSIBLE 😡=============\n')