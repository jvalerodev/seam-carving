#include <Carve.hpp>
#include <Color.hpp>
#include <Energy.hpp>
#include <Seam.hpp>

Carve::Carve(const std::vector<std::vector<Color>>& _pixels) noexcept
  : pixels(_pixels)
{
  
}

std::vector<std::vector<Color>> Carve::remove_n_lowest_seams(std::size_t num_seams_to_remove) const noexcept
{
  // TODO

  return std::vector<std::vector<Color>>{};
}

std::vector<std::vector<Color>> Carve::remove_seam(const std::vector<std::vector<Color>>& image, const std::vector<std::size_t>& seam_cols) const noexcept
{
  // TODO

  return std::vector<std::vector<Color>>{};
}
