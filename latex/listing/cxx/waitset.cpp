WaitSet ws;
ReadCondition rc(dr, DataState::new_data());
ws += rc;
// Wait for data to be available
ws.wait();
// read data
auto samples = dr.read();
