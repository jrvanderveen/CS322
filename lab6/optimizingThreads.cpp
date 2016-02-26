// Filip Jagodzinski
// CSCI322
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <thread>
#include <future>

using namespace std;

// get the wall time
double get_wallTime() {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  return (double) (tp.tv_sec + tp.tv_usec/1000000.0);
}

// A vanilla random number generator
double genRandNum(double min, double max){
  return min + (rand() / (RAND_MAX / (max - min)));
}

// A ridiculous calculation
double ridiculousCalc(double* array1, double* array2,
		      double* array3, int dimension, int start){

  double* resultArray1 = new double[dimension];
  double* resultArray2 = new double[dimension];
  double* resultArray3 = new double[dimension];
  double* resultArray4 = new double[dimension];
  double* resultArray5 = new double[dimension];
  double* outputArray = new double[dimension];
  double factor = 0.000000001;

  for (int i=start; i<dimension; i++){
    resultArray1[i] = array1[i] / array2[i] * array3[i] * -1.456;
    resultArray2[i] = resultArray1[i] / array3[i] * array3[i];
    resultArray3[i] = array3[i] * array2[i] + array1[i] 
      * array2[i]/(array2[i] * -0002.7897);
    resultArray4[i] = resultArray3[i] * array2[i] / array1[i];
    resultArray5[i] = resultArray4[i] * array2[i] / array1[i] 
      * resultArray4[i] * 0.0000000023;
    outputArray[i] = resultArray1[i]*factor + resultArray2[i]*factor 
      + resultArray3[i]*factor + resultArray4[i]*factor 
      + resultArray5[i]*factor;
  }

  double output = 0.0;
  for (int i=0; i<dimension; i++){
    output += outputArray[i];
  }  

  return output;

}
//optimaized code
double ridiculousCalcOptimized(double* array1, double* array2,
		      double* array3, int dimension, int start){

  double resultArray1 = 0.0;
  double resultArray2 = 0.0;
  double resultArray3 = 0.0;
  double resultArray4 = 0.0;
  double resultArray5 = 0.0;
  
  double array1i = 0.0;
  double array2i = 0.0;
  double array3i = 0.0;
  double array1ib = 0.0;
  double array2ib = 0.0;
  double array3ib = 0.0;
  
  int iplus1 = 0;
  double* outputArray = new double[dimension];
  double factor = 0.000000001;

  for (int i=start; i<dimension; i=i+2){
    //set loop unraveling variables
    iplus1 = i+1;
    array1i = array1[i];  
    array2i = array2[i];
    array3i = array3[i];
    array1ib = array1[iplus1];  
    array2ib = array2[iplus1];
    array3ib = array3[iplus1];
    //preform calculations
    resultArray1 = array1i / array2i * array3i * -1.456;
    resultArray2 = resultArray1 / array3i * array3i;
    resultArray3 = array3i * array2i + array1i * array2i/(array2i * -0002.7897);
    resultArray4 = resultArray3 * array2i / array1i;
    resultArray5 = resultArray4 * array2i / array1i * resultArray4 * 0.0000000023;
    outputArray[i] = resultArray1*factor + resultArray2*factor + resultArray3*factor + resultArray4*factor + resultArray5*factor;
    
    resultArray1 = array1ib / array2ib * array3ib * -1.456;
    resultArray2 = resultArray1 / array3ib * array3ib;
    resultArray3 = array3ib * array2ib + array1ib * array2ib/(array2ib * -0002.7897);
    resultArray4 = resultArray3 * array2ib / array1ib;
    resultArray5 = resultArray4 * array2ib / array1ib * resultArray4 * 0.0000000023;
    outputArray[iplus1] = resultArray1*factor + resultArray2*factor + resultArray3*factor + resultArray4*factor + resultArray5*factor;
  }

  double output = 0.0;
  for (int i=0; i<dimension; i++){
    output += outputArray[i];
  }  

  return output;

}
// main routine
int main(){

  // dimension of the array
  int dim = 10000000;
  
  // seed the random number generator
  srand( time(NULL));

  // create the arrays and populate them 
  // time the entire event
  double createStart = get_wallTime();
  static double *array1 = new double[dim];
  static double *array2 = new double[dim];
  static double *array3 = new double[dim];
  for (int i=0; i<dim; i++){
    array1[i] = genRandNum(0, 1000000);
    array2[i] = genRandNum(0, 1000000);
    array3[i] = genRandNum(0, 1000000);
  }
  double createEnd = get_wallTime();
  cout << "\n Time needed to create arrays                  : "
       << createEnd - createStart << endl;
  cout << " ========================================================"
       << endl;
   ///////////////////////////////////////////////////////////////////////////
  // perform non-optimized calculations
  double ridiculousStart = get_wallTime();
  double output = ridiculousCalc(array1, array2, array3, dim, 0);
  double ridiculousEnd = get_wallTime();
  cout << " Time needed to complete ridiculous calculation: "
       << ridiculousEnd - ridiculousStart << endl;
  cout << " Ridiculous calculation output                 : "
       << output << endl;
  cout << " ========================================================\n"
       << endl;
   ///////////////////////////////////////////////////////////////////////////
   // perform optimized calculations      
  ridiculousStart = get_wallTime();
  output = ridiculousCalcOptimized(array1, array2, array3, dim, 0);
  ridiculousEnd = get_wallTime();
  cout << " Time needed to complete ridiculous calculation: "
       << ridiculousEnd - ridiculousStart << endl;
  cout << " Ridiculous calculation output                 : "
       << output << endl;
  cout << " ========================================================\n"
       << endl;
   ///////////////////////////////////////////////////////////////////////////
   // perform non-optimized calculations with multiple threads
    int start = 0;
    int end = 0;
    int numThreads = std::thread::hardware_concurrency();
    cout << " Number of threads available: " << numThreads << endl;
    cout << " ========================================================\n"
       << endl;
    std::vector<std::future<double>> threads;
    
    ridiculousStart = get_wallTime();
    for(int i = 0; i<numThreads; i++){
        start = (dim/numThreads) * i;
        end = start + (dim/numThreads);
        threads.push_back( std::async(launch::async,
                                        ridiculousCalc,
                                        array1, array2,
                                        array3, end, start));
    }
    output = 0.0;
    for (int i=0; i < threads.size(); i++) {
        output += threads[i].get();
    }
    ridiculousEnd = get_wallTime();
    cout << " Time needed to complete ridiculous calculation: "
       << ridiculousEnd - ridiculousStart << endl;
    cout << " Ridiculous calculation output                 : "
       << output << endl;
    cout << " ========================================================\n"
       << endl;
   ///////////////////////////////////////////////////////////////////////////
   // perform optimized calculations with multiple threads
    std::vector<std::future<double>> threadsOp;
    
    ridiculousStart = get_wallTime();
    for(int i = 0; i<numThreads; i++){
        start = (dim/numThreads) * i;
        end = start + (dim/numThreads);
        threadsOp.push_back( std::async(launch::async,
                                        ridiculousCalcOptimized,
                                        array1, array2,
                                        array3, end, start));
    }
    output = 0.0;
    for (int i=0; i < threadsOp.size(); i++) {
        output += threadsOp[i].get();
    }
    ridiculousEnd = get_wallTime();
    cout << " Time needed to complete ridiculous calculation: "
       << ridiculousEnd - ridiculousStart << endl;
    cout << " Ridiculous calculation output                 : "
       << output << endl;
    cout << " ========================================================\n"
       << endl;
    
}