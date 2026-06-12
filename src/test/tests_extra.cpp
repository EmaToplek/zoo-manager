#include "catch_amalgamated.hpp"
#include "../animals/animal.hpp"
#include "../animals/mammal.hpp"
#include "../animals/fish.hpp"
#include "../animals/bird.hpp"
#include "../animals/reptile.hpp"
#include "../animals/amphibian.hpp"
#include "../app/animal_manager.hpp"
#include <iostream>

TEST_CASE("Bird getters and special_info_map", "[Bird]") {
    std::map<std::string, std::string> info = {{"can_fly", "Yes"}, {"wingspan", "1.2"}};
    Bird bird(3, "Tweety", "Canary", 2, 0.05, "Aviary", HealthStatus::Healthy, info);

    REQUIRE(bird.get_id() == 3);
    REQUIRE(bird.get_name() == "Tweety");
    REQUIRE(bird.get_species() == "Canary");
    REQUIRE(bird.get_category() == AnimalCategory::Bird);
    REQUIRE(bird.get_category_to_string() == "Bird");
    REQUIRE(bird.get_feeding_type() == "Seeds/Insects");
    REQUIRE(bird.get_habitat() == "Aviary");
    REQUIRE(bird.get_min_enclosure_size() == Catch::Approx(50.0));
    REQUIRE(bird.get_special_info_map() == info);
}

TEST_CASE("Reptile getters and special_info_map", "[Reptile]") {
    std::map<std::string, std::string> info = {{"is_venomous", "No"}, {"body_length", "2.5"}};
    Reptile reptile(4, "Rex", "Iguana", 5, 3.2, "Terrarium", HealthStatus::Sick, info);

    REQUIRE(reptile.get_id() == 4);
    REQUIRE(reptile.get_name() == "Rex");
    REQUIRE(reptile.get_species() == "Iguana");
    REQUIRE(reptile.get_category() == AnimalCategory::Reptile);
    REQUIRE(reptile.get_category_to_string() == "Reptile");
    REQUIRE(reptile.get_feeding_type() == "Insects/Small animals");
    REQUIRE(reptile.get_habitat() == "Jungle Terrarium");
    REQUIRE(reptile.get_min_enclosure_size() == Catch::Approx(30.0));
    REQUIRE(reptile.get_special_info_map() == info);
}

TEST_CASE("Category count - Bird, Fish, Reptile", "[Animal manager][category count]") {
  Animal_Manager manager;

  manager.add_animal(new Bird(1, "Tweety", "Canary", 1, 0.05, "Aviary", HealthStatus::Healthy));
  manager.add_animal(new Fish(2, "Nemo", "Clownfish", 1, 0.5, "Aquarium", HealthStatus::Healthy));
  manager.add_animal(new Reptile(3, "Rex", "Iguana", 2, 3.0, "Terrarium", HealthStatus::Sick));

  uint64_t mammal_count, fish_count, bird_count, reptile_count, amphibian_count;
  manager.category_count(mammal_count, fish_count, bird_count, reptile_count, amphibian_count);

  REQUIRE(mammal_count == 0);
  REQUIRE(fish_count == 1);
  REQUIRE(bird_count == 1);
  REQUIRE(reptile_count == 1);
  REQUIRE(amphibian_count == 0);
}

TEST_CASE("Health count - all three statuses", "[Animal manager][health count]") {
  Animal_Manager manager;

  manager.add_animal(new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy));
  manager.add_animal(new Mammal(2, "Mia", "Tiger", 3, 150.0, "Savannah", HealthStatus::Sick));
  manager.add_animal(new Mammal(3, "Bobo", "Bear", 5, 200.0, "Forest", HealthStatus::In_Treatment));
  manager.add_animal(new Mammal(4, "Lala", "Wolf", 2, 40.0, "Forest", HealthStatus::Healthy));

  uint64_t healthy, sick, in_treatment;
  manager.health_count(healthy, sick, in_treatment);

  REQUIRE(healthy == 2);
  REQUIRE(sick == 1);
  REQUIRE(in_treatment == 1);
}

