// -- Std C/C++ Include
#include <iostream>
#include <stdlib.h>
#include <time.h>
// -- Boost Include
#include <boost/program_options.hpp>
// -- SimD Include
#include <dds/dds.hpp>
// -- Custom Include
#include "gen/ccpp_TempControl.h"
#include "util.hpp"

REGISTER_TOPIC_TRAITS(TempSensorType);

const unsigned short tsPrio = 10;

const unsigned short DEFAULT_ID = 0;

int
main(int argc, char* argv[])
{
  try {
    // Parse the command line args
    tspub_options opt = parse_tspub_args(argc, argv);
    // Initialize random number generation with a seed
    srandom(clock());
    // Create a SimD runtime
    dds::Runtime runtime("");
    // Create the "TempSensor" Topic
    dds::TopicQos tqos;
    dds::Duration latency_budget = {2, 0};
    dds::Duration deadline = {4, 0};
    tqos.set_latency_budget(latency_budget);
    tqos.set_deadline(deadline);
    tqos.set_priority(tsPrio);
    dds::Topic<TempSensorType> tsTopic("TempSensor", tqos);
    // Create a DataWriter
    dds::DataWriterQos dwqos(tqos);
    dds::DataWriter<TempSensorType> dw(tsTopic, dwqos);
    
    // Write some temperature randomly changing around a set point
    float temp = opt.t0 + ((random()*opt.dt)/RAND_MAX);
    float hum  = opt.h0 + ((random()*opt.dh)/RAND_MAX);
    TempSensorType sensor = { opt.id, temp, hum, opt.scale };
    for (unsigned int i = 0; i < opt.samples; ++i) {
      dw.write(sensor);
      std::cout << "DW << " << sensor << std::endl;
      nanosleep(&opt.period, 0);
      sensor.temp = opt.t0 + ((random()*opt.dt)/RAND_MAX);
      sensor.hum =  opt.h0 + ((random()*opt.dh)/RAND_MAX);
    }
  }
  catch (...) { }
  return 0;
}
