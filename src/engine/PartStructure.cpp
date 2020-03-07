#include "PartStructure.h"

#include <stack>

PartStructure::PartStructure()
{
}

PartStructure::PartStructure(Part* part)
{
	rootNode = PSNode(part);
}


Part* PartStructure::getPart()
{
	return rootNode.part;
}

PartStructure PartStructure::at(int index) const
{
	return PartStructure(&rootNode.at(index));//TODO Make refferencial
}

PartStructure PartStructure::add(int index, PartStructure ps)
{
	return add(index, ps.rootNode);
}

PartStructure PartStructure::add(int index, Part* part)
{
	return add(index, PSNode(part));
}

void PartStructure::onRequest(const CasRequest& request, Poco::Net::HTTPServerResponse& response)
{
	if (rootNode.part != nullptr)
	{
		/*
		InlineParts ip;
		for (auto node : rootNode.children)
		{
			ip.emplace(node.first, node.second.part);
		}
		std::ostream& os = response.send();
		rootNode.part->makeHtml(os,ip);
		os.flush();
		*/
		std::ostream& os = response.send();
		std::stack<std::pair<PSNode, int>> stack;
		stack.push({ rootNode,0 });


		while (!stack.empty())
		{
			Part::Fragment* f = stack.top().first.part->getFragment(stack.top().second);

			switch (f->getType())
			{
			case Part::Fragment::none:
				stack.pop();
				if(!stack.empty())
					stack.top().second++;
				break;

			case Part::Fragment::html:
				os << f->getContent();
				stack.top().second++;
				break;

			case Part::Fragment::part:
			{
				try
				{
					auto n = stack.top().first.at(f->getPluginPoint());
					stack.push({ n,0 });
				}
				catch (...)
				{
					stack.top().second++;
				}

				break;
			}

			default:

				break;
			}
		}

		os.flush();
	}
	else
	{
		std::ostream& os = response.send();
		os << "";
		os.flush();
	}
}

PartStructure::PSNode::PSNode(Part* part)
{
	this->part = part;
}

PartStructure::PSNode PartStructure::PSNode::at(int index) const
{
	return children.at(index);
}

PartStructure PartStructure::add(int index, PSNode node)
{
	rootNode.children.emplace(index, node);
	return *this;
}
