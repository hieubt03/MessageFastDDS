#pragma once

#include <string>

class Message {
public:
	Message(const std::string& title, const std::string& content);
	std::string getContent() const;
	std::string getTitle() const;

private:
	std::string title;
	std::string content;
};
