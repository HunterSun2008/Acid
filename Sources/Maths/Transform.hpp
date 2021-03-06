﻿#pragma once

#include "Engine/Exports.hpp"
#include "Scenes/Component.hpp"
#include "Serialized/Metadata.hpp"
#include "Matrix4.hpp"
#include "Vector3.hpp"

namespace acid
{
	/// <summary>
	/// Holds position, rotation, and scale components.
	/// </summary>
	class ACID_EXPORT Transform :
		public Component
	{
	public:
		/// <summary>
		/// Constructor for Transform.
		/// </summary>
		/// <param name="position"> The position. </param>
		/// <param name="rotation"> The rotation. </param>
		/// <param name="scaling"> The scaling. </param>
		explicit Transform(const Vector3 &position = Vector3::Zero, const Vector3 &rotation = Vector3::Zero, const Vector3 &scaling = Vector3::One);

		/// <summary>
		/// Constructor for Transform.
		/// </summary>
		/// <param name="position"> The position. </param>
		/// <param name="rotation"> The rotation. </param>
		/// <param name="scale"> The scale. </param>
		Transform(const Vector3 &position, const Vector3 &rotation, const float &scale);

		/// <summary>
		/// Constructor for Transform.
		/// </summary>
		/// <param name="source"> Creates this vector out of a transform. </param>
		Transform(const Transform &source);

		void Start() override;

		void Update() override;

		void Decode(const Metadata &metadata) override;

		void Encode(Metadata &metadata) const override;

		/// <summary>
		/// Multiplies this transform with another transform.
		/// </summary>
		/// <param name="other"> The other transform. </param>
		/// <returns> The resultant transform. </returns>
		Transform Multiply(const Transform &other) const;

		Matrix4 GetWorldMatrix() const;

		const Vector3 &GetPosition() const { return m_position; }

		void SetPosition(const Vector3 &position);

		const Vector3 &GetRotation() const { return m_rotation; }

		void SetRotation(const Vector3 &rotation);

		const Vector3 &GetScaling() const { return m_scaling; }

		void SetScaling(const Vector3 &scaling);

		const bool &IsDirty() const { return m_dirty; }

		void SetDirty(const bool &dirty) const;

		bool operator==(const Transform &other) const;

		bool operator!=(const Transform &other) const;

		ACID_EXPORT friend Transform operator*(const Transform &left, const Transform &right);

		Transform &operator*=(const Transform &other);

		ACID_EXPORT friend std::ostream &operator<<(std::ostream &stream, const Transform &transform);

		std::string ToString() const;

		static const Transform Identity;
	private:
		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scaling;
		mutable Matrix4 m_worldMatrix;
		mutable bool m_dirty;
	};
}
