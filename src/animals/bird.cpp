#include "bird.hpp"


Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool can_fly, double wingspan,
            const std::string& feeding_type, const std::string& habitat,
            double min_enclosure_size) 
    : Animal (id, name, species, age, weight, enclosure, health_status, feeding_type, habitat, min_enclosure_size), 
    can_fly_(can_fly),
    wingspan_(wingspan)
{}

AnimalCategory Bird::get_category() const 
{
    return AnimalCategory::Bird; 
}

bool Bird::can_fly() const 
{
    return can_fly_; 
}

double Bird::get_wingspan() const 
{
    return wingspan_; 
}









