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
		 * Avance dans le code source jusqu'à ce que le prédicat soit satisfait.
		 * 
		 * @param predicate quand arrêter l'avancé du programme.
		 * @return séquence de chaîne de caractères 
		 */
		auto advance_as_long_as_possible(PredicateParser& predicate) -> std::string;

		/**
		 * Consomme les prochains caractères.
		 */
		void consume_next(const std::string& input);

		/**
		 * Consomme tous les espaces blancs.
		 */
		void consume_whitespace(const std::string& input = "");

		/**
		 * Incrémente l'index courant d'une certaine distance.
		 * 
		 * @param distance 
		 */
		void increment_idx(uint64_t distance = 1);

		/**
		 * Vérifie si le code source est entièrement lu.
		 * 
		 * @return fin du code source ou non.
		 */
		auto is_eof() const -> bool;

		/**
         * Le prochain élément de la source. Ne CONSOMME PAS la source.
         * Autrement dit, la valeur de retour du prochain appel à la fonction
         * [`Parser::consume_next`] DOIT être la valeur de retour de cette
         * fonction.
		 */
        [[nodiscard]]
        auto peek_next(const std::string& input) const -> bool;
        [[nodiscard]]
        auto peek_next(const PredicateParser& predicate) const -> bool;

    private:
        std::string source;
        uint64_t current_idx;
};

#endif