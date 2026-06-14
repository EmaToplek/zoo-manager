#include "mammal.hpp"
#include <sstream>

constexpr const char* kFeedingType = "Meat/Plants";
constexpr const char* kHabitat = "Savanna";
constexpr double kMinEnclosureSize = 200.0;

Mammal::Mammal(uint64_t id, const std::string& name, const std::string& species,
               uint64_t age, double weight, const std::string& enclosure,
               HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Mammal::get_category() const { return AnimalCategory::Mammal; }

std::string Mammal::get_feeding_type() const { return kFeedingType; }
std::string Mammal::get_habitat() const { return kHabitat; }
double Mammal::get_min_enclosure_size() const { return kMinEnclosureSize; }


std::map<std::string, std::string> Mammal::get_special_info_map() const 
{
    return special_info_;     
}
