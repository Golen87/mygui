/*!
	@file
	@author		Albert Semenov
	@date		11/2007
	@module
*/
#ifndef __MYGUI_WIDGET_MANAGER_H__
#define __MYGUI_WIDGET_MANAGER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_Instance.h"
#include "MyGUI_WidgetCreator.h"
#include "MyGUI_UnlinkWidget.h"
#include "MyGUI_CastWidget.h"

namespace MyGUI
{

	// ������� ��� ��������
	typedef delegates::CDelegate3<WidgetPtr,  const Ogre::String &, const Ogre::String &> ParseDelegate;

	class _MyGUIExport WidgetManager : public UnlinkWidget
	{
		INSTANCE_HEADER(WidgetManager);

	public:
		typedef std::map<Ogre::String, ParseDelegate> MapDelegate;
		typedef std::set<WidgetFactoryInterface*> SetWidgetFactory;

	public:
		void initialise();
		void shutdown();

		WidgetPtr createWidget(const Ogre::String & _type, const Ogre::String & _skin, const IntCoord& _coord, Align _align, CroppedRectanglePtr _parent, WidgetCreator * _creator, const Ogre::String & _name);

		/** Destroy all widgets FIXME or remove - doesn't work*/
		void destroyAllWidget();

		/** Destroy _widget */
		void destroyWidget(WidgetPtr _widget);
		/** Destroy vector of widgets */
		void destroyWidgetsVector(VectorWidgetPtr &_widgets);

		/** Register widget factory */
		void registerFactory(WidgetFactoryInterface * _factory);
		/** Unregister widget factory */
		void unregisterFactory(WidgetFactoryInterface * _factory);

		// ����� ��� ������ �������
		/** Find widget by name */
		WidgetPtr findWidgetT(const Ogre::String & _name);
		/** Find widget by name and prefix*/
		inline WidgetPtr findWidgetT(const std::string& _name, const std::string& _prefix)
		{
			return findWidgetT(_prefix + _name);
		}
		/** Find widget by name and cast it to T type.
			If T and found widget have different types cause error in DEBUG mode.
		*/
		template <class T> inline T* findWidget(const std::string& _name)
		{
			WidgetPtr widget = findWidgetT(_name);
			if (null == widget) return null;
			return castWidget<T>(widget);
		}

		/** Find widget by name and prefix and cast it to T type*/
		template <class T> inline T* findWidget(const std::string& _name, const std::string& _prefix)
		{
			return findWidget<T>(_prefix + _name);
		}

		// ����������� ����� �� ������� � ���������� �������
		/** Convert position on widget to global position */
		static IntPoint convertToGlobal(const IntPoint& _point, WidgetPtr _widget);

		// ������� ��� � �������
		void _unlinkWidget(WidgetPtr _widget);

		// ������������ �������
		/** Register delegate for parsing in layout files or by WidgetManager::parse method 
			@code manager.registerDelegate("Button_Pressed") = newDelegate(this, &ButtonFactory::Button_Pressed); @endcode
		*/
		ParseDelegate & registerDelegate(const Ogre::String & _key);
		/** Unregister delegate for parsing in layout files or by WidgetManager::parse method */
		void unregisterDelegate(const Ogre::String & _key);

		// ������ ���� ��������
		/** Parse and apply property to widget
			@param _widget to which property will be applied
			@param _key property
			@param _value for applying
			@code WidgetManager::getInstance()->parse(widget, "Button_Pressed", "true"); @endcode
		*/
		void parse(WidgetPtr _widget, const Ogre::String &_key, const Ogre::String &_value);

		// ��� ��� ����� �������� � ���� ������ ��� ��������
		/** Register unlinker (call unlink if for any destroyed widget)*/
		void registerUnlinker(UnlinkWidget * _unlink);
		/** Unregister unlinker (call unlink if for any destroyed widget)*/
		void unregisterUnlinker(UnlinkWidget * _unlink);
		/** Unlink widget */
		void unlinkFromUnlinkers(WidgetPtr _widget);

		/* Convert from relative to pixel coordinates.
			@param
				_coord relative coordinates. (relative to _parent client area coordinates)
			@param
				_parent Widget.
		*/
		IntCoord convertRelativeToInt(const FloatCoord & _coord, WidgetPtr _parent);
		/* Convert from pixel to relative coordinates.
			@param
				_coord relative coordinates. (relative to _parent client area coordinates)
			@param
				_parent Widget.
		*/
		FloatCoord convertIntToRelative(const IntCoord & _coord, WidgetPtr _parent);

	protected:
		SetWidgetFactory mFactoryList;
		MapWidgetPtr mWidgets;
		MapDelegate mDelegates;

		// set of integrated factories
		SetWidgetFactory mIntegratedFactoryList;

		// ������ ���������� ��� ������� ��� ��������
		VectorUnlinkWidget mVectorUnlinkWidget;

	};

} // namespace MyGUI

#endif // __MYGUI_WIDGET_MANAGER_H__
