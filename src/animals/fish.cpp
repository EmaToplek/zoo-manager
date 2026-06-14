#include "fish.hpp"
#include <sstream>

constexpr const char* kFeedingType = "Pellets/Live fish";
constexpr const char* kHabitat = "Aquarium";
constexpr double kMinEnclosureSize = 20.0;

Fish::Fish(uint64_t id, const std::string& name, const std::string& species,
           uint64_t age, double weight, const std::string& enclosure,
           HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Fish::get_category() const { return AnimalCategory::Fish; }

std::string Fish::get_feeding_type() const { return kFeedingType; }
std::string Fish::get_habitat() const { return kHabitat; }
double Fish::get_min_enclosure_size() const { return kMinEnclosureSize; }


std::map<std::string, std::string> Fish::get_special_info_map() const 
{
    return special_info_;     
}
