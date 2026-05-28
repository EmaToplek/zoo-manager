#include "amphibian.hpp"
#include <sstream>

Amphibian::Amphibian(uint64_t id, const std::string& name, const std::string& species,
                     uint64_t age, double weight, const std::string& enclosure,
                     HealthStatus health_status, const std::map<std::string, std::string>& special_info)
    : Animal(id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

AnimalCategory Amphibian::get_category() const { return AnimalCategory::Amphibian; }

std::string Amphibian::get_feeding_type() const { return "Insects"; }
std::string Amphibian::get_habitat() const { return "Wetlands"; }
double Amphibian::get_min_enclosure_size() const { return 15.0; }


std::map<std::string, std::string> Amphibian::get_special_info_map() const 
{
    return special_info_;     
}

// returns human-readable string for GUI detail panel
std::string Amphibian::get_special_info() const
{
    std::ostringstream oss;
    for (const auto& [key, val] : special_info_) 
    {
        oss << key << ": " << val << "\n";
    }
    return oss.str();
}

void Amphibian::update_special_info(const std::string& key, const std::string& value) 
{
    special_info_[key] = value;
}
