#include <iostream>
#include <thread>
#include <ctime>
#include <sys/time.h>
#include <math.h>
#define DIM 800

using namespace std;

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double) (time.tv_sec + time.tv_usec / 1000000.0);
}
int **popArary(int x){
    int **array = new int*[DIM];
    for (int i = 0; i<DIM; i++){
        array[i] = new int[DIM];
        for (int j = 0; j<DIM; j++){
            array[i][j] = x;
        }
    }
    return array;
}

void sumArray(int **array1, int **array2){
    int sum = 0;
    for(int i = 0; i<DIM; i++){
        for (int j = 0; j<DIM; j++){
            for (int z = 0; z<DIM; z++){
                sum += array1[z][j] * array2[i][z];
            }
            sum = 0;
        }
    }
}

int main (){
    double startT = 0, endT = 0;
    int **array1 = popArary(1); 
    cout << endl;
    int **array2 = popArary(2);
    cout << endl << DIM << endl << endl;
    
    for(int i = 0; i<6; i++){
        startT = get_wall_time();
        for(int x = 0; x<pow(2,i); x++){
            sumArray(array1, array2);
        }
        endT = get_wall_time();
        cout << pow(2,i) << "times: " << (endT-startT) << endl;  
    }
}
