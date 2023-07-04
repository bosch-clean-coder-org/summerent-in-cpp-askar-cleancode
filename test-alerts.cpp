#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits high") {
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits Normal") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach according to limits too high") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("classifyTemperatureBreach according to limits too Low") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("classifyTemperatureBreach according to limits too high") {
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 42) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach according to limits too Low") {
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
}

TEST_CASE("checkAndAlert to controller according to limits too high") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING, "bosch"};
  checkAndAlert(TO_CONTROLLER, batteryChar, 50) ;
}

TEST_CASE("checkAndAlert to mail according to limits too low") {
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "bosch"};
  checkAndAlert(TO_EMAIL, batteryChar, -1) ;
}

TEST_CASE("checkAndAlert to controller according to limits Normal") {
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "bosch"};
  checkAndAlert(TO_EMAIL, batteryChar, 20);
}

