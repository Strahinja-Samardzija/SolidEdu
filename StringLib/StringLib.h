#pragma once
#include "framework.h"
#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

namespace stringlib
{
	// exception class
	class bad_filename {};

	inline std::string trim(std::string str)
	{
		str.erase(str.cbegin(), std::find_if(str.cbegin(), str.cend(), [](char ch) {
			return !std::isspace(ch);
			}));
		str.erase(std::find_if(str.crbegin(), str.crend(), [](char ch) {
			return !std::isspace(ch);
			}).base(), str.cend());
		return str;
	}

	inline bool endsWith(const std::string& haystack, const std::string& needle)
	{
		return !haystack.compare(haystack.size() - needle.size(), std::string::npos, needle);
	}

	inline bool startsWith(const std::string& haystack, const std::string& needle)
	{
		return !haystack.compare(0, needle.size(), needle);
	}

	std::vector<std::string> split(std::string str, char delim);

	bool fileExists(const std::string& fileDest);

	void createFile(const std::string& fileDest);

	void deleteFile(const std::string& fileDest) throw(bad_filename);

	void writeAllLines(const std::string& fileDest, const std::vector<std::string>& lines);

	void appendAllLines(const std::string& fileDest, const std::vector<std::string>& lines) throw(bad_filename);

	std::vector<std::string> readAllLines(const std::string& fileDest) throw(bad_filename);

	std::vector<std::string> readAllLines(const std::string& fileDest, char delim) throw(bad_filename);

	//template< class InputIt, class T >

	template<typename T>
		requires requires (const T& t) { t.cbegin(); }
	std::string prettyPrint(const T& container)
	{
		std::ostringstream output{};
		output << "{ ";
		int everyFifth = 5;
		for (auto& elem : container)
		{
			output << elem << ", ";
			if (--everyFifth == 0)
			{
				everyFifth = 5;
				output << '\n';
			}
		}
		if (container.size() % 5 == 0) 
		{
			output.seekp(-3, std::ios::end);
		}
		else
		{
			output.seekp(-2, std::ios::end);
		}
		output << " }";
		return output.str();
	}
}
