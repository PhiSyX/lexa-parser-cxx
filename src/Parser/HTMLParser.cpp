// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Copyright: (c) 2023, Mike 'PhiSyX' S. (https://github.com/PhiSyX)         ┃
// ┃ SPDX-License-Identifier: MPL-2.0                                          ┃
// ┃ ╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌╌ ┃
// ┃                                                                           ┃
// ┃  This Source Code Form is subject to the terms of the Mozilla Public      ┃
// ┃  License, v. 2.0. If a copy of the MPL was not distributed with this      ┃
// ┃  file, You can obtain one at https://mozilla.org/MPL/2.0/.                ┃
// ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

#include <DOM/Node/CommentNode.hpp>
#include <DOM/Node/ElementNode.hpp>
#include <DOM/Node/TextNode.hpp>
#include <Parser/HTMLParser.hpp>

HTMLParser::HTMLParser(std::string html_source) 
	: Parser<DOM::BoxNode>(std::move(html_source))
{}

auto
HTMLParser::parse_children() -> DOM::Children
{
	DOM::Children children;

	while(true)
	{
		consume_whitespace();
		if (is_eof() || is_peek_until("</")) break;
		children.push_back(DOM::BoxNode(parse_node()));
	}

	return children;
}

auto
HTMLParser::parse_node() -> DOM::BoxNode
{
	if (is_peek_until("<!--")) 		return parse_comment_node();
	else if (is_peek_until("<")) 	return parse_element_node();
	else 							return parse_text_node();
}

auto
HTMLParser::parse_comment_node() -> DOM::BoxNode
{
	consume_until("<!--");
	auto inner_comment = advance([this](char) 
	{
		return is_peek_until("-->");
	});
	consume_until("-->");
	return DOM::BoxNode(new DOM::CommentNode(inner_comment));
}

auto
HTMLParser::parse_text_node() -> DOM::BoxNode
{
	auto inner_text = advance([this](char) 
	{
		return is_peek_until("<");
	});
	return DOM::BoxNode(new DOM::TextNode(inner_text));
}

auto
HTMLParser::parse_element_node() -> DOM::BoxNode
{
	consume_until("<");

	auto tag_name = advance([](char ch) 
	{
		return !std::isalnum(ch);
	});

	auto attributes = parse_element_attributes();

	consume_whitespace_and(">");
		
	auto children = parse_children();

	consume_until("</");
	consume_whitespace_and(tag_name);
	consume_whitespace_and(">");
	
	return DOM::BoxNode(new DOM::ElementNode(tag_name, attributes, children));
}

auto
HTMLParser::parse_element_attributes() -> DOM::AttributeMap
{
	DOM::AttributeMap attrs;

	while(true)
	{
		consume_whitespace();
		if (is_eof() || is_peek_until(">")) break;
		auto attr_key = advance([](char ch)
		{
			return !std::isalnum(ch);
		});
		consume_until("=\"");
		auto attr_value = advance("\"");
		consume_until("\"");

		attrs.insert(attr_key, attr_value);
	}

	return attrs;
}