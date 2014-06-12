// create a Domain Participant
DomainParticipant dp(default_id());
// create the Topic
Topic<TempSensorType> topic(dp, "TempSensorTopic");
// create a Subscriber
Subscriber sub(dp);
// create a DataReader
DataReader<TempSensorType> dr(sub. topic);
while (true) {
  LoanedSamples<TempSensorType> samples = dr.read();
  std::for_each(dr.begin(), 
		dr.end(), 
		[](const Sample<TempSensorType>& s) { 
		  std::cout << s.data() << std::endl;
		});
  std::this_thread::sleep_for(std::chrono::seconds(1));
 }
