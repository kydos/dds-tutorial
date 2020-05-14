// -- Std C/C++ Include
#include <iostream>
#include <stdlib.h>
#include <time.h>
// -- Boost Include
#include <boost/program_options.hpp>
// -- SimD Include
#include <dds/dds.hpp>
// -- Custom Include
#include "TempControl_DCPS.hpp"
#include "util.hpp"

using namespace tutorial;

const unsigned short tsPrio = 10;

const unsigned short DEFAULT_ID = 0;

using namespace dds;
using namespace dds::core;
using namespace dds::core::policy;
using namespace dds::topic;
using namespace dds::pub;
using namespace dds::sub;

using namespace org::eclipse;

int
main(int argc, char* argv[])
{
  
  try {
    // Parse the command line args
    tspub_options opt = parse_tspub_args(argc, argv);

    // Create the domain participant
    dds::domain::DomainParticipant dp(cyclonedds::domain::default_id());
  
    // Initialize random number generation with a seed
    srandom(clock());    
  
    dds::topic::qos::TopicQos tqos = 
      dp.default_topic_qos() << LatencyBudget(Duration(2,0)) << Deadline(Duration(4,0));

    auto topic = Topic<tutorial::TempSensorType>(dp, "TempSensorTopic", tqos);
    auto pub = Publisher(dp);
    auto dw = DataWriter<tutorial::TempSensorType>(pub, topic, tqos);

    
    // Write some temperature randomly changing around a set point
    float temp = opt.t0 + ((random()*opt.dt)/RAND_MAX);
    float hum  = opt.h0 + ((random()*opt.dh)/RAND_MAX);
    TempSensorType sensor(opt.id, temp, hum, opt.scale);

    for (unsigned int i = 0; i < opt.samples; ++i) {
      dw << sensor;
      std::cout << "DW << " << sensor << std::endl;
      nanosleep(&opt.period, 0);
      sensor.temp(opt.t0 + ((random()*opt.dt)/RAND_MAX));
      sensor.hum(opt.h0 + ((random()*opt.dh)/RAND_MAX));
    }

  }
  catch (...) { }
  
  return 0;
}
