#pragma once
#include <string>
#include <vector>
#include <map>
#include <ostream>

using std::string;
using std::vector;

typedef std::pair<string, string> HTMLnodeAttribut;
typedef std::map<string, string> HTMLnodeAttributList;

class HTMLNode;

class HTMLNodeList :public vector<HTMLNode>
{

};

class HTMLNode
{
public:
	HTMLNode();

	//getter / setter
	string getTagName() const;

	bool isTextNode() const;
	string getText() const;

	string getAttribute(string key) const;
	bool hasAttribute(string key) const;
	HTMLnodeAttributList getAllAttributes() const;

	string getOuterHTML() const;
	void setOuterHTML(string rawHtml); // parsing
	string getInnerHTML() const;
	void setInnerHTML(string rawHtml); // parsing
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


class HTMLParser
{

};