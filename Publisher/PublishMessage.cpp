#include <PublishMessage.h>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/topic/qos/TopicQos.hpp>
#include <fastdds/dds/topic/TopicDataType.hpp>
#include <fastcdr/Cdr.h>
#include <fastcdr/FastBuffer.h>
#include <cassert>
#include <Message.h>
using namespace eprosima::fastdds::dds;

class MessageType : public eprosima::fastdds::dds::TopicDataType {
public:
    MessageType() {
        setName("MessageType");
    }

    bool serialize(void* data, eprosima::fastrtps::rtps::SerializedPayload_t* payload) override {
		Message* msg = static_cast<Message*>(data);
		eprosima::fastcdr::FastBuffer buffer(reinterpret_cast<char*>(payload->data), payload->max_size);
		eprosima::fastcdr::Cdr ser(buffer);
		ser << msg->getTitle() << msg->getContent();
		payload->length = static_cast<uint32_t>(ser.get_serialized_data_length());
		return true;
	}

    bool deserialize(eprosima::fastrtps::rtps::SerializedPayload_t* payload, void* data) override {
		Message* msg = static_cast<Message*>(data);
		eprosima::fastcdr::FastBuffer buffer(reinterpret_cast<char*>(payload->data), payload->max_size);
		eprosima::fastcdr::Cdr des(buffer);
		std::string title, content;
		des >> title >> content;
		*msg = Message(title, content);
		return true;
    }

    std::function<uint32_t()> getSerializedSizeProvider(void* data) override {
		return [data]() -> uint32_t {
			Message* msg = static_cast<Message*>(data);
			eprosima::fastcdr::FastBuffer buffer(nullptr, 0);
			eprosima::fastcdr::Cdr ser(buffer);
			size_t initial_position = ser.get_serialized_data_length();
			ser << msg->getTitle() << msg->getContent();
			return ser.get_serialized_data_length() - initial_position;
			};
    }

    bool getKey(void* data, eprosima::fastrtps::rtps::InstanceHandle_t* ihandle, bool force_md5) override {
        return false;
    }

    void* createData() override {
        return new Message("","");
    }

    void deleteData(void* data) override {
        delete static_cast<Message*>(data);
    }
};
PublishMessage::PublishMessage() {
	participant = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
	assert(participant != nullptr && "Failed to create DomainParticipant");

	TypeSupport type = TypeSupport(new MessageType());
	type.register_type(participant, "MessageType");

	publisher = participant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
	assert(publisher != nullptr && "Failed to create Publisher");
	
	topic = participant->create_topic("MessageTopic", "MessageType", TOPIC_QOS_DEFAULT);
	assert(topic != nullptr && "Failed to create Topic");

	writer = publisher->create_datawriter(topic, DATAWRITER_QOS_DEFAULT, nullptr);
	assert(writer != nullptr && "Failed to create DataWriter");
	
}

PublishMessage::~PublishMessage() {
	participant->delete_contained_entities();
	DomainParticipantFactory::get_instance()->delete_participant(participant);
}

void PublishMessage::publishMessage(const Message& message) {
	if (writer == nullptr) {
		return;
	}
	writer->write(const_cast<Message*>(&message));
}