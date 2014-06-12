// -- Std C++ Include
#include <iostream>
// -- Boost Include
#include <boost/program_options.hpp>
// -- SimD includes
#include <dds/dds.hpp>
#include <gen/ccpp_TempControl.h>
// -- Custom Include
#include "util.hpp"

// Does some C++ magic required by SimD
REGISTER_TOPIC_TRAITS(TempSensorType);

const unsigned short tsPrio = 10;
int main(int argc, char* argv[]) {
  try {
    // Parse command line args
    tssub_options opt = parse_tssub_args(argc, argv);    
    // Init the SimD runtime
    dds::Runtime runtime("");    
    // Create the "TempSensor" Topic 
    dds::TopicQos tqos;
    dds::Duration latency_budget = {2, 0};
    dds::Duration deadline = {4, 0};
    tqos.set_latency_budget(latency_budget);
    tqos.set_deadline(deadline);
    tqos.set_priority(tsPrio);
    dds::Topic<TempSensorType> tsTopic("TempSensor", tqos);    
    // Create the DataReader
    dds::DataReaderQos drqos(tqos);
    dds::DataReader<TempSensorType> dr(tsTopic, drqos);
    // Declare the containers
    TempSensorTypeSeq data;
    DDS::SampleInfoSeq status;
    
    // Poll & Sleep untill you've not read opt.samples
    unsigned int count = 0;
    while (count < opt.samples) {
      // Read data from DDS
      dr.read(data, status);
      count += data.length();
      // Display all the read samples
      for (unsigned int i = 0; i < data.length(); ++i) {
	std::cout << data[i] << std::endl;
      }
      // Return the loaned memory to DDS.
      dr.return_loan(data, status); 
      // Sleep a bit before issuing another read
      nanosleep(&opt.period, 0);
    }
  }
  catch (...) {
    // Do nothing...
  }
  return 0;
}
