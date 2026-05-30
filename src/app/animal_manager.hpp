#ifndef ANIMAL_MANAGER_HPP
#define ANIMAL_MANAGER_HPP

#include "../animals/animal.hpp"
#include "../animals/mammal.hpp"
#include "../animals/bird.hpp"
#include "../animals/fish.hpp"
#include "../animals/reptile.hpp"
#include "../animals/amphibian.hpp"
#include <vector>
#include <fstream>
#include <string>
#include<iostream>
#include <nlohmann/json.hpp>



class Animal_Manager 
{
private:
    std::vector<Animal*> animals_list_; //stores all animals currently in the zoo

    std::map<std::string, std::vector<std::string>> species_list_;

    std::map<std::string, std::map<std::string, std::string>> default_traits_;

public:
    Animal_Manager();
    void save();
    void load();
    void add_animal(uint64_t id, const std::string& name, const std::string& species, 
        std::string category, uint64_t age, double weight, const std::string& enclosure, 
        std::string health_status, int position = -1, std::map<std::string, std::string> special_info = {});
    bool remove_animal(uint64_t id);
    const std::vector<Animal*>& get_all_animals() const;
    std::vector<Animal*> filter_by_category(AnimalCategory category) const;
    std::vector<Animal*> filter_by_status(HealthStatus status) const;
    void category_count(uint64_t& mammal_count, uint64_t& fish_count, uint64_t& bird_count, uint64_t& reptile_count, uint64_t& amphibian_count);
    uint64_t total_count();
    void health_count(uint64_t& healthy, uint64_t& sick, uint64_t& in_treatment) const;

    void load_species();
    
    std::vector<std::string> get_species_for_category(const std::string& category) const;
    std::map<std::string, std::string> get_default_traits(const std::string& category) const;

    std::vector<Animal*> search(const std::string& query) const;

    void add_animal(Animal* animal); // used by tests 

}; // class


#endif //ANIMAL_MANAGER_HPP