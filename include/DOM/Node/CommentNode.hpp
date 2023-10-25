// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_DOM_COMMENT_NODE_HPP
#define LEXA_DOM_COMMENT_NODE_HPP

#include <DOM/Node/Node.hpp>

namespace DOM 
{

class CommentNode 
	: public Node
{
	public:
		/**
		 * Crée un [noeud de commentaire](CommentNode).
		 * 
		 * @param content contenu du noeud de commentaire.
		 */
		explicit CommentNode(std::string content);
		CommentNode(const CommentNode& _) = delete;
		~CommentNode() override = default;

		/**
		 * Le commentaire de ce noeud.
		 * 
		 * @return @see CommentNode#m_content
		 */
		[[nodiscard]]
		auto comment() const -> std::string;

	private:
		std::string m_content;

		/**
		 * Clone du noeud commentaire.
		 */
		auto clone() -> DOM::BoxNode override;
};

}

#endif // LEXA_DOM_COMMENT_NODE_HPP
