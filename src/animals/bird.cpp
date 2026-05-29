#include "bird.hpp"
#include <sstream>

// standard constructor — initializes base class Animal via initializer list
// then sets Bird-specific private members directly (type safe)
Bird::Bird (uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status,const std::map<std::string, std::string>& special_info) 
    : Animal (id, name, species, age, weight, enclosure, health_status),
    special_info_(special_info)
{}

// Static Factory Method — called when loading from JSON
// extracts and converts string values from map, then calls the constructor above
// Bird class owns this logic
/*Bird* Bird::create_from_map(uint64_t id, const std::string& name, const std::string& species,
    uint64_t age, double weight, const std::string& enclosure, 
    HealthStatus health_status, const std::map<std::string, std::string>& special_info)
{
    return new Bird(id, name, species, age, weight, enclosure, health_status, special_info);
}
*/


AnimalCategory Bird::get_category() const { return AnimalCategory::Bird; }

std::string Bird::get_feeding_type() const { return "Seeds/Insects"; }
std::string Bird::get_habitat() const { return "Aviary"; }
double Bird::get_min_enclosure_size() const { return 50.0; }

// builds a map from private members for JSON serialization in save()
// returns the map as-is — Animal_Manager::save() iterates it generically,
// so no manual field packing is needed here.
std::map<std::string, std::string> Bird::get_special_info_map() const 
{
    return special_info_;     
}






