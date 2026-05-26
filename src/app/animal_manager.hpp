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



class Animal_Manager 
{
private:
    std::vector<Animal*> animals_list_; //stores all animals currently in the zoo

public:
    Animal_Manager(){};
    void save();
    void load();
    void add_animal(uint64_t id, const std::string& name, const std::string& species, 
        std::string category, uint64_t age, double weight, const std::string& enclosure, 
        std::string health_status, int position = -1);
    bool remove_animal(uint64_t id);
    const std::vector<Animal*>& get_all_animals() const;
    std::vector<Animal*> filter_by_category(AnimalCategory category) const;
    std::vector<Animal*> filter_by_status(HealthStatus status) const;
    void category_count(uint64_t& mammal_count, uint64_t& fish_count, uint64_t& bird_count, uint64_t& reptile_count, uint64_t& amphibian_count);
    uint64_t total_count();

}; // class


#endif //ANIMAL_MANAGER_HPP


