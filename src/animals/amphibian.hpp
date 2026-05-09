#ifndef AMPHIBIAN_HPP
#define AMPHIBIAN_HPP

#include "animal.hpp"

class Amphibian : public Animal{
    
public:
    Amphibian(uint64_t id, const std::string& name, const std::string& species, 
           uint64_t age, double weight, const std::string& enclosure, 
           HealthStatus health_status) 
        : Animal(id, name, species, age, weight, enclosure, health_status){}
    
    AnimalCategory get_category() const override;
};



#endif //AMPHIBIAN_HPP