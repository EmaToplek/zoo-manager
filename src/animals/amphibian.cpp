#include "amphibian.hpp"

Amphibian::Amphibian(uint64_t id, const std::string& name, const std::string& species,
                     uint64_t age, double weight, const std::string& enclosure,
                     HealthStatus health_status)
    : Animal(id, name, species, age, weight, enclosure, health_status)
{}

AnimalCategory Amphibian::get_category() const { return AnimalCategory::Amphibian; }

std::string Amphibian::get_feeding_type() const { return "Insects"; }
std::string Amphibian::get_habitat() const { return "Wetlands"; }
double Amphibian::get_min_enclosure_size() const { return 15.0; }
std::string Amphibian::get_special_info() const { return "No additional info"; }