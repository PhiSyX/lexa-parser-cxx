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
	: source(std::move(source))
	, current_idx(0ULL)
{
}

template<typename T>
auto
Parser<T>::advance_as_long_as_possible(Parser<T>::PredicateParser& predicate) -> std::string
{
	consume_whitespace();

	std::string output;

	while (!is_eof() && !peek_next(predicate)) 
	{
		output += source[current_idx];
		increment_idx();
	}

	return output;
}

template <typename T>
void
Parser<T>::consume_next(const std::string& input) 
{
	assert(peek_next(input));
	increment_idx(input.length());
}

template <typename T>
void
Parser<T>::consume_whitespace(const std::string& input) 
{
	while (std::isspace(source[current_idx])) 
	{
		increment_idx();
	}

	consume_next(input);
}

template <typename T>
void 
Parser<T>::increment_idx(uint64_t distance) 
{
	current_idx += distance;
}

template <typename T>
auto
Parser<T>::is_eof() const -> bool
{
	return current_idx >= source.length();
}

template <typename T>
auto
Parser<T>::peek_next(const std::string& input) const -> bool 
{
	return program.rfind(input, current_idx) == current_idx;
}

template <typename T>
auto
Parser<T>::peek_next(const Parser<T>::PredicateParser& predicate) const -> bool 
{
	return predicate(source[current_idx]);
}
