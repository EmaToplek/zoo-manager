#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include<iostream>
#include<string>
#include <cstdint>
// Animal base class + Mammal, Fish subclasses

enum class HealthStatus{
    Healthy,
    Sick,
    In_Treatment,
};

enum class AnimalCategory{
    Mammal,
    Fish,
    Bird,
    Reptile,
    Amphibian,
};

class Animal{
    protected:
      uint64_t id_;
      std::string name_;
      std::string species_;
      uint64_t age_;
      double weight_;
      std::string enclosure_;
      HealthStatus health_status_;
      std::string feeding_type_;     
      std::string habitat_;           
      double min_enclosure_size_;
      uint64_t ticks_;

    public:
        Animal(uint64_t id,const std::string& name, const std::string& species, uint64_t age, 
            double weight, const std::string& enclosure, HealthStatus health_status,
            const std::string& feeding_type, const std::string& habitat, double min_enclosure_size);

        virtual ~Animal()=default;
        
        uint64_t get_id()const{return id_;}
        
        const std::string& get_name()const {return name_;}
        void set_name(const std::string& name) {name_ = name;}
        
        const std::string& get_species()const {return species_;}
        void set_species(const std::string& species) {species_ = species;}
        
        uint64_t get_age()const {return age_;}
        void set_age(uint64_t age) {age_ = age;}
        
        double get_weight()const {return weight_;}
        void set_weight(double weight) {weight_ = weight;}
        
        const std::string& get_enclosure()const {return enclosure_;}
        void set_enclosure(const std::string& enclosure) {enclosure_ = enclosure;}
        
        HealthStatus get_health_status()const {return health_status_;}
        void set_health_status(HealthStatus health_status) {health_status_ = health_status;}

        std::string get_feeding_type() const {return feeding_type_;}

        std::string get_habitat() const {return habitat_;}

        double get_min_enclosure_size() const {return min_enclosure_size_;}
        std::string get_health_status_to_string() const;

        virtual AnimalCategory  get_category() const=0;  // Abstract class
        std::string get_category_to_string();
        // healthy to sick its happening on the GUI
        static constexpr uint64_t sickt_to_treatment_tick = 3;
        static constexpr uint64_t treatment_to_healthy_tick = 2;
        void tickhealth();  // wxTimer calls this.
};

#endif //ANIMAL_HPP
