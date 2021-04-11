//g++ main.cpp -l pthread
#include <iostream>
#include <thread>

using namespace std;

void func(string& s) {
    cout << s << "  hello, this is my thread == " << this_thread::get_id() <<endl;
}

int main() {
    //thread th = thread(func);
    
    string s = "test";
    thread th = thread(func, std::ref(s));//传入参数s   
    th.join();
    cout << "this is main == " << this_thread::get_id()<<endl;

}