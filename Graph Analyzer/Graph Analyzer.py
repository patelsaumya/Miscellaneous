"""# Graph Library"""

import re
import operator

class Neighbour:
    def __init__(self, index):
        self.index = index

class Vertex:
    def __init__(self, name):
        self.neighbours = []
        self.tmpNeighbours = []
        self.neighbourTree = []
        self.isConnected = [] 
        self.isDisconnected = []
        self.name = name
        self.degree = 0
        self.parent = ()
        self.isVisited = 0
        self.relationsDestroyed = 0
        self.colour = ""

    def addNeighbour(self, index):
        neighbour = Neighbour(index)
        self.neighbours.append(neighbour)

class Graph:
    def __init__(self, vertices, edges):
        self.vertices = []
        self.edges = []
        self.error = 1
        self.queue = []
        self.edgesLeft = []
        self.edgesForSimpleGraph = []
        self.distance = 0
        self.diameter = 0
        self.connectedComponentsOfGraph = []
        self.parallelEdges = []
        self.tmpParallelEdges = []

        vertices = re.sub(' {2,}', ' ', vertices)
        vertices = vertices.split(' ')

        for i in range(0, len(vertices)):
            vertex = Vertex(vertices[i])
            self.vertices.append(vertex)


        for l in range(0, len(self.vertices) - 1):
            for m in range(l+1, len(self.vertices)):
                if self.vertices[l].name == self.vertices[m].name:
                    self.error = 0
                    print(f'\nThere are multiple instances of {self.vertices[l].name}')
                    print('Graph is invalid')
                    return

        edges = re.sub(' {2,}', ' ', edges)
        edges = re.split('[ |-]', edges)

        for i in range(0, len(edges)):
            self.edges.append(edges[i])

        self.distance = len(self.edgesForSimpleGraph)/2

        for i in range(0, len(edges)-1):
            if i%2 == 0:
                index1 = self.findVertexIndex(edges[i])
                index2 = self.findVertexIndex(edges[i+1])
            else:
                continue

            if index1 == -1:
                print(f'\nVertex {edges[i]} not found')
                print('Graph is invalid')
                self.error = 0
                return

            if index2 == -1:
                print(f'\nVertex {edges[i+1]} not found')
                print('Graph is invalid')
                self.error = 0
                return

            isPresent = 0
            if index1 != index2:
                for j in range(0, len(self.vertices[index1].neighbours)):
                    if self.vertices[index1].neighbours[j].index == index2:
                        isPresent = 1
                        break
                if isPresent == 0:
                    self.edgesForSimpleGraph.append(edges[i])
                    self.edgesForSimpleGraph.append(edges[i+1])
                if isPresent == 1:
                    l = 0
                    b = {edges[i], edges[i+1]}
                    for k in range(0, len(self.parallelEdges)):
                        a = set(self.parallelEdges[k][0])
                        if a == b:
                            l = 1
                            y = list(self.parallelEdges[k])
                            y[1] += 1
                            self.parallelEdges.pop(k)
                            self.parallelEdges.append(tuple(y))
                            break

                    if l == 0:
                        self.parallelEdges.append((b, 2))

            self.vertices[index1].addNeighbour(index2)
            if index1 != index2:
                self.vertices[index2].addNeighbour(index1)

        for n in range(0, len(self.vertices)):
            for o in range(0, len(self.vertices[n].neighbours)):
                self.vertices[n].tmpNeighbours.append(self.vertices[n].neighbours[o])

        for z in range(0, len(self.parallelEdges)):
            self.tmpParallelEdges.append(self.parallelEdges[z])

        return

    def findVertexIndex(self, name):
        for i in range(0, len(self.vertices)):
            if self.vertices[i].name == name:
                return i
        return -1

    def edgesLeftInitialised(self, beginningNode, destinationNode, path):
        if self.error == 1:
            self.initialise()
            beginningNodeIndex = self.findVertexIndex(beginningNode)
            destinationNodeIndex = self.findVertexIndex(destinationNode)
            if beginningNodeIndex == -1:
                return -2
            if destinationNodeIndex == -1:
                return -3
            for i in range(0, len(self.edgesForSimpleGraph)):
                index = self.findVertexIndex(self.edgesForSimpleGraph[i])
                self.edgesLeft.append(index)
            return self.queueMaking(beginningNodeIndex, destinationNodeIndex, path)

    def queueMaking(self, beginningNodeIndex, destinationNodeIndex, path):
        if self.error == 1:
            isBeginningNodeVisited = 0
            self.queue.append((destinationNodeIndex,0))
            self.vertices[destinationNodeIndex].isVisited = 1
            while len(self.queue) != 0:
                currentNodeIndex = self.queue.pop(0)
                if currentNodeIndex[0] == beginningNodeIndex:
                    isBeginningNodeVisited = 1
                    if currentNodeIndex[1] < self.distance:
                        self.distance = currentNodeIndex[1]
                self.makeNeighbourGraph(currentNodeIndex)
                for i in range(0, len(self.vertices[currentNodeIndex[0]].neighbourTree)):
                    self.queue.append((self.vertices[currentNodeIndex[0]].neighbourTree[i], currentNodeIndex[1]+1))
                    if self.vertices[self.vertices[currentNodeIndex[0]].neighbourTree[i]].isVisited == 0:
                        self.vertices[self.vertices[currentNodeIndex[0]].neighbourTree[i]].parent = (self.vertices[currentNodeIndex[0]].name, currentNodeIndex[0])
                        self.vertices[self.vertices[currentNodeIndex[0]].neighbourTree[i]].isVisited = 1
            if isBeginningNodeVisited == 1:
                path.clear()
                self.formPath(beginningNodeIndex, destinationNodeIndex, path)
                return self.distance
            else:
                return -1

    def makeNeighbourGraph(self, currentNodeIndex):

        if self.error == 1:
            if len(self.edgesLeft) == 0:
                return

            edgesLeftLen = len(self.edgesLeft)
            tmpEdgesCompleted = []
            isPresent = 0
            for i in range(0, edgesLeftLen):
                if self.edgesLeft[i] == currentNodeIndex[0]:
                    for j in range(0, len(tmpEdgesCompleted)):
                        if tmpEdgesCompleted[j] == i:
                            isPresent = 1
                            break
                        else:
                            isPresent = 0
                    if isPresent == 0:
                        tmpEdgesCompleted.append(i)

                    if i%2 == 0:
                        for k in range(0, len(tmpEdgesCompleted)):
                            if tmpEdgesCompleted[k] == i+1:
                                isPresent = 1
                                break
                            else:
                                isPresent = 0
                        if isPresent == 0:
                            self.vertices[currentNodeIndex[0]].neighbourTree.append(self.edgesLeft[i+1])
                            tmpEdgesCompleted.append(i+1)

                    else:
                        for l in range(0, len(tmpEdgesCompleted)):
                            if tmpEdgesCompleted[l] == i-1:
                                isPresent = 1
                                break
                            else:
                                isPresent = 0
                        if isPresent == 0:
                            self.vertices[currentNodeIndex[0]].neighbourTree.append(self.edgesLeft[i-1])
                            tmpEdgesCompleted.append(i-1)

            tmpEdgesCompleted.sort()
            m = 0
            for i in range(0, len(tmpEdgesCompleted)):
                self.edgesLeft.pop((tmpEdgesCompleted[i])-m)
                m += 1
            return

    def printNeighbourTree(self):
        if self.error == 1:
            for i in range(0, len(self.vertices)):
                neighbourTreeName = [self.vertices[self.vertices[i].neighbourTree[j]].name for j in range(0, len(self.vertices[i].neighbourTree))]

    def formPath(self, beginningNodeIndex, destinationNodeIndex, path):
        if self.error == 1:
            path.clear()
            if beginningNodeIndex == destinationNodeIndex:
                path.append(self.vertices[beginningNodeIndex].name)
            else:
                i = self.vertices[beginningNodeIndex]
                path.append(i.name)
                for k in range(0, int(self.distance)):
                    if i == self.vertices[destinationNodeIndex]:
                        path.append(self.vertices[destinationNodeIndex].name)
                    else:
                        j = i.parent[1]
                        path.append(i.parent[0])
                        i = self.vertices[j]

    def initialiseTmps(self):
        for i in range(0, len(self.vertices)):
            self.vertices[i].tmpNeighbours.clear()
        for n in range(0, len(self.vertices)):
            for o in range(0, len(self.vertices[n].neighbours)):
                self.vertices[n].tmpNeighbours.append(self.vertices[n].neighbours[o])
        self.tmpParallelEdges.clear()
        for z in range(0, len(self.parallelEdges)):
            self.tmpParallelEdges.append(self.parallelEdges[z])

    def initialise(self):
        self.edgesLeft = []
        self.queue = []
        for i in range(0, len(self.vertices)):
            self.vertices[i].neighbourTree = []
            self.vertices[i].isVisited = 0
            self.vertices[i].parent = ()
        self.error = 1
        self.distance = len(self.edgesForSimpleGraph)/2
        self.connectedComponentsOfGraph.clear()

    def initialiseConnectedAndDisconnected(self):
        for x in range(0, len(self.vertices)):
            self.vertices[x].isConnected.clear()
            self.vertices[x].isDisconnected.clear()

    def findDiameter(self, pathDiameter, fromTo):
        if self.error == 1:
            self.diameter = 0
            h = 0
            tmpPathDiameter = []
            self.initialiseConnectedAndDisconnected()

            for k in range(0, len(self.vertices)):
                self.vertices[k].isConnected.append(k)

            for i in range(0, (len(self.vertices))-1):
                for j in range(i+1, len(self.vertices)):
                    self.initialise()
                    pathDiameter.clear()
                    distance = self.edgesLeftInitialised(self.vertices[i].name, self.vertices[j].name, pathDiameter)
                    if distance >= 0:
                        self.vertices[i].isConnected.append(j)
                        self.vertices[j].isConnected.append(i)
                        if distance > self.diameter:
                            tmpPathDiameter.clear()
                            for k in range (0, len(pathDiameter)):
                                tmpPathDiameter.append(pathDiameter[k])
                            fromTo.clear()
                            self.diameter = distance
                            fromTo.append(self.vertices[i].name)
                            fromTo.append(self.vertices[j].name)
                    else:
                        self.vertices[i].isDisconnected.append(j)
                        self.vertices[j].isDisconnected.append(i)
                        self.initialise()
                        pathDiameter.clear()
                        h = 1

            self.initialise()
            pathDiameter.clear()
            for l in range(0, len(tmpPathDiameter)):
                pathDiameter.append(tmpPathDiameter[l])
            if h == 1:
                return -1
            else:
                return self.diameter

    def modifyEdgesList(self, cutPoint):
        if self.error == 1:
            vertexToBeRemoved = []
            for i in range(0, len(self.edgesForSimpleGraph)):
                if self.edgesForSimpleGraph[i] == cutPoint:
                    if i%2 == 0:
                        vertexToBeRemoved.append(i)
                        vertexToBeRemoved.append(i+1)
                    else:
                        vertexToBeRemoved.append(i)
                        vertexToBeRemoved.append(i-1)
            j = 0
            vertexToBeRemoved.sort()
            for l in range(0, len(vertexToBeRemoved)):
                self.edgesForSimpleGraph.pop((vertexToBeRemoved[l]) - j)
                j += 1

    def findCutPoints(self, cutPoints):
        if self.error == 1:
            tmpEdges = []
            cutPoints.clear()
            for l in range(0, len(self.edgesForSimpleGraph)):
                tmpEdges.append(self.edgesForSimpleGraph[l])
            distance2 = 0
            distance1 = 0
            for i in range(0, len(self.vertices)):
                self.initialise()
                cutPoint = self.vertices[i].name
                self.modifyEdgesList(cutPoint)
                path = []
                relationsDestroyed = 0
                for j in range(0, len(self.vertices) - 1):
                    if j == i:
                        continue
                    for k in range(j+1, len(self.vertices)):
                        distance1 = 0
                        distance2 = 0
                        if k == i:
                            continue
                        self.initialise()
                        distance2 = self.edgesLeftInitialised(self.vertices[j].name, self.vertices[k].name, path)
                        if distance2 == -1:
                            self.edgesForSimpleGraph = []
                            for m in range(0, len(tmpEdges)):
                                self.edgesForSimpleGraph.append(tmpEdges[m])
                            self.initialise()
                            distance1 = self.edgesLeftInitialised(self.vertices[j].name, self.vertices[k].name, path)
                            self.initialise()
                            if distance1 > 0:
                                if relationsDestroyed == 0:
                                    cutPoints.append(cutPoint)
                                relationsDestroyed += 1
                                self.vertices[i].relationsDestroyed = relationsDestroyed
                            self.modifyEdgesList(cutPoint)
                self.edgesForSimpleGraph = []
                for n in range(0, len(tmpEdges)):
                    self.edgesForSimpleGraph.append(tmpEdges[n])
                self.initialise()
            return

    def findBridges(self, bridges, numberOfRelationsDestroyedByEachBridge):
        if self.error == 1:
            tmpEdges = []
            path = []
            bridges.clear()
            numberOfRelationsDestroyedByEachBridge.clear()
            for i in range(0, len(self.edgesForSimpleGraph)):
                tmpEdges.append(self.edgesForSimpleGraph[i])
            for j in range(0, len(tmpEdges), 2):
                self.initialise()
                self.edgesForSimpleGraph.pop(j)
                self.edgesForSimpleGraph.pop(j)
                relationsDestroyed = 0
                haveDestroyed = 0
                for k in range(0, len(self.vertices) - 1):
                    for l in range(k+1, len(self.vertices)):
                        distance1 = 0
                        distance2 = 0
                        self.initialise()
                        distance2 = self.edgesLeftInitialised(self.vertices[k].name, self.vertices[l].name, path)
                        if distance2 == -1:
                            self.edgesForSimpleGraph = []
                            for m in range(0, len(tmpEdges)):
                                self.edgesForSimpleGraph.append(tmpEdges[m])
                            self.initialise()
                            distance1 = self.edgesLeftInitialised(self.vertices[k].name, self.vertices[l].name, path)
                            self.initialise()
                            if distance1 > 0:
                                if relationsDestroyed == 0:
                                    haveDestroyed = 1
                                    bridges.append((tmpEdges[j], tmpEdges[j+1]))
                                relationsDestroyed += 1
                            self.edgesForSimpleGraph.pop(j)
                            self.edgesForSimpleGraph.pop(j)
                if haveDestroyed == 1:
                    numberOfRelationsDestroyedByEachBridge.append(relationsDestroyed)
                self.edgesForSimpleGraph = []
                for n in range(0, len(tmpEdges)):
                    self.edgesForSimpleGraph.append(tmpEdges[n])
                self.initialise()
            return

    def fillDegreeList(self, degreeList):
        if self.error == 1:
            degreeList.clear()
            for i in range(0, len(self.vertices)):
                numberOfNeighbours = len(self.vertices[i].neighbours)
                nodeNeighbourIndex = [self.vertices[i].neighbours[j].index for j in range(0, numberOfNeighbours)]
                for k in range(0, len(nodeNeighbourIndex)):
                    if nodeNeighbourIndex[k] == i:
                        self.vertices[i].degree += 2
                    else:
                        self.vertices[i].degree += 1
                degreeList.append(self.vertices[i].degree)
            return

    def ConnectedComponents(self, connectedComponents, maximallyConnectedComponents):
        if self.error == 1:
            self.initialise()
            connectedComponents.clear()
            maximallyConnectedComponents.clear()
            isPresent = 0
            pathDiameter = []
            fromTo = []
            self.findDiameter(pathDiameter, fromTo)
            tmpSubGraphs = [self.vertices[i].isConnected for i in range(0, len(self.vertices))]
            tmpComponents = []

            for j in range(0, len(tmpSubGraphs)):
                isPresent = 0
                a = set(tmpSubGraphs[j])
                for k in range(0, len(self.connectedComponentsOfGraph)):
                    b = set(self.connectedComponentsOfGraph[k])
                    if a == b:
                        isPresent = 1
                        break
                if isPresent == 0:
                    self.connectedComponentsOfGraph.append(tmpSubGraphs[j])


            for m in range(0, len(self.connectedComponentsOfGraph)):
                connectedComponents.append(self.connectedComponentsOfGraph[m])

            for n in range(0, len(connectedComponents)):
                for o in range(0, len(connectedComponents[n])):
                    connectedComponents[n][o] = self.vertices[connectedComponents[n][o]].name

            for p in range(0, len(connectedComponents)):
                tmpComponents.append(len(connectedComponents[p]))

            maximumConnectedVertices = tmpComponents[0]
            for q in range(0, len(tmpComponents)):
                if maximumConnectedVertices < tmpComponents[q]:
                    maximumConnectedVertices = tmpComponents[q]

            for r in range(0, len(connectedComponents)):
                if tmpComponents[r] == maximumConnectedVertices:
                    maximallyConnectedComponents.append(connectedComponents[r])

            return

    def isThereInParallelEdges(self, edge):
        for i in range(0, len(self.tmpParallelEdges)):
            if self.tmpParallelEdges[i][0] == edge:
                y = list(self.tmpParallelEdges[i])
                if y[1] == 2:
                    self.tmpParallelEdges.pop(i)
                else:
                    self.tmpParallelEdges.pop(i)
                    y[1] -= 1
                    self.tmpParallelEdges.append(tuple(y))
                return 1
        return 0

    def Fleury(self, fromVertex, CycleOrPath):
        if self.error == 1:
            self.initialise()
            self.initialiseTmps()
            tmp = []
            for i in range(0, len(self.edgesForSimpleGraph)):
                tmp.append(self.edgesForSimpleGraph[i])
            CycleOrPath.clear()
            y = int(len(self.edges) / 2)
            for x in range(0, y+1):
                if fromVertex != None:
                    bridges = []
                    numberOfRelationsDestroyedByEachBridge = []
                    self.findBridges(bridges, numberOfRelationsDestroyedByEachBridge)
                    CycleOrPath.append(self.vertices[fromVertex].name)
                    toVertex = None

                    for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                        if fromVertex == self.vertices[fromVertex].tmpNeighbours[q].index:
                            toVertex = fromVertex
                            break

                    if toVertex == None:
                        for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                            isPresent = 0
                            b = {self.vertices[fromVertex].name,
                                 self.vertices[self.vertices[fromVertex].tmpNeighbours[q].index].name}
                            if self.isThereInParallelEdges(b) == 1:
                                for z in range(0, len(bridges)):
                                    a = set(bridges[z])
                                    if a != b:
                                        isPresent = 0
                                    else:
                                        isPresent = 1
                                        break
                                if isPresent == 0:
                                    toVertex = self.vertices[fromVertex].tmpNeighbours[q].index
                                    break

                        if toVertex == None:
                            for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                                b = {self.vertices[fromVertex].name,
                                     self.vertices[self.vertices[fromVertex].tmpNeighbours[q].index].name}
                                for z in range(0, len(bridges)):
                                    a = set(bridges[z])
                                    if a == b:
                                        if self.isThereInParallelEdges(b) == 1:
                                            toVertex = self.vertices[fromVertex].tmpNeighbours[q].index
                                            break
                                if toVertex == self.vertices[fromVertex].tmpNeighbours[q].index:
                                    break

                            if toVertex == None:
                                for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                                    isPresent = 0
                                    b = {self.vertices[fromVertex].name,
                                         self.vertices[self.vertices[fromVertex].tmpNeighbours[q].index].name}
                                    if self.isThereInParallelEdges(b) == 0:
                                        for z in range(0, len(bridges)):
                                            a = set(bridges[z])
                                            if a != b:
                                                isPresent = 0
                                            if a == b:
                                                isPresent = 1
                                                break
                                        if isPresent == 0:
                                            toVertex = self.vertices[fromVertex].tmpNeighbours[q].index
                                            break

                                if toVertex == None:
                                    for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                                        b = {self.vertices[fromVertex].name,
                                             self.vertices[self.vertices[fromVertex].tmpNeighbours[q].index].name}
                                        for z in range(0, len(bridges)):
                                            a = set(bridges[z])
                                            if a == b:
                                                if self.isThereInParallelEdges(b) == 0:
                                                    toVertex = self.vertices[fromVertex].tmpNeighbours[q].index
                                                    break
                                        if toVertex == self.vertices[fromVertex].tmpNeighbours[q].index:
                                            break

                    for q in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                        if self.vertices[fromVertex].tmpNeighbours[q].index == toVertex:
                            self.vertices[fromVertex].tmpNeighbours.pop(q)
                            break
                    if fromVertex != toVertex:
                        if toVertex != None:
                            for q in range(0, len(self.vertices[toVertex].tmpNeighbours)):
                                if self.vertices[toVertex].tmpNeighbours[q].index == fromVertex:
                                    self.vertices[toVertex].tmpNeighbours.pop(q)
                                    break

                    if toVertex != None:
                        a = {self.vertices[fromVertex].name, self.vertices[toVertex].name}
                        countNumberEdgesAvailable = 0
                        for j in range(0, len(self.vertices[fromVertex].tmpNeighbours)):
                            if self.vertices[toVertex].name == self.vertices[self.vertices[fromVertex].tmpNeighbours[j].index].name:
                                countNumberEdgesAvailable = 1
                                break
                        if countNumberEdgesAvailable == 0:
                            for k in range(0, len(self.edgesForSimpleGraph), 2):
                                b = {self.edgesForSimpleGraph[k], self.edgesForSimpleGraph[k+1]}
                                if a == b:
                                    self.edgesForSimpleGraph.pop(k)
                                    self.edgesForSimpleGraph.pop(k)
                                    break

                    fromVertex = toVertex
                    continue

            self.edgesForSimpleGraph.clear()
            for j in range(0, len(tmp)):
                self.edgesForSimpleGraph.append(tmp[j])
            self.initialiseTmps()
            return

    def Euler(self, CycleOrPath):
        if self.error == 1:
            self.initialise()
            self.initialiseTmps()
            connectedComponents = []
            maximallyConnectedComponents = []
            degreeList = []
            CycleOrPath.clear()
            self.ConnectedComponents(connectedComponents, maximallyConnectedComponents)
            for j in range(0, len(self.connectedComponentsOfGraph) - 1):
                b = set(self.connectedComponentsOfGraph[j])
                if len(b) == 1:
                    index1 = self.findVertexIndex(self.connectedComponentsOfGraph[j][0])
                    if len(self.vertices[index1].neighbours) == 0:
                        continue
                for k in range(j+1, len(self.connectedComponentsOfGraph)):
                    a = set(self.connectedComponentsOfGraph[k])
                    if a != b:
                        if len(a) == 1:
                            index2 = self.findVertexIndex(self.connectedComponentsOfGraph[k][0])
                            if len(self.vertices[index2].neighbours) == 0:
                                continue
                        return 0

            self.fillDegreeList(degreeList)
            numberOfVerticesHavingOddDegrees = 0
            numberOfVerticesHavingEvenDegrees = 0
            for l in range(0, len(degreeList)):
                if degreeList[l] % 2 == 0:
                    numberOfVerticesHavingEvenDegrees += 1
                else:
                    numberOfVerticesHavingOddDegrees += 1
            nonZeroDegreeList = []
            for p in range(0, len(degreeList)):
                if degreeList[p] != 0:
                    nonZeroDegreeList.append(p)

            if numberOfVerticesHavingOddDegrees > 2:
                return 0

            if numberOfVerticesHavingOddDegrees == 2:
                fromTo = []
                for q in range(0, len(nonZeroDegreeList)):
                    if self.vertices[nonZeroDegreeList[q]].degree % 2 != 0:
                        fromTo.append(nonZeroDegreeList[q])
                fromVertex = fromTo[0]
                self.Fleury(fromVertex, CycleOrPath)

                return -1

            if numberOfVerticesHavingEvenDegrees == len(degreeList):
                if len(nonZeroDegreeList) != 0:
                    fromVertex = None
                    for q in range(0, len(nonZeroDegreeList)):
                        if self.vertices[nonZeroDegreeList[q]].degree % 2 == 0:
                            fromVertex = nonZeroDegreeList[q]
                            break
                    self.Fleury(fromVertex, CycleOrPath)
                return 1

    def degreeOfVertex(self, vertexIndex):
        return self.vertices[vertexIndex].degree

