#include <memory>
#include "iostream"
// #include "fatherImpl.h"
using namespace std;

class father {  // interface class
   public:
    virtual const std::string getname() = 0;
    virtual ~father(){};

    static std::shared_ptr<father> create(string name);

   private:
    // static std::shared_ptr<fatherImpl> pp;  //管理内存
};

class fatherImpl : public father  // derived class
{
   public:
    virtual const string getname() { return name; };

    fatherImpl(string nameTmp) : name(nameTmp) { cout << "start" << endl; };
    ~fatherImpl() { cout << "finish" << endl; }

   private:
    string name = "father default";
};
