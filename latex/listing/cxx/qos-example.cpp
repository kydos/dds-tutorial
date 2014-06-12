
DomainParticipant dp(default_domain_id());

auto tqos = dp.default_topic_qos() 
  << Reliability::Reliable()
  << Durability::TransientLocal();

Topic<TempSensorType> topic(dp, "TempSensor", tqos);

PublisherQos pqos = dp.default_publisher_qos() 
  << Partition("building-1:floor-2:room:3");

Publisher pub(dp, pqos);
 
DataWriterQos dwqos = tqos
     << TransportPriority(10);

DataWriter<TempSensorType> dw(pub, dwqos);


