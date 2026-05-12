#include "reptile.hpp"


Reptile::Reptile(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool is_venomous, double body_length,
            const std::string& feeding_type, const std::string& habitat,
            double min_enclosure_size) 
    : Animal (id, name, species, age, weight, enclosure, health_status, feeding_type, habitat, min_enclosure_size),
    is_venomous_(is_venomous),
    body_length_(body_length)
{}

AnimalCategory Reptile::get_category() const 
{
    return AnimalCategory::Reptile; 
}

bool Reptile::get_is_venomous() const 
{
    return is_venomous_; 
}

double Reptile::get_body_length() const 
{
    return body_length_; 
}









