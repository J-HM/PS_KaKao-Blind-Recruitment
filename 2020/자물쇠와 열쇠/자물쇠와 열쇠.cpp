#include <iostream>
#include <vector>
#include <algorithm>


using std::vector;

struct Position
{
  short int x_;
  short int y_;
  Position operator-(const Position& position) const
  {
    short int x = x_ - position.x_;
    short int y = y_ - position.y_;
    return Position{x, y};
  }
  const bool operator==(const Position& position)
  {
    return x_ == position.x_ && y_ == position.y_;
  }
  const bool isInRange(short int range)
  {
    if (x_ >=0 &&  y_ >=0 && x_ < range && y_ < range) return true;
    else return false;
  }
};

vector<Position> getPositionsFromMatrix(vector<vector<int>> matrix, int value)
{
  vector<Position> positions;
  auto size = matrix.size();
  for (short int y = 0; y < size; y++)
    for (short int x = 0; x < size; x++)
      if (matrix.at(y).at(x) == value) 
        positions.push_back(Position{x, y});
  return positions;
}

void rotateMatrix(vector<vector<int>>& matrix)
{
  auto size = matrix.size();
  for (int y = 0; y < size / 2; y++) 
  {
    for (int x = y; x < size - y - 1; x++) 
    {
      int temp = matrix[y][x];
      matrix[y][x] = matrix[x][size - 1 - y];
      matrix[x][size - 1 - y] = matrix[size - 1 - y][size - 1 - x];
      matrix[size - 1 - y][size - 1 - x]  = matrix[size - 1 - x][y];
      matrix[size - 1 - x][y] = temp;
    }
  }
}

bool unlock(vector<Position> lock_positions, vector<Position> key_positions, short int lock_size)
{
  if (lock_positions.size() == 0) // Already unlocked
    return true; 
  if (lock_positions.size() > key_positions.size()) // Spin of the lock is greater than spin of the key
    return false;
  for (auto lock_position : lock_positions)
  {
    for (auto key_position : key_positions)
    {
      int matched_position_number = 0;
      auto delta_position = key_position - lock_position;
      for (auto shifted_key_position : key_positions)
      {
        shifted_key_position = shifted_key_position - delta_position;
        if (shifted_key_position.isInRange(lock_size)) // When Shifted Key Position is In Range
        {
          auto fine_value = std::find(lock_positions.begin(), lock_positions.end(), shifted_key_position);
          if (fine_value == lock_positions.end())
          {
            matched_position_number = 0;
            break;
          }
          else
          {
            matched_position_number++;
          }
        }
        if (matched_position_number == lock_positions.size()) return true;
      }
    }
  }
  return false;
}

bool isUnlockable(vector<vector<int>> key, vector<vector<int>> lock)
{
  auto lock_positions = getPositionsFromMatrix(lock, 0);
  for (int i = 0; i < 4; i++)
  {
    auto key_positions = getPositionsFromMatrix(key, 1);
    if (unlock(lock_positions, key_positions, lock.size())) return true;;
    rotateMatrix(key);
  }
  return false;
}

int main()
{
  vector<vector<int>> key;
  vector<vector<int>> lock;

  key = {{1, 1, 1},  
         {1, 1, 1},  
         {1, 1, 1}};

  lock = {{1, 1, 1, 1}, 
          {1, 1, 1, 1}, 
          {1, 1, 0, 0}, 
          {1, 1, 0, 1}};

  std::cout << isUnlockable(key, lock) << std::endl;
  return 0;
}