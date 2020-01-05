#pragma once
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <list>
#include <cctype>

using std::string;
using std::vector;

typedef std::pair<string, string> HTMLnodeAttribut;
typedef std::map<string, string> HTMLnodeAttributList;

class HTMLNode;

class HTMLNodeList :public vector<HTMLNode>
{
public:

};

class HTMLNode
{
public:
	HTMLNode(const string& tagName, const string& text, HTMLNodeList childNodes, HTMLnodeAttributList attributs);
	HTMLNode(const string& text);

	//getter / setter
	string getTagName() const;

	bool isTextNode() const;
	string getText() const;

	bool isEmpty() const;

	string getAttribute(const string& key) const;
	bool hasAttribute(const string& key) const;
	HTMLnodeAttributList getAllAttributes() const;

	string getOuterHTML() const;
	//void setOuterHTML(const string &rawHtml); // parsing

	string getInnerHTML() const;
	//void setInnerHTML(const string &rawHtml); // parsing

	string getOpeningTag() const;
	string getClosingTag() const;

	HTMLNodeList getChildren() const;
	HTMLNodeList getChildrenIncludingText() const;

private:
	string tagName;
	string text;
	HTMLNodeList childNodes;
	HTMLnodeAttributList attributs;



	friend std::ostream& operator<<(std::ostream& os, const HTMLnodeAttributList& attrs);

};

std::ostream& operator<<(std::ostream& os, const HTMLnodeAttribut& attr);
std::ostream& operator<<(std::ostream& os, const HTMLnodeAttributList& attrs);
std::ostream& operator<<(std::ostream& os, const HTMLNode& node);
std::ostream& operator<<(std::ostream& os, const HTMLNodeList& nodes);


class HTMLParser
{
public:
	static HTMLNodeList parseHTML(const string& html);

//private:
	struct Token
	{
		enum Type { text, tag };

		Token(Type t, string v) :type(t), value(v) {}

		Type type;
		string value;

		bool isClosingTag()
		{
			return
				(value.size() > 2) &&
				(type == tag && (value.at(1) == '/' /*|| value.substr(value.size()-2) == "/>"*/));
		}

		string getTagName()
		{
			if (type != tag)
				return "";
			if (value.size() < 3)
				return "";

			string tagName = "";
			string checking;

			if (isClosingTag())
				checking = value.substr(2);
			else
				checking = value.substr(1);

			for (unsigned char c : checking)
			{
				if(isspace(c)||c=='>')
					return tagName;

				tagName += c;
			}

			return "";
		}
	};
	using TokenList = std::list<Token>;

	static HTMLNodeList parseNodesFromTokenIterator(TokenList::iterator& tokenIt, const TokenList::iterator& endIt);

	static HTMLNode parseFirstNodeFromTokenList(TokenList& tokens);

	static HTMLNode parseNodeFromToken(const Token & token, HTMLNodeList childNodes = HTMLNodeList());
	static HTMLNode parseNodeFromString(const string & tagString, HTMLNodeList childNodes = HTMLNodeList());

	friend bool operator==(const HTMLParser::Token& left, const HTMLParser::Token& right);
};

bool operator==(const HTMLParser::Token& left, const HTMLParser::Token& right);