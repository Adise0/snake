#include <string>
#include <vector>

using namespace std;

namespace Snake {
namespace Rendering {
class Sprite {
public:
  vector<string> data;
  short width;
  short height;

  Sprite(vector<string> data, short width, short height) {
    this->data = data;
    this->width = width;
    this->height = height;
  }
};

} // namespace Rendering
} // namespace Snake
