#include<iostream>
#include "cjson.h"


int main() {
    cJSON* root = cJSON_CreateObject();
    
	//  1.创建json数据
    cJSON*item=cJSON_CreateString("Brett");
	cJSON_AddItemToObject(root,"Name",item);
    free(item);

    //  2.cJSON结构体数据
    char* out=cJSON_Print(root);
    std::cout << out <<std::endl <<std::endl;
    free(out);
    
	//  3.转cJSON结构体为字符串
    char* tmp = cJSON_PrintUnformatted(root);
    std::cout << tmp <<std::endl<<std::endl;
    free(tmp);

	//  4.解析json字符串--> cJSON结构体  
    char demo1[] = "{\"commmand\":{\"message\":{\"method\":\"run\",\"params\":\"\"},\"module\":\"lbw\"}}";
    cJSON *test = cJSON_Parse(demo1); //将JSON字符串转换成cJSON结构体
    char* demo2=cJSON_Print(test);
    std::cout << demo2 <<std::endl<<std::endl;
	free(demo2);

	//  5.解析cJSON结构体得到里面的内容
    cJSON* source_data  =cJSON_GetObjectItem(test,"commmand");
    printf("cJSON_GetObjectItem: type= %d, key = %s, value = %s\n",source_data->type,source_data->string,source_data->valuestring);

    cJSON* src  =cJSON_GetObjectItem(source_data,"message");
    printf("cJSON_GetObjectItem: type= %d, key = %s, value = %s\n",src->type,src->string,src->valuestring);

    cJSON* srcxx  =cJSON_GetObjectItem(src,"method");
    std::cout <<  "cJSON_GetObjectItem: type = " << srcxx->type << ", key = "<< srcxx->string <<" ,value = " << srcxx->valuestring << std::endl;

	cJSON_Delete(root);
	return 0;
}
