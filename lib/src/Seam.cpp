#include <iostream>
#include <Color.hpp>
#include <Seam.hpp>

unsigned min_between_two(const unsigned a, const unsigned b) noexcept;
unsigned min_between_three(const unsigned a, const unsigned b, const unsigned c) noexcept;
void get_cumulative_energy(const std::vector<std::vector<unsigned>> &energy, std::vector<std::vector<unsigned>> &cumulative_energy, long width, int i, int j) noexcept;
std::pair<std::size_t, unsigned> get_min_energy_pair(std::vector<std::vector<unsigned>> cumulative_energy, long width, long height) noexcept;

Seam::Seam(const std::vector<std::vector<unsigned>> &_energy) noexcept
    : energy(_energy)
{
}

std::pair<std::size_t, unsigned> Seam::compute_vertical_seam() const noexcept
{
  long height = energy.size();
  long width = energy[0].size();
  std::vector<std::vector<unsigned>> cumulative_energy(height, std::vector<unsigned>(width, 0));

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      get_cumulative_energy(energy, cumulative_energy, width, i, j);
    }
  }

  return get_min_energy_pair(cumulative_energy, width, height);
}

std::pair<std::vector<std::size_t>, unsigned> Seam::compute_vertical_seams() const noexcept
{
  // long height = energy.size();
  // long width = energy[0].size();

  // double prev_pixel_energy = 0;
  // std::vector<std::vector<unsigned>> cumulative_energy(height, std::vector<unsigned>(width, 0));

  // for (int i = height - 1; i >= 0; i--)
  // {
  //   for (int j = 0; j < width; j++)
  //   {
  //     unsigned pixel_energy = energy[i][j];

  //     if (i == height - 1)
  //     {
  //       cumulative_energy[i][j] = pixel_energy;
  //       continue;
  //     }

  //     if (j == 0)
  //     {
  //       cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i + 1][j], cumulative_energy[i + 1][j + 1]);
  //     }
  //     else if (j == width - 1)
  //     {
  //       cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i + 1][j], cumulative_energy[i + 1][j - 1]);
  //     }
  //     else
  //     {
  //       cumulative_energy[i][j] = pixel_energy + min_between_three(cumulative_energy[i + 1][j - 1], cumulative_energy[i + 1][j], cumulative_energy[i + 1][j + 1]);
  //     }
  //   }
  // }

  return std::make_pair(std::vector<std::size_t>{}, 0);
}

std::vector<std::vector<Color>> Seam::min_seam_to_colors(const std::vector<std::vector<Color>> &pixels, std::size_t end_j) noexcept
{
  long h = pixels.size();
  long w = pixels[0].size();

  std::vector<std::vector<Color>> new_pixels{pixels};

  std::size_t min_j = std::max(long(end_j) - 5, 0L);
  std::size_t max_j = std::min(long(end_j) + 5, w - 1);

  std::size_t min_i = std::max(h - 11, 0L);

  for (std::size_t i = min_i; i < h; ++i)
  {
    for (std::size_t j = min_j; j <= max_j; ++j)
    {
      new_pixels[i][j] = Color(255, 0, 0);
    }
  }

  return new_pixels;
}

std::vector<std::vector<Color>> Seam::min_seams_to_colors(const std::vector<std::vector<Color>> &pixels, const std::vector<std::size_t> &seam_cols) noexcept
{
  long h = pixels.size();
  long w = pixels[0].size();

  std::vector<std::vector<Color>> new_pixels{pixels};

  for (std::size_t i = 0; i < seam_cols.size(); ++i)
  {

    std::size_t min_j = std::max(long(seam_cols[i]) - 2, 0L);
    std::size_t max_j = std::min(long(seam_cols[i]) + 2, w - 1);

    for (std::size_t j = min_j; j <= max_j; ++j)
    {
      new_pixels[i][j] = Color(255, 0, 0);
    }
  }

  return new_pixels;
}

unsigned min_between_two(const unsigned a, const unsigned b) noexcept
{
  return std::min(a, b);
}

unsigned min_between_three(const unsigned a, const unsigned b, const unsigned c) noexcept
{
  return std::min(a, std::min(b, c));
}

void get_cumulative_energy(const std::vector<std::vector<unsigned>> &energy, std::vector<std::vector<unsigned>> &cumulative_energy, long width, int i, int j) noexcept
{
  unsigned pixel_energy = energy[i][j];

  if (i == 0)
  {
    cumulative_energy[i][j] = pixel_energy;
    return;
  }

  if (j == 0)
  {
    cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i - 1][j], cumulative_energy[i - 1][j + 1]);
  }
  else if (j == width - 1)
  {
    cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i - 1][j], cumulative_energy[i - 1][j - 1]);
  }
  else
  {
    cumulative_energy[i][j] = pixel_energy + min_between_three(cumulative_energy[i - 1][j - 1], cumulative_energy[i - 1][j], cumulative_energy[i - 1][j + 1]);
  }

  return;
}

std::pair<std::size_t, unsigned> get_min_energy_pair(std::vector<std::vector<unsigned>> cumulative_energy, long width, long height) noexcept
{
  long min_energy = cumulative_energy[height - 1][0];
  int index = 0;

  for (int i = 0; i < width; i++)
  {
    if (cumulative_energy[height - 1][i] < min_energy)
    {
      min_energy = cumulative_energy[height - 1][i];
      index = i;
    }
  }

  return std::make_pair(index, min_energy);
}