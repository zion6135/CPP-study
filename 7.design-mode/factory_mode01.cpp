// 简单工厂模式
// 通过factory去创建不同的具体类---本质上还是switch,case
// 缺点很明显--添加一个子类就需要修改soapBase,不符合开闭原则

#include "iostream"
using namespace std;

enum Product {SFJ,XSL};

class soapBase {
    public:
    virtual ~soapBase() {};
    virtual void show() = 0;
};

class SFJsoap:public soapBase {
    public:
    void show() {cout << "SFJ" << endl;}
};

class XSLsoap:public soapBase {
    public:
    void show() {cout << "XSL" << endl;}
};

class Factory {
    public:
    soapBase* createSoap(Product type) {
        switch (type)
        {
            case SFJ:
                return new SFJsoap();
                break;

            case XSL:
                return new XSLsoap();
                break;           
        }
    }
};

int main()
{
    Factory factory;
    soapBase* soap1 = factory.createSoap(SFJ);
    soap1->show();

    soapBase* soap2 = factory.createSoap(XSL);
    soap2->show();
}