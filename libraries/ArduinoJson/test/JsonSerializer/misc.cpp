#include <ArduinoJson.h>
#include <catch.hpp>
#include <limits>

template <typename T>
void check(T value, const std::string &expected) {
  DynamicJsonDocument doc;
  doc.to<JsonVariant>().set(value);
  char buffer[256] = "";
  size_t returnValue = serializeJson(doc, buffer, sizeof(buffer));
  REQUIRE(expected == buffer);
  REQUIRE(expected.size() == returnValue);
}

TEST_CASE("serializeJson(JsonObjectSubscript)") {
  DynamicJsonDocument doc;
  deserializeJson(doc, "{\"hello\":42}");
  JsonObject obj = doc.as<JsonObject>();
  std::string result;

  serializeJson(obj["hello"], result);

  REQUIRE(result == "42");
}

TEST_CASE("serializeJson(JsonArraySubscript)") {
  DynamicJsonDocument doc;
  deserializeJson(doc, "[42]");
  JsonArray arr = doc.as<JsonArray>();
  std::string result;

  serializeJson(arr[0], result);

  REQUIRE(result == "42");
}

TEST_CASE("serializeJson(JsonVariantSubscript)") {
  DynamicJsonDocument doc;
  deserializeJson(doc, "[42]");
  JsonVariant var = doc.as<JsonVariant>();
  std::string result;

  serializeJson(var[0], result);

  REQUIRE(result == "42");
}
