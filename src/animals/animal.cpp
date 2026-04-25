#include "animal.hpp"

Animal::Animal(uint64_t id, const std::string& name, const std::string& species, uint64_t age, double weight, const std::string& enclosure, HealthStatus health_status=HealthStatus::Healthy){
    id_ = id;
    name_ = name;
    species_ = species;
    age_ = age;
    weight_ = weight;
    enclosure_ = enclosure;
    health_status_ = health_status;
    ticks_ = 0;   
}

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