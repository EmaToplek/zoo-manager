#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

void Animal_Manager::load()
{
    std::ifstream file("../data.json");
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
        add_animal(id, name, species, category, age, weight, enclosure, health);
    }
}


void Animal_Manager::add_animal(uint64_t id,const std::string& name, const std::string& species, std::string category, uint64_t age, double weight, const std::string& enclosure, std::string health_status){
     HealthStatus own_health;
        if(health_status == "Healthy"){own_health = HealthStatus::Healthy;}
        else if(health_status == "Sick"){own_health = HealthStatus::Sick;}
        else if(health_status == "In Treatment"){own_health = HealthStatus::In_Treatment;}

    Animal* a;
    if(category == "Bird" || category == "Reptile"){
        return;
    }
    if(category == "Mammal"){
            a = new Mammal(id, name, species, age, weight, enclosure, own_health);
    }
    if(category == "Fish"){
            a = new Fish(id, name, species, age, weight, enclosure, own_health);
    }
    if(category == "Amphibian"){
            a = new Amphibian (id, name, species, age, weight, enclosure, own_health);
    }
    animals_list_.push_back(a);
}

const std::vector<Animal*>& Animal_Manager::get_all_animals() const{
    return animals_list_;
}





