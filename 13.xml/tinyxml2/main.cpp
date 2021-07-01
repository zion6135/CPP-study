// 编译：g++ tinyxml.cpp main.cpp

#include "tinyxml2.h"
#include <string>
using namespace std;
using namespace tinyxml2;

void read_config() {
    XMLDocument doc;
    doc.LoadFile("test.xml");  // 加载xml
    
    const char* content = doc.FirstChildElement("Hello")->GetText();
    printf("hello, %s\n", content);
}

void creat_xml() {
    tinyxml2::XMLDocument doc;
    
    //1.添加声明
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
    doc.InsertFirstChild(declaration);
    
    //2.创建根节点
    tinyxml2::XMLElement* root = doc.NewElement("school");
    doc.InsertEndChild(root);
    
    //3.创建子节点
    tinyxml2::XMLElement* childNodeStu = doc.NewElement("student");
    tinyxml2::XMLElement* childNodeTea = doc.NewElement("teacher");
    tinyxml2::XMLElement* childNodeTeaGender = doc.NewElement("gender");
    
    //4.为子节点增加内容
    tinyxml2::XMLText* contentStu = doc.NewText("stu");
    childNodeStu->InsertFirstChild(contentStu);
    
    tinyxml2::XMLText* contentGender = doc.NewText("man");
    childNodeTeaGender->InsertFirstChild(contentGender);
    
    //5.为子节点增加属性
    childNodeStu->SetAttribute("Name", "libai");
    
    root->InsertEndChild(childNodeStu);//childNodeStu是root的子节点
    root->InsertEndChild(childNodeTea);//childNodeTea是root的子节点
    childNodeTea->InsertEndChild(childNodeTeaGender);//childNodeTeaGender是childNodeTea的子节点
    
    //6.保存xml文件
    doc.SaveFile("school.xml");
}

void read_xml() {
    tinyxml2::XMLDocument doc;
    
    //1.加载xml文件
    if(doc.LoadFile("school.xml") != 0) {
        return;
    }
    
    //2.找到根节点
    tinyxml2::XMLElement* xmlRoot = doc.RootElement();
    if (xmlRoot == NULL) {
        return;
    }
    
    //3.获取子节点信息
    tinyxml2::XMLElement* childNodeStu = xmlRoot->FirstChildElement("student");
    string contentStu = childNodeStu->GetText();
    printf("student = %s\n", contentStu.c_str());
}

int main() {
    read_config();
    creat_xml();
    read_xml();
    return 0;

}