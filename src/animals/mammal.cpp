#include "mammal.hpp"

AnimalCategory Mammal::get_category() const {
    return AnimalCategory::Mammal;
}

std::string Mammal::get_feeding_type() const {
    return feeding_type_;
}

std::string Mammal::get_habitat() const {
    return habitat_;
}

double Mammal::get_min_enclosure_size() const {
    return min_enclosure_size_;
}



