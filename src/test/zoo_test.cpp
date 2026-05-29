#include "catch_amalgamated.hpp"
#include "../animals/animal.hpp"
#include "../animals/mammal.hpp"
#include "../animals/fish.hpp"
#include "../animals/bird.hpp"
#include "../animals/reptile.hpp"
#include "../animals/amphibian.hpp"
#include "../app/animal_manager.hpp"
#include <iostream>

TEST_CASE("Animal Creation & test getters", "[Animal getters]") {
    Mammal mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy);
    REQUIRE(mammal.get_id() == 1);
    REQUIRE(mammal.get_name() == "Leo");
    REQUIRE(mammal.get_species() == "Lion");
    REQUIRE(mammal.get_age() == 4);
    REQUIRE(mammal.get_weight() == Catch::Approx(192.0));
    REQUIRE(mammal.get_enclosure() == "Savannah");
    REQUIRE(mammal.get_health_status() == HealthStatus::Healthy);
    REQUIRE(mammal.get_health_status_to_string() == "Healthy");
    REQUIRE(mammal.get_category() == AnimalCategory::Mammal);
    REQUIRE(mammal.get_category_to_string() == "Mammal");

    Fish fish(2, "Nemo", "Clownfish", 1, 0.5, "Aquarium", HealthStatus::Sick);
    REQUIRE(fish.get_id() == 2);
    REQUIRE(fish.get_name() == "Nemo");
    REQUIRE(fish.get_species() == "Clownfish");
    REQUIRE(fish.get_age() == 1);
    REQUIRE(fish.get_weight() == Catch::Approx(0.5));
    REQUIRE(fish.get_enclosure() == "Aquarium");
    REQUIRE(fish.get_health_status() == HealthStatus::Sick);
    REQUIRE(fish.get_health_status_to_string() == "Sick");
    REQUIRE(fish.get_category() == AnimalCategory::Fish);
    REQUIRE(fish.get_category_to_string() == "Fish");
}

TEST_CASE("Animal Creation & test setters", "[Animal setter]") {
    Mammal mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy);
    mammal.set_name("");
    mammal.set_species("Lion");
    mammal.set_age(4);
    mammal.set_weight(192.0);
    mammal.set_enclosure("Savannah");
    mammal.set_health_status(HealthStatus::Sick);

    REQUIRE(mammal.get_id() == 1);
    REQUIRE(mammal.get_name() == "");
    REQUIRE(mammal.get_species() == "Lion");
    REQUIRE(mammal.get_age() == 4);
    REQUIRE(mammal.get_weight() == Catch::Approx(192.0));
    REQUIRE(mammal.get_enclosure() == "Savannah");
    REQUIRE(mammal.get_health_status() == HealthStatus::Sick);
    REQUIRE(mammal.get_health_status_to_string() == "Sick");
    REQUIRE(mammal.get_category() == AnimalCategory::Mammal);
    REQUIRE(mammal.get_category_to_string() == "Mammal");

    Fish fish(2, "Nemo", "Clownfish", 1, 0.5, "Aquarium", HealthStatus::Sick);
    fish.set_name("");
    fish.set_species("Clownfish");
    fish.set_age(2);
    fish.set_weight(0.8);
    fish.set_enclosure("Aquarium");
    fish.set_health_status(HealthStatus::Sick);
    REQUIRE(fish.get_id() == 2);
    REQUIRE(fish.get_name() == "");
    REQUIRE(fish.get_species() == "Clownfish");
    REQUIRE(fish.get_age() == 2);
    REQUIRE(fish.get_weight() == Catch::Approx(0.8));
    REQUIRE(fish.get_enclosure() == "Aquarium");
    REQUIRE(fish.get_health_status() == HealthStatus::Sick);
    REQUIRE(fish.get_health_status_to_string() == "Sick");
    REQUIRE(fish.get_category() == AnimalCategory::Fish);
    REQUIRE(fish.get_category_to_string() == "Fish");
}

