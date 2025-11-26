#pragma once
#include <string>
#include <vector>

using namespace std;

namespace Snake {
namespace Rendering {
class Sprite {
public:
  vector<string> data;
  short height;
  short width;

  Sprite(vector<string> data);

  vector<u32string> GetStrings32();
};

} // namespace Rendering
} // namespace Snake
