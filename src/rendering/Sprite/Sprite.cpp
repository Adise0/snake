#include "Sprite.h"
#include <string>
#include <vector>

using namespace std;

namespace Snake {
namespace Rendering {

Sprite::Sprite(vector<u32string> drawing) : drawing(drawing) {
  this->height = drawing.size();

  short maxWidth = 0;
  for (u32string line : drawing) {
    if (line.length() > maxWidth) maxWidth = line.length();
  }
  this->width = maxWidth;
}
} // namespace Rendering

} // namespace Snake
