class TempSensorListener : 
  public virtual NoOpDataReaderListener<TemSensorType> 
{
public:
  virtual void on_data_available(DataReader<TempSensorType>& dr) {
    auto samples = dr.read();
    std::for_each(samples.begin(), samples.end(),
		  [](const Sample<TempSensorType>& s) { 
		    std::cout << s.data() << std::endl;
		  });
    
  }
};

TempSensorListener listener;
dr.listener(&listener, StatusMask::data_available());


