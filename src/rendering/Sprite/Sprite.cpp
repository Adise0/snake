#include "Sprite.h"
#include "iostream"
#include <string>
#include <vector>

using namespace std;

namespace Snake {
namespace Rendering {

Sprite::Sprite(short id, vector<u32string> drawing) : id(id), drawing(drawing) {
  this->height = drawing.size();

  short maxWidth = 0;
  for (u32string line : drawing) {
    if (line.length() > maxWidth) maxWidth = line.length();
  }
  this->width = maxWidth;

  // cout << "From sprite width:" << to_string(width) << " height " << to_string(height) << endl;
}
} // namespace Rendering

} // namespace Snake
