#pragma once

#include "Renderer/Buffers/UniformBuffer.hpp"

namespace fl
{
	/// <summary>
	/// Class that handles a uniform buffer.
	/// </summary>
	class FL_EXPORT UniformHandler
	{
	private:
		bool m_multipipeline;
		UniformBlock *m_uniformBlock;
		UniformBuffer *m_uniformBuffer;
		void *m_data;
		bool m_changed;
	public:
		UniformHandler(const bool &multipipeline = false);

		~UniformHandler();

		template<typename T>
		void Push(const T &object, const size_t &offset, const size_t &size)
		{
			memcpy((char *) m_data + offset, &object, size);
			m_changed = true;
		}

		template<typename T>
		void Push(const std::string &uniformName, const T &object, const size_t &size = 0)
		{
			if (m_uniformBlock == nullptr)
			{
				return;
			}

			auto uniform = m_uniformBlock->GetUniform(uniformName);

			if (uniform == nullptr)
			{
				return;
			}

			Push(object, static_cast<size_t>(uniform->GetOffset()), size == 0 ? sizeof(object) : size); // static_cast<size_t>(uniform->m_size)
		}

		bool Update(UniformBlock *uniformBlock);

		UniformBuffer *GetUniformBuffer() const { return m_uniformBuffer; }
	};
}