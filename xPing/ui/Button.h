#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "IWidget.h"
#include <string>
#include <functional>
#include <XPLMDefs.h>

namespace xPing
{
	class Button : public IWidget
	{
	public:
		Button(
			int x, 
			int y, 
			std::string label
		);

		void draw() override;

		void registerClickCallback(std::function<void()> callback);
		void checkClick(XPLMMouseStatus status);
		void checkHover(int x, int y);
		void changeLabel(std::string newLabel);

	private:
		std::function<void()> onClick;

		bool clicked;
		bool hovered;
		std::string label;
		int labelWidth;
		int buttonWidth;
		int buttonHeight;
	};
}

#endif
