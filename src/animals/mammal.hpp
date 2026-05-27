#ifndef MAMMAL_HPP
#define MAMMAL_HPP
#include "animal.hpp"

class Mammal : public Animal{
    
public:
    Mammal(uint64_t id, const std::string& name, const std::string& species, 
       uint64_t age, double weight, const std::string& enclosure, 
       HealthStatus health_status);
    
    AnimalCategory get_category() const override;
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;
    std::string get_special_info() const override;

    static std::vector<std::string> get_available_species() 
    {
        return {"Lion", "Tiger", "Elephant", "Zebra", "Gorilla", "Giraffe", "Hippo", "Cheetah", "Wolf", "Bear"};
    }

};

#endif