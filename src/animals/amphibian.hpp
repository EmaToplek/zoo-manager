#ifndef AMPHIBIAN_HPP
#define AMPHIBIAN_HPP
#include "animal.hpp"

class Amphibian : public Animal {
public:
    Amphibian(uint64_t id, const std::string& name, const std::string& species,
              uint64_t age, double weight, const std::string& enclosure,
              HealthStatus health_status);

    AnimalCategory get_category() const override;
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;
    std::string get_special_info() const override;

    static std::vector<std::string> get_available_species() 
    {
        return {"Frog", "Salamander", "Axolotl", "Tree Frog", "Toad", "Newt"};
    }
};

#endif