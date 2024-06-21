#pragma once
#include <Message.h>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>

using namespace eprosima::fastdds::dds;

class PublishMessage {
public:
	PublishMessage();
	~PublishMessage();

	void publishMessage(const Message& message);

private:
	DomainParticipant* participant = nullptr;
	Publisher* publisher = nullptr;
	Topic* topic = nullptr;
	DataWriter* writer = nullptr;

};