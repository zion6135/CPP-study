/******************* 简单工厂模式**************************/
// 写的时候是根据不同的初始化条件：判断不同的初始化方法---
// 面向的对象是 抽象水果&水果工厂---与具体的苹果类解耦
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

//水果工厂
class FruitFactory {
public:
    static AbstractFruit* createFruit(string flag) {
        if (flag == "apple") {
            return new Apple;
        }
    }
};

int main() {

    FruitFactory* factory = new FruitFactory();
    AbstractFruit* fruit = factory->createFruit("apple");
    fruit->showname();
    delete fruit;
    return 0;
}