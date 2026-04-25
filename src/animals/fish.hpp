#ifndef FISH_HPP
#define FISH_HPP

#include "animal.hpp"

class Fish : public Animal{
    
public:
    Fish(uint64_t id, const std::string& name, const std::string& species, 
           uint64_t age, double weight, const std::string& enclosure, 
           HealthStatus health_status) 
        : Animal(id, name, species, age, weight, enclosure, health_status){}
    
    AnimalCategory get_category() const override;
};



#endif //FISH_HPP
