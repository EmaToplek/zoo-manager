#ifndef FISH_HPP
#define FISH_HPP
#include "animal.hpp"

class Fish : public Animal {
public:
    Fish(uint64_t id, const std::string& name, const std::string& species,
         uint64_t age, double weight, const std::string& enclosure,
         HealthStatus health_status);

    // override pure virtuals from Animal
    AnimalCategory get_category() const override;
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;
    std::string get_special_info() const override;
};

#endif