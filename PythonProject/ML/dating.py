from numpy import *
from os import listdir
import operator
import matplotlib
import matplotlib.pyplot as plt
from os import listdir

def classify0(inX, dataSet, labels, k):
    dataSetSize = dataSet.shape[0]
    diffMat = tile(inX, (dataSetSize,1)) - dataSet
    sqDiffMat = diffMat**2
    sqDistances = sqDiffMat.sum(axis=1)
    distances = sqDistances**0.5
    sortedDistIndicies = distances.argsort()
    classCount={}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel,0) + 1
    sortedClassCount = sorted(classCount.iteritems(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]

def file2matrix(filename):
    fr = open(filename)
    arrayOfLines = fr.readlines()
    numberOfLines = len(arrayOfLines)
    returnMat = zeros((numberOfLines, 3))
    classLabelVectr = []
    index = 0
    attitude2number = {'largeDoses':1, 'smallDoses':2, 'didntLike':3}
    for line in arrayOfLines:
        line = line.strip()
        listFromLine = line.split('\t')
        returnMat[index, :] = listFromLine[0:3]
        classLabelVectr.append(attitude2number[listFromLine[-1]])
        index += 1
    return returnMat, classLabelVectr
dataSet, labels = file2matrix('datingTestSet.txt')
def autoNorm(data):
    minVal = data.min(0)
    maxVal = data.max(0)
    ranges = maxVal - minVal
    normData = zeros(shape(data))
    m = data.shape[0]
    normData = data - tile(minVal, (m, 1))
    normData = normData / tile(ranges, (m, 1))
    return normData
dataSet = autoNorm(dataSet)
def solve(data = dataSet, label = labels):
    number2attitude = {1:'largeDoses', 2:'smallDosed', 3:'didntLike'}
    a = input()
    b = input()
    c = input()
    print number2attitude[classify0([a,b,c], data, label, 100)]

def print_graph(data = dataSet, label = labels):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(data[:,0], data[:,1],15.0*array(label), 15.0 * array(label))
    plt.show()

def testAlgorithm():
    hoRatio = 0.10
    datingDataMat, datingLabels = file2matrix('datingTestSet.txt')
    normMat = autoNorm(datingDataMat)
    m = normMat.shape[0]
    numTestVecs = int(m * hoRatio)
    errorCount = 0.0
    for i in range(numTestVecs):
        classifierResult = classify0(normMat[i, :], normMat[numTestVecs:m, :],\
                                     datingLabels[numTestVecs:m], 7)
        print "the clasifier came back with: {}, the real answer is {}".format(classifierResult, datingLabels[i])
        if(classifierResult != datingLabels[i]):
            errorCount += 1
    print "the total error rate is {}".format(errorCount/double(numTestVecs))


def img2vector(filename):
    returnVect = zeros((1, 1024))
    fr = open(filename)
    for i in range(32):
        linestr = fr.readline()
        for j in range(32):
            returnVect[0, 32*i+j] = int(linestr[j])
    return returnVect

def handwritingClassTest():
    hwLabels = []
    trainingFileList = listdir('trainingDigits')
    m = len(trainingFileList)
    trainingMat = zeros((m, 1024))
    for i in range(m):
        fileNameStr = trainingFileList[i]
        fileStr = fileNameStr.split('.')[0]
        classNumStr = int(fileStr.split('_')[0])
        hwLabels.append(classNumStr)
        trainingMat[i, :] = img2vector('trainingDigits/{}'.format(fileNameStr))
    testFileList = listdir('testDigits')
    errorCount = 0.0
    mTest = len(testFileList)
    for i in range(mTest):
        fileNameStr = testFileList[i]
        fileStr = fileNameStr.split('.')[0]
        classNameStr = int(fileStr.split('_')[0])
        vectorUnderTest = img2vector('testDigits/{}'.format(fileNameStr))
        classfierResult = classify0(vectorUnderTest, trainingMat, hwLabels, 1)
        #print 'the programm came back with value {} while the right answer is {}'.format(classfierResult, classNameStr)
        if(classfierResult != classNameStr): errorCount += 1.0
    print 'the total error rate is {}'.format(errorCount/float(mTest))
