#include "reptile.hpp"
#include <sstream>


Reptile::Reptile(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, const std::map<std::string, std::string>& special_info) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

Reptile* Reptile::create_from_map(uint64_t id, const std::string& name, const std::string& species,
    uint64_t age, double weight, const std::string& enclosure, 
    HealthStatus health_status, const std::map<std::string, std::string>& special_info)
{
    return new Reptile(id, name, species, age, weight, enclosure, health_status, special_info);
}


AnimalCategory Reptile::get_category() const { return AnimalCategory::Reptile; }

std::string Reptile::get_feeding_type() const { return "Insects/Small animals"; }
std::string Reptile::get_habitat() const      { return "Jungle Terrarium"; }
double Reptile::get_min_enclosure_size() const { return 30.0; }

std::map<std::string, std::string> Reptile::get_special_info_map() const 
{
    return special_info_; 
     
}

std::string Reptile::get_special_info() const 
{
    std::ostringstream oss;
    for (const auto& [key, val] : special_info_) 
    {
        oss << key << ": " << val << "\n";
    }
    return oss.str();
}

void Reptile::update_special_info(const std::string& key, const std::string& value) 
{
    special_info_[key] = value;
}










