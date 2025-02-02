#include "bind.h"

#include <functional>


namespace Rml::SolLua
{

	sol::object makeObjectFromVariant(const Rml::Variant* variant, sol::state_view s)
	{
		if (!variant) return sol::make_object(s, sol::nil);

		switch (variant->GetType())
		{
		case Rml::Variant::BOOL:
			return sol::make_object(s, variant->Get<bool>());
		case Rml::Variant::BYTE:
		case Rml::Variant::CHAR:
		case Rml::Variant::INT:
			return sol::make_object(s, variant->Get<int>());
		case Rml::Variant::INT64:
			return sol::make_object(s, variant->Get<int64_t>());
		case Rml::Variant::UINT:
			return sol::make_object(s, variant->Get<unsigned int>());
		case Rml::Variant::UINT64:
			return sol::make_object(s, variant->Get<uint64_t>());
		case Rml::Variant::FLOAT:
		case Rml::Variant::DOUBLE:
			return sol::make_object(s, variant->Get<double>());
		case Rml::Variant::COLOURB:
			return sol::make_object_userdata<Rml::Colourb>(s, variant->Get<Rml::Colourb>());
		case Rml::Variant::COLOURF:
			return sol::make_object_userdata<Rml::Colourf>(s, variant->Get<Rml::Colourf>());
		case Rml::Variant::STRING:
			return sol::make_object(s, variant->GetReference<Rml::String>());
		case Rml::Variant::VECTOR2:
			return sol::make_object_userdata<Rml::Vector2f>(s, variant->Get<Rml::Vector2f>());
		case Rml::Variant::VOIDPTR:
			return sol::make_object(s, variant->Get<void*>());
		default:
			return sol::make_object(s, sol::nil);
		}

		return sol::make_object(s, sol::nil);
	}

	Rml::Variant makeVariantFromObject(const sol::object& o)
	{
		switch (o.get_type())
		{
		case sol::type::string:
			return Rml::Variant(o.as<std::string>());
		case sol::type::number:
			return Rml::Variant(o.as<float>());
		case sol::type::boolean:
			return Rml::Variant(o.as<bool>());
		case sol::type::userdata:
		{
			if (auto c = o.as<sol::optional<Rml::Colourb>>(); c)
				return Rml::Variant(*c);
			else if (auto c = o.as<sol::optional<Rml::Colourf>>(); c)
				return Rml::Variant(*c);
			else if (auto c = o.as<sol::optional<Rml::Colourf>>(); c)
				return Rml::Variant(*c);
			else if (auto c = o.as<sol::optional<Rml::Vector2f>>(); c)
				return Rml::Variant(*c);
			else if (auto c = o.as<sol::optional<Rml::Vector3f>>(); c)
				return Rml::Variant(*c);
			else if (auto c = o.as<sol::optional<Rml::Vector4f>>(); c)
				return Rml::Variant(*c);
			else
				return Rml::Variant();
		}
		case sol::type::lightuserdata:
			return Rml::Variant(o.as<void*>());
		default:
			return Rml::Variant();
		}
	}


} // end namespace Rml::SolLua
