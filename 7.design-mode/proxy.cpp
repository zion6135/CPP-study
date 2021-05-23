// 代理模式

#include "iostream"

class factory {
    virtual void price() = 0;
};

class Delegate : public factory {
    public:
    void price() {
        std::cout << factory_price + 50 << std::endl;  // 代理报价
    };

    private:
        int factory_price = 100; //工厂原价

};

class Client {
    public:
    Client(){
        std::cout << "i want get price" << std::endl;   // 客户需求
    }
};

int main ()
{
    Client client;
    Delegate delegate; 

    delegate.price();  //代理商报价  完全隐藏了工厂作了什么

}