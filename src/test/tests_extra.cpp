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
gi