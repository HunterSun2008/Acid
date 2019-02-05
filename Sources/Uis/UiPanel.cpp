#include "UiPanel.hpp"

#include "Maths/Visual/DriverSlide.hpp"
#include "Inputs/UiInputButton.hpp"
#include "Uis.hpp"

namespace acid
{
	static const Vector2f SCROLL_BAR = Vector2f(0.01f, 0.2f);

	UiPanel::UiPanel(UiObject *parent, const UiBound &rectangle, const bitmask<ScrollBar> &scrollBars) :
		UiObject(parent, rectangle),
		m_background(std::make_unique<Gui>(this, UiBound::Maximum, Texture::Create("Guis/White.png"), UiInputButton::BackgroundColour)),
		m_content(std::make_unique<UiObject>(this, UiBound::Maximum)),
		m_scrollX(std::make_unique<UiScrollBar>(this, ScrollBar::Horizontal, UiBound(Vector2f(0.0f, 1.0f), UiReference::BottomLeft, UiAspect::Position | UiAspect::Dimensions, Vector2f(SCROLL_BAR.m_y, SCROLL_BAR.m_x)))),
		m_scrollY(std::make_unique<UiScrollBar>(this, ScrollBar::Vertical, UiBound(Vector2f(1.0f, 0.0f), UiReference::TopRight, UiAspect::Position | UiAspect::Dimensions, Vector2f(SCROLL_BAR.m_x, SCROLL_BAR.m_y)))),
		m_scrollBars(scrollBars),
		m_min(Vector2f()),
		m_max(Vector2f())
	{
	}

	void UiPanel::UpdateObject()
	{
		Vector2f contentSize = (m_max - m_min) / GetScreenDimensions();
		m_scrollX->SetEnabled((m_scrollBars & ScrollBar::Horizontal) && contentSize.m_x > 1.05f);
		m_scrollY->SetEnabled((m_scrollBars & ScrollBar::Vertical) && contentSize.m_y > 1.05f);

		m_scrollX->GetRectangle().SetDimensions(Vector2f(0.5f * (1.0f / contentSize.m_x), SCROLL_BAR.m_x));
		m_scrollY->GetRectangle().SetDimensions(Vector2f(SCROLL_BAR.m_x, 0.5f * (1.0f / contentSize.m_y)));

	//	m_content->GetRectangle().SetPosition(0.5f - (Vector2f(m_scrollX->GetProgress(), m_scrollY->GetProgress()) * contentSize));

		m_min = Vector2f(+std::numeric_limits<float>::infinity(), +std::numeric_limits<float>::infinity());
		m_max = Vector2f(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
		SetScissor(m_scrollX.get());
		SetScissor(m_scrollY.get());
		SetScissor(m_content.get(), true);
	}

	void UiPanel::SetScissor(UiObject *object, const bool &size)
	{
		auto position = m_background->GetScreenPosition();
		auto dimension = m_background->GetScreenDimensions();
		object->SetScissor(Vector4(position.m_x, position.m_y, dimension.m_x, dimension.m_y));

		if (object->IsEnabled() && size)
		{
			m_min = Vector2f::MinVector(m_min, object->GetScreenPosition());
			m_max = Vector2f::MaxVector(m_max, object->GetScreenPosition() + object->GetScreenDimensions());
		}

		for (auto &child : object->GetChildren())
		{
			SetScissor(child, size);
		}
	}
}