TEST_CASE("Test tickhealth healthy", "[tickhealth][healthy]") {
    Mammal mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy);
    for(size_t i = 0; i < 5; i++){
        mammal.tickhealth();
    }
    REQUIRE(mammal.get_health_status() == HealthStatus::Healthy);
}

TEST_CASE("Test tickhealth sick", "[tickhealth][sick]") {
    Mammal mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Sick);
    for(size_t i = 0; i < Animal::sick_to_treatment_tick; i++){
        mammal.tickhealth();
    }
    REQUIRE(mammal.get_health_status() == HealthStatus::In_Treatment);
}

TEST_CASE("Test tickhealth in treatment", "[tickhealth][In treatment]") {
    Mammal mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::In_Treatment);
    for(size_t i = 0; i < Animal::treatment_to_healthy_tick; i++){
        mammal.tickhealth();
    }
    REQUIRE(mammal.get_health_status() == HealthStatus::Healthy);
}

TEST_CASE("Animal manager start empty", "[Animal manager][Empty]") {
    Animal_Manager manager;
    REQUIRE(manager.get_all_animals().empty() == true);
}

TEST_CASE("Animal manager add one animal", "[Animal manager][add_animal]") {
    Animal_Manager manager;
    manager.add_animal(1, "Leo", "Lion", "Mammal", 4, 192.0, "Savannah", "In_Treatment");
    REQUIRE(manager.get_all_animals().size() == 1);
    REQUIRE(manager.get_all_animals().front()->get_id() == 1);
    REQUIRE(manager.get_all_animals().front()->get_category() == AnimalCategory::Mammal);
}
/*
TEST_CASE("Load animal", "[Animal manager][load_animal]") {
    //Count animals in data.json
    std::ifstream file("../data.json");
    nlohmann::json j;
    file >> j;
    std::size_t count = j.size();
    Animal_Manager manager;
    manager.load();
    REQUIRE(manager.get_all_animals().size() == count);
}
*/

TEST_CASE("Animal total count", "[Animal manager][total count]"){
    Animal_Manager manager;
    Mammal* mammal = new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::In_Treatment);
    REQUIRE(manager.total_count() == 0);
    manager.add_animal(mammal);
    REQUIRE(manager.total_count() == 1);
}

TEST_CASE("Category count", "[Animal manager][category count]") {
    Animal_Manager manager;
    Mammal* mammal = new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::In_Treatment);
    Amphibian* amphibian = new Amphibian(19, "Toad", "Amphibian", 4, 0.4, "Pond", HealthStatus::Sick);
    manager.add_animal(mammal);
    manager.add_animal(amphibian);
    uint64_t mammal_count = 0;
    uint64_t fish_count = 0;
    uint64_t amphibian_count = 0;
    uint64_t bird_count = 0;
    uint64_t reptile_count = 0;
    manager.category_count(mammal_count, fish_count, bird_count, reptile_count, amphibian_count);
    REQUIRE(mammal_count == 1);
    REQUIRE(fish_count == 0);
    REQUIRE(amphibian_count == 1);
    REQUIRE(reptile_count == 0);
    REQUIRE(bird_count == 0);
}
/*
TEST_CASE("Save animal", "[Animal manager][save_animal]") {
    Animal_Manager manager;
    Mammal* mammal = new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::In_Treatment);
    Amphibian* amphibian = new Amphibian(19, "Toad", "Amphibian", 4, 0.4, "Pond", HealthStatus::Sick);
    manager.add_animal(mammal);
    manager.add_animal(amphibian);
    manager.save();
    //Count animals in data.json
    
    std::ifstream file("../data.json");
    nlohmann::json j;
    file >> j;
    std::size_t count = j.size();
    REQUIRE(count == 2 );    
}
*/
TEST_CASE("Demo animal", "[Animal manager][load demo animals]") {
    Animal_Manager manager;
    std::filesystem::rename("../data.json", "data2.json");
    manager.load();
    CHECK(manager.total_count() == 2);
    std::filesystem::rename("data2.json", "../data.json");
}

