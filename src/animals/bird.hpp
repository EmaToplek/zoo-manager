#ifndef BIRD_HPP
#define BIRD_HPP

#include "animal.hpp"

class Bird : public Animal 
{
public: 
    // standard constructor — called directly when we already have typed values
    Bird(uint64_t id, const std::string& name, const std::string& species,
        uint64_t age, double weight, const std::string& enclosure, 
        HealthStatus health_status, const std::map<std::string, std::string>& special_info);
        
    //override pure virtuals from animals, so compiler throws an error if one is forgotten
    AnimalCategory get_category() const override; 
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;

    // returns special_info_ map for JSON save and GUI detail panel
    std::map<std::string, std::string> get_special_info_map() const override;

private: 
    // single map replaces all individual member variables
    // adding a new field only requires inserting a key here — no header changes needed 
    std::map<std::string, std::string> special_info_;

};

 



#endif