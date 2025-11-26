#include "Sprite.h"
#include <codecvt>
#include <iostream>

using namespace std;

namespace Snake {
namespace Rendering {
Sprite::Sprite(vector<string> data) : data(data) {
  height = data.size();

  short maxWidth = 0;
  for (string line : data) {
    wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
    u32string u32 = conv.from_bytes(line);

    cout << "Line width: " << u32.length() << line << endl;
    if (u32.length() > maxWidth) {
      maxWidth = u32.length();
    }
  }
  width = maxWidth;
}

vector<u32string> Sprite::GetStrings32() {
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  vector<u32string> result;

  for (string line : data) {
    u32string u32 = conv.from_bytes(line);
    result.push_back(u32);
  }

  return result;
}
} // namespace Rendering
} // namespace Snake
