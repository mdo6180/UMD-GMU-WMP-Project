Clone repository off of GitHub
```
git clone https://github.com/mdo6180/UMD-GMU-WMP-Project
make cleanall
make all
```

To save model in python...

1. Use the following command to save the entire model as an HDF5 file
```
keras.model.save('model_name.h5')
```

2. Put the HDF into the deployment_file/python folder

Once you have saved and exported your model as a .h5 file...
 
1. Put your .h5 file into the python folder

2. Find the include and linker directories

To find numpy headers, type in the following commands in terminal:
```
Python
>> import numpy as np
>> np.get_include()
```

Resulting output should be a path to your numpy headers
```
'/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include'
```

To find Python.h and include directories:
```
python-config --include
```	

Resulting output:
```
-iwithsysroot /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -iwithsysroot /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
```

To find linker directories, type in the following commands in terminal:
```
python-config --ldflags
```

Resulting output:
```
-L/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config -lpython2.7 -ldl -framework CoreFoundation
```

3. Put it all together in the Makefile:
```
LIB_DIR = -L/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/config
LIB = -lpython2.7 
INCLUDE = -I/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7 -I/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include

all: <filename>.cpp
	g++ $(LIB_DIR) $(LIB) $(INCLUDE) <other flags> <filename>.cpp -o <executable name>
```
4. Go into the load_model.py file and edit the filename variable to the name of your .h5 file

5. Make sure that #include "predict.h" is located at the top of every .cpp file that needs to use the saved model to make predictions

6. Make sure that the second argument in the setenv() command in predict.cpp is set to the directory containing the load_model.py file 

7. Make sure that the second argument in the PyObject_GetAttrString() command in predict.cpp is set to the predict_result() function (or the name of the function that responsible for making the prediction) in the python file

8. Make sure that the argument in the PyImport_ImportModule() command in predict.cpp is set to the name of the python file that holds the predict_result() function (or the name of the function that responsible for making the prediction) 

9. In order for the python file to work, make sure that numpy, os, and tensorflow is installed

	
