#include "Python.h"
#include "predict.h"

PyObject* myModule = NULL;
PyObject* pValue = NULL;
PyObject* pFunc = NULL;
PyObject* pArgTuple = NULL;
PyObject* pArg = NULL;

// formats the input vector, calls the python function to make the prediction,
// and returns the result of the python function call as a double
double predict(std::vector<double>& args){
    
    setenv("PYTHONPATH", "../python", 1);               // Set PYTHONPATH to directory containing python file
    
    Py_Initialize();                                    // Py_Initialize() must be called before using any other Python/C API functions
    
    myModule = PyImport_ImportModule("load_model");     // import python file
    if(myModule == NULL){
        return -1;
    }
    
    pArgTuple = PyTuple_New(args.size());
    
    for(int i = 0; i < args.size(); ++i){

    	pValue = PyFloat_FromDouble(args[i]);				// convert double to python float
    	if(pValue == NULL){
    		return -1;
    	}

        if(PyTuple_SetItem(pArgTuple, i, pValue) != 0){		// add python float value into tuple
        	return -1;
        }
    }

    // embed pArgTuple inside another tuple
    // if we pass pArgTuple to PyObject_CallObject(), the program is going to think that we want to pass multiple arguments;
    // therefore, we have to embed pArgTuple inside another tuple so the program knows that we want to pass only 1 argument that is a tuple.
    pArg = PyTuple_New(1);
    if(PyTuple_SetItem(pArg, 0, pArgTuple) != 0){
        std::cout << "Cannot create final input array" << std::endl;
        return -1;
    }

    //Get the function by its name
    pFunc = PyObject_GetAttrString(myModule, "predict_result");
    if(pFunc == NULL){
        std::cout << "Cannot get reference to function" << std::endl;
    }

    //Call the python function
    pValue = PyObject_CallObject(pFunc, pArg);
    if(pValue == NULL){
    	std::cout << "Cannot call function" << std::endl;
        return -1;
    }

    return PyFloat_AsDouble(pValue);
}

// frees the PyObject* variables
// must be called after all predict(std::vector<double>& args) commands otherwise you will get memory leaks
void cleanup(){
    
    // the function will keep on decrementing the reference count for each variable (declared up top) until all varibles' reference count reaches 0
    // at which point, all resources will be freed up by CPython
    
    while (Py_REFCNT(myModule) > 0) {
        Py_XDECREF(myModule);
    }
    
    while (Py_REFCNT(pValue) > 0) {
        Py_XDECREF(pValue);
    }
    
    while (Py_REFCNT(pFunc) > 0) {
        Py_XDECREF(pFunc);
    }
    
    while (Py_REFCNT(pArg) > 0) {
        Py_XDECREF(pArg);
    }
    
    while (Py_REFCNT(pArgTuple) > 0) {
        Py_XDECREF(pArgTuple);
    }
}
