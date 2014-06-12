#include <thread>
#include <chrono>
#include <TempSensorType_Dcps.h>

using namespace dds::domain;
using namespace dds::sub;

int main(int, char**) {
  DomainParticipant dp(default_ip());
  Topic<TempSensorType> topic(dp, "TempSensorTopic");
  Publisher pub(dp);
  DataWriter<TempSensorType> dw(pub, topic);

  TempSensorType ts;
  //[NOTE #1]: Instances implicitly registered as part 
  // of the write.
  //   {id,  temp   hum    scale};
  ts = {1,   25.0F, 65.0F, CELSIUS};
  dw.write(ts);

  ts = {2,   26.0F, 70.0F, CELSIUS};
  dw.write(ts);

  ts = {3,   27.0F, 75.0F, CELSIUS};
  dw.write(ts);

  std::this_thread::sleep_for(std::chrono::seconds(10));
  //[NOTE #2]: Instances automatically unregistered and 
  // disposed as result of the destruction of the dw object
  return 0;
}
