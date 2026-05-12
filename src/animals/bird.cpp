#include "bird.hpp"


Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool can_fly, double wingspan,
            const std::string& feeding_type, const std::string& habitat,
            double min_enclosure_size) 
    : Animal (id, name, species, age, weight, enclosure, health_status), 
    can_fly_(can_fly),
    wingspan_(wingspan),
    feeding_type_(feeding_type),
    habitat_(habitat),
    min_enclosure_size_(min_enclosure_size) 
{}

AnimalCategory Bird::get_category() const 
{
    return AnimalCategory::Bird; 
}

std::string Bird::get_feeding_type() const 
{
    return feeding_type_; 
}

std::string Bird::get_habitat() const 
{
    return habitat_; 
}

double Bird::get_min_enclosure_size() const 
{
    return min_enclosure_size_; 
}

bool Bird::can_fly() const 
{
    return can_fly_; 
}

double Bird::get_wingspan() const 
{
    return wingspan_; 
}









