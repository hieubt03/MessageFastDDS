#pragma once

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include "Message.h"

using namespace eprosima::fastdds::dds;

class SubscribeMessage {
public:
	SubscribeMessage();
	~SubscribeMessage();

	void subscribeMessage();
private:
    DomainParticipant* participant;
    Subscriber* subscriber;
    Topic* topic;
    DataReader* reader;
    TypeSupport type;

    class MessageListener : public DataReaderListener {
    public:
        void on_data_available(DataReader* reader) override;
    };

    MessageListener listener;

};