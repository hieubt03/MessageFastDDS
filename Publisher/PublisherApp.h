#pragma once

#include <QMainWindow>
#include "ui_PublisherApp.h"
#include <PublishMessage.h>

class PublisherApp : public QMainWindow
{
	Q_OBJECT

public:
	PublisherApp(QWidget *parent = nullptr);
	~PublisherApp();
	
private:
	Ui::PublisherAppClass ui;
	PublishMessage messagePublisher;
private slots: 
	void onPublishButtonClicked();
};
 
