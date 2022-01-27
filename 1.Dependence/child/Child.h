#include <memory>
#include "iostream"
// #include "ChildImpl.h"
using namespace std;

class Child {  // interface class
   public:
    virtual const std::string getname() = 0;
    virtual ~Child(){};

    static std::shared_ptr<Child> create(string name);

   private:
    // static std::shared_ptr<ChildImpl> pp;  //管理内存
};

class ChildImpl : public Child  // derived class
{
   public:
    virtual const string getname() { return name; };

    ChildImpl(string nameTmp) : name(nameTmp) { cout << "start" << endl; };
    ~ChildImpl() { cout << "finish" << endl; }

   private:
    string name = "Child default";
};
