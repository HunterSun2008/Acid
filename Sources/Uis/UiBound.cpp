#include "UiBound.hpp"

#include "Engine/Log.hpp"

namespace acid
{
	const Vector2f UiReference::TopLeft = Vector2f(0.0f, 0.0f);
	const Vector2f UiReference::TopCentre = Vector2f(0.5f, 0.0f);
	const Vector2f UiReference::TopRight = Vector2f(1.0f, 0.0f);
	const Vector2f UiReference::CentreLeft = Vector2f(0.0f, 0.5f);
	const Vector2f UiReference::Centre = Vector2f(0.5f, 0.5f);
	const Vector2f UiReference::CentreRight = Vector2f(1.0f, 0.5f);
	const Vector2f UiReference::BottomLeft = Vector2f(0.0f, 1.0f);
	const Vector2f UiReference::BottomCentre = Vector2f(0.5f, 1.0f);
	const Vector2f UiReference::BottomRight = Vector2f(1.0f, 1.0f);

	const UiBound UiBound::Screen = UiBound(Vector2f(0.0f, 0.0f), UiReference::TopLeft, UiAspect::Position);
	const UiBound UiBound::Maximum = UiBound(Vector2f(0.5f, 0.5f), UiReference::Centre, UiAspect::Position | UiAspect::Scale);
	const UiBound UiBound::Left = UiBound(Vector2f(0.0f, 0.5f), UiReference::CentreLeft);
	const UiBound UiBound::Centre = UiBound(Vector2f(0.5f, 0.5f), UiReference::Centre);
	const UiBound UiBound::Right = UiBound(Vector2f(1.0f, 0.5f), UiReference::CentreRight);

	UiBound::UiBound(const Vector2f &position, const Vector2f &reference, const bitmask<UiAspect> &aspect, const Vector2f &dimensions) :
		m_position(position),
		m_reference(reference),
		m_aspect(aspect),
		m_dimensions(dimensions)
	{
	}

	Vector2f UiBound::GetScreenPosition(const float &aspectRatio) const
	{
		Vector2f screenPosition = m_position;

		if (!(m_aspect & UiAspect::Position))
		{
			screenPosition.m_x /= aspectRatio;
		}

		return screenPosition;
	}

	Vector2f UiBound::GetScreenDimensions(const float &aspectRatio) const
	{
		Vector2f screenDimensions = m_dimensions;

		if (m_aspect & UiAspect::Dimensions)
		{
			screenDimensions.m_x /= aspectRatio;
		}

		return screenDimensions;
	}

	bool UiBound::operator==(const UiBound &other) const
	{
		return m_position == other.m_position && m_reference == other.m_reference && m_aspect == other.m_aspect && m_dimensions == other.m_dimensions;
	}

	bool UiBound::operator!=(const UiBound &other) const
	{
		return !(*this == other);
	}
}
