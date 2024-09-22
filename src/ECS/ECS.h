#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
#include<bitset>
#include<array>
#include<string>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity = nullptr;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
	virtual ~Component() {};
	virtual std::string getKind() const { return "base"; }
};

class Entity {
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray{};
	ComponentBitSet componentBitSet{};
	GroupBitSet groupBitSet{};

public:
	Entity(Manager& man) : manager{ man } {}
	void update() {
		for (auto& c : components) c->update();
	}
	void draw(bool debug) {
		for (auto& c : components) {
			if (!(c->getKind() == "collider") || debug) {
				c->draw();
			}
		}
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group g) {
		return groupBitSet[g];
	}
	void addGroup(Group g);
	void delGroup(Group g) {
		groupBitSet[g] = false;
	}

	template <typename T>
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T>
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	void update() {
		for (auto& e : entities) e->update();
	}

	void draw(bool debug) {
		for (auto& e : entities) e->draw(debug);
	}

	void refresh() {
		for (auto i{ 0u }; i < maxGroups; ++i) {
			auto& v = groupedEntities[i];
			v.erase(
				std::remove_if(
					std::begin(v), std::end(v),
					[i](Entity* ent) {
						return !ent->isActive() || !ent->hasGroup(i);
					}
				), std::end(v)
			);
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void addToGroup(Entity* ent, Group g) {
		groupedEntities[g].emplace_back(ent);
	}

	std::vector<Entity*>& getGroup(Group g) {
		return groupedEntities[g];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};