#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

Animal_Manager::Animal_Manager() 
{ 
    load_species(); 
}


// reads data.json and deserializes each entry into correct Animal subclass
// called on startup to restore the previous session
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

        // read special_info block from JSON into map if it exists
        std::map<std::string, std::string> special_info;
        if (animal.contains("special_info")) 
        {
            for (auto& [key, val] : animal["special_info"].items()) 
            {
                special_info[key] = val.get<std::string>();
            }
        }

        add_animal(id, name, species, category, age, weight, enclosure, health, -1, special_info);
    }
}

// serializes all animals from memory to data.json
// called after every modification (add, edit, remove) to persist changes
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
        entry["category"] = animal->get_category_to_string(); // calls pure virtual via base pointer 
        entry["age"] = animal->get_age();
        entry["weight"] = animal->get_weight();
        entry["enclosure"] = animal->get_enclosure();
        entry["health"] = animal->get_health_status_to_string();

        auto info_map = animal->get_special_info_map();
        if (!info_map.empty()) 
        {
            for (auto& [key, val] : info_map) 
            {
                entry["special_info"][key] = val;
            }
        }

        j.push_back(entry);
    }

    //write JSON arrray to data.json with 4 space indentation
    std::ofstream file("../data.json");
    file << j.dump(4);
}


// creates the correct Animal subclass based on category string
// Animal is abstract — the vector holds Animal* pointers, but actual objects
// on the heap are concrete subclasses (Mammal, Fish, Bird, Reptile, Amphibian)
void Animal_Manager::add_animal(uint64_t id, const std::string& name, 
    const std::string& species, std::string category, uint64_t age, 
    double weight, const std::string& enclosure, std::string health_status, int position,
    std::map<std::string, std::string> special_info)
{

    HealthStatus own_health = HealthStatus::Healthy;
    if(health_status == "Healthy") 
    { 
        own_health = HealthStatus::Healthy; 
    }
    else if(health_status == "Sick") 
    { 
        own_health = HealthStatus::Sick; 
    }
    else if(health_status == "In Treatment") 
    { 
        own_health = HealthStatus::In_Treatment; 
    }

    Animal* a = nullptr;
    
    if(category == "Bird") 
    {
        a = new Bird(id, name, species, age, weight, enclosure, own_health, special_info);
    }
    else if(category == "Reptile") 
    {
        a = new Reptile(id, name, species, age, weight, enclosure, own_health, special_info);
    }
    else if(category == "Mammal") 
    {
        a = new Mammal(id, name, species, age, weight, enclosure, own_health, special_info); 
    }
    else if(category == "Fish") 
    {
        a = new Fish(id, name, species, age, weight, enclosure, own_health, special_info);
    }
    else if(category == "Amphibian") 
    {
        a = new Amphibian(id, name, species, age, weight, enclosure, own_health, special_info);
    }
    
    if (a != nullptr) 
    {
        // if position is valid, insert at that index to preserve original order, otherwise push_back
        if (position >= 0 && position < (int)animals_list_.size()) 
        {
            animals_list_.insert(animals_list_.begin() + position, a);
        }
        else 
        {
            animals_list_.push_back(a);
        }    
    }
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


void Animal_Manager::load_species()
{
    std::ifstream file("../species.json");
    if (!file.is_open()) return; // to prevent crashes 

    nlohmann::json j;
    file >> j;
    for (auto& [category, species] : j.items()) 
    {
        for (auto& s : species) 
        {
            species_list_[category].push_back(s.get<std::string>());
        }
    }
}

std::vector<std::string> Animal_Manager::get_species_for_category(const std::string& category) const
{
    auto it = species_list_.find(category);
    if (it != species_list_.end()) return it->second;
    return {};
}