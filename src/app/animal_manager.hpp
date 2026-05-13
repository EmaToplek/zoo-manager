#ifndef ANIMAL_MANAGER_HPP
#define ANIMAL_MANAGER_HPP

#include "animal.hpp"
#include "mammal.hpp"
#include "bird.hpp"
#include "fish.hpp"
#include "reptile.hpp"
#include "amphibian.hpp"
#include <vector>
#include <fstream>
#include <string>
#include<iostream>
#include <nlohmann/json.hpp>



class Animal_Manager{

    private:
    std::vector<Animal*> animals_list_;

    
    public:
    Animal_Manager(){};
    void save() const;
    void load();
    void add_animal(uint64_t id, const std::string& name, const std::string& species, 
        std::string category, uint64_t age, double weight, const std::string& enclosure, 
        std::string health_status, const std::string& feeding_type = "Omnivore",
        const std::string& habitat = "Unknown", double min_enclosure_size = 20.0);
    bool remove_animal(uint64_t id);
    const std::vector<Animal*>& get_all_animals() const;
    std::vector<Animal*> filter_by_category(AnimalCategory category) const;
    std::vector<Animal*> filter_by_status(HealthStatus status) const;

    


}; // class


#endif //ANIMAL_MANAGER_HPP


