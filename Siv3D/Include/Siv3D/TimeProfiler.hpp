﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <unordered_map>
# include "Fwd.hpp"
# include "Time.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Utility.hpp"

namespace s3d
{
	class TimeProfiler
	{
	private:

		struct Detail
		{
			uint64 sum = 0;

			uint64 begin = 0;

			uint64 min = UINT64_MAX;

			uint64 max = 0;

			uint32 count = 0;

			uint16 index = 0;

			bool open = false;
		};

		std::unordered_map<String, Detail> m_data;

		Array<String> m_labels;

		String m_name;

		uint16 m_index;

		const uint64 m_start;

		uint64* begin_impl(const String& label);

		void end_impl(const uint64 end);

		String toString(const uint64 ns) const;

		void log(const uint64 end) const;

	public:

		TimeProfiler(const String& name = L"Profiler")
			: m_name(name)
			, m_index(0)
			, m_start(Time::GetNanosec()) {}

		~TimeProfiler()
		{
			const uint64 end = Time::GetNanosec();

			log(end);
		}

		void begin(const String& label)
		{
			if (auto p = begin_impl(label))
			{
				*p = Time::GetNanosec();
			}
		}

		void end()
		{
			const uint64 end = Time::GetNanosec();

			end_impl(end);
		}
	};
}
