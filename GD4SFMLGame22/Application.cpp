#include "Application.hpp"

class TitleState;
class MenuState;
class GameState;
class PauseState;

const sf::Time Application::kTimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: m_window(sf::VideoMode(640, 480), "States", sf::Style::Close),
	m_stack(State::Context(m_window, m_textures, m_fonts, m_player)),
	m_statistics_numframes(0)
{
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		time_since_last_update += elapsedTime;

		while (time_since_last_update > kTimePerFrame)
		{
			time_since_last_update -= kTimePerFrame;
			ProcessInput();
			Update(kTimePerFrame);
		}
		UpdateStatistics(elapsedTime);
		Render();
	}
}

void Application::ProcessInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		m_stack.HandleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Application::Update(sf::Time delta_time)
{
	m_stack.Update(delta_time);
}

void Application::Render()
{
	m_window.clear();
	m_stack.Draw();

	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_statistics_text);
	m_window.display();
}

void Application::UpdateStatistics(sf::Time elapsed_time)
{
	m_statistics_updatetime += elapsed_time;
	m_statistics_numframes += 1;

	if (m_statistics_updatetime >= sf::seconds(1.0f))
	{
		m_statistics_text.setString(
			"Frames / Second = " + std::to_string(m_statistics_numframes) + "\n" +
			"Time / Update = " + std::to_string(m_statistics_updatetime.asMicroseconds() / m_statistics_numframes) + "us");

		m_statistics_updatetime -= sf::seconds(1.0f);
		m_statistics_numframes = 0;
	}
}

void Application::RegisterStates()
{
	m_stack.RegisterState<TitleState>(StateID::kTitle);
	m_stack.RegisterState<MenuState>(StateID::KMenu);
	m_stack.RegisterState<GameState>(StateID::kGame);
	m_stack.RegisterState<PauseState>(StateID::kPause);
}