#pragma once
#include "State.hpp"
#include "StateID.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private  sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

public:
	explicit StateStack(State::Context context);
	template <typename T>
	void RegisterState(StateID state_id);
	void Update(sf::Time dt);
	void Draw();
	void HandleEvent(const sf::Event& event);
	void PushState(StateID state_id);
	void PopState();
	void ClearStates();
	bool IsEmpty() const;

private:
	State::Ptr CreateState(StateID state_id);
	void ApplyPendingChanges();

private:
	struct PendingChange
	{
		explicit PendingChange(Action action, StateID state_id = StateID::kNone);
		Action action;
		StateID state_id;
	};

private:
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pending_list;
	State::Context m_context;
	std::map<StateID, std::function<State::Ptr>> m_state_factory;
};

/*template <typename T>
void StateStack::RegisterState(StateID state_id)
{
	m_state_factory[state_id] = [this]()
	{
		return State::Ptr(new(*this, m_context));
	}
}*/