// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_DOM_TEXT_NODE_HPP
#define LEXA_DOM_TEXT_NODE_HPP

#include <DOM/Node/Node.hpp>

namespace DOM 
{

class TextNode 
	: public Node
{
	public:
		/**
		 * Crée un [noeud de texte](TextNode).
		 * 
		 * @param text_content contenu texte du noeud de texte.
		 */
		explicit TextNode(std::string text_content);
		TextNode(const TextNode& _) = delete;
		~TextNode() override = default;

		/**
		 * Le contenu texte du noeud de texte.
		 * 
		 * @return @see TextNode#text_content
		 */
		[[nodiscard]]
		auto textContent() const -> std::string;

	private:
		std::string text_content;

		/**
		 * Clone du noeud de texte.
		 */
		auto clone() -> DOM::BoxNode override;
};

}

#endif // LEXA_DOM_TEXT_NODE_HPP
