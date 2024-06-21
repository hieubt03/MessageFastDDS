#include <SubscribeMessage.h>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>
#include <cassert>

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
		return new Message("", "");
	}

	void deleteData(void* data) override {
		delete static_cast<Message*>(data);
	}
};

SubscribeMessage::SubscribeMessage() {
	participant = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
	assert(participant != nullptr && "Failed to create DomainParticipant");

	TypeSupport type = TypeSupport(new MessageType());
	type.register_type(participant, "MessageType");

	subscriber = participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
	assert(subscriber != nullptr && "Failed to create Subscriber");

	topic = participant->create_topic("MessageTopic", "MessageType", TOPIC_QOS_DEFAULT);
	assert(topic != nullptr && "Failed to create Topic");

	reader = subscriber->create_datareader(topic, DATAREADER_QOS_DEFAULT, &listener);
}

void SubscribeMessage::MessageListener::on_data_available(DataReader* reader) {
	SampleInfo info;
	Message message("","");
	if (reader->take_next_sample(&message, &info) == ReturnCode_t::RETCODE_OK) {
		if (info.instance_state == ALIVE) {
			std::cout << "Received message: " << message.getTitle() << message.getContent() << std::endl;
		}
	}

}
SubscribeMessage::~SubscribeMessage() {
	participant->delete_contained_entities();
	DomainParticipantFactory::get_instance()->delete_participant(participant);
}

void SubscribeMessage::subscribeMessage() {

}