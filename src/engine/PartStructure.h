#pragma once
#include "part/Part.h"

class PartStructure
{
public:
	template <typename T>
	PartStructure(T part);
	PartStructure();
	PartStructure(Part* part);

	Part* getPart();

	PartStructure at(int index) const;
	
	template<typename T>
	PartStructure add(int index, T part);
	PartStructure add(int index, PartStructure ps);
	PartStructure add(int index, Part* part);

	void onRequest(const CasRequest& request, Poco::Net::HTTPServerResponse& pairs);

private:
	struct PSNode
	{
		PSNode() = default;
		PSNode(Part* part);

		Part* part = nullptr;
		std::map<int, PSNode> children;
		PSNode at(int index) const;
	};
	
	PartStructure add(int index, PSNode node);

	PartStructure(PSNode * node)
	{
		rootNode = *node;
	}

	PSNode rootNode;
};

template <typename T>
PartStructure::PartStructure(T part)
{
	rootNode = PSNode(part.getInstance());
}


template <typename T>
PartStructure PartStructure::add(int index, T part)
{
	return add(index, static_cast<Part*>(part.getInstance()));
}

