DataWriter<KeylessTempSensorType> kldw(pub, kltsTopic);
TempSensorType ts = {1, 26.0F, 70.0F, CELSIUS};
kldw.write(ts);
ts = {2, 26.0F, 70.0F, CELSIUS};
kldw.write(ts);
