#include "PublisherApp.h">
#include <Message.h>
#include <iostream>
#include <PublishMessage.h>

PublisherApp::PublisherApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.publishButton, &QPushButton::clicked, this, &PublisherApp::onPublishButtonClicked);
}
void PublisherApp::onPublishButtonClicked() {
	std::string title = ui.messageTitle->toPlainText().toStdString();
	std::string content = ui.messageContent->toPlainText().toStdString();
	Message message(title, content);
	messagePublisher.publishMessage(message);
}

PublisherApp::~PublisherApp()
{}
