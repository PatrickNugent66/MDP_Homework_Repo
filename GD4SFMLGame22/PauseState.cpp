#include "PauseState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context),
	m_option_index(0)
{
	sf::Texture& texture = context.textures->Get(Textures::kPauseScreen);
	sf::Font& font = context.fonts->Get(Fonts::kMain);

	m_background_sprite.setTexture(texture);

	//A simple menu
	sf::Text resume_option;
	resume_option.setFont(font);
	resume_option.setString("Resume");
	Utility::CenterOrigin(resume_option);
	resume_option.setPosition(context.window->getView().getSize() / 2.f);
	m_options.emplace_back(resume_option);

	sf::Text exit_option;
	exit_option.setFont(font);
	exit_option.setString("Exit");
	Utility::CenterOrigin(exit_option);
	exit_option.setPosition(resume_option.getPosition() + sf::Vector2f(0.f, 30.f));
	m_options.emplace_back(exit_option);


	UpdateOptionText();
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_background_sprite);
	for (const sf::Text& text : m_options)
	{
		window.draw(text);
	}
}

bool PauseState::Update(sf::Time dt)
{
	return true;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_option_index == static_cast<int>(Options::Resume))
		{
			RequestStackPop();
		}
		else if (m_option_index == static_cast<int>(Options::Exit))
		{
			RequestStackPop();
			RequestStackPop();
			RequestStackPush(StateID::kTitle);
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		if (m_option_index > 0)
		{
			m_option_index--;
		}
		else
		{
			m_option_index = m_options.size() - 1;
		}
		UpdateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (m_option_index < m_options.size() - 1)
		{
			m_option_index++;
		}
		else
		{
			m_option_index = 0;
		}
		UpdateOptionText();
	}

	return true;
}

void PauseState::UpdateOptionText()
{
	if (m_options.empty())
	{
		return;
	}

	for (sf::Text& text : m_options)
	{
		text.setFillColor(sf::Color::Green);
	}

	m_options[m_option_index].setFillColor(sf::Color::Blue);
}
