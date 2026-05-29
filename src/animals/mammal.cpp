#include "mammal.hpp"
#include <sstream>

Mammal::Mammal(uint64_t id, const std::string& name, const std::string& species,
               uint64_t age, double weight, const std::string& enclosure,
               HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Mammal::get_category() const { return AnimalCategory::Mammal; }

std::string Mammal::get_feeding_type() const { return "Meat/Plants"; }
std::string Mammal::get_habitat() const { return "Savanna"; }
double Mammal::get_min_enclosure_size() const { return 200.0; }


std::map<std::string, std::string> Mammal::get_special_info_map() const 
{
    return special_info_;     
}
