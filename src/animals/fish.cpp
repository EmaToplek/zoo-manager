#include "fish.hpp"
#include <sstream>

Fish::Fish(uint64_t id, const std::string& name, const std::string& species,
           uint64_t age, double weight, const std::string& enclosure,
           HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Fish::get_category() const { return AnimalCategory::Fish; }

std::string Fish::get_feeding_type() const { return "Pellets/Live fish"; }
std::string Fish::get_habitat() const { return "Aquarium"; }
double Fish::get_min_enclosure_size() const { return 20.0; }


std::map<std::string, std::string> Fish::get_special_info_map() const 
{
    return special_info_;     
}

// returns human-readable string for GUI detail panel
std::string Fish::get_special_info() const
{
    std::ostringstream oss;
    for (const auto& [key, val] : special_info_) 
    {
        oss << key << ": " << val << "\n";
    }
    return oss.str();
}

void Fish::update_special_info(const std::string& key, const std::string& value) 
{
    special_info_[key] = value;
}
