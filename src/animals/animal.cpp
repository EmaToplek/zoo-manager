#include "animal.hpp"

Animal::Animal(uint64_t id, const std::string& name, const std::string& species, uint64_t age, double weight, 
               const std::string& enclosure, HealthStatus health_status, const std::string& feeding_type, 
               const std::string& habitat, double min_enclosure_size)
    : id_(id), name_(name), species_(species), age_(age), weight_(weight),
    enclosure_(enclosure), health_status_(health_status),
    feeding_type_(feeding_type), habitat_(habitat),
    min_enclosure_size_(min_enclosure_size)
{}


void Animal::tickhealth(){
    if(health_status_ == HealthStatus::Healthy){
        return;
    }
    ticks_++; // => only ticks if sick or in treatment
    if(health_status_ == HealthStatus::Sick && ticks_ >= sickt_to_treatment_tick){
        health_status_ = HealthStatus::In_Treatment;
        ticks_ = 0;
    }
    if(health_status_ == HealthStatus::In_Treatment && ticks_ >= treatment_to_healthy_tick){
        health_status_ = HealthStatus::Healthy;
        ticks_ = 0;
    }
}

std::string Animal::get_health_status_to_string() const{
    switch (health_status_)
    {
    case HealthStatus::Healthy:
        return "Healthy";
        break;
    case HealthStatus::Sick:
        return "Sick";
        break;
    
    case HealthStatus::In_Treatment:
        return "In Treatment";
        break;

    default:
        return "None";
    }
}

std::string Animal::get_category_to_string(){
    if(get_category() == AnimalCategory::Mammal){
        return "Mammal";
    }
    else if(get_category() == AnimalCategory::Amphibian){
        return "Amphibian";
    }
    else if(get_category() == AnimalCategory::Bird){
        return "Bird";
    }
    else if(get_category() == AnimalCategory::Fish){
        return "Fish";
    }
    else if(get_category() == AnimalCategory::Reptile){
        return "Reptile";
    }
    return "Unknown";
};