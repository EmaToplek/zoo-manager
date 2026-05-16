#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>


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

    HealthStatus own_health;
    if(health_status == "Healthy") { own_health = HealthStatus::Healthy; }
    else if(health_status == "Sick") { own_health = HealthStatus::Sick; }
    else if(health_status == "In Treatment") { own_health = HealthStatus::In_Treatment; }

    Animal* a;
    if(category == "Bird" || category == "Reptile") {
        return;
    }
    if(category == "Mammal") {
        a = new Mammal(id, name, species, age, weight, enclosure, own_health);
    }
    if(category == "Fish") {
        a = new Fish(id, name, species, age, weight, enclosure, own_health);
    }
    if(category == "Amphibian") {
        a = new Amphibian(id, name, species, age, weight, enclosure, own_health);
    }
    animals_list_.push_back(a);
}

// returns a reference to the internal list without copying
const std::vector<Animal*>& Animal_Manager::get_all_animals() const{
    return animals_list_;
}
// Counts each animal category
void Animal_Manager::category_count(uint64_t& mammal_count, uint64_t& fish_count, uint64_t& bird_count, uint64_t& reptile_count, uint64_t& amphibian_count){
    mammal_count =  fish_count = bird_count = reptile_count = amphibian_count = 0;
    for(Animal* animal : animals_list_){
        switch (animal->get_category())
        {
        case AnimalCategory::Amphibian: amphibian_count++; break;
        case AnimalCategory::Mammal: mammal_count++; break;
        case AnimalCategory::Bird: bird_count++; break;
        case AnimalCategory::Reptile: reptile_count++; break;
        case AnimalCategory::Fish: fish_count++; break;
        }
    }
}

uint64_t Animal_Manager::total_count(){
    return animals_list_.size();
}
