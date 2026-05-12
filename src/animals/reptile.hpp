#ifndef REPTILE_HPP
#define REPTILE_HPP

#include "animal.hpp"

class Reptile : public Animal 
{
public: 
    Reptile(uint64_t id, const std::string& name, const std::string& species,
        uint64_t age, double weight, const std::string& enclosure, 
        HealthStatus health_status, bool is_venomous, double body_length,
        const std::string& feeding_type, const std::string& habitat,
        double min_enclosure_size);
    
    AnimalCategory get_category() const override; 
    bool get_is_venomous() const;
    double get_body_length() const;


private:
    bool is_venomous_;
    double body_length_;
};


#endif