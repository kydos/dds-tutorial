
// Define the query predicate
std::string predicate =
   "(temp NOT BETWEEN (%0 AND %1)) \
     OR \
    (hum NOT BETWEEN (%2 and %3))";

// Define the query parameters 
std::vector<std::string> params = 
   {"20.5", "21.5", "30", "50"};

dds::core::Query query(predicate, params);

auto samples = dr.select()
  .query(predicate)
  .read();
