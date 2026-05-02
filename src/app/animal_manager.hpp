#ifndef ANIMAL_MANAGER_HPP
#define ANIMAL_MANAGER_HPP

#include "animal.hpp"
#include <vector>

class Animal_Manager{

    private:
    std::vector<Animal> animals_list_;

    
    public:
    Animal_Manager();
    void save() const;
    void load();
    void add_animal(uint64_t id,const std::string& name, const std::string& species, uint64_t age, double weight, const std::string& enclosure, HealthStatus health_status);
    bool remove_animal(uint64_t id);
    std::vector<Animal>& get_all_animals() const;
    std::vector<Animal> filter_by_category(AnimalCategory category) const;
    std::vector<Animal> filter_by_status(HealthStatus status) const;

    


}; // class


#endif //ANIMAL_MANAGER_HPP


