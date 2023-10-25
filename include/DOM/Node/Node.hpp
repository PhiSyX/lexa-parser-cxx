// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_DOM_NODE_HPP
#define LEXA_DOM_NODE_HPP

#include <memory>
#include <string>
#include <vector>

namespace DOM 
{

class Node;

using BoxNode = std::unique_ptr<Node>;

class Node 
{
	public:
		/**
		 * Crée un noeud DOM.
		 * @param tag_name Nom de la balise.
		 */
		explicit Node(std::string tag_name);

		virtual ~Node() = 0;

		/**
		 * Clone le [noeud](Node).
		 */
		virtual auto clone() -> BoxNode = 0;

		[[nodiscard]]
		auto is(const std::string& cand) const -> bool;

		/**
		 * Retourne le nom de la balise de ce noeud.
		 * @return @see Node#m_tag_name
		 */
		[[nodiscard]]
		auto tag_name() const -> std::string;

	private:
		std::string m_tag_name;
};

}

#endif // LEXA_DOM_NODE_HPP