DataWriter<EventCountType>  kdw(pub, ecTopic);
TempSensorType ts = {1, 26.0F, 70.0F, CELSIUS};
kdw.write(ts);
ts = {2, 26.0F, 70.0F, CELSIUS};
kdw.write(ts);
