#include "fish.hpp"

AnimalCategory Fish::get_category() const {
    return AnimalCategory::Fish;
}

std::string Fish::get_feeding_type() const {
    return feeding_type_;
}

std::string Fish::get_habitat() const {
    return habitat_;
}

double Fish::get_min_enclosure_size() const {
    return min_enclosure_size_;
}




