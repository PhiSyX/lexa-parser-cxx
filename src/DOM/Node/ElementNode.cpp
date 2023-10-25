// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>

#include <DOM/Node/ElementNode.hpp>

// -------------- //
// Implémentation // -> DOM::ElementNode
// -------------- //

DOM::ElementNode::ElementNode(
	std::string tag_name,
	DOM::AttributeMap attributes,
	const DOM::Children& children
)
	: Node(std::move(tag_name))
	, m_attributes(std::move(attributes))
	, m_children()
{
	m_children.reserve(children.size());

	std::for_each(children.begin(), children.end(), 
		[this](const auto& child) 
		{
			this->m_children.push_back(child->clone());
		}
	);
}

auto
DOM::ElementNode::clone() -> DOM::BoxNode
{
	return BoxNode(new ElementNode(tag_name(), m_attributes, m_children));
}

auto
DOM::ElementNode::attributes() const -> std::string
{
	return m_attributes.to_string();
}

auto
DOM::ElementNode::classNames() const -> std::vector<std::string>
{
	auto class_names = m_attributes.find("class");

	if (class_names == m_attributes.end()) return {
	};

	std::istringstream stream(class_names->second);

	return {
		std::istream_iterator<std::string> { stream },
		std::istream_iterator<std::string> { 		}
	};
}

auto
DOM::ElementNode::id() const -> std::string
{
	auto attr_id = m_attributes.find("id");
	return attr_id != m_attributes.end() 
		? attr_id->second 
		: "";
}

// -------------- //
// Implémentation // -> DOM::AttributeMap
// -------------- //

void 
DOM::AttributeMap::insert(const std::string& attr_key, const std::string& attr_value)
{
	if (find(attr_key) != end()) return;
	(*this)[attr_key] = attr_value;
	m_items.push_back(attr_key);
}

auto 
DOM::AttributeMap::to_string() const -> std::string
{
	if (empty()) return "";

	auto kv = [this](const auto& attr_key)
	{
		auto attr_value = const_cast<DOM::AttributeMap&>(*this)[attr_key];
		return attr_key + "=\"" + attr_value + "\"";
	};

	return std::accumulate(
		std::next(m_items.begin()), 
		m_items.end(), 
		kv(m_items.front()),
		[&kv](auto acc, auto cur) 
		{
			return acc + " " + kv(cur);
		}
	);
}
