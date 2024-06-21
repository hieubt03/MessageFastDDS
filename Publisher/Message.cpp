#include <Message.h>

Message::Message(const std::string& title, const std::string& content) : title(title), content(content) {}

std::string Message::getContent() const {
    return content;
}

std::string Message::getTitle() const {
    return title;
}
