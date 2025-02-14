#ifndef __IWIDGET_H__
#define __IWIDGET_H__

namespace xPing {
	class IWidget {
	public:
		virtual ~IWidget() = default;
		virtual void draw() = 0;

		void updatePosition(int deltaX, int deltaY) {
			l += deltaX;
			r += deltaX;
			t += deltaY;
			b += deltaY;
		};

	protected:
		int l, r, t, b;
	};
}

#endif
