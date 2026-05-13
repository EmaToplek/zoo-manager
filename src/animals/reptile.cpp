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

AnimalCategory Reptile::get_category() const { return AnimalCategory::Reptile; }

std::string Reptile::get_feeding_type() const { return "Insects/Small animals"; }
std::string Reptile::get_habitat() const      { return "Jungle Terrarium"; }
double Reptile::get_min_enclosure_size() const { return 30.0; }

bool Reptile::get_is_venomous() const { return is_venomous_; }

std::string Reptile::get_special_info() const {
    std::ostringstream oss;
    oss << "Body length: " << std::fixed << std::setprecision(1) << body_length_ << "m\n"
        << "Venomous: " << (is_venomous_ ? "Yes" : "No");
    return oss.str();
}

double Reptile::get_body_length() const { return body_length_; }









