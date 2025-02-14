#ifndef __IWIDGET_H__
#define __IWIDGET_H__

namespace xPing {
	class IWidget {
	public:
		virtual ~IWidget() = default;
		virtual void draw() = 0;

	protected:
		int l, r, t, b;
	};
}

#endif
