﻿#pragma once

#include "Helpers/String.hpp"
#include "Resources/Resource.hpp"
#include "Textures/Texture.hpp"
#include "FontMetafile.hpp"

namespace acid
{
	/// <summary>
	/// A loader capable of loading font data into a instance of a text mesh.
	/// </summary>
	class ACID_EXPORT FontType :
		public Resource
	{
	public:
		/// <summary>
		/// Will find an existing font type with the same values, or create a new font type.
		/// </summary>
		/// <param name="metadata"> The metadata to decode values from. </param>
		static std::shared_ptr<FontType> Create(const Metadata &metadata);

		/// <summary>
		/// Will find an existing font type with the same values, or create a new font type.
		/// </summary>
		/// <param name="filename"> The family file path that the texture atlases and character infos are contained in. </param>
		/// <param name="style"> The style selected to load as this type. </param>
		static std::shared_ptr<FontType> Create(const std::string &filename, const std::string &style = "Regular");

		/// <summary>
		/// Creates a new font type.
		/// </summary>
		/// <param name="filename"> The family file path that the texture atlases and character infos are contained in. </param>
		/// <param name="fontStyle"> The style selected to load as this type. </param>
		/// <param name="load"> If this resource will load immediately, otherwise <seealso cref="#Load()"/> can be called. </param>
		FontType(const std::string &filename, const std::string &fontStyle, const bool &load = true);

		void Load() override;

		void Decode(const Metadata &metadata) override;

		void Encode(Metadata &metadata) const override;

		const std::shared_ptr<Texture> &GetTexture() const { return m_texture; }

		const FontMetafile *GetMetadata() const { return m_metadata.get(); }
	private:
		std::string m_filename;
		std::string m_style;

		std::shared_ptr<Texture> m_texture;
		std::unique_ptr<FontMetafile> m_metadata;
	};
}
