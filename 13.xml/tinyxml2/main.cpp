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

void creat_xml0() {
    tinyxml2::XMLDocument doc;
    
    //1.添加声明
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
    doc.InsertFirstChild(declaration);
    
    //2.创建根节点
    tinyxml2::XMLElement* root = doc.NewElement("school");
    doc.InsertEndChild(root);
    
    //3.创建子节点
    tinyxml2::XMLElement* childNodeStu = doc.NewElement("havp_path_pos");
    root->InsertEndChild(childNodeStu);

    childNodeStu->SetAttribute("index", "2");
    tinyxml2::XMLText* contentStu = doc.NewText("xxx");
    childNodeStu->InsertFirstChild(contentStu);
    // root->InsertEndChild(childNodeStu);

    //6.保存xml文件
    doc.SaveFile("school.xml");
}

void creat_xml1() {
    tinyxml2::XMLDocument doc;
    
    //1.添加声明
    tinyxml2::XMLDeclaration* declaration = doc.NewDeclaration();
    doc.InsertFirstChild(declaration);
    
    //2.创建根节点
    tinyxml2::XMLElement* root = doc.NewElement("school");
    doc.InsertEndChild(root);
    
    //3.创建子节点
    tinyxml2::XMLElement* childNodeTea = doc.NewElement("teacher");
    tinyxml2::XMLElement* childNodeTeaGender = doc.NewElement("gender");

    tinyxml2::XMLText* contentGender = doc.NewText("man");
    childNodeTeaGender->InsertFirstChild(contentGender);
    
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
    // tinyxml2::XMLElement* childNodeStu = xmlRoot->FirstChildElement("havp_path_pos");
    // string contentStu = childNodeStu->GetText();
    // printf("havp_path_pos = %s\n", contentStu.c_str());
}

int main() {
    // read_config();
    // creat_xml0();
    creat_xml1();
    read_xml();
    return 0;

}