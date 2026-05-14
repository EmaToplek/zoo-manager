#include "bird.hpp"
#include <sstream>
#include <iomanip>

Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, bool can_fly, double wingspan) 
    : Animal (id, name, species, age, weight, enclosure, health_status), 
    can_fly_(can_fly),
    wingspan_(wingspan)
{}

AnimalCategory Bird::get_category() const { return AnimalCategory::Bird; }

// bird always live in aviary, not possible to make bird with habitat desert
std::string Bird::get_feeding_type() const { return "Seeds/Insects"; }

std::string Bird::get_habitat() const { return "Aviary"; }

double Bird::get_min_enclosure_size() const { return 50.0; }

//builds a formatted string using << like std::cout
//std::fixed + setprecision(1) ensures wingspan shows as "2.5" not "2.500000"
std::string Bird::get_special_info() const {
    std::ostringstream oss; 
    oss << "Wingspan: " << std::fixed << std::setprecision(1) << wingspan_ << "m\n"
        << "Can fly: " << (can_fly_ ? "Yes" : "No");
    return oss.str();
}

bool Bird::can_fly() const { return can_fly_; }

double Bird::get_wingspan() const { return wingspan_; }









