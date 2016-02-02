#include <iostream>
#include <thread>

using namespace std;

void task (int x){
    for(int i = 0; i < 100000000; i = i + 1){
        double a = (i/3) * 3.1415;
        a = (a/5.5) * 1.8;   
    }
    cout << "task " << x << " complete" << endl;
}

int main (){
    thread t1 (task, 0);
    thread t2 (task, 1);
    thread t3 (task, 2);
    thread t4 (task, 3);
    thread t5 (task, 4);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    cout << "done!" << endl;
}

