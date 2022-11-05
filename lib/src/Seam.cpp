#include <Color.hpp>
#include <Seam.hpp>

Seam::Seam(const std::vector<std::vector<unsigned>> &_energy) noexcept
    : energy(_energy)
{
}

std::pair<std::size_t, unsigned> Seam::compute_vertical_seam() const noexcept
{
  // TODO

  return std::make_pair(0, 0);
}

std::pair<std::vector<std::size_t>, unsigned> Seam::compute_vertical_seams() const noexcept
{
  // TODO

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
