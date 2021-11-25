#pragma once
#include "State.hpp"
#include "Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);
	virtual void Draw();
	virtual void AssignControls(int control);
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

private:
	sf::Sprite m_background_sprite;
	GUI::Container m_gui_container;
};
