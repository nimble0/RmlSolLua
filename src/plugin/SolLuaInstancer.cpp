#include "SolLuaInstancer.h"

#include "SolLuaDocument.h"
#include "SolLuaEventListener.h"


namespace Rml::SolLua
{

	ElementPtr SolLuaDocumentElementInstancer::InstanceElement(Element* parent, const String& tag, const XMLAttributes& attributes)
	{
		return ElementPtr(new SolLuaDocument(m_state, tag));
	}

	void SolLuaDocumentElementInstancer::ReleaseElement(Element* element)
	{
	}


	EventListener* SolLuaEventListenerInstancer::InstanceEventListener(const String& value, Element* element)
	{
		return new SolLuaEventListener(m_state, value, element);
	}

} // end namespace Rml::SolLua
