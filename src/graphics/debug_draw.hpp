#ifndef TOODELOO_GRAPHICS_DEBUG_DRAW_HPP
#define TOODELOO_GRAPHICS_DEBUG_DRAW_HPP

namespace Toodeloo
{
	namespace Graphics
	{
		class DebugDraw : public b2DebugDraw
		{
			public:
				void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
				void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
				void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
				void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
				void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
				void DrawXForm(const b2XForm& xf);
		};
	}
}

#endif

