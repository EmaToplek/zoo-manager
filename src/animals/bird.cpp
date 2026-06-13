#include "bird.hpp"
#include <sstream>

constexpr const char* kFeedingType = "Seeds/Insects";
constexpr const char* kHabitat = "Aviary";
constexpr double kMinEnclosureSize = 50.0;


// standard constructor — initializes base class Animal via initializer list
// then sets Bird-specific private members directly (type safe)
Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status,const std::map<std::string, std::string>& special_info) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Bird::get_category() const { return AnimalCategory::Bird; }

std::string Bird::get_feeding_type() const { return kFeedingType; }
std::string Bird::get_habitat() const { return kHabitat; }
double Bird::get_min_enclosure_size() const { return kMinEnclosureSize; }

// builds a map from private members for JSON serialization in save()
// returns the map as-is — Animal_Manager::save() iterates it generically,
// so no manual field packing is needed here.
std::map<std::string, std::string> Bird::get_special_info_map() const 
{
    return special_info_;     
}






