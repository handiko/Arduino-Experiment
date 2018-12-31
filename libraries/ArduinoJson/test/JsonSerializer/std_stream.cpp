// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>
#include <sstream>

TEST_CASE("operator<<(std::ostream)") {
  DynamicJsonDocument doc;
  std::ostringstream os;

  SECTION("JsonVariant containing false") {
    JsonVariant variant = doc.to<JsonVariant>();

    variant.set(false);
    os << variant;

    REQUIRE("false" == os.str());
  }

  SECTION("JsonVariant containing string") {
    JsonVariant variant = doc.to<JsonVariant>();

    variant.set("coucou");
    os << variant;

    REQUIRE("\"coucou\"" == os.str());
  }

  SECTION("JsonObject") {
    JsonObject object = doc.to<JsonObject>();
    object["key"] = "value";

    os << object;

    REQUIRE("{\"key\":\"value\"}" == os.str());
  }

  SECTION("JsonObjectSubscript") {
    JsonObject object = doc.to<JsonObject>();
    object["key"] = "value";

    os << object["key"];

    REQUIRE("\"value\"" == os.str());
  }

  SECTION("JsonArray") {
    JsonArray array = doc.to<JsonArray>();
    array.add("value");

    os << array;

    REQUIRE("[\"value\"]" == os.str());
  }

  SECTION("JsonArraySubscript") {
    JsonArray array = doc.to<JsonArray>();
    array.add("value");

    os << array[0];

    REQUIRE("\"value\"" == os.str());
  }
}
