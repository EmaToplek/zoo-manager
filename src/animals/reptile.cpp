#include "reptile.hpp"
#include <sstream>
#include <iomanip>


Reptile::Reptile(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool is_venomous, double body_length) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    is_venomous_(is_venomous), 
    body_length_(body_length)
{}

Reptile* Reptile::create_from_map(uint64_t id, const std::string& name, const std::string& species,
    uint64_t age, double weight, const std::string& enclosure, 
    HealthStatus health_status, const std::map<std::string, std::string>& special_info)
{
    bool is_venomous   = special_info.count("is_venomous") ? (special_info.at("is_venomous") == "true") : false;
    double body_length = special_info.count("body_length") ? std::stod(special_info.at("body_length")) : 1.0;
    return new Reptile(id, name, species, age, weight, enclosure, health_status, is_venomous, body_length);
}


AnimalCategory Reptile::get_category() const { return AnimalCategory::Reptile; }

std::string Reptile::get_feeding_type() const { return "Insects/Small animals"; }
std::string Reptile::get_habitat() const      { return "Jungle Terrarium"; }
double Reptile::get_min_enclosure_size() const { return 30.0; }

std::map<std::string, std::string> Reptile::get_special_info_map() const 
{
    return 
    {
        {"is_venomous", is_venomous_ ? "true" : "false"},
        {"body_length", std::to_string(body_length_)}
    }; 
}

std::string Reptile::get_special_info() const 
{
    std::ostringstream oss;
    oss << "Body length: " << std::fixed << std::setprecision(1) << body_length_ << "m\n";
    oss << "Venomous: " << (is_venomous_ ? "Yes" : "No");
    return oss.str();
}










