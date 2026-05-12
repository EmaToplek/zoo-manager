#ifndef BIRD_HPP
#define BIRD_HPP

#include "animal.hpp"

class Bird : public Animal 
{
public: 
    Bird(uint64_t id, const std::string& name, const std::string& species,
        uint64_t age, double weight, const std::string& enclosure, 
        HealthStatus health_status, bool can_fly, double wingspan,
        const std::string& feeding_type, const std::string& habitat,
        double min_enclosure_size);
    
    AnimalCategory get_category() const override; 
    std::string get_feeding_type() const override;
    std::string get_habitat() const override; 
    double get_min_enclosure_size() const override; 
    bool can_fly() const; 
    double get_wingspan() const;


private: 
    std::string feeding_type_;
    std::string habitat_;
    double min_enclosure_size_;
    bool  can_fly_;
    double wingspan_; 
};





#endif