// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#include <Parser/Parser.hpp>

template<typename T>
Parser<T>::Parser(std::string source)
	: m_source(std::move(source))
	, m_current_idx(0ULL)
{
}

template<typename T>
auto
Parser<T>::advance(const std::string& input) -> std::string
{
	consume_whitespace();

	std::string output;

	while (!is_eof() && !is_peek_until(input)) 
	{
		output.push_back(m_source.at(m_current_idx));
		increment_current_idx();
	}

	return output;
}

template<typename T>
auto
Parser<T>::advance(Parser<T>::PredicateParser& predicate) -> std::string
{
	consume_whitespace();

	std::string output;

	while (!is_eof() && !is_peek_until(predicate)) 
	{
		output.push_back(m_source.at(m_current_idx));
		increment_current_idx();
	}

	return output;
}

template <typename T>
void
Parser<T>::consume_until(const std::string& input) 
{
	assert(is_peek_until(input));
	increment_current_idx(input.length());
}

template <typename T>
void
Parser<T>::consume_whitespace() 
{
	while (std::isspace(m_source.at(m_current_idx))) 
	{
		increment_current_idx();
	}
}

template <typename T>
void
Parser<T>::consume_whitespace_and(const std::string& input) 
{
	consume_whitespace();
	consume_until(input);
}

template <typename T>
void 
Parser<T>::increment_current_idx(uint64_t distance) 
{
	m_current_idx += distance;
}

template <typename T>
auto
Parser<T>::is_eof() const -> bool
{
	return m_current_idx >= m_source.length();
}

template <typename T>
auto
Parser<T>::is_peek_until(const std::string& input) const -> bool 
{
	return m_source.rfind(input, m_current_idx) == m_current_idx;
}

template <typename T>
auto
Parser<T>::is_peek_until(const Parser<T>::PredicateParser& predicate) const -> bool 
{
	return predicate(m_source.at(m_current_idx));
}
