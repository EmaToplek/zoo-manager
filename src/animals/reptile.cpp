#include "reptile.hpp"


Reptile::Reptile(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool is_venomous, double body_length,
            const std::string& feeding_type, const std::string& habitat,
            double min_enclosure_size) 
    : Animal (id, name, species, age, weight, enclosure, health_status), 
    is_venomous_(is_venomous),
    body_length_(body_length),
    feeding_type_(feeding_type),
    habitat_(habitat),
    min_enclosure_size_(min_enclosure_size) 
{}

AnimalCategory Reptile::get_category() const 
{
    return AnimalCategory::Reptile; 
}

std::string Reptile::get_feeding_type() const 
{
    return feeding_type_; 
}

std::string Reptile::get_habitat() const 
{
    return habitat_; 
}

double Reptile::get_min_enclosure_size() const 
{
    return min_enclosure_size_; 
}

bool Reptile::get_is_venomous() const 
{
    return is_venomous_; 
}

double Reptile::get_body_length() const 
{
    return body_length_; 
}









