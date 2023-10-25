// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_PARSER_HTML_HPP
#define LEXA_PARSER_HTML_HPP

#include <DOM/Node/Node.hpp>
#include <DOM/Node/ElementNode.hpp>
#include <Parser/Parser.hpp>

class HTMLParser 
	: public Parser<DOM::BoxNode>
{
	public:
		/**
		 * Ctor
		 *
		 * @param html_source -- Code source HTML à analyser.
		 */
		explicit HTMLParser(std::string html_source);

		/**
		 * Dtor 
		 */
		~HTMLParser() override = default;

	
	private:
		/**
		 * Analyse les enfants du noeud DOM.
		 */
		auto parse_children() -> DOM::Children;

		/**
		 * Analyse un noeud DOM.
		 */
		auto parse_node() -> DOM::BoxNode;

		/**
		 * Analyse un noeud de commentaire dans le DOM.
		 */
		auto parse_comment_node() -> DOM::BoxNode;

		/**
		 * Analyse un noeud élément DOM.
		 */
		auto parse_element_node() -> DOM::BoxNode;

		/**
		 * Analyse des attributs d'un élément.
		 */
		auto parse_element_attributes() -> DOM::AttributeMap;

		/**
		 * Analyse un noeud de texte dans le DOM.
		 */
		auto parse_text_node() -> DOM::BoxNode;
};

#endif // LEXA_PARSER_HTML_HPP
