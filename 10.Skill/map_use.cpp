// 用map数组实现字符串的转换----避免了一堆的if else
#include "string.h"
#include <map>
#include "iostream"

using namespace std;

std::map< std::string, std::string> mapvector ={
            {"front" , "qwe"},
    };

void func(string TTS, string& ID) {
    for(map<string, string> ::iterator it = mapvector.begin(); it != mapvector.end(); it++)
    {
        cout << "Key= " << (*it).first << " ,Value= " << (*it).second << endl;
        if (TTS == (*it).first) {
            ID = (*it).second;
            break;
        }
    }
}

int main()
{
    string data = "No";
    func ("1", data);
    printf( "===%s\n", data.c_str());

    // const string flag = "123";
	// int intStr = atoi(flag.c_str());

    // const string flag000 = "front_warning";
	// int intStr000 = atoi(flag000.c_str());

    return 0;
}