#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

void Animal_Manager::load()
{
    std::ifstream file("data.json");
    nlohmann::json j;
    file >> j;
    
    for(auto& animal : j) {
        uint64_t id = animal["id"];
        std::string name = animal["name"];
        std::string species = animal["species"];
        std::string category = animal["category"];
        uint64_t age = animal["age"];
        double weight = animal["weight"];
        std::string enclosure = animal["enclosure"];
        std::string health = animal["health"];
        
        HealthStatus own_health;
        if(health == "Healthy"){own_health = HealthStatus::Healthy;}
        else if(health == "Sick"){own_health = HealthStatus::Sick;}
        else if(health == "In Treatment"){own_health = HealthStatus::In_Treatment;}

        // uint64_t id,const std::string& name, const std::string& species, uint64_t age, double weight, const std::string& enclosure, HealthStatus health_status
        if(category == "Mammal"){
            Mammal* m = new Mammal(id, name, species, age, weight, enclosure, own_health);
        }
    }
}



