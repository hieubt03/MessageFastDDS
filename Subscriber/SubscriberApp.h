#pragma once

#include <QMainWindow>
#include "ui_SubscriberApp.h"

class SubscriberApp : public QMainWindow
{
	Q_OBJECT

public:
	SubscriberApp(QWidget *parent = nullptr);
	~SubscriberApp();

private:
	Ui::SubscriberAppClass ui;
};
