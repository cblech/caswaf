#include "HTMLParser.h"
#include <sstream>
#include <list>
#include "log.h"

using stsr = std::stringstream;

bool HTMLNode::isTextNode() const
{
	return tagName == "";
}

HTMLNode::HTMLNode(
	const string& tagName,
	const string& text,
	HTMLNodeList childNodes,
	HTMLnodeAttributList attributs) :
	tagName(tagName),
	text(text),
	childNodes(childNodes),
	attributs(attributs)
{

}

HTMLNode::HTMLNode(const string& text) :
	tagName(""),
	text(text),
	childNodes(HTMLNodeList()),
	attributs(HTMLnodeAttributList())
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

bool HTMLNode::isEmpty() const
{
	return childNodes.size() == 0;
}

string HTMLNode::getAttribute(const string& key)const
{
	return attributs.at(key);
}

bool HTMLNode::hasAttribute(const string& key)const
{
	return attributs.count(key) > 0;
}

HTMLnodeAttributList HTMLNode::getAllAttributes() const
{
	return attributs;
}

string HTMLNode::getOuterHTML() const
{
	stsr ss;
	ss << this;
	return ss.str();
}


string HTMLNode::getInnerHTML() const
{
	stsr ss;
	for (auto node : childNodes)
	{
		ss << node;
	}
	return ss.str();
}

string HTMLNode::getOpeningTag() const
{
	if (isTextNode())
		return "";

	stsr ss;
	ss << "<" << getTagName() << " " << getAllAttributes()/* << (isEmpty() ? "/" : "")*/ << ">";
	return ss.str();
}

string HTMLNode::getClosingTag() const
{
	if (isTextNode())
		return "";

	stsr ss;
	ss << "</" << getTagName() << ">";
	return ss.str();
}

HTMLNodeList HTMLNode::getChildren() const
{
	auto nl = HTMLNodeList();

	for (auto n : childNodes)
	{
		if (!n.isTextNode())
		{
			nl.push_back(n);
		}
	}

	return nl;
}

HTMLNodeList HTMLNode::getChildrenIncludingText() const
{
	return childNodes;
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
		if (node.isEmpty())
		{
			os << node.getOpeningTag();
		}
		else
		{
			os << node.getOpeningTag();
			os << node.getInnerHTML();
			os << node.getClosingTag();
		}

	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const HTMLNodeList& nodes)
{
	for (auto n : nodes)
	{
		os << n;
	}
	return os;
}

HTMLNodeList HTMLParser::parseHTML(const string& html)
{
	TokenList dirtiytokens;

	stsr htmlss;
	htmlss << html;


	//tokenize
	while (!htmlss.eof())
	{
		char next = (char)htmlss.peek();
		if (htmlss.eof())
			break;

		switch (next)
		{
		case '<':
		{

			stsr text;

			while (!htmlss.eof())
			{
				text << (char)htmlss.get();
				if ((char)htmlss.peek() == '>')
				{
					text << (char)htmlss.get();
					break;
				}
			}

			dirtiytokens.push_back(Token(Token::tag, text.str()));

			break;

		}
		default:
		{
			stsr text;
			while ((char)htmlss.peek() != '<' && !htmlss.eof())
			{
				text << (char)htmlss.get();
			}

			dirtiytokens.push_back(Token(Token::text, text.str()));

			break;
		}
		}

	}

	//clean tokens
	TokenList tokens;

	for (Token& t : dirtiytokens)
	{
		if (t.value.size() != 0)
		{
			bool onlyWhitespaces = true;

			for (unsigned char c : t.value)
				if (!isspace(c))
					onlyWhitespaces = false;

			if (!onlyWhitespaces)
				tokens.push_back(t);
		}
	}

	//DEBUG
	/*
	for (auto t : tokens) {
		info << t.type<< ((t.isClosingTag()) ? " (closing)" : "") <<": "<<t.value ;
	}
	*/


	auto tokenIt = tokens.begin();

	return HTMLParser::parseNodesFromTokenIterator(tokenIt, tokens.end());;
}

