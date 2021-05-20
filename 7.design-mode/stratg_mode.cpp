#include <iostream>
using namespace std;
#define  free_ptr(p) \
	if(p) delete p; p = NULL;
 
class IWind{
public:
	virtual ~IWind(){};
	virtual void blowWind() = 0;
};
 
class ColdWind : public IWind{
public:
	void blowWind(){
		cout<<"Blowing cold wind!"<<endl;
	};
};
 
class WarmWind : public IWind{
public:
	void blowWind(){
		cout<<"Blowing warm wind!"<<endl;
	}
};
 
class NoWind : public IWind{
public:
	void blowWind(){
		cout<<"No Wind!"<<endl;
	}
};


class WindMode{
public:
	WindMode(IWind* wind): m_wind(wind){}; //给m_wind赋值为wind
	~WindMode(){free_ptr(m_wind);}
	void blowWind(){
		m_wind->blowWind();// 指向基类的指针，因为为虚函数，会调用派生类的同名方法
	};
private:
	IWind* m_wind;
};

int main() {
    
    IWind* No_wind = new NoWind();
    No_wind->blowWind();
    free_ptr(No_wind);

    WindMode* wind1 = new WindMode(new NoWind());
    wind1->blowWind();
    free_ptr(wind1);

}