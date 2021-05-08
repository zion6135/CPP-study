// 子类继承父类--父类写virtual或不写都调用子类的方法

#include "iostream"
using namespace std;

class Base{
    public:
        virtual void init(void){
            cout << "father0" << endl;
        };
        void init(int a){
            cout << "father1" << endl;
        };
};

class TCP : public Base{
    public:
        void init(void) {
            cout << "son0" << endl;
        };
        void init(int b) {
            cout << "son1" << endl;
        };
};


int main() {
    TCP* mTCP = new TCP();
    mTCP->init();
    mTCP->init(11);  // 只会调用子函数的方法
    return 0;
}