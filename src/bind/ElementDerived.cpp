#include "bind.h"

#include "plugin/SolLuaEventListener.h"

#include <unordered_map>


namespace Rml::SolLua
{

	void bind_element_derived(sol::state_view& lua)
	{

		lua.new_usertype<Rml::ElementText>("ElementText", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementText>("sol.ElementText"),
			// G
			"text", sol::property(&Rml::ElementText::GetText, &Rml::ElementText::SetText),

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);

		///////////////////////////

		lua.new_usertype<Rml::ElementDataGrid>("ElementDataGrid", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementDataGrid>("sol.ElementDataGrid"),
			// M
			"AddColumn", sol::resolve<bool(const Rml::String&, const Rml::String&, float, const Rml::String&)>(&Rml::ElementDataGrid::AddColumn),
			"SetDataSource", &Rml::ElementDataGrid::SetDataSource,

			// G
			"rows", sol::readonly_property(&getIndexedTable<Rml::ElementDataGridRow, Rml::ElementDataGrid, &Rml::ElementDataGrid::GetRow, &Rml::ElementDataGrid::GetNumRows>),

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);

		lua.new_usertype<Rml::ElementDataGridRow>("ElementDataGridRow", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementDataGridRow>("sol.ElementDataGridRow"),
			// M
			//--
			"RefreshRows", &Rml::ElementDataGridRow::RefreshRows,

			// G+S
			"expanded", sol::property(&Rml::ElementDataGridRow::IsRowExpanded, [](Rml::ElementDataGridRow& self, bool expanded) { if (expanded) self.ExpandRow(); else self.CollapseRow(); }),

			// G
			"parent_relative_index", sol::readonly_property(&Rml::ElementDataGridRow::GetParentRelativeIndex),
			"table_relative_index", sol::readonly_property(&Rml::ElementDataGridRow::GetTableRelativeIndex),
			"parent_row", sol::readonly_property(&Rml::ElementDataGridRow::GetParentRow),
			"parent_grid", sol::readonly_property(&Rml::ElementDataGridRow::GetParentGrid),

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);

		//--
		lua.new_usertype<Rml::ElementDataGridCell>("ElementDataGridCell", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementDataGridCell>("sol.ElementDataGridCell"),
			// G
			//--
			"column", sol::readonly_property(&Rml::ElementDataGridCell::GetColumn),

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);

		///////////////////////////

		lua.new_usertype<Rml::ElementTabSet>("ElementTabSet", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementTabSet>("sol.ElementTabSet"),
			// M
			"SetPanel", sol::resolve<void(int, const Rml::String&)>(&Rml::ElementTabSet::SetPanel),
			"SetTab", sol::resolve<void(int, const Rml::String&)>(&Rml::ElementTabSet::SetTab),
			//--
			"RemoveTab", &Rml::ElementTabSet::RemoveTab,

			// G+S
			"active_tab", sol::property(
				[](const Rml::ElementTabSet& self) -> int
				{
					return to_lua_index(self.GetActiveTab());
				},
				[](Rml::ElementTabSet& self, int i)
				{
					self.SetActiveTab(from_lua_index(i));
				}
			),

			// G
			"num_tabs", &Rml::ElementTabSet::GetNumTabs,

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);

		///////////////////////////

		//--
		lua.new_usertype<Rml::ElementProgress>("ElementProgress", sol::no_constructor,
			sol::meta_function::to_string, pointer_to_string<Rml::ElementProgress>("sol.ElementProgress"),
			// G+S
			//--
			"value", sol::property(&Rml::ElementProgress::GetValue, &Rml::ElementProgress::SetValue),
			"max", sol::property(&Rml::ElementProgress::GetMax, &Rml::ElementProgress::SetMax),

			// B
			sol::base_classes, sol::bases<Rml::Element>()
		);
	}

} // end namespace Rml::SolLua
