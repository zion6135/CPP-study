#include <iostream>
#include <thread>

using namespace std;

void func() {
    cout << "hello, this is my thread == " << this_thread::get_id() <<endl;
}

int main() {
    thread th = thread(func);
    th.join();
    cout << "this is main == " << this_thread::get_id()<<endl;

}