#include <TempSensorType_Dcps.h>

using namespace dds::core;
using namespace dds::domain;
using namespace dds::pub;

int main(int, char**) {
  DomainParticipant dp(default_ip());
  Topic<TempSensorType> topic("TempSensorTopic");
   
  //[NOTE #1]: Avoid topic-instance dispose on unregister
  DataWriterQos dwqos = dp.default_datawriter_qos() 
    << WriterDataLifecycle::ManuallyDisposeUnregisteredInstances();
   
  //[NOTE #2]: Creating DataWriter with custom QoS.
  // QoS will be covered in detail in article #4.
  dds::DataWriter<TempSensorType> dw(topic, dwqos);
   
  TempSensorType data = {0, 24.3F, 0.5F, CELSIUS};
  dw.write(data);   

  TempSensorType key;
  key.id = 1;
   
  //[NOTE #3] Registering topic-instance explicitly 
  InstanceHandle h1 = dw.register_instance(key);
   
  key.id = 2;
  InstanceHandle h2 = dw.register_instance(key);
	
  key.id = 3;
  InstanceHandle h3 = dw.register_instance(key);
   
  data = {1, 24.3F, 0.5F, CELSIUS};
  dw.write(data);
   
  data = {2, 23.5F, 0.6F, CELSIUS};
  dw.write(data);
   
  data = {3, 21.7F, 0.5F, CELSIUS};
  dw.write(data);
   
  // [NOTE #4]: unregister topic-instance with id=1 
  dw.unregister_instance(h1);
   
  // [NOTE #5]: dispose topic-instance with id=2
  dw.dispose(h2);   

  //[NOTE #6]:topic-instance with id=3 will be unregistered as 
  // result of the dw object destruction 
   
  return 0;
}
