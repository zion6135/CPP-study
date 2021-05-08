/******************* 抽象工厂模式 **************************/

#include "iostream"
using namespace std;

//抽象水果
class AbstractFruit{
public:
    virtual void showname() = 0;
};

//苹果
class Apple : public AbstractFruit{
public:
    virtual void showname(){
        cout << "i am apple" << endl;
    }
};

//鸭梨
class pear : public AbstractFruit{
public:
    virtual void showname(){
        cout << "i am pear" << endl;
    }
};

//抽象工厂
class AbstractFruitFactory{
public:
    virtual AbstractFruit* createFruit() = 0; 
};

//苹果工厂
class AppleFactory : public AbstractFruitFactory{
public:
    virtual AbstractFruit* createFruit() {
        return new Apple();
    }
};

//鸭梨工厂
class PearFactory : public AbstractFruitFactory{
public:
    virtual AbstractFruit* createFruit() {
        return new pear();
    }
};

int main() {

    AbstractFruitFactory* factory = nullptr;
    AbstractFruit* fruit = nullptr;

    factory = new AppleFactory();
    fruit = factory->createFruit(); //子类继承父类的虚函数，子类具体实现虚函数
    fruit->showname();
    delete fruit;
    delete factory;

    factory = new PearFactory();
    fruit = factory->createFruit(); //子类继承父类的虚函数，子类具体实现虚函数
    fruit->showname();
    delete fruit;
    delete factory;

    return 0;
}