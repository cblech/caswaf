#include "HTMLParser.h"
#include <sstream>


bool HTMLNode::isTextNode() const
{
	return tagName=="";
}

HTMLNode::HTMLNode()
{
}

string HTMLNode::getTagName()const
{
	return tagName;
}

string HTMLNode::getText()const
{
	return text;
}

string HTMLNode::getAttribute(string key)const
{
	return attributs.at(key);
}

bool HTMLNode::hasAttribute(string key)const
{
	return attributs.count(key)>0;
}

HTMLnodeAttributList HTMLNode::getAllAttributes() const
{
	return attributs;
}

string HTMLNode::getOuterHTML() const
{
	std::stringstream ss;
	ss << this;
	return ss.str();
}

string HTMLNode::getInnerHTML() const
{
	std::stringstream ss;
	for (auto node : childNodes)
	{
		ss << node;
	}
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const HTMLnodeAttribut& attr)
{
	os << attr.first << "=\"" << attr.second << "\"";
	return os;
}

std::ostream& operator<<(std::ostream& os, const HTMLnodeAttributList& attrs)
{
	for (auto attr : attrs)
	{
		os << attr << " ";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const HTMLNode& node)
{
	if (node.isTextNode())
	{
		os << node.getText();
	}
	else
	{
		os << "<" << node.getTagName() << node.getAllAttributes() << " >";
		os << node.getInnerHTML();
		os << "</" << node.getTagName() << ">";
	}
	return os;
}
