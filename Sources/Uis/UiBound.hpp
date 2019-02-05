#pragma once

#include "Maths/Vector2.hpp"
#include "Helpers/EnumClass.hpp"

namespace acid
{
	class ACID_EXPORT UiReference
	{
	public:
		static const Vector2f TopLeft;
		static const Vector2f TopCentre;
		static const Vector2f TopRight;
		static const Vector2f CentreLeft;
		static const Vector2f Centre;
		static const Vector2f CentreRight;
		static const Vector2f BottomLeft;
		static const Vector2f BottomCentre;
		static const Vector2f BottomRight;
	};

	enum class UiAspect : uint32_t
	{
		None = 0,
		Position = 1,
		Dimensions = 2,
		Scale = 4
	};
	ENABLE_BITMASK_OPERATORS(UiAspect)

	/// <summary>
	/// A rectangle made of a position and dimension.
	/// </summary>
	class ACID_EXPORT UiBound
	{
	public:
		/// <summary>
		/// Constructor for rectangle.
		/// </summary>
		/// <param name="position"> The object screen position. </param>
		/// <param name="reference"> The reference vertex of the parent bounds, where position is. </param>
		/// <param name="aspect"> The aspect that will be used for bounding in the parent reference. </param>
		/// <param name="dimensions"> The object dimensions. </param>
		explicit UiBound(const Vector2f &position = Vector2f(0.0f, 0.0f), const Vector2f &reference = UiReference::TopLeft,
			const bitmask<UiAspect> &aspect = UiAspect::Position | UiAspect::Dimensions, const Vector2f &dimensions = Vector2f(1.0f, 1.0f));

		/// <summary>
		/// Gets the bounds position in the current screen space.
		/// </summary>
		/// <returns> The position in screen space. </returns>
		Vector2f GetScreenPosition(const float &aspectRatio) const;

		/// <summary>
		/// Gets the bounds dimensions in the current screen space.
		/// </summary>
		/// <returns> The dimensions in screen space. </returns>
		Vector2f GetScreenDimensions(const float &aspectRatio) const;

		const Vector2f &GetPosition() const { return m_position; }

		void SetPosition(const Vector2f &position) { m_position = position; }

		const Vector2f &GetReference() const { return m_reference; }

		void SetReference(const Vector2f &reference) { m_reference = reference; }

		const bitmask<UiAspect> &GetAspect() const { return m_aspect; }

		void SetAspect(const bitmask<UiAspect> &aspect) { m_aspect = aspect; }

		const Vector2f &GetDimensions() const { return m_dimensions; }

		void SetDimensions(const Vector2f &dimensions) { m_dimensions = dimensions; }

		bool operator==(const UiBound &other) const;

		bool operator!=(const UiBound &other) const;

		static const UiBound Screen;
		static const UiBound Maximum;
		static const UiBound Left;
		static const UiBound Centre;
		static const UiBound Right;

		Vector2f m_position;
		Vector2f m_reference;
		bitmask<UiAspect> m_aspect;
		Vector2f m_dimensions;
	};
}
