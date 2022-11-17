#pragma once

#include <vector>

class Color;

/**
 * @brief The second step in the seam carving algorithm: finding the energy of the lowest-energy seam in an image.
 *
 * This class contains the operations to compute and visualize the lowest-energy seam. *
 */
class Seam
{
public:
  Seam(const std::vector<std::vector<unsigned>> &_energy) noexcept;

  /**
   * @brief Find the lowest-energy vertical seam given the energy of each pixel in the input image.
   *
   * The image energy should have been computed before by the `compute_energy` method in the `Energy` class.
   *
   * This is the first version of the seam finding algorithm. It implements the recurrence relation directly, outputting the energy of the lowest-energy
   * seam and the j-coordinate (the column) where that seam ends.
   *
   * @return a pair with the j-coordinate where the lowest-energy seam ends and the total energy of that seam.
   */
  std::pair<std::size_t, unsigned> compute_vertical_seam() const noexcept;

  /**
   * @brief Find the lowest-energy vertical seam given the energy of each pixel in the input image.
   *
   * The image energy should have been computed before by the `compute_energy` method in the `Energy` class.
   *
   * This is the second version of the seam finding algorithm. In addition to storing and finding the lowest-energy value of any seam,
   * it also stores back pointers used to reconstruct the lowest-energy seam.
   *
   *
   * @return a pair with the list of x-coordinates forming the lowest-energy seam, starting at the top of the image.
   * and the total energy of that seam.
   */
  std::pair<std::vector<std::size_t>, unsigned> compute_vertical_seams() const noexcept;

  /**
   * @brief Draws a red box at the bottom of the image at the specified x-coordinate.
   *
   * This is done to visualize approximately where a vertical seam ends.
   *
   * @param pixels The matrix of pixels.
   * @param min_end_j The j-coordinate where the lowest-energy seam ends.
   * @return A new matrix of pixels with the red box.
   */
  static std::vector<std::vector<Color>> min_vertical_seam_to_colors(const std::vector<std::vector<Color>> &pixels, std::size_t min_end_j) noexcept;

  /**
   * @brief Draws a red line on the image along the given seam.
   *
   * This is done to visualize where the seam is.
   *
   * @param pixels The matrix of pixels.
   * @param seam_cols the list of j-coordinates forming the lowest-energy seam.
   * @return std::vector<std::vector<Color>>
   */
  static std::vector<std::vector<Color>> min_seams_to_colors(const std::vector<std::vector<Color>> &pixels, const std::vector<std::size_t> &seam_cols) noexcept;

  /**
   * @brief Find the lowest-energy horizontal seam given the energy of each pixel in the input image.
   *
   * The image energy should have been computed before by the `compute_energy` method in the `Energy` class.
   *
   * This is the first version of the seam finding algorithm. It implements the recurrence relation directly, outputting the energy of the lowest-energy
   * seam and the i-coordinate (the row) where that seam ends.
   *
   * @return a pair with the i-coordinate where the lowest-energy seam ends and the total energy of that seam.
   */
  std::pair<std::size_t, unsigned> compute_horizontal_seam() const noexcept;

  /**
   * @brief Draws a red box at the right of the image at the specified y-coordinate.
   *
   * This is done to visualize approximately where a vertical seam ends.
   *
   * @param pixels The matrix of pixels.
   * @param min_end_i The i-coordinate where the lowest-energy seam ends.
   * @return A new matrix of pixels with the red box.
   */
  static std::vector<std::vector<Color>> min_horizontal_seam_to_colors(const std::vector<std::vector<Color>> &pixels, std::size_t min_end_i) noexcept;

private:
  const std::vector<std::vector<unsigned>> &energy;
};
