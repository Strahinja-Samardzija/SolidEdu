#include "pch.h"
#include "framework.h"
#include "StringLib.h"

namespace stringlib
{
	std::vector<std::string> split(std::string str, char delim)
	{
		std::istringstream lineStream(str);

		std::vector<std::string> vec;

		for (std::string aFriend; std::getline(lineStream, aFriend, delim);)
		{
			vec.push_back(trim(aFriend));
		}
		return vec;
	}

	bool fileExists(const std::string& fileDest)
	{
		std::ifstream file(fileDest);
		if (file)
		{
			file.close();
			return true;
		}
		return false;
	}

	void createFile(const std::string& fileDest)
	{
		std::ofstream newFile(fileDest);
		if (!newFile.is_open())
		{
			throw bad_filename();
		}
		newFile.close();
	}

	void deleteFile(const std::string& fileDest) throw(bad_filename)
	{
		if (!remove(fileDest.c_str()));
		else
			throw bad_filename{};
	}

	void writeAllLines(const std::string& fileDest, const std::vector<std::string>& lines)
	{
		std::ofstream file(fileDest);
		if (file.is_open())
		{
			for (auto& line : lines)
			{
				file << line << '\n';
			}
			file.close();
		}
	}

	void appendAllLines(const std::string& fileDest, const std::vector<std::string>& lines) throw(bad_filename)
	{
		std::fstream file(fileDest, std::ios::app | std::ios::in);
		if (file.is_open())
		{
			file.seekg(-1, std::ios_base::end);
			std::string line;
			std::getline(file, line);
			file.clear();

			bool needNewLine = false;
			if (trim(line) != "")
				needNewLine = true;

			file.seekp(0, std::ios_base::end);
			file.clear();
			if (needNewLine)
			{
				file << "\n";
			}
			if (!file) {
				std::cerr << "err";
			}
			for (auto& line : lines)
			{
				file << line << "\n";
			}
			file.close();
		}
		else
		{
			throw bad_filename{};
		}
	}

	std::vector<std::string> readAllLines(const std::string& fileDest) throw(bad_filename)
	{
		std::vector<std::string> lines;
		std::ifstream file(fileDest);
		if (file.is_open())
		{
			for (std::string line; std::getline(file, line);)
			{
				lines.push_back(trim(line));
			}
			file.close();
			return lines;
		}
		else
		{
			throw bad_filename{};
		}
	}

	std::vector<std::string> readAllLines(const std::string& fileDest, char delim) throw(bad_filename)
	{
		std::vector<std::string> lines;
		std::ifstream file(fileDest);
		if (file.is_open())
		{
			for (std::string line; std::getline(file, line, delim);)
			{
				lines.push_back(trim(line));
			}
			file.close();
			return lines;
		}
		else
		{
			throw bad_filename{};
		}
	}
}