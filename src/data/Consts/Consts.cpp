#include "Consts.h"

namespace Snake::Data {
const int Consts::MAP_X = 17;
const int Consts::MAP_Y = 15;

const int Consts::CELL_RESOLUTION_X = 5;
const int Consts::CELL_RESOLUTION_Y = 2;

const int Consts::CHAR_RESOLUTION_X = 9;
const int Consts::CHAR_RESOLUTION_Y = 16;


const int Consts::RESOLUTION_X = MAP_X * CELL_RESOLUTION_X + 1;
const int Consts::RESOLUTION_Y = MAP_Y * CELL_RESOLUTION_Y + 1;
} // namespace Snake::Data


