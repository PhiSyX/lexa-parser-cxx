// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#ifndef LEXA_DOM_ELEMENT_NODE_HPP
#define LEXA_DOM_ELEMENT_NODE_HPP

#include <map>

#include <DOM/Node/Node.hpp>

namespace DOM 
{

using Children = std::vector<BoxNode>;

class AttributeMap
	: public std::map<std::string, std::string>
{
	public:
		void insert(const std::string& attr_key, const std::string& attr_value);

		[[nodiscard]]
		auto to_string() const -> std::string;

	private:
		std::vector<std::string> m_items;
};

class ElementNode 
	: public Node
{
	public:
		/**
		 * Crée un [noeud d'élément](ElementNode).
		 * 
		 * @param tag_name Nom de la balise de l'élément.
		 * @param attributes les attributs associés à l'élément.
		 * @param children les enfants associés à l'élément.
		 */
		explicit ElementNode(
			std::string tag_name,
			AttributeMap attributes = AttributeMap(),
			const Children& children      = Children()
		);
		ElementNode(const ElementNode& _) = delete;
		~ElementNode() override = default;

		/**
		 * Les attributs de l'élément.
		 */
		[[nodiscard]]
		auto attributes() const -> std::string;

		/**
		 * Les éléments enfants de l'élément.
		 */
		[[nodiscard]]
		auto children() const -> std::string;

		/**
		 * ID de l'élément.
		 */
		[[nodiscard]]
		auto id() const -> std::string;

		/**
		 * Les classes de l'élément.
		 */
		[[nodiscard]]
		auto classNames() const -> std::vector<std::string>;

	private:
		AttributeMap m_attributes;
		Children m_children;

		/**
		 * Clone du noeud HTML.
		 */
		auto clone() -> DOM::BoxNode override;
};

}

#endif // LEXA_DOM_ELEMENT_NODE_HPP
