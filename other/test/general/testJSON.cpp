#include <iostream>
#include <fstream>
#include <cstring>
#include <lib/cjson/cJSON.h>

int main() {
	cJSON* object = cJSON_CreateObject();
	cJSON* text = cJSON_CreateString(u8"hello, this is \n 漢字, bye!");
	cJSON_AddItemToObject(object, "text", text);
	char* s = cJSON_PrintUnformatted(object);
	std::ofstream file("out.txt", std::ios::app);
	file.write(s, strlen(s));
	file.put('\r');
	file.put('\n');
	delete[] s;
	cJSON_Delete(object);
	return 0;
}