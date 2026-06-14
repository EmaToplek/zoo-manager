#include "reptile.hpp"
#include <sstream>

constexpr const char* kFeedingType = "Insects/Small animals";
constexpr const char* kHabitat = "Jungle Terrarium";
constexpr double kMinEnclosureSize = 30.0;

Reptile::Reptile(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, const std::map<std::string, std::string>& special_info) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Reptile::get_category() const { return AnimalCategory::Reptile; }

std::string Reptile::get_feeding_type() const { return kFeedingType; }
std::string Reptile::get_habitat() const  { return kHabitat; }
double Reptile::get_min_enclosure_size() const { return kMinEnclosureSize; }

std::map<std::string, std::string> Reptile::get_special_info_map() const 
{
    return special_info_; 
     
}











