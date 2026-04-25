#ifndef BIRD_HPP
#define BIRD_HPP

#include "animal.hpp"

class Bird : public Animal 
{
public: 
    Bird(uint64_t id, const std::string& name, const std::string& species,
        uint64_t age, double weight, const std::string& enclosure, 
        HealthStatus health_status, bool can_fly, double wingspan);
    
    AnimalCategory get_category() const override; 
    std::string get_feeding_type() const;
    std::string get_habitat() const; 
    float get_min_enclosure_size() const; 
    bool can_fly() const; 
    double get_wingspan() const; 

private: 
    std::string feeding_type_;
    std::string habitat_;
    float min_enclosure_size_;
    bool  can_fly_;
    double wing_span_; 
};





#endif