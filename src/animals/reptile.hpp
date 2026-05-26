#ifndef REPTILE_HPP
#define REPTILE_HPP

#include "animal.hpp"

class Reptile : public Animal 
{
public: 
    Reptile(uint64_t id, const std::string& name, const std::string& species,
        uint64_t age, double weight, const std::string& enclosure, 
        HealthStatus health_status, bool is_venomous, double body_length);
    
    static Reptile* create_from_map(uint64_t id, const std::string& name, const std::string& species,
            uint64_t age, double weight, const std::string& enclosure, 
            HealthStatus health_status, const std::map<std::string, std::string>& special_info);
    
    AnimalCategory get_category() const override; 
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;

    std::string get_special_info() const override;

    std::map<std::string, std::string> get_special_info_map() const override;
    
    static std::vector<std::string> get_available_species() 
    {
        return {"Komodo Dragon", "Gecko", "Iguana", "Crocodile", "Boa Constrictor", "Chameleon", "Tortoise"};
    }


private:
    bool is_venomous_;
    double body_length_;
};


#endif