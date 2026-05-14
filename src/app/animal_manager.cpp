#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

Animal_Manager::Animal_Manager(){
    init_factories();
}

void Animal_Manager::load()
{   
    //opens data.json and parses its contents
    std::ifstream file("../data.json");
    nlohmann::json j;
    file >> j;
    
    //for each entry in json array, extracts fields and calls add_animal()
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

// checks category string, creates matching subclass instance, assign it to Animal* a and appends to internal animals_list 
void Animal_Manager::add_animal(uint64_t id, const std::string& name, 
    const std::string& species, std::string category, uint64_t age, 
    double weight, const std::string& enclosure, std::string health_status)
{
    if(animal_factory_.find(category) != animal_factory_.end() && 
       health_map_.find(health_status) != health_map_.end()) {
        Animal* a = animal_factory_[category](id, name, species, age, weight, enclosure, health_map_[health_status]);
        animals_list_.push_back(a);
    }
}

// returns a reference to the internal list without copying
const std::vector<Animal*>& Animal_Manager::get_all_animals() const{
    return animals_list_;
}

void Animal_Manager::init_factories() {
    animal_factory_["Mammal"] = [](auto id, auto& name, auto& species, auto age, auto weight, auto& enclosure, auto health) {
        return new Mammal(id, name, species, age, weight, enclosure, health);
    };
    animal_factory_["Fish"] = [](auto id, auto& name, auto& species, auto age, auto weight, auto& enclosure, auto health) {
        return new Fish(id, name, species, age, weight, enclosure, health);
    };
    animal_factory_["Amphibian"] = [](auto id, auto& name, auto& species, auto age, auto weight, auto& enclosure, auto health) {
        return new Amphibian(id, name, species, age, weight, enclosure, health);
    };
    animal_factory_["Bird"] = [](auto id, auto& name, auto& species, auto age, auto weight, auto& enclosure, auto health) {
        return new Bird(id, name, species, age, weight, enclosure, health, false, 0.0);
    };
    animal_factory_["Reptile"] = [](auto id, auto& name, auto& species, auto age, auto weight, auto& enclosure, auto health) {
        return new Reptile(id, name, species, age, weight, enclosure, health, false, 0.0);
    };

    health_map_["Healthy"] = HealthStatus::Healthy;
    health_map_["Sick"] = HealthStatus::Sick;
    health_map_["In Treatment"] = HealthStatus::In_Treatment;
}