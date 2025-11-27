#pragma once
#include <string>
#include <vector>



using namespace std;

namespace Snake {
namespace Rendering {
class Sprite {
public:
  vector<u32string> drawing;
  short height;
  short width;
  Sprite(vector<u32string> drawing);
};
} // namespace Rendering
} // namespace Snake
