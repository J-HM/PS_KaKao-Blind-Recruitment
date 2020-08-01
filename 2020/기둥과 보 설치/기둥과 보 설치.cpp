#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> pillarss;
vector<vector<int>> beamss;

bool isBeampossible(int x, int y)
{
  if (pillarss[y - 1][x] == 1)
    return true;
  if (pillarss[y - 1][x + 1] == 1)
    return true;
  if (beamss[y][x - 1] == 1 && beamss[y][x + 1] == 1 && x > 0)
    return true;
  return false;
}

bool isPillarpossible(int x, int y)
{
  if (y == 0)
    return true;
  if (pillarss[y - 1][x] == 1)
    return true;
  if (beamss[y][x] == 1)
    return true;
  if (beamss[y][x - 1] == 1 && x > 0)
    return true;
  return false;
}

void installBeam(int x, int y)
{
  if (isBeampossible(x, y)) 
    beamss[y][x] = 1;
}

void installPillar(int x, int y)
{
  if (isPillarpossible(x, y)) 
    pillarss[y][x] = 1;
}

void removeBeam(int x, int y)
{
  beamss[y][x] = 0;
  if (beamss[y][x + 1] && !isBeampossible(x + 1, y))     // 오른쪽 끝 부분에 있는 보가 조건 불충족
    beamss[y][x] = 1;
  if (beamss[y][x - 1] && !isBeampossible(x - 1, y))     // 왼쪽 끝 부분에 있는 보가 조건 불충족
    beamss[y][x] = 1;
  if (pillarss[y][x] && !isPillarpossible(x, y))         // 오른쪽 끝 부분 위에 있는 기둥이 조건 불충족
    beamss[y][x] = 1;
  if (pillarss[y][x + 1] && !isPillarpossible(x + 1, y)) // 왼쪽 끝 부분 위에 있는 기둥이 조건 불충족
    beamss[y][x] = 1;
}

void removePillar(int x, int y)
{
  pillarss[y][x] = 0;
  if (beamss[y + 1][x] && !isBeampossible(x, y + 1))         // 위-오른쪽 부분에 있는 보가 조건 불충족
    pillarss[y][x] = 1;
  if (beamss[y + 1][x - 1] && !isBeampossible(x - 1, y + 1)) // 위-왼쪽 부분에 있는 보가 조건 불충족
    pillarss[y][x] = 1;
  if (pillarss[y + 1][x] && !isPillarpossible(x, y + 1))     // 위쪽에 있는 기둥이 조건 불충족
    pillarss[y][x] = 1;
}

void print(int n)
{
  cout << "BEAM: " << endl;
  for (int i = n; i >= 0; i--)
  {
    auto beams = beamss[i];
    for (auto beam : beams)
      cout << beam << " ";
    cout << endl;
  }

  cout << endl << "PILLAR: " << endl;
  for (int i = n - 1; i >= 0; i--)
  {
    auto pillars = pillarss[i];
    for (auto pillar : pillars)
      cout << pillar << " ";
    cout << endl;
  }
}

vector<vector<int>> buildStructures(int n)
{
  vector<vector<int>> structures;
  for (int x = 0; x < n + 1; x++)
  {
    for (int y = 0; y < n + 1; y++)
    {
      if (pillarss[y][x] == 1)
        structures.push_back({x, y, 0});
      if (beamss[y][x] == 1)
        structures.push_back({x, y, 1});
    }
  }
  return structures;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frames)
{
  beamss.resize(n + 1, vector<int> (n + 1, 0));
  pillarss.resize(n + 1, vector<int> (n + 1, 0));
  for (auto build_frame : build_frames)
  {
    int x = build_frame.at(0);
    int y = build_frame.at(1);
    vector<int> structure;
    if (build_frame.at(2))   // Beam
    {
      if (build_frame.at(3)) // Beam - Install
        installBeam(x, y);
      else                   // Beam - Remove
        removeBeam(x, y);
    }

    else                     // Pillar
    {
      if (build_frame.at(3)) // Pillar - Install
        installPillar(x, y);
      else                   // Pillar - Remove
        removePillar(x, y);
    }
  }
  print(n);
  vector<vector<int>> structures = buildStructures(n);
  return structures;
}


int main()
{
  int n;
  vector<vector<int>> build_frames;

  n = 5;
	build_frames = {{0,0,0,1},{2,0,0,1},{4,0,0,1},{0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},{2,0,0,0},{1,1,1,0},{2,2,0,1}};
  // build_frames = {{1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1},{0,1,0,1}};
  // build_frames = {{0,0,0,1},{0,1,0,1},{0,2,0,1},
  //                 {2,0,0,1},{2,1,0,1},{2,2,0,1},
  //                 {4,0,0,1},{4,1,0,1},{4,2,0,1},
  //                 {0,3,1,1},{1,3,1,1},{2,3,1,1},{3,3,1,1},
  //                 {0,1,1,1},{1,1,1,1},{2,1,1,1},{3,1,1,1},
  //                 {2,0,0,0}};
  auto structures = solution(n, build_frames);

  for (auto structure : structures)
  {
    cout << "[";
    cout << structure.at(0) << ", ";
    cout << structure.at(1) << ", ";
    cout << structure.at(2);
    cout << "]";
    cout << endl;
  }
      
  return 0;
}