"""# User Interface"""

import os

print('=================== UnDirected Graph ===================\n')
vertices = input('Enter the vertices: ')
edges = input('Enter edges: ')
print('\n======================================')
g = Graph(vertices, edges)
if g.error == 1:
    print(f'\nNumber Of Vertices: {len(g.vertices)}')
    print(f'Number Of Edges: {int(len(g.edges)/2)}')
    pathDiameter = []
    fromTo = []
    diameter = g.findDiameter(pathDiameter, fromTo)
    g.initialise()
    cutPoints = []
    g.findCutPoints(cutPoints)
    g.initialise()
    cutPointsIndex = [g.findVertexIndex(cutPoints[i]) for i in range(0, len(cutPoints))]
    numberOfRelationsDestroyedByEachCutPoint = []
    for x in range(0, len(cutPointsIndex)):
        numberOfRelationsDestroyedByEachCutPoint.append(g.vertices[cutPointsIndex[x]].relationsDestroyed)

    maxRelationsDestroyerCutPoints = []
    maxRelationsDestroyedCutPoints = 0
    if len(numberOfRelationsDestroyedByEachCutPoint) != 0:
        maxRelationsDestroyedCutPoints = max(numberOfRelationsDestroyedByEachCutPoint)
        for z in range(0, len(numberOfRelationsDestroyedByEachCutPoint)):
            if numberOfRelationsDestroyedByEachCutPoint[z] == maxRelationsDestroyedCutPoints:
                maxRelationsDestroyerCutPoints.append(cutPoints[z])
    g.initialise()
    bridges = []
    numberOfRelationsDestroyedByEachBridge = []
    g.findBridges(bridges, numberOfRelationsDestroyedByEachBridge)
    maxRelationsDestroyedBridges = 0
    maxRelationsDestroyerBridges = []
    if len(bridges) != 0:
        maxRelationsDestroyedBridges = max(numberOfRelationsDestroyedByEachBridge)
        for z in range(0, len(bridges)):
            if numberOfRelationsDestroyedByEachBridge[z] == maxRelationsDestroyedBridges:
                maxRelationsDestroyerBridges.append(bridges[z])
    g.initialise()
    connectedComponents = []
    maximallyConnectedComponents = []
    g.ConnectedComponents(connectedComponents, maximallyConnectedComponents)
    numberOfVerticesInSubgraphs = []
    for i in range(0, len(connectedComponents)):
        numberOfVerticesInSubgraphs.append(len(connectedComponents[i]))
    maximumNumberOfVerticesInSubgraph = 0
    if len(maximallyConnectedComponents) != 0:
        maximumNumberOfVerticesInSubgraph = len(maximallyConnectedComponents[0])
    g.initialise()
    EulerCycleOrPath = []
    a = g.Euler(EulerCycleOrPath)
    g.initialise()
    g.initialise()
    choice = 'y'
    if g.error == 1:
        print('\n======================================')
        if g.error == 1:
            if diameter >= 0:
                print(f'\nDiameter Of Graph: {int(diameter)}')
                print(f'\tPossible Diameter from {fromTo[0]} to {fromTo[1]}: {pathDiameter}')
            if diameter == -1:
                print('\nDiameter does not exists, as Graph is DISCONNECTED!!!')
            
            print('\n======================================')
            print(f'\nConnected Components: {connectedComponents}')
            print(f'Number of Vertices in all Connected Components: {numberOfVerticesInSubgraphs}')
            print(f'Number of Connected Components: {len(connectedComponents)}')
            print(f'Maximally Connected Components of Graph: {maximallyConnectedComponents}')
            print(f'Maximum connected Vertices among all Connected Components : {maximumNumberOfVerticesInSubgraph}')
            print(f'Number of Maximally Connected Components: {len(maximallyConnectedComponents)}')
            print('\n======================================')
            print(f'\nCut-Points: {cutPoints}')
            print(f'Number of Cut Points: {len(cutPoints)}')
            print(f'Number Of Relations Destroyed by each Cut Point: {numberOfRelationsDestroyedByEachCutPoint}')
            print(f'Maximum Relations Destroyed by a Node: {maxRelationsDestroyedCutPoints}')
            print(f'Maximum Relations Destroyer (Node): {maxRelationsDestroyerCutPoints}')
            print(f'Number of Nodes which destroy maximum relations: {len(maxRelationsDestroyerCutPoints)}')
            print('\n======================================')
            print(f'\nBridges: {bridges}')
            print(f'Number of Bridges: {len(bridges)}')
            print(f'Number Of Relations Destroyed by each Bridge: {numberOfRelationsDestroyedByEachBridge}')
            print(f'Maximum Relations Destroyed by an Edge: {maxRelationsDestroyedBridges}')
            print(f'Maximum Relations Destroyer (Edge): {maxRelationsDestroyerBridges}')
            print(f'Number of Edges which destroy maximum relations: {len(maxRelationsDestroyerBridges)}')
            print('\n======================================')
            if a == -1:
                print(f'\nEulerian Path exists')
                print(f'\tOne possible Eulerian Path:')
                print(f'\t{EulerCycleOrPath}')
                print(f'Graph is Semi-Eulerian')
            if a == 1:
                print(f'\nEulerian Cycle exists')
                print(f'\tOne possible Eulerian Cycle:')
                print(f'\t{EulerCycleOrPath}')
                print(f'Graph is Eulerian')
            if a == 0:
                print(f'\nNo Euler Cycle nor Euler path exists')
                print(f'Graph is Non-Eulerian')
            while choice != 'n':
                print('\n======================================')
                beginningNode = input('\nEnter the beginning node: ')
                destinationNode = input('Enter the destination node: ')
                g.initialise()
                path = []
                print('\n--------------------------------------')
                distance = g.edgesLeftInitialised(beginningNode, destinationNode, path)
                if distance == -2:
                    print(f'\n{beginningNode} does not exist')
                if distance == -3:
                    print(f'\n{destinationNode} does not exist')
                if distance == -1:
                    print(f'\n{beginningNode} is not connected to {destinationNode}\n')
                    g.printNeighbourTree()
                if distance >= 0:
                    print(f'\n(minimum) Distance between {beginningNode} and {destinationNode} is {int(distance)}')
                    print(f'\t(optimal) Possible Path: {path}')
                    g.printNeighbourTree()
                print('\n--------------------------------------')
                choice = input('\nDo you want to continue(y/n): ')
                os.system('cls')
                g.initialise()
print('\n=================== ENDED ===================')