// Create the TempSensor topic
Topic<TempSensorType> topic(dp,"TempSensor");

// Define the filter predicate
std::string predicate =
   "(temp NOT BETWEEN (%0 AND %1)) \
     OR \
    (hum NOT BETWEEN (%2 and %3))";

// Define the filter parameters 
std::vector<std::string> params = 
   {"20.5", "21.5", "30", "50"}; 

// Create the ContentFilteredTopic
ContentFilteredTopic<TempSensorType> 
cftopic("CFTempSensor",
	topic,
	predicate,
	params);

// This data reader will only receive data that
// maches the content filter
DataReader<TempSensorType> dr(sub, cftopic);

