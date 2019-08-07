import numpy as np
from tensorflow import keras
import os

filename = 'mpg.h5'

def predict_result(input):
    # print(type(input))
    
    dir = os.path.dirname(os.path.realpath(__file__))   # get the python directory
    path = dir + '/' + filename                         # create filepath
    
    # print(path)
    
    input_arr = np.asarray(input).reshape((1,9))        # reshape the input tuple
    # print("input successfully reshaped")
    
    model = keras.models.load_model(filepath=path)      # load the HDF5 model (remember to add the full path to the file)
    # print("model loaded")
    
    prediction = model.predict(input_arr).flatten()     # make the prediction
    # print("prediction made")
    
    # .item(0) command will extract number from array and return as a float, set parameter to 0 to index the only element in the array
    return prediction.item(0)

'''
def predict(a, b):
    return a + b

def printList(CList):
    #print("not working")
    for i in CList:
        print(i)

def sumList(CList):
    print(type(CList))
    
    sum = 0
    for i in CList:
        sum += i
        print(i)
    
    return sum

def dotProduct(a, b):
    
    # convert to numpy ndarray
    a = np.asarray(a)
    b = np.asarray(b)
    
    print(type(a))
    print(type(b))
    print(a.shape)
    print(b.shape)
    
    return np.dot(a, b)
'''

#result = predict_result( (1.483887, 1.865988, 2.234620, 1.018782, -2.530891, -1.604642, 0.774676, -0.465148, -0.495225) )
#print(result)
#print(type(result))

