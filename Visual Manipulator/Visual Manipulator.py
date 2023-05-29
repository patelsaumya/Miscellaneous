from PIL import Image
import numpy as np
import array
import math
import cv2
import random
import time

"""# Rotate"""

def rotation(originalImagePath, thetaInDegrees, rotationAboutXCoordinate, rotationAboutYCoordinate):
    #Even if axes rotates or changes(Moves or translates) the distance between any 2 points will be same before and after changing the orientation of axes.
    imageOriginal = Image.open(originalImagePath)
    data = np.array(imageOriginal)
    dataBlack = np.array(imageOriginal)
    for i in range(0, dataBlack.shape[0]):
        for j in range(0, dataBlack.shape[1]):
            dataBlack[i][j][0] = 0
            dataBlack[i][j][1] = 0
            dataBlack[i][j][2] = 0
            #dataBlack[i][j][3] = 255

    theta = math.pi * thetaInDegrees / 180
    cosTheta = math.cos(theta)
    sinTheta = math.sin(theta)
    widthOfImage = data.shape[1]
    heightOfImage = data.shape[0]
    PixelsThatWillBeBlackAfterRotation = []

    for i in range(0, data.shape[0]):
        for j in range(0, data.shape[1]):
            xnew = (j - rotationAboutXCoordinate) * cosTheta - (i - rotationAboutYCoordinate) * sinTheta + rotationAboutXCoordinate
            ynew = (j - rotationAboutXCoordinate) * sinTheta + (i - rotationAboutYCoordinate) * cosTheta + rotationAboutYCoordinate

            columnAccordingToxnew = int(xnew // 1)
            rowAccordingToynew = int(ynew // 1)

            if columnAccordingToxnew < 0 or columnAccordingToxnew > widthOfImage or rowAccordingToynew < 0 or rowAccordingToynew > heightOfImage:
                PixelsThatWillBeBlackAfterRotation.append((i,j))
                continue

            if columnAccordingToxnew == widthOfImage:
                if rowAccordingToynew == heightOfImage:
                    dataBlack[i][j][0] = data[rowAccordingToynew-1][columnAccordingToxnew-1][0]
                    dataBlack[i][j][1] = data[rowAccordingToynew-1][columnAccordingToxnew-1][1]
                    dataBlack[i][j][2] = data[rowAccordingToynew-1][columnAccordingToxnew-1][2]
                    #same for data[i][j][3]
                else:
                    dataBlack[i][j][0] = data[rowAccordingToynew][columnAccordingToxnew-1][0]
                    dataBlack[i][j][1] = data[rowAccordingToynew][columnAccordingToxnew-1][1]
                    dataBlack[i][j][2] = data[rowAccordingToynew][columnAccordingToxnew-1][2]
                    #same for data[i][j][3]
            elif columnAccordingToxnew != widthOfImage:
                if rowAccordingToynew == heightOfImage:
                    dataBlack[i][j][0] = data[rowAccordingToynew-1][columnAccordingToxnew][0]
                    dataBlack[i][j][1] = data[rowAccordingToynew-1][columnAccordingToxnew][1]
                    dataBlack[i][j][2] = data[rowAccordingToynew-1][columnAccordingToxnew][2]
                    #same for data[i][j][3]
                else:
                    dataBlack[i][j][0] = data[rowAccordingToynew][columnAccordingToxnew][0]
                    dataBlack[i][j][1] = data[rowAccordingToynew][columnAccordingToxnew][1]
                    dataBlack[i][j][2] = data[rowAccordingToynew][columnAccordingToxnew][2]
                    #same for data[i][j][3]

    for k in range(0, len(PixelsThatWillBeBlackAfterRotation)):
        dataBlack[PixelsThatWillBeBlackAfterRotation[k][0]][PixelsThatWillBeBlackAfterRotation[k][1]][0] = 0
        dataBlack[PixelsThatWillBeBlackAfterRotation[k][0]][PixelsThatWillBeBlackAfterRotation[k][1]][1] = 0
        dataBlack[PixelsThatWillBeBlackAfterRotation[k][0]][PixelsThatWillBeBlackAfterRotation[k][1]][2] = 0
        #data[PixelsThatWillBeBlackAfterRotation[k][0]][PixelsThatWillBeBlackAfterRotation[k][1]][3] = 0
    return 1, dataBlack

#(rotationAboutXCoordinate, rotationAboutYCoordinate)

#             |
# (-ve, -ve)  |  (+ve, -ve)
#             |
#             |
# --------------------------
#             |
# (-ve, +ve)  |  (+ve, +ve)
#             |
#             |

#positive(+ve) angle rotation of image from left to right rotation
#negative(-ve) angle rotation of image from right to left rotation

originalImagePath = input('Enter the file path for old(original) image: ')
print(f'\nEnter theta in degrees')
thetaInDegrees = float(input('Angle of rotation: '))
aboutCenter = input(f'\nDo you want to rotate the image about center point of image(y/n):')
if aboutCenter == 'y':
    imageOriginal = Image.open(originalImagePath)
    rotationAboutXCoordinate = imageOriginal.size[0]/2
    rotationAboutYCoordinate = imageOriginal.size[1]/2
else:
    rotationAboutXCoordinate = float(input('\nEnter the x coordinate of the point about which you want to rotate: '))
    rotationAboutYCoordinate = float(input('Enter the y coordinate of the point about which you want to rotate: '))
error, dataNew = rotation(originalImagePath, thetaInDegrees, rotationAboutXCoordinate, rotationAboutYCoordinate)
rotatedImagePath = input(f'\nWhere you want to save new image(file path): ')
rotatedImage = Image.fromarray(dataNew)
rotatedImage.save(rotatedImagePath)
print(f'\nImage saved successfully !!!')

"""# Resize"""

def lcm(a, b):
    i = 1
    n = b
    m = a
    if a > b:
        n = a
        m = b
    while(True):
        j = n * i
        if j % m == 0:
            return j
        i += 1

def increaseSizes(imageOld, heightOfImageNew, widthOfImageNew):
    dataOld = np.array(imageOld)
    heightOfImageOld = dataOld.shape[0]
    widthOfImageOld = dataOld.shape[1]
    columnRatio = int(widthOfImageNew / widthOfImageOld)
    rowRatio = int(heightOfImageNew / heightOfImageOld)
    dataNew = np.zeros(shape=(heightOfImageNew, widthOfImageNew, 3), dtype=np.uint8)
    #If alpha there then do 4
    #1 column in imageOld equal to columnRatio number of consecutive columns in imageNew
    #1 row in imageOld equal to rowRatio number of consecutive rows in imageNew
    for i in range(0, dataOld.shape[0]):
        for j in range(0, dataOld.shape[1]):
            rowCounter = i * rowRatio
            for l in range(0, rowRatio):
                columnCounter = j * columnRatio
                for k in range(0, columnRatio):
                    dataNew[rowCounter][columnCounter][0] = dataOld[i][j][0]
                    dataNew[rowCounter][columnCounter][1] = dataOld[i][j][1]
                    dataNew[rowCounter][columnCounter][2] = dataOld[i][j][2]
                    #Same for 3
                    columnCounter += 1
                rowCounter += 1       
    return dataNew

def decreaseSizes(imageOld, heightOfImageNew, widthOfImageNew):
    dataOld = np.array(imageOld)
    heightOfImageOld = dataOld.shape[0]
    widthOfImageOld = dataOld.shape[1]
    columnRatio = int(widthOfImageOld / widthOfImageNew) #Actually it will be reversed but for iterative purpose it is written like this
    rowRatio = int(heightOfImageOld / heightOfImageNew)
    dataNew = np.zeros(shape=(heightOfImageNew, widthOfImageNew, 3), dtype=np.uint8)
    for i in range(0, heightOfImageNew):
        for j in range(0, widthOfImageNew):
            rowCounter = i*rowRatio
            sumR = 0
            sumG = 0
            sumB = 0
            for k in range(0, rowRatio):
                columnCounter = j*columnRatio
                for l in range(0, columnRatio):
                    sumR += dataOld[rowCounter][columnCounter][0]
                    sumG += dataOld[rowCounter][columnCounter][1]
                    sumB += dataOld[rowCounter][columnCounter][2]
                    columnCounter += 1
                rowCounter += 1
            dataNew[i][j][0] = int(sumR / (rowRatio * columnRatio))
            dataNew[i][j][1] = int(sumG / (rowRatio * columnRatio))
            dataNew[i][j][2] = int(sumB / (rowRatio * columnRatio))
            #Same for 3
    return dataNew

def altersize(imageOldFilePath, heightOfImageNew, widthOfImageNew):
    if heightOfImageNew <= 0 or widthOfImageNew <= 0:
        dataNew = []
        return 0, dataNew
    else:
        imageOld = Image.open(imageOldFilePath)
        if heightOfImageNew % imageOld.size[1] == 0 and widthOfImageNew % imageOld.size[0] == 0:
            dataNew = increaseSizes(imageOld, heightOfImageNew, widthOfImageNew)
        if heightOfImageNew % imageOld.size[1] != 0 or widthOfImageNew % imageOld.size[0] != 0:
            heightLcm = lcm(heightOfImageNew, imageOld.size[1])
            widthLcm = lcm(widthOfImageNew, imageOld.size[0])
            dataNew = increaseSizes(imageOld, heightLcm, widthLcm)
            imageIntermmediate = Image.fromarray(dataNew)
            dataNew = decreaseSizes(imageIntermmediate, heightOfImageNew, widthOfImageNew)
        return 1,dataNew

imageOldFilePath = input('Enter the file path for old(original) image: ')
print(f'\nEnter a positive integer values for height and width')
print(f'If you enter a positive decimal value then it will be rounded off\n')
heightOfImageNew = int(input('Height of new image: '))
widthOfImageNew = int(input('Width of new image: '))
error, dataNew = altersize(imageOldFilePath, heightOfImageNew, widthOfImageNew)
if error == 0:
    print(f'\n\nError: You entered a non-positive integer value')
else:
    imageNewFilePath = input('Where you want to save the new(modified) image: ')
    imageSizeModified = Image.fromarray(dataNew)
    imageSizeModified.save(imageNewFilePath)
    print(f'\n\nDimensions of the new image: {widthOfImageNew} X {heightOfImageNew}')
    print('New Image saved successfully !!!')