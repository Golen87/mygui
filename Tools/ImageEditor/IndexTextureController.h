/*!
	@file
	@author		Albert Semenov
	@date		07/2012
*/

#ifndef _b80becd5_97bb_4126_acb5_348f9b926682_
#define _b80becd5_97bb_4126_acb5_348f9b926682_

#include "IControlController.h"
#include "ScopeTextureControl.h"

namespace tools
{
	class IndexTextureController :
		public IControlController,
		public sigslot::has_slots<>
	{
	public:
		IndexTextureController();
		virtual ~IndexTextureController();

		virtual void setTarget(Control* _control);

		virtual void activate();
		virtual void deactivate();

	private:
		void notifyChangeDataSelector(Data* _data, bool _changeOnlySelection);
		void notifyChangeProperty(Property* _sender);
		void notifyChangeValue(const std::string& _value);
		void notifyChangeScope(const std::string& _scope);

	private:
		ScopeTextureControl* mControl;
		std::string mParentTypeName;
		Data* mParentData;
		bool mActivated;
	};
}

#endif