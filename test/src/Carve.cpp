#include <Carve.hpp>
#include <Color.hpp>
#include <TestUtils.hpp>

using namespace std;

struct Data
{
  static const vector<vector<Color>> pixels;
  static constexpr std::size_t num_seams_to_remove = 1;

  static const vector<vector<Color>> expected_pixels;
};

const vector<vector<Color>> Data::pixels = 
{
  {Color{10, 20, 30}, Color{124, 35, 78}, Color{234,  255, 90}, Color{56, 32, 89}},
  {Color{26, 85, 168}, Color{123, 0, 58}, Color{255, 255, 255}, Color{45, 98, 125}},
  {Color{0, 0, 0}, Color{55, 155, 255}, Color{0, 100, 0}, Color{55, 55, 55}}
};

const vector<vector<Color>> Data::expected_pixels =
{
  {Color{10, 20, 30}, Color{124, 35, 78}, Color{56, 32, 89}},
  {Color{26, 85, 168}, Color{123, 0, 58}, Color{255, 255, 255}},
  {Color{0, 0, 0}, Color{55, 155, 255}, Color{0, 100, 0}}
};

void test_remove_n_lowest_seams()
{
  cout << "Given the pixels ";
  print_matrix(Data::pixels, cout);
  cout << "and " << Data::num_seams_to_remove << " seam" << (Data::num_seams_to_remove != 1 ? "s " : " ") << "to remove\n";
  cout << "When the method remove_n_lowest_seams is called, it should return ";
  print_matrix(Data::expected_pixels, cout);

  Carve carve{Data::pixels};
  auto result = carve.remove_n_lowest_seams(Data::num_seams_to_remove);
  assert_equal_matrix(result, Data::expected_pixels);
}

int main()
{
  cout << "Running test cases for class Carve\n";
  test_remove_n_lowest_seams();
  cout << "Everything ok!\n";
  return EXIT_SUCCESS;
}
