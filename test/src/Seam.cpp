#include <Seam.hpp>
#include <TestUtils.hpp>

using namespace std;

struct Data
{
  static const vector<vector<unsigned>> energy;
  static const pair<std::size_t, unsigned> expected_vertical_seam;
  static const pair<vector<std::size_t>, unsigned> expected_vertical_seams;
};

const vector<vector<unsigned>> Data::energy
{
  {39050, 110627, 32420, 87187},
  {30134, 139400, 107058, 87335},
  {128200, 77458, 204075, 14924},
};

const pair<std::size_t, unsigned> Data::expected_vertical_seam = make_pair(3, 134679);
const pair<vector<std::size_t>, unsigned> Data::expected_vertical_seams = make_pair(vector<std::size_t>{2, 3, 3}, 134679);

void test_min_seam()
{
  cout << "Given the energy ";
  print_matrix(Data::energy, cout);
  cout << "When the method compute_vertical_seam is called, it should return ";
  print_pair(Data::expected_vertical_seam, cout);

  Seam seam{Data::energy};
  auto result = seam.compute_vertical_seam();
  assert_equal(result.first, Data::expected_vertical_seam.first);
  assert_equal(result.second, Data::expected_vertical_seam.second);
}

void test_min_seams()
{
  cout << "Given the energy ";
  print_matrix(Data::energy, cout);
  cout << "When the method compute_vertical_seams is called, it should return (\n";
  print_vector(Data::expected_vertical_seams.first, cout);
  cout << Data::expected_vertical_seams.second << endl << ")\n";

  Seam seam{Data::energy};
  auto result = seam.compute_vertical_seams();
  assert_equal_vector(result.first, Data::expected_vertical_seams.first);
  assert_equal(result.second, Data::expected_vertical_seams.second);
}

int main()
{
  cout << "Running test cases for class Seam\n";
  test_min_seam();
  test_min_seams();
  cout << "Everything ok!\n";
  return EXIT_SUCCESS;
}