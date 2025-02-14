#ifndef __INPUT_H__
#define __INPUT_H__

#include "IWidget.h"
#include <string>

namespace xPing {
	class Input : public IWidget
	{
	public:
		Input(int x, int y, std::string txt, int max = 20, bool password = false);

		void draw() override;

		void checkClick();
		void checkHover(int x, int y);
		void checkKey(char key);

	private:
		bool focused;
		bool hovered;
		int width;
		int height;
		bool password;
		std::string text;
	};
}

#endif

