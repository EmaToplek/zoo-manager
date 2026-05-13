#include "fish.hpp"

Fish::Fish(uint64_t id, const std::string& name, const std::string& species,
           uint64_t age, double weight, const std::string& enclosure,
           HealthStatus health_status)
    : Animal(id, name, species, age, weight, enclosure, health_status)
{}

AnimalCategory Fish::get_category() const { return AnimalCategory::Fish; }

std::string Fish::get_feeding_type() const { return "Pellets/Live fish"; }
std::string Fish::get_habitat() const { return "Aquarium"; }
double Fish::get_min_enclosure_size() const { return 20.0; }
std::string Fish::get_special_info() const { return "No additional info"; }