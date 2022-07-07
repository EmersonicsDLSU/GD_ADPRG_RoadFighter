#ifndef JSONPARSER
#define JSONPARSER
#include <stddef.h>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
using namespace rapidjson;

class JSONParser
{
public:
	void parseJson(std::string JSONpath);
	rapidjson::Value& getSheet(std::string mainKey);
	rapidjson::GenericArray<false, rapidjson::Value> getSheetArr(std::string mainKey, std::string key);
	std::vector<std::string> returnProperties();
private:
	static JSONParser* sharedInstance;
	rapidjson::Document doc;

};

#endif // !JSONPARSER
