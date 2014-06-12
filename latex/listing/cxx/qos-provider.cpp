QoSProvier qp("file:///somewhere/on/my/fs/qos.xml", "myapp");

DomainParticipant dp(default_domain_id());
Topic<TempSensorType> topic(dp, "TempSensor", qp.topic_qos());
Publisher pub(dp, qp.publisher_qos());
DataWriter<TempSensorType> dw(pub, qp.datawriter_qos());