HTMLNodeList HTMLParser::parseNodesFromTokenIterator(TokenList::iterator& tokenIt, const TokenList::iterator& endIt)
{
	auto nodes = HTMLNodeList();
	Token openedTag = Token(Token::Type::tag, "");
	auto potentialChildren = HTMLNodeList();

	while (tokenIt != endIt)
	{


		//If the token is a text token, just make a text HTMLNode and push it to the nodes
		//Also parse the remaining tokens
		if (tokenIt->type == Token::Type::text)
		{
			nodes.push_back(HTMLNode(tokenIt->value));
			tokenIt++;
		}

		//If the token is a tag token, check if it is a closing tag token. If it isn't a
		//  closing one, save it as the opened Tag and parse the potetnial Children of this tag
		else if (!tokenIt->isClosingTag())
		{
			//Special case: <!DOCTYPE html>
			if (tokenIt->value.at(1) == '!')
			{
				nodes.push_back(HTMLNode(tokenIt->value));
				tokenIt++;
			}
			else
			{
				openedTag = *tokenIt;
				tokenIt++;
				potentialChildren = parseNodesFromTokenIterator(tokenIt, endIt);
			}


		}

		//If the token is an closing tag, test if the closing tag fitts the opened tag.
		else
		{
			//If it fits, make new Node form the opeded tag and add the potential children as 
			//  ChildNodes.
			if (tokenIt->getTagName() == openedTag.getTagName())
			{
				nodes.push_back(parseNodeFromToken(openedTag, potentialChildren));
				tokenIt++;

				openedTag = Token(Token::Type::tag, "");
				potentialChildren = HTMLNodeList();

			}
			//If it doesn't fit, it means, that the opened tag does not have a dedicated closing tag,
			//  therefore add the opened tag as an empty HTMLNode, followed(!) by the potetial children.
			//  This also means, that the next token belongs to the parent depth.
			else
			{
				if (openedTag.value != "")
					nodes.push_back(parseNodeFromToken(openedTag));

				for (auto n : potentialChildren)
				{
					nodes.push_back(n);
				}
				return nodes;
			}
		}


	}
	if (openedTag.value != "")
		nodes.push_back(parseNodeFromToken(openedTag));

	for (auto n : potentialChildren)
	{
		nodes.push_back(n);
	}
	return nodes;
}

HTMLNode HTMLParser::parseNodeFromToken(const Token& token, HTMLNodeList childNodes /* = HTMLNodeList() */)
{
	struct atTok {
		enum Type { key, value, equ };
		Type type;
		string content;
	};


	string parse = token.value.substr(1, token.value.size() - 2);

	if (parse.at(parse.size() - 1) == '/')
		parse = parse.substr(0, parse.size() - 1);

	auto parseIt = parse.begin();

	std::list<atTok> atToks;

	while (parseIt != parse.end())
	{
		if (!isspace(*parseIt))
		{
			if (*parseIt == '=')
			{
				atToks.push_back(atTok{ atTok::Type::equ,"=" });
				parseIt++;
			}
			else if (*parseIt == '"')
			{
				string val = "";
				parseIt++;

				while (parseIt != parse.end() && *parseIt != '"')
				{
					val += *parseIt;
					parseIt++;
				}
				parseIt++;

				atToks.push_back(atTok{ atTok::Type::value,val });
			}
			else
			{
				string key = "";
				while (parseIt != parse.end() && !isspace(*parseIt) && *parseIt != '=' && *parseIt != '"')
				{
					key += *parseIt;
					parseIt++;
				}
				atToks.push_back(atTok{ atTok::Type::key,key });
			}
		}
		else
		{
			parseIt++;
		}
	}

	auto atributes = HTMLnodeAttributList();
	string tagName = "";


	auto atToksIt = atToks.begin();

	if (atToksIt->type != atTok::Type::key) {
		error << "Invalid HTML Tag";
	}
	else
	{
		tagName = atToksIt->content;
		atToksIt++;

		while (atToksIt != atToks.end())
		{
			string key = "";
			string val = "";
			if (atToksIt->type == atTok::Type::key)
			{
				key = atToksIt->content;
				atToksIt++;
				if (atToksIt != atToks.end() && atToksIt->type == atTok::Type::equ)
				{
					atToksIt++;
					if (atToksIt != atToks.end() && atToksIt->type == atTok::Type::value)
					{
						val = atToksIt->content;
						atToksIt++;
					}
				}
				atributes.try_emplace(key, val);
			}
			else
			{
				warning << "Unexpected atribute syntax";
				atToksIt++;
			}
		}
	}




	/*
	//Skip whitespaces
	while (parseIt != parse.end() && isspace(*parseIt))
		parseIt++;

	//find TagName
	while (parseIt != parse.end() && !isspace(*parseIt) && *parseIt!='"')
	{
		tagName += *parseIt;
		parseIt++;
	}

	//Skip whitespaces
	while (parseIt != parse.end() && isspace(*parseIt))
		parseIt++;

	//Find Atributes
	while (parseIt != parse.end())
	{
		//find Atribute Key
		string atributeKey="";
		while (parseIt != parse.end() && !isspace(*parseIt) && *parseIt != '=')
		{
			atributeKey += *parseIt;
			parseIt++;
		}

		while (parseIt != parse.end() && *parseIt != '=')
			parseIt++;

	}
	*/

	return HTMLNode(tagName, "", childNodes, atributes);
}

HTMLNode HTMLParser::parseNodeFromString(const string& tagString, HTMLNodeList childNodes/* = HTMLNodeList()*/)
{
	return parseNodeFromToken(Token(Token::Type::tag, tagString), childNodes);
}



bool operator==(const HTMLParser::Token& left, const HTMLParser::Token& right)
{
	return &left == &right;
}