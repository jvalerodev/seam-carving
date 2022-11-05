#include <cmath>

#include <Color.hpp>
#include <Energy.hpp>

Energy::Energy(const std::vector<std::vector<Color>>& _pixels) noexcept
  : pixels(_pixels)
{

}

std::vector<std::vector<unsigned>> Energy::compute_energy() const noexcept
{
  // TODO

  return std::vector<std::vector<unsigned>>{};
}

std::vector<std::vector<Color>> Energy::energy_to_colors(const std::vector<std::vector<unsigned>>& energy)
{
  std::vector<std::vector<Color>> colors{energy.size(), std::vector<Color>{}};

  unsigned max_energy = 0;

  for (std::size_t i = 0; i < energy.size(); ++i)
  {
    for (unsigned e: energy[i])
    {
      if (e > max_energy)
      {
        max_energy = e;
      }
    }
  }

  for (std::size_t i = 0; i < energy.size(); ++i)
  {
    for (unsigned e: energy[i])
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
  // TODO

  return 0;
}