#ifndef MAMMAL_HPP
#define MAMMAL_HPP
#include "animal.hpp"

class Mammal : public Animal{
    
public:
    Mammal(uint64_t id, const std::string& name, const std::string& species, 
       uint64_t age, double weight, const std::string& enclosure, 
       HealthStatus health_status, const std::map<std::string, std::string>& special_info = {});
    
    AnimalCategory get_category() const override;
    std::string get_feeding_type() const override;
    std::string get_habitat() const override;
    double get_min_enclosure_size() const override;
    std::string get_special_info() const override;

          // returns special_info_ map for JSON save and GUI detail panel
    std::map<std::string, std::string> get_special_info_map() const override;
    
    // A way for the GUI to edit properties directly in the map
    void update_special_info(const std::string& key, const std::string& value);
private: 
    // single map replaces all individual member variables
    // adding a new field only requires inserting a key here — no header changes needed 
    std::map<std::string, std::string> special_info_;
};

#endif