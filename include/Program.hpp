#ifndef Program_HPP
#define Program_HPP

#include <SFML/Graphics.hpp>

/// @brief Top level class responsible for handling the main program loop
class Program
{
public:
  /// @brief The various states the program can be in
  enum class State
  {
    gameplay,
    terminated
  };

public:
  /// @brief Constructs the program and initialises a SFML window
  Program();

  /// @brief Handles SFML events
  void events();
  /// @brief Updates the program variables and classes
  void update();
  /// @brief Renders program components to the screen
  void render();

  /// @brief Returns whether the program has finished running
  /// @return `true` if the program is no longer running, `false` otherwise
  bool hasTerminated();

  /// @brief Returns the correction needed to clip some entity within a boundary
  /// @param centre - The world position of the entity
  /// @param padding - Some padding representing how much space the entity takes up from its central position
  /// @param bounds - The boundary that the entity will be clipped within
  /// @return The correction vector that can be applied to the given centre position to clip the entity within the boundary
  sf::Vector2f clipWithinBounds(sf::Vector2f centre, sf::Vector2f padding, sf::IntRect bounds);

private:
  /// @brief The current status of the program
  State state = State::terminated;

  /// @brief The main SFML rendering window
  sf::RenderWindow window;

	/// @brief The view that represents the camera of the program
	sf::View view;

  // The following varaibles are for testing purposes only
  bool wPressed = false;
  bool sPressed = false;
  bool dPressed = false;
  bool aPressed = false;

  sf::Texture tileTex;
  sf::Texture charTex;

  sf::IntRect worldRect;
  sf::Sprite tile;
  sf::Sprite character;
};


#endif