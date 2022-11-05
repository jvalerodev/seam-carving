#include <iostream>

#include <TestUtils.hpp>
#include <Color.hpp>

using namespace std;

void test_color_red_component(const Color& color, uint8_t expected)
{
  cout << "When the method get_red() is called, it should return the value " << int(expected) << endl;
  assert_equal(color.get_red(), expected);
}

void test_color_green_component(const Color& color, uint8_t expected)
{
  cout << "When the method get_green() is called, it should return the value " << int(expected) << endl;
  assert_equal(color.get_green(), expected);
}

void test_color_blue_component(const Color& color, uint8_t expected)
{
  cout << "When the method get_blue() is called, it should return the value " << int(expected) << endl;
  assert_equal(color.get_blue(), expected);
}

void test_color_string(const Color& color, const std::string& expected)
{
  cout << "When the method to_string() is called, it should return the value " << expected << endl;
  assert_equal(color.to_string(), expected);
}

void test_color()
{
  cout << "Given a color with the RGB values (45, 10, 90)\n";
  Color color(45, 10, 90);
  test_color_red_component(color, 45);
  test_color_green_component(color, 10);
  test_color_blue_component(color, 90);
  test_color_string(color, "Color(45,10,90)");
}

int main()
{
  cout << "Running test cases for class Color\n";
  test_color();
  cout << "Everything ok!\n";
  return EXIT_SUCCESS;
}