TEST_CASE("Remove animal - existing and non-existing id", "[Animal manager][remove_animal]") {
  Animal_Manager manager;
  manager.add_animal(new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy));
  manager.add_animal(new Mammal(2, "Mia", "Tiger", 3, 150.0, "Savannah", HealthStatus::Healthy));

  REQUIRE(manager.total_count() == 2);

  // removing an existing id
  bool removed = manager.remove_animal(1);
  REQUIRE(removed == true);
  REQUIRE(manager.total_count() == 1);
  REQUIRE(manager.get_all_animals().front()->get_id() == 2);

  // removing a non-existing id should not change anything
  bool removed_again = manager.remove_animal(999);
  REQUIRE(removed_again == false);
  REQUIRE(manager.total_count() == 1);
}

TEST_CASE("Search - by name and species, case-insensitive", "[Animal manager][search]") {
  Animal_Manager manager;
  manager.add_animal(new Mammal(1, "Leo", "Lion", 4, 192.0, "Savannah", HealthStatus::Healthy));
  manager.add_animal(new Mammal(2, "Mia", "Tiger", 3, 150.0, "Savannah", HealthStatus::Healthy));
  manager.add_animal(new Fish(3, "Nemo", "Clownfish", 1, 0.5, "Aquarium", HealthStatus::Healthy));

  // search by name (case-insensitive)
  auto by_name = manager.search("leo");
  REQUIRE(by_name.size() == 1);
  REQUIRE(by_name.front()->get_name() == "Leo");

  // search by species (case-insensitive, partial match)
  auto by_species = manager.search("CLOWN");
  REQUIRE(by_species.size() == 1);
  REQUIRE(by_species.front()->get_species() == "Clownfish");

  // search with no matching results
  auto no_match = manager.search("zebra");
  REQUIRE(no_match.empty());
}

TEST_CASE("Species list and default traits - known and unknown category", "[Animal manager][species.json]") {
  Animal_Manager manager;

  // known category must return a non-empty species list
  auto mammal_species = manager.get_species_for_category("Mammal");
  REQUIRE_FALSE(mammal_species.empty());

  // unknown category returns an empty vector
  auto unknown_species = manager.get_species_for_category("Dinosaur");
  REQUIRE(unknown_species.empty());

  // unknown category returns an empty default_traits map
  auto unknown_defaults = manager.get_default_traits("Dinosaur");
  REQUIRE(unknown_defaults.empty());
}

TEST_CASE("Add animal with position parameter inserts at correct index", "[Animal manager][add_animal][position]") {
  Animal_Manager manager;
  manager.add_animal(1, "Leo", "Lion", "Mammal", 4, 192.0, "Savannah", "Healthy");
  manager.add_animal(2, "Mia", "Tiger", "Mammal", 3, 150.0, "Savannah", "Healthy");

  // insert at position 1 (between Leo and Mia)
  manager.add_animal(3, "Bobo", "Bear", "Mammal", 5, 200.0, "Forest", "Sick", 1);

  REQUIRE(manager.total_count() == 3);
  REQUIRE(manager.get_all_animals()[0]->get_id() == 1);
  REQUIRE(manager.get_all_animals()[1]->get_id() == 3);
  REQUIRE(manager.get_all_animals()[2]->get_id() == 2);
}

TEST_CASE("Add animal with unknown category adds nothing", "[Animal manager][add_animal][invalid category]") {
  Animal_Manager manager;
  manager.add_animal(1, "Spike", "Unicorn", "Unicorn", 1, 50.0, "Meadow", "Healthy");

  REQUIRE(manager.total_count() == 0);
  REQUIRE(manager.get_all_animals().empty());
}

TEST_CASE("Add animal (Bird) via string overload preserves special_info", "[Animal manager][add_animal][special_info]") {
  Animal_Manager manager;
  std::map<std::string, std::string> info = {{"can_fly", "Yes"}, {"wingspan", "0.8"}};

  manager.add_animal(5, "Tweety", "Canary", "Bird", 2, 0.05, "Aviary", "Healthy", -1, info);

  REQUIRE(manager.total_count() == 1);
  Animal* a = manager.get_all_animals().front();
  REQUIRE(a->get_category() == AnimalCategory::Bird);
  REQUIRE(a->get_special_info_map() == info);
}