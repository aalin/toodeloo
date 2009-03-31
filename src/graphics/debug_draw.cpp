#include "../common.hpp"

namespace Toodeloo
{
	namespace Graphics
	{

		void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
		{
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_LINE_LOOP);
			for (int32 i = 0; i < vertexCount; ++i)
			{
				glVertex2f(vertices[i].x, vertices[i].y);
			}
			glEnd();
		}

		void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
		{
			glEnable(GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
			glBegin(GL_TRIANGLE_FAN);
			for (int32 i = 0; i < vertexCount; ++i)
			{
				glVertex2f(vertices[i].x, vertices[i].y);
			}
			glEnd();
			glDisable(GL_BLEND);

			glColor4f(color.r, color.g, color.b, 1.0f);
			glBegin(GL_LINE_LOOP);
			for (int32 i = 0; i < vertexCount; ++i)
			{
				glVertex2f(vertices[i].x, vertices[i].y);
			}
			glEnd();
		}

		void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
		{
			const float32 k_segments = 16.0f;
			const float32 k_increment = 2.0f * b2_pi / k_segments;
			float32 theta = 0.0f;
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_LINE_LOOP);
			for (int32 i = 0; i < k_segments; ++i)
			{
				b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
				glVertex2f(v.x, v.y);
				theta += k_increment;
			}
			glEnd();
		}

		void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
		{
			const float32 k_segments = 16.0f;
			const float32 k_increment = 2.0f * b2_pi / k_segments;
			float32 theta = 0.0f;
			glEnable(GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
			glBegin(GL_TRIANGLE_FAN);
			for (int32 i = 0; i < k_segments; ++i)
			{
				b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
				glVertex2f(v.x, v.y);
				theta += k_increment;
			}
			glEnd();
			glDisable(GL_BLEND);

			theta = 0.0f;
			glColor4f(color.r, color.g, color.b, 1.0f);
			glBegin(GL_LINE_LOOP);
			for (int32 i = 0; i < k_segments; ++i)
			{
				b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
				glVertex2f(v.x, v.y);
				theta += k_increment;
			}
			glEnd();

			b2Vec2 p = center + radius * axis;
			glBegin(GL_LINES);
			glVertex2f(center.x, center.y);
			glVertex2f(p.x, p.y);
			glEnd();
		}

		void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
		{
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_LINES);
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glEnd();
		}

		void DebugDraw::DrawXForm(const b2XForm& xf)
		{
			b2Vec2 p1 = xf.position, p2;
			const float32 k_axisScale = 0.4f;
			glBegin(GL_LINES);

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(p1.x, p1.y);
			p2 = p1 + k_axisScale * xf.R.col1;
			glVertex2f(p2.x, p2.y);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(p1.x, p1.y);
			p2 = p1 + k_axisScale * xf.R.col2;
			glVertex2f(p2.x, p2.y);

			glEnd();
		}
	}
}
