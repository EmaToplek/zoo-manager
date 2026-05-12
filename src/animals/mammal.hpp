#ifndef MAMMAL_HPP
#define MAMMAL_HPP

#include "animal.hpp"

class Mammal : public Animal{
    
public:
    Mammal(uint64_t id, const std::string& name, const std::string& species, 
       uint64_t age, double weight, const std::string& enclosure, 
       HealthStatus health_status, const std::string& feeding_type,
       const std::string& habitat, double min_enclosure_size) 
    : Animal(id, name, species, age, weight, enclosure, health_status, 
             feeding_type, habitat, min_enclosure_size){}
    
    AnimalCategory get_category() const override;
};

#endif