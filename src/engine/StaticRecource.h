#pragma once
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Resource
{

public:
	//Resource(const int ds,const std::vector<char> dt,const std::string ct) :data_size(ds),data(dt),content_type(ct) {}
	int data_size = 0;
	std::vector<char> data;
	std::string content_type;

	static std::vector<char> initializeResourceData(const fs::path & resoucePath);
};