from pythonThreading import *

def function_1 ():
    global x
    global y
    
    y = x - 3;
    semaphore.signal()
    semaphore1.wait()
    y = x + y;
    semaphore2.signal()
    
def function_2():
    global x
    global y
    global z
    
    semaphore.wait()
    x = z;
    semaphore1.signal()
    semaphore2.wait()
    z = x + y;

semaphore = Semaphore(0)
semaphore1 = Semaphore(0)
semaphore2 = Semaphore(0)
x = 1
y = 4
z = 13

Thread(function_1)
Thread(function_2)

print "x =" ,x
print "y =" ,y
print "z =" ,z