// create a Domain Participant
DomainParticipant dp(default_id());
// create the Topic
Topic<TempSensorType> topic(dp, "TempSensorTopic");
// create a Publisher
Publisher pub(dp);
// Create a DataWriter
DataWriter<TempSensorType> dw(dp, topic);

TempSensorType ts = {1, 26.0F, 70.0F, CELSIUS};
// Write Data
dw.write(ts);
// Write some more data using streaming operators
dw << TempSensorType(2, 26.5F, 74.0F, CELSIUS);

