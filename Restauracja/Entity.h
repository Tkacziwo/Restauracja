#pragma once

namespace ent {
	class Entity
	{
	protected:

		int Id = NULL;

		Entity() {};

		Entity(int id) : Id(id) {};

	public:
		virtual std::string GetInfo() const noexcept = 0;
		virtual std::string GetPartialInfo() const noexcept = 0;
		virtual std::string DisplayTemplate() const noexcept = 0;
		virtual std::string DisplayPartialTemplate() const noexcept = 0;

		void SetId(int id)
		{
			Id = id;
		}

		int GetEntityId() const noexcept
		{
			return Id;
		}
	};
}