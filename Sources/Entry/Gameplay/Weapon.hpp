#pragma once

#include <Game/ScriptObject.hpp>
#include <Kunlaboro/Component.hpp>
#include <Math/Vec2.hpp>
#include <Util/Time.hpp>

#include <unordered_map>

namespace Gameplay
{

	namespace Weapon
	{

		class Manager
		{
		public:
			static Manager& Singleton();

			Game::ScriptObject* createProjectile(Kunlaboro::EntitySystem& es, const std::string& name);
			Game::ScriptObject* createWeapon(Kunlaboro::EntitySystem& es, const std::string& name);

			void addProjectile(const std::string& name, asIObjectType* obj);
			void addWeapon(const std::string& name, asIObjectType* obj);

		private:
			std::unordered_map<std::string, asIObjectType*> mProjectiles;
			std::unordered_map<std::string, asIObjectType*> mWeapons;
		};

		class Missile : public Kunlaboro::Component
		{
		public:
			Missile();
			~Missile() = default;

			void addedToEntity();

		private:
			void tick(const Util::Timespan& dt);

			Math::Vec2 mPosition, mVelocity;
		};

		enum Type
		{
			Type_Beam,
			Type_Cone,
			Type_Projectile
		};

	}

}
