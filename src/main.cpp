#include "predict.h"	// remember to include predict.h if you want to use the functions in predict.cpp

int main(){
    
    std::vector<double> features;
    features.push_back(1.483887);
    features.push_back(1.865988);
    features.push_back(2.234620);
    features.push_back(1.018782);
    features.push_back(-2.530891);
    features.push_back(-1.604642);
    features.push_back(0.774676);
    features.push_back(-0.465148);
    features.push_back(-0.495225);
    
	//double result = predict(1.483887, 1.865988, 2.234620, 1.018782, -2.530891, -1.604642, 0.774676, -0.465148, -0.495225);
    double result = predict(features);
	std::cout << "result is " << result << std::endl;
    //cleanup();
    
    double answer = predict(features);
    std::cout << "answer is " << answer << std::endl;
    cleanup();
    
	return 0;
}
