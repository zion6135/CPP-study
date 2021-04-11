//g++ main.cpp -l pthread
#include <iostream>
#include <thread>

using namespace std;

struct A
{
    void operator()(int limit) {
        for (int i = 0; i < limit; i++){
            cout << "i is" << i << endl;
        }
    }

    // void operator()(int limit) {
    //     for (int i = 0; i < limit; i++){
    //         cout << "limit is" << limit << endl;
    //     }
    // }
};

void show(string& s) {
    cout << "s == " << s << endl; 
};

int main() {
   // string s = "test";
  //  thread thread1 = thread(A(), s);
     thread thread1 = thread(A(), 128);
        for (int i = 0; i < 130; i++){
            cout << "main is" << i << endl;
        }
        thread1.detach();
}