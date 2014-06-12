TempSensor key = {123, 0, 0, 0};
auto handle = dr.lookup_instance(key);

auto samples = dr.select()
  .instance(handle)
  .read();

