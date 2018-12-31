// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonObject::isNull()") {
  DynamicJsonDocument doc;

  SECTION("returns true") {
    JsonObject obj;
    REQUIRE(obj.isNull() == true);
  }

  SECTION("returns false") {
    JsonObject obj = doc.to<JsonObject>();
    REQUIRE(obj.isNull() == false);
  }
}

TEST_CASE("JsonObjectConst::isNull()") {
  DynamicJsonDocument doc;

  SECTION("returns true") {
    JsonObjectConst obj;
    REQUIRE(obj.isNull() == true);
  }

  SECTION("returns false") {
    JsonObjectConst obj = doc.to<JsonObject>();
    REQUIRE(obj.isNull() == false);
  }
}
