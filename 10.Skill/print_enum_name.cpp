#include <map>
#include "iostream"
typedef enum { 
    MONDAY, TUESDAY 
} signal;

void test(){
    std::map<signal,std::string> m_data;
    m_data[MONDAY] ="MONDAY";
    printf("%s\n",m_data[MONDAY].c_str());
}
int main()
{
    test();
    return 0;
}