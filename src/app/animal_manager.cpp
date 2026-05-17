#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

// serializes all animals from memory to data.json
//called on exit or after any modification to persist changes
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

// reads data.json and deserializes each entry into correct Animal subclass
//called on startup to restore the previous session
void Animal_Manager::save() 
{
    //create empty json array to hold all animals
    nlohmann::json j = nlohmann::json::array();

    for(Animal* animal : animals_list_) 
    {
        nlohmann::json entry; // creates json obj for each animal
        entry["id"] = animal->get_id();
        entry["name"] = animal->get_name();
        entry["species"] = animal->get_species();
        entry["category"] = animal->get_category_to_string();
        entry["age"] = animal->get_age();
        entry["weight"] = animal->get_weight();
        entry["enclosure"] = animal->get_enclosure();
        entry["health"] = animal->get_health_status_to_string();

        j.push_back(entry);
    }

    //write JSON arrray to data.json with 4 space indentation
    std::ofstream file("../data.json");
    file << j.dump(4);
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

//removes an animal from list by id
//deletes obj from heap and erases the pointer from vector
bool Animal_Manager::remove_animal(uint64_t id) 
{
    for(auto it = animals_list_.begin(); it != animals_list_.end(); it++) 
    {
        if((*it)->get_id() == id) //*it gives me Animal*, -> dereferences Animal* (so we can call get_id() on the object)
        {
            delete *it;
            animals_list_.erase(it);
            return true;
        }
    }
    return false;
}