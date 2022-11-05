#include <Color.hpp>
#include <Energy.hpp>
#include <TestUtils.hpp>

using namespace std;

struct Data
{
  static const vector<vector<Color>> pixels;

  static const vector<vector<unsigned>> expected_energy;
};

const vector<vector<Color>> Data::pixels = 
{
  {Color{10, 20, 30}, Color{124, 35, 78}, Color{234,  255, 90}, Color{56, 32, 89}},
  {Color{26, 85, 168}, Color{123, 0, 58}, Color{255, 255, 255}, Color{45, 98, 125}},
  {Color{0, 0, 0}, Color{55, 155, 255}, Color{0, 100, 0}, Color{55, 55, 55}}
};

const vector<vector<unsigned>> Data::expected_energy
{
  {39050, 110627, 32420, 87187},
  {30134, 139400, 107058, 87335},
  {128200, 77458, 204075, 14924},
};

void test_energy()
{
  cout << "Given the pixels ";
  print_matrix(Data::pixels, cout);
  cout << "When the method compute_energy is called, it should return ";
  print_matrix(Data::expected_energy, cout);

  Energy energy{Data::pixels};
  assert_equal_matrix(energy.compute_energy(), Data::expected_energy);
}

int main()
{
  cout << "Running test cases for class Energy\n";
  test_energy();
  cout << "Everything ok!\n";
  return EXIT_SUCCESS;
}
