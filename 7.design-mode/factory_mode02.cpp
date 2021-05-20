// 工厂方法模式

#include <iostream>
using namespace std;
enum PRODUCTTYPE {SFJ,XSL,NAS};
class soapBase
{
	public:
	virtual ~soapBase(){};
	virtual void show() = 0;
};
 
class SFJSoap:public soapBase
{
	public:
	void show() {cout<<"SFJ Soap!"<<endl;}
};
 
class XSLSoap:public soapBase
{
	public:
	void show() {cout<<"XSL Soap!"<<endl;}
};
 
class NASSoap:public soapBase
{
	public:
	void show() {cout<<"NAS Soap!"<<endl;}
};
 
class Factory
{
	public:
    // 父类指针可以指向子类。因为子类包含了父类，new出来的子类，是一个指向子类的指针，然后这个指针转换为父类。相当于把可以用的范围限定到父类。
    // 父类的show()函数是虚函数，它的子类回去重新实现父类方法，所以会去调用子类的实现。
	soapBase * creatSoap(PRODUCTTYPE type)
	{
		switch(type)
		{
			case SFJ: 
				return new SFJSoap();
				break;
			case XSL:
				return new XSLSoap();
				break;
			case NAS:
				return new NASSoap();
				break;
			default:break;
		}
		
	}
};
 
int main()
{
    Factory factory;
    soapBase* sfjsoap = factory.creatSoap(SFJ);
    sfjsoap->show();

    delete sfjsoap;

	return 0;
}