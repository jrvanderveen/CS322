#include <iostream>

using namespace std;

void task (int x){
    for(int i = 0; i < 100000000; i = i + 1){
        double a = (i/3) * 3.1415;
        a = (a/5.5) * 1.8;   
    }
    cout << "task " << x << " complete" << endl;
}

int main (){
    task(0);
    task(1);
    task(2);
    task(3);
    task(4);
    cout << "done!" << endl;
}
