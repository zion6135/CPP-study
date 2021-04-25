#include<iostream>
#include "cjson.h"


void printf_cjson(cJSON* root) {
    char* out=cJSON_Print(root);
    std::cout << out <<std::endl <<std::endl;
    free(out);
}
void send_data()
{
	//  创建cJSON结构体  
//     {
//     "com.living.park":{
//         "message":{
//             "method":"launchavm",
//             "params":""
//         },
//         "module":"AVM"
//     }
//   }
    cJSON* root0 = cJSON_CreateObject();//创建对象
    cJSON*item;
    item = cJSON_CreateString("xxx");
	cJSON_AddItemToObject(root0, "method", item);
    item = cJSON_CreateString("");
	cJSON_AddItemToObject(root0, "params",item );

    cJSON* root = cJSON_CreateObject();//创建对象
    cJSON_AddItemToObject(root,"message",root0);

    item=cJSON_CreateString("xxx");
    cJSON_AddItemToObject(root,"module",item);

    cJSON* root1 = cJSON_CreateObject();//创建对象
    cJSON_AddItemToObject(root1,"root",root);

    char* tmp = cJSON_PrintUnformatted(root1); //转字符串
    std::cout << tmp <<std::endl<<std::endl;

    printf_cjson(root1);
    cJSON_Delete(root1);

}


int main() {
    cJSON* root = cJSON_CreateObject();

send_data();
	// //  1.创建json数据
    // cJSON*item=cJSON_CreateString("Brett");
	// cJSON_AddItemToObject(root,"Name",item);
    // free(item);

    // //  2.cJSON结构体数据
    // char* out=cJSON_Print(root);
    // std::cout << out <<std::endl <<std::endl;
    // free(out);
    
	// //  3.转cJSON结构体为字符串
    // char* tmp = cJSON_PrintUnformatted(root);
    // std::cout << tmp <<std::endl<<std::endl;
    // free(tmp);

	// //  4.解析json字符串--> cJSON结构体  
    // char demo1[] = "{\"commmand\":{\"message\":{\"method\":\"run\",\"params\":\"\"},\"module\":\"lbw\"}}";
    // cJSON *test = cJSON_Parse(demo1); //将JSON字符串转换成cJSON结构体
    // char* demo2=cJSON_Print(test);
    // std::cout << demo2 <<std::endl<<std::endl;
	// free(demo2);

	// //  5.解析cJSON结构体得到里面的内容
    // cJSON* source_data  =cJSON_GetObjectItem(test,"commmand");
    // printf("cJSON_GetObjectItem: type= %d, key = %s, value = %s\n",source_data->type,source_data->string,source_data->valuestring);

    // cJSON* src  =cJSON_GetObjectItem(source_data,"message");
    // printf("cJSON_GetObjectItem: type= %d, key = %s, value = %s\n",src->type,src->string,src->valuestring);

    // cJSON* srcxx  =cJSON_GetObjectItem(src,"method");
    // std::cout <<  "cJSON_GetObjectItem: type = " << srcxx->type << ", key = "<< srcxx->string <<" ,value = " << srcxx->valuestring << std::endl;

	cJSON_Delete(root);
	return 0;
}
