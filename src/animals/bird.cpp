#include "bird.hpp"
#include <sstream>
#include <iomanip>

// standard constructor — initializes base class Animal via initializer list
// then sets Bird-specific private members directly (type safe)
Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool can_fly, double wingspan) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    can_fly_(can_fly), 
    wingspan_(wingspan)
{}

// Static Factory Method — called when loading from JSON
// extracts and converts string values from map, then calls the constructor above
// Bird class owns this logic
Bird* Bird::create_from_map(uint64_t id, const std::string& name, const std::string& species,
    uint64_t age, double weight, const std::string& enclosure, 
    HealthStatus health_status, const std::map<std::string, std::string>& special_info)
{
    bool can_fly = special_info.count("can_fly") ? (special_info.at("can_fly") == "true") : true;
    double wingspan = special_info.count("wingspan") ? std::stod(special_info.at("wingspan")) : 1.0;
    return new Bird(id, name, species, age, weight, enclosure, health_status, can_fly, wingspan);
}

AnimalCategory Bird::get_category() const { return AnimalCategory::Bird; }

// bird always live in aviary, not possible to make bird with habitat desert
std::string Bird::get_feeding_type() const { return "Seeds/Insects"; }
std::string Bird::get_habitat() const { return "Aviary"; }
double Bird::get_min_enclosure_size() const { return 50.0; }

// builds a map from private members for JSON serialization in save()
std::map<std::string, std::string> Bird::get_special_info_map() const 
{
    return 
    {
        {"can_fly", can_fly_ ? "true" : "false"},
        {"wingspan", std::to_string(wingspan_)}
    };
}

// returns human-readable string for GUI detail panel
std::string Bird::get_special_info() const
{
    std::ostringstream oss;
    oss << "Wingspan: " << std::fixed << std::setprecision(1) << wingspan_ << "m\n";
    oss << "Can fly: " << (can_fly_ ? "Yes" : "No");
    return oss.str();
}









