#include "Program.hpp"

Program::Program()
{
  sf::Vector2i windowDim = 60 * sf::Vector2i(16, 9);
	window.create(sf::VideoMode(windowDim.x, windowDim.y), "It Takes A Village", sf::Style::Close);

  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  window.setPosition(sf::Vector2i((desktop.width - window.getSize().x) / 2, (desktop.height - window.getSize().y) / 2));

	window.setKeyRepeatEnabled(false);

  window.setVerticalSyncEnabled(true);

	view = window.getDefaultView();

  worldRect = sf::IntRect(-1000, -1000, 2000, 2000);

	tileTex.loadFromFile("assets/testTile.png");
  tile = sf::Sprite(tileTex);
  
	charTex.loadFromFile("assets/testChar.png");
  character = sf::Sprite(charTex);
  character.setOrigin(0.5f * (sf::Vector2f)charTex.getSize());

  state = State::gameplay;
}

void Program::events()
{
	sf::Event e;
	
	while (window.pollEvent(e)) 
	{
		switch (e.type) 
		{
		case sf::Event::Closed: 
      state = State::terminated;
      return;

      case sf::Event::KeyPressed:
        switch (e.key.code)
        {
          case sf::Keyboard::Escape:
            state = State::terminated;
            break;
          case sf::Keyboard::W:
            wPressed = true;
            break;
          case sf::Keyboard::S:
            sPressed = true;
            break;
          case sf::Keyboard::D:
            dPressed = true;
            break;
          case sf::Keyboard::A:
            aPressed = true;
            break;
          default:
            break;
        }
        break;

      case sf::Event::KeyReleased:
        switch (e.key.code)
        {
          case sf::Keyboard::W:
            wPressed = false;
            break;
          case sf::Keyboard::S:
            sPressed = false;
            break;
          case sf::Keyboard::D:
            dPressed = false;
            break;
          case sf::Keyboard::A:
            aPressed = false;
            break;
          default:
            break;
        }
        break;

		default:
			break;
		}
	}
}

void Program::update()
{
  if (hasTerminated())
    return;

  sf::Vector2f move = sf::Vector2f(dPressed - aPressed, sPressed - wPressed);

  character.move((500.0f / 60.0f) * move);

  // Clip character within world bounds
  sf::Vector2f pos = character.getPosition();

  pos += clipWithinBounds(pos, 0.5f * (sf::Vector2f)charTex.getSize(), worldRect);
  character.setPosition(pos);

  // Clip camera within world bounds
  pos += clipWithinBounds(pos, 0.5f * view.getSize(), worldRect);

  view.setCenter(pos);
  window.setView(view);
}

void Program::render()
{
  if (hasTerminated())
    return;

	window.clear({255, 255, 255});

  for (int y = worldRect.top; y < worldRect.top + worldRect.height; y += tileTex.getSize().y)
  {
    for (int x = worldRect.left; x < worldRect.left + worldRect.width; x += tileTex.getSize().x)
    {
      tile.setPosition(sf::Vector2f(x, y));
      window.draw(tile);
    }
  }

  window.draw(character);

  window.display();
}

bool Program::hasTerminated()
{
  return state == State::terminated;
}

sf::Vector2f Program::clipWithinBounds(sf::Vector2f centre, sf::Vector2f padding, sf::IntRect bounds)
{
  sf::Vector2f correction(0, 0);

  if (centre.y - padding.y < bounds.top)
    correction.y = bounds.top - (centre.y - padding.y);

  else if (centre.y + padding.y > bounds.top + bounds.height)
    correction.y = (bounds.top + bounds.height) - (centre.y + padding.y);

  if (centre.x - padding.x < bounds.left)
    correction.x = bounds.left - (centre.x - padding.x);

  else if (centre.x + padding.x > bounds.left + bounds.width)
    correction.x = (bounds.left + bounds.width) - (centre.x + padding.x);
  
  return correction;
}
