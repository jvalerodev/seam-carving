#include <Carve.hpp>
#include <Color.hpp>
#include <Energy.hpp>
#include <Seam.hpp>

Carve::Carve(const std::vector<std::vector<Color>> &_pixels) noexcept
    : pixels(_pixels)
{
}

std::vector<std::vector<Color>> Carve::remove_n_lowest_seams(std::size_t num_seams_to_remove) const noexcept
{
  std::vector<std::vector<Color>> new_image(pixels);

  for (int num = 0; num < num_seams_to_remove; num++)
  {
    std::vector<std::vector<unsigned>> energy_matrix = Energy(new_image).compute_energy();
    std::vector<std::size_t> optimal_path = Seam(energy_matrix).compute_vertical_seams().first;
    new_image = remove_seam(new_image, optimal_path);
  }

  return new_image;
}

std::vector<std::vector<Color>> Carve::remove_seam(const std::vector<std::vector<Color>> &image, const std::vector<std::size_t> &seam_cols) const noexcept
{
  long height = image.size();
  long width = image[0].size();

  std::vector<std::vector<Color>> new_image(height);

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (j != seam_cols[i])
      {
        new_image[i].push_back(image[i][j]);
      }
    }
  }

  return new_image;
}