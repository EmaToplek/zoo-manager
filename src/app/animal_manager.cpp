#include "animal_manager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

Animal_Manager::Animal_Manager() 
{ 
    load_species(); 
}
#include <filesystem>


// reads data.json and deserializes each entry into correct Animal subclass
// called on startup to restore the previous session
void Animal_Manager::load()
{
    //opens data.json and parses its contents
    std::ifstream file("../data.json");
    if(!file) {
        std::cerr << "File doesn't exists!Adding demo animals!" << std::endl;
        add_animal(1, "Leo", "Lion", "Mammal", 4, 192.0, "Savannah", "In Treatment");
        add_animal(19, "Toad", "Amphibian", "Amphibian", 4, 0.4, "Pond", "Sick");
    } else{
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
        a = new Mammal(id, name, species, age, weight, enclosure, own_health,special_info); 
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

// counts animals per health status
void Animal_Manager::health_count(uint64_t& healthy, uint64_t& sick, uint64_t& in_treatment) const
{
    healthy = 0;
    sick = 0;
    in_treatment = 0;

    for (Animal* animal : animals_list_)
    {
        switch (animal->get_health_status())
        {
            case HealthStatus::Healthy: 
                healthy++; 
                break;
            case HealthStatus::Sick: 
                sick++; 
                break;
            case HealthStatus::In_Treatment: 
                in_treatment++; 
                break;
        }
    }
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

// loads species lists and default traits from species.json
// species.json is the single source of truth for both
void Animal_Manager::load_species()
{
    std::ifstream file("../species.json");
    if (!file.is_open()) return; // to prevent crashes 

    nlohmann::json j;
    file >> j;
    
    //species list
    for (auto& [category, species] : j.items()) 
    {
        if (category != "default_traits") 
        {
            for (auto& s : species) 
            {
                species_list_[category].push_back(s.get<std::string>());
            }
        }
    }

    // default traits
    if (j.contains("default_traits")) 
    {
        for (auto& [cat, traits] : j["default_traits"].items()) 
        {
            for (auto& [key, val] : traits.items())
            {
                default_traits_[cat][key] = val.get<std::string>();  
            }
        }
    }        
                    
}

// returns the default special_info map for a given category
// if the category has no defaults defined, returns an empty map
std::map<std::string, std::string> Animal_Manager::get_default_traits(const std::string& category) const
{
    auto it = default_traits_.find(category);
    if (it != default_traits_.end()) 
    {
        return it->second;
    }
    return {};
}

// returns the species list for a given category
// used by AddEditDialog to populate the species dropdown
std::vector<std::string> Animal_Manager::get_species_for_category(const std::string& category) const
{
    auto it = species_list_.find(category);
    if (it != species_list_.end()) 
    {
        return it->second;
    }
    return {};
}

// returns all animals whose name or species contains the query string (case-insensitive)
std::vector<Animal*> Animal_Manager::search(const std::string& query) const
{
    std::vector<Animal*> result;
    std::string lower_query = query;
    std::transform(lower_query.begin(), lower_query.end(), lower_query.begin(), ::tolower);

    for (Animal* animal : animals_list_)
    {
        std::string name = animal->get_name();
        std::string species = animal->get_species();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(species.begin(), species.end(), species.begin(), ::tolower);

        if (name.find(lower_query) != std::string::npos || species.find(lower_query) != std::string::npos)
        {
            result.push_back(animal);
        }
    }
    
    return result;
}

void Animal_Manager::add_animal(Animal* animal)
{
    animals_list_.push_back(animal);
}