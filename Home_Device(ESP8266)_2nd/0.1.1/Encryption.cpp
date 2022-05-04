#include "Encryption.h"

char hexTable[17] = "0123456789ABCDEF";
String mrand(size_t n) {
  String str;
  for (size_t i = 0; i < n; i++)
    str += hexTable[rand() % 16];
  return str;
};
String UUID() {
  return mrand(8) + '-' + mrand(4) + '-' + mrand(4) + '-' + mrand(4) + '-' + mrand(12);
};

void encrypt(String value, JsonObject object) {
  String key = UUID();
  size_t len_key = key.length();
  size_t len_value = value.length();
  for (size_t i = 0, j = 0; i < len_value; i++, j++) {
    if (j == len_key)
      j = 0;
    value[i] ^= key[j];
  }
  for (size_t i = 0, j = len_key - 1; i < len_value; i++, j--) {
    value[i] ^= key[j];
    if (j == 0)
      j = len_key;
  }
  object["key"] = key;
  object["value"] = value;
}

String decrypt(String key, String value) {
  size_t len_value = value.length();
  size_t len_key = key.length();
  for (size_t i = 0, j = len_key - 1; i < len_value; i++, j--) {
    value[i] ^= key[j];
    if (j == 0)
      j = len_key;
  }
  for (size_t i = 0, j = 0; i < len_value; i++, j++) {
    if (j == len_key)
      j = 0;
    value[i] ^= key[j];
  }
  return value;
}

String decrypt(JsonObject object) {
  return decrypt(object["key"], object["value"]);
}
