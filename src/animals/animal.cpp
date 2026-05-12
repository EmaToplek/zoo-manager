#include "animal.hpp"

Animal::Animal(uint64_t id, const std::string& name, const std::string& species, uint64_t age, double weight, 
               const std::string& enclosure, HealthStatus health_status, const std::string& feeding_type, 
               const std::string& habitat, double min_enclosure_size)
    : id_(id), name_(name), species_(species), age_(age), weight_(weight),
    enclosure_(enclosure), health_status_(health_status),
    feeding_type_(feeding_type), habitat_(habitat),
    min_enclosure_size_(min_enclosure_size)
{}