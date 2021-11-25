#include "SettingsState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Button.hpp"
#include "Player.hpp"


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Texture& texture = context.textures->Get(Textures::kTitleScreen);

	m_background_sprite.setTexture(texture);

	auto up_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	up_button->setPosition(100, 100);
	up_button->SetText("Move up");
	up_button->SetCallback([this]()
		{
			AssignControls(1);
		});

	auto down_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	down_button->setPosition(100, 150);
	down_button->SetText("Move down");
	down_button->SetCallback([this]()
		{
			AssignControls(2);
		});

	auto left_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	left_button->setPosition(100, 200);
	left_button->SetText("Move left");
	left_button->SetCallback([this]()
		{
			AssignControls(3);
		});

	auto right_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	right_button->setPosition(100, 250);
	right_button->SetText("Move right");
	right_button->SetCallback([this]()
		{
			AssignControls(4);
		});

	auto back_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	back_button->setPosition(100, 350);
	back_button->SetText("Back to main menu");
	back_button->SetCallback([this]()
		{
			RequestStackPop();
		});

	m_gui_container.Pack(up_button);
	m_gui_container.Pack(down_button);
	m_gui_container.Pack(left_button);
	m_gui_container.Pack(right_button);
	m_gui_container.Pack(back_button);
}

void SettingsState::AssignControls(int control)
{
	Context context = this->GetContext();

	//Get input from the user here and store the inputted key
	sf::Keyboard::Key input = sf::Keyboard::W; //example of input
	//input = ;

	//use int passed in to determine which PlayerAction to change
	if (control == 1)
	{
		context.player->AssignKey(PlayerAction::kMoveUp, input);
	}
	else if (control == 2)
	{
		context.player->AssignKey(PlayerAction::kMoveDown, input);
	}
	else if (control == 3)
	{
		context.player->AssignKey(PlayerAction::kMoveLeft, input);
	}
	else
	{
		context.player->AssignKey(PlayerAction::kMoveRight, input);
	}
}

void SettingsState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_background_sprite);
	window.draw(m_gui_container);
}

bool SettingsState::Update(sf::Time dt)
{
	return true;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	m_gui_container.HandleEvent(event);
	return false;
}


