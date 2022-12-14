#include <Color.hpp>
#include <Seam.hpp>

unsigned min_between_two(const unsigned a, const unsigned b) noexcept;
unsigned min_between_three(const unsigned a, const unsigned b, const unsigned c) noexcept;

// Vertical functions
std::vector<std::vector<unsigned>> get_vertical_cumulative_energy_matrix(const std::vector<std::vector<unsigned>> &energy) noexcept;
std::pair<std::size_t, unsigned> get_min_vertical_energy_pixel(const std::vector<std::vector<unsigned>> &cumulative_energy) noexcept;
std::pair<std::vector<std::size_t>, unsigned> get_optimal_vertical_path(std::vector<std::vector<unsigned>> cumulative_energy) noexcept;

// Horizontal functions
std::vector<std::vector<unsigned>> get_horizontal_cumulative_energy_matrix(const std::vector<std::vector<unsigned>> &energy) noexcept;
std::pair<std::size_t, unsigned> get_min_horizontal_energy_pixel(const std::vector<std::vector<unsigned>> &cumulative_energy) noexcept;
std::pair<std::vector<std::size_t>, unsigned> get_optimal_horizontal_path(std::vector<std::vector<unsigned>> cumulative_energy) noexcept;

Seam::Seam(const std::vector<std::vector<unsigned>> &_energy) noexcept
    : energy(_energy)
{
}

std::pair<std::size_t, unsigned> Seam::compute_vertical_seam() const noexcept
{
  std::vector<std::vector<unsigned>> cumulative_energy = get_vertical_cumulative_energy_matrix(energy);

  return get_min_vertical_energy_pixel(cumulative_energy);
}

std::pair<std::vector<std::size_t>, unsigned> Seam::compute_vertical_seams() const noexcept
{
  std::vector<std::vector<unsigned>> cumulative_energy = get_vertical_cumulative_energy_matrix(energy);

  return get_optimal_vertical_path(cumulative_energy);
}

std::vector<std::vector<Color>> Seam::min_vertical_seam_to_colors(const std::vector<std::vector<Color>> &pixels, std::size_t end_j) noexcept
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

std::vector<std::vector<Color>> Seam::min_vertical_seams_to_colors(const std::vector<std::vector<Color>> &pixels, const std::vector<std::size_t> &seam_cols) noexcept
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

std::pair<std::size_t, unsigned> Seam::compute_horizontal_seam() const noexcept
{
  std::vector<std::vector<unsigned>> cumulative_energy = get_horizontal_cumulative_energy_matrix(energy);

  return get_min_horizontal_energy_pixel(cumulative_energy);
}

std::pair<std::vector<std::size_t>, unsigned> Seam::compute_horizontal_seams() const noexcept
{
  std::vector<std::vector<unsigned>> cumulative_energy = get_horizontal_cumulative_energy_matrix(energy);

  return get_optimal_horizontal_path(cumulative_energy);
}

std::vector<std::vector<Color>> Seam::min_horizontal_seam_to_colors(const std::vector<std::vector<Color>> &pixels, std::size_t end_i) noexcept
{
  long h = pixels.size();
  long w = pixels[0].size();

  std::vector<std::vector<Color>> new_pixels{pixels};

  std::size_t min_i = std::max(long(end_i) - 5, 0L);
  std::size_t max_i = std::min(long(end_i) + 5, w - 1);

  std::size_t min_j = std::max(w - 11, 0L);

  for (std::size_t j = min_j; j < w; ++j)
  {
    for (std::size_t i = min_i; i <= max_i; ++i)
    {
      new_pixels[i][j] = Color(255, 0, 0);
    }
  }

  return new_pixels;
}

std::vector<std::vector<Color>> Seam::min_horizontal_seams_to_colors(const std::vector<std::vector<Color>> &pixels, const std::vector<std::size_t> &seam_cols) noexcept
{
  long h = pixels.size();
  long w = pixels[0].size();

  std::vector<std::vector<Color>> new_pixels{pixels};

  for (std::size_t j = 0; j < seam_cols.size(); ++j)
  {
    std::size_t min_i = std::max(long(seam_cols[j]) - 2, 0L);
    std::size_t max_i = std::min(long(seam_cols[j]) + 2, w - 1);

    for (std::size_t i = min_i; i <= max_i; ++i)
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

std::vector<std::vector<unsigned>> get_vertical_cumulative_energy_matrix(const std::vector<std::vector<unsigned>> &energy) noexcept
{
  long height = energy.size();
  long width = energy[0].size();
  std::vector<std::vector<unsigned>> cumulative_energy(height, std::vector<unsigned>(width, 0));

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      unsigned pixel_energy = energy[i][j];

      if (i == 0)
      {
        cumulative_energy[i][j] = pixel_energy;
        continue;
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
    }
  }

  return cumulative_energy;
}

std::pair<std::size_t, unsigned> get_min_vertical_energy_pixel(const std::vector<std::vector<unsigned>> &cumulative_energy) noexcept
{
  long height = cumulative_energy.size();
  long width = cumulative_energy[0].size();

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

std::pair<std::vector<std::size_t>, unsigned> get_optimal_vertical_path(std::vector<std::vector<unsigned>> cumulative_energy) noexcept
{
  long height = cumulative_energy.size();
  long width = cumulative_energy[0].size();

  std::pair<std::size_t, unsigned> min_energy_pixel_pair = get_min_vertical_energy_pixel(cumulative_energy);
  std::size_t index = min_energy_pixel_pair.first;
  unsigned min_energy = min_energy_pixel_pair.second;

  std::vector<std::size_t> optimal_pixel_path(height, 0);
  optimal_pixel_path[height - 1] = index;

  for (int i = height - 1; i > 0; i--)
  {
    if (index == 0) // Left
    {
      if (cumulative_energy[i - 1][index] > cumulative_energy[i - 1][index + 1]) // Top vs. Top-Right
        index++;
    }
    else if (index == width - 1) // Right
    {
      if (cumulative_energy[i - 1][index] > cumulative_energy[i - 1][index - 1]) // Top vs. Top-Left
        index--;
    }
    else if (cumulative_energy[i - 1][index] > cumulative_energy[i - 1][index - 1]) // Top vs. Top-Left
    {
      if (cumulative_energy[i - 1][index - 1] < cumulative_energy[i - 1][index + 1]) // Top-Left vs. Top-Right
        index--;
      else
        index++;
    }
    else
    {
      if (cumulative_energy[i - 1][index] > cumulative_energy[i - 1][index + 1]) // Top vs. Top-Right
        index++;
    }

    optimal_pixel_path[i - 1] = index; // Save path
  }

  return std::make_pair(optimal_pixel_path, min_energy);
}

std::vector<std::vector<unsigned>> get_horizontal_cumulative_energy_matrix(const std::vector<std::vector<unsigned>> &energy) noexcept
{
  long height = energy.size();
  long width = energy[0].size();
  std::vector<std::vector<unsigned>> cumulative_energy(height, std::vector<unsigned>(width, 0));

  for (int j = 0; j < width; j++)
  {
    for (int i = 0; i < height; i++)
    {
      unsigned pixel_energy = energy[i][j];

      if (j == 0)
      {
        cumulative_energy[i][j] = pixel_energy;
        continue;
      }

      if (i == 0)
      {
        cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i][j - 1], cumulative_energy[i + 1][j - 1]);
      }
      else if (i == height - 1)
      {
        cumulative_energy[i][j] = pixel_energy + min_between_two(cumulative_energy[i][j - 1], cumulative_energy[i - 1][j - 1]);
      }
      else
      {
        cumulative_energy[i][j] = pixel_energy + min_between_three(cumulative_energy[i - 1][j - 1], cumulative_energy[i][j - 1], cumulative_energy[i + 1][j - 1]);
      }
    }
  }

  return cumulative_energy;
}

std::pair<std::size_t, unsigned> get_min_horizontal_energy_pixel(const std::vector<std::vector<unsigned>> &cumulative_energy) noexcept
{
  long height = cumulative_energy.size();
  long width = cumulative_energy[0].size();

  long min_energy = cumulative_energy[0][width - 1];
  int index = 0;

  for (int i = 0; i < height; i++)
  {
    if (cumulative_energy[i][width - 1] < min_energy)
    {
      min_energy = cumulative_energy[i][width - 1];
      index = i;
    }
  }

  return std::make_pair(index, min_energy);
}

std::pair<std::vector<std::size_t>, unsigned> get_optimal_horizontal_path(std::vector<std::vector<unsigned>> cumulative_energy) noexcept
{
  long height = cumulative_energy.size();
  long width = cumulative_energy[0].size();

  std::pair<std::size_t, unsigned> min_energy_pixel_pair = get_min_horizontal_energy_pixel(cumulative_energy);
  std::size_t index = min_energy_pixel_pair.first;
  unsigned min_energy = min_energy_pixel_pair.second;

  std::vector<std::size_t> optimal_pixel_path(width, 0);
  optimal_pixel_path[width - 1] = index;

  for (int j = width - 1; j > 0; j--)
  {
    if (index == 0) // Top
    {
      if (cumulative_energy[index][j - 1] > cumulative_energy[index + 1][j - 1]) // Left vs. Bottom-Left
        index++;
    }
    else if (index == height - 1) // Bottom
    {
      if (cumulative_energy[index][j - 1] > cumulative_energy[index - 1][j - 1]) // Left vs. Top-Left
        index--;
    }
    else if (cumulative_energy[index][j - 1] > cumulative_energy[index - 1][j - 1]) // Left vs. Top-Left
    {
      if (cumulative_energy[index - 1][j - 1] < cumulative_energy[index + 1][j - 1]) // Top-Left vs. Bottom-Left
        index--;
      else
        index++;
    }
    else
    {
      if (cumulative_energy[index][j - 1] > cumulative_energy[index + 1][j - 1]) // Left vs. Bottom-Left
        index++;
    }

    optimal_pixel_path[j - 1] = index; // Save path
  }

  return std::make_pair(optimal_pixel_path, min_energy);
}