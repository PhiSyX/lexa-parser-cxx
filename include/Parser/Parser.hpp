// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_PARSER_HPP
#define LEXA_PARSER_HPP

#include <algorithm>
#include <functional>
#include <string>

template<typename T>
class Parser
{
	public:
		/**
		 * Ctor
		 *
		 * @param source -- Code source à analyser.
		 */
		explicit Parser(std::string source);

		/**
		 * Dtor 
		 */
		virtual ~Parser() = default;

	protected:
		using PredicateParser = std::function<bool(char)> const;

		/**
		 * Avance dans le code source jusqu'au caractères donnés et retourne
		 * une chaîne construite.
		 *
		 * @param input
		 * @return string
		 */
		auto advance(const std::string& input) -> std::string;
		/**
		 * Avance dans le code source tant que le prédicat est satisfait.
		 * 
		 * @param predicate
		 * @return séquence de chaîne de caractères 
		 */
		auto advance(PredicateParser& predicate) -> std::string;

		/**
		 * Consomme la source jusqu'au caractères donnés.
		 *
		 * @param input
		 */
		void consume_until(const std::string& input);

		/**
		 * Consomme tous les espaces blancs.
		 */
		void consume_whitespace();
		/**
		 * Consomme tous les espaces blancs et les caractères donnés.
		 */
		void consume_whitespace_and(const std::string& input);

		/**
		 * Incrémente l'index courant d'une certaine distance.
		 * 
		 * @param distance 
		 */
		void increment_current_idx(uint64_t distance = 1);

		/**
		 * Vérifie si le code source est entièrement lu.
		 * 
		 * @return fin du code source ou non.
		 */
		auto is_eof() const -> bool;

		/**
         * @return retourne true si les prochains caractères que l'on rencontre
         * sont équivalents à la chaîne donné, false sinon.
		 */
        [[nodiscard]]
        auto is_peek_until(const std::string& input) const -> bool;
		/**
         * @return retourne true si les prochains caractères que l'on rencontre
         * remplissent le prédicat donné, false sinon.
		 */
        [[nodiscard]]
        auto is_peek_until(const PredicateParser& predicate) const -> bool;

    private:
        std::string m_source;
        uint64_t m_current_idx;
};

#endif // LEXA_PARSER_HPP