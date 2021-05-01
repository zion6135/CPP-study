// 单例模式:系统中只有一个对象
// 通过将构造函数写在private中，使得无法在类以外的地方new新的对象，从而保证整个系统只有一个对象。
// 将构造函数放在getInstance()函数当中，从而使得系统唯一的类指针被分配和调用。
// 所以这个唯一的指针需要为static的，从而可以全局存在。

#include "iostream"
using namespace std;

class Base{
    private:
        Base() {
            // mBase = new Base();
                cout << " Base();" << endl;
        }; 
        static Base *mBase;
    public:
        static Base* getInstance()
        {
            if (mBase == nullptr) {
                mBase = new Base();
                cout << "new Base();" << endl;
            }
                cout << "mBase addr" << endl;
                cout << Base::mBase << endl;

            return mBase;
        }
};

Base* Base::mBase = nullptr;

int main() {
    cout << "start()" << endl;
    Base* aTemp = Base::getInstance();
    cout << aTemp << endl;
    cout << "over()" << endl;
    return 0;
}