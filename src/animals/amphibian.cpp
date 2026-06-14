#include "amphibian.hpp"
#include <sstream>

constexpr const char* kFeedingType = "Insects/Larvae";
constexpr const char* kHabitat = "Pond/Terrarium";
constexpr double kMinEnclosureSize = 15.0;

Amphibian::Amphibian(uint64_t id, const std::string& name, const std::string& species,
                     uint64_t age, double weight, const std::string& enclosure,
                     HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Amphibian::get_category() const { return AnimalCategory::Amphibian; }

std::string Amphibian::get_feeding_type() const { return kFeedingType; }
std::string Amphibian::get_habitat() const { return kHabitat; }
double Amphibian::get_min_enclosure_size() const { return kMinEnclosureSize; }


std::map<std::string, std::string> Amphibian::get_special_info_map() const 
{
    return special_info_;     
}
