#include "JSONParser.h"
#define _CRT_SECURE_NO_DEPRECATE
void JSONParser::parseJson(std::string JSONpath)
{
	//1
	JSONpath += ".json";
	FILE* file = fopen(JSONpath.c_str(), "rb");
	assert(file != 0);
	//2
	char readBuffer[65536];
	rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
	//3
	this->doc.ParseStream(is);
	fclose(file);
}

rapidjson::Value& JSONParser::getSheet(std::string mainKey)
{
	rapidjson::Value& player = this->doc[mainKey.c_str()];
	return player; //player["name"].GetString()/GetInt();
}

rapidjson::GenericArray<false, rapidjson::Value> JSONParser::getSheetArr(std::string mainKey, std::string key)
{
	rapidjson::GenericArray<false, rapidjson::Value> items = getSheet(mainKey)[key.c_str()].GetArray();
	return items; //items[i].GetFloat();
}


std::vector<std::string> JSONParser::returnProperties()
{
	std::vector<std::string> sample;
	for (Value::ConstMemberIterator itr = doc["frames"].MemberBegin();
		itr != doc["frames"].MemberEnd(); ++itr)
	{
		sample.push_back(itr->name.GetString());
	}
	return sample;
}