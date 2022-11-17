#include <cmath>

#include <Color.hpp>
#include <Energy.hpp>

Energy::Energy(const std::vector<std::vector<Color>> &_pixels) noexcept
    : pixels(_pixels)
{
}

std::vector<std::vector<unsigned>> Energy::compute_energy() const noexcept
{
  long height = pixels.size();
  long width = pixels[0].size();
  std::vector<std::vector<unsigned>> energy_matrix(height, std::vector<unsigned>(width, 0));

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      unsigned energy = energy_at(i, j);
      energy_matrix[i][j] = energy;
    }
  }

  return energy_matrix;
}

std::vector<std::vector<Color>> Energy::energy_to_colors(const std::vector<std::vector<unsigned>> &energy)
{
  std::vector<std::vector<Color>> colors{energy.size(), std::vector<Color>{}};

  unsigned max_energy = 0;

  for (std::size_t i = 0; i < energy.size(); ++i)
  {
    for (unsigned e : energy[i])
    {
      if (e > max_energy)
      {
        max_energy = e;
      }
    }
  }

  for (std::size_t i = 0; i < energy.size(); ++i)
  {
    for (unsigned e : energy[i])
    {
      // Normalize the energy value to be in [0, 255]
      uint8_t energy_normalized = round(255.f * float(e) / float(max_energy));
      // Convert the value into a grayscale color.
      colors[i].push_back(Color{energy_normalized, energy_normalized, energy_normalized});
    }
  }

  return colors;
}

unsigned Energy::energy_at(std::size_t i, std::size_t j) const noexcept
{
  long height = pixels.size();
  long width = pixels[0].size();

  int rx = 0, gx = 0, bx = 0;
  int ry = 0, gy = 0, by = 0;

  // X gradient
  if (j == 0) // Left of the image
  {
    rx = pixels[i][j].get_red() - pixels[i][j + 1].get_red();
    gx = pixels[i][j].get_green() - pixels[i][j + 1].get_green();
    bx = pixels[i][j].get_blue() - pixels[i][j + 1].get_blue();
  }
  else if (j == width - 1) // Rigth of the image
  {
    rx = pixels[i][j].get_red() - pixels[i][j - 1].get_red();
    gx = pixels[i][j].get_green() - pixels[i][j - 1].get_green();
    bx = pixels[i][j].get_blue() - pixels[i][j - 1].get_blue();
  }
  else
  {
    rx = pixels[i][j - 1].get_red() - pixels[i][j + 1].get_red();
    gx = pixels[i][j - 1].get_green() - pixels[i][j + 1].get_green();
    bx = pixels[i][j - 1].get_blue() - pixels[i][j + 1].get_blue();
  }

  // Y gradient
  if (i == 0) // Top of the image
  {
    ry = pixels[i][j].get_red() - pixels[i + 1][j].get_red();
    gy = pixels[i][j].get_green() - pixels[i + 1][j].get_green();
    by = pixels[i][j].get_blue() - pixels[i + 1][j].get_blue();
  }
  else if (i == height - 1) // Bottom of the image
  {
    ry = pixels[i][j].get_red() - pixels[i - 1][j].get_red();
    gy = pixels[i][j].get_green() - pixels[i - 1][j].get_green();
    by = pixels[i][j].get_blue() - pixels[i - 1][j].get_blue();
  }
  else
  {
    ry = pixels[i - 1][j].get_red() - pixels[i + 1][j].get_red();
    gy = pixels[i - 1][j].get_green() - pixels[i + 1][j].get_green();
    by = pixels[i - 1][j].get_blue() - pixels[i + 1][j].get_blue();
  }

  unsigned x_grad = pow(rx, 2) + pow(gx, 2) + pow(bx, 2);
  unsigned y_grad = pow(ry, 2) + pow(gy, 2) + pow(by, 2);

  return x_grad + y_grad;
}