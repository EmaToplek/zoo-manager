#include "animal.hpp"

Animal::Animal(uint64_t id, const std::string& name, const std::string& species, uint64_t age, double weight, 
               const std::string& enclosure, HealthStatus health_status)
    : id_(id), name_(name), species_(species), age_(age), weight_(weight),
    enclosure_(enclosure), health_status_(health_status), ticks_(0)
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

// New solution for hard coded problem
const std::vector<std::pair<AnimalCategory, std::string>> Animal::category_names_ = {
    {AnimalCategory::Mammal, "Mammal"},
    {AnimalCategory::Fish, "Fish"},
    {AnimalCategory::Amphibian, "Amphibian"},
    {AnimalCategory::Bird, "Bird"},
    {AnimalCategory::Reptile, "Reptile"}
};

// New solution for hard coded problem
std::string Animal::get_category_to_string() const {
    for(const auto& pair : category_names_){
        if(pair.first == get_category()){
            return pair.second;
        }
    }
    return "Unknown";
}

const std::vector<std::pair<HealthStatus, std::string>> Animal::health_names_ = {
    {HealthStatus::Healthy, "Healthy"},
    {HealthStatus::In_Treatment, "In Treatment"},
    {HealthStatus::Sick, "Sick"}
};

std::string Animal::get_health_status_to_string() const {
    for(const auto& pair : health_names_){
        if(pair.first == get_health_status()){
            return pair.second;
        }
    }
    return "None";
}
