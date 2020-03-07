#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "casTypes.h"

#define MAKE_PART_ID __COUNTER__

class Part;
typedef std::pair<int, Part*> PartPlugin;
typedef std::map<int, Part*> InlineParts;

class Part
{
public:
	struct Fragment
	{
	public:
		~Fragment();

		Fragment(const Fragment& f);
		
		enum Type {none, html, part };

		Fragment(int pp):type(part), pluginPoint(pp)
		{}
		
		Fragment(std::string c):type(html), content(c)
		{}
		
		static Fragment nullFragment;

		bool operator==(Fragment other);

	private:
		Fragment():type(none)
		{}

		Type type;
	public:
		Type getType() const
		{
			return type;
		}

		void setType(Type type)
		{
			this->type = type;
		}

	private:
		
		union
		{
			std::string content;	//Valid if type is html
			int pluginPoint;		//Valid if type is part
		};
	public:
		std::string getContent() const
		{

#ifdef _DEBUG
			if (type != html)
				throw std::exception("Can only get Content on html fragments");
#endif

			return content;
		}

		void setContent(const std::string& content)
		{

#ifdef _DEBUG
			if (type != html)
				throw std::exception("Can only set Content on html fragments");
#endif

			this->content = content;
		}

		int getPluginPoint() const
		{

#ifdef _DEBUG
			if (type != part)
				throw std::exception("Can only get PluginPoint on part fragments");
#endif

			return pluginPoint;
		}

		void setPluginPoint(int part_id)
		{

#ifdef _DEBUG
			if (type != part)
				throw std::exception("Can only set PluginPoint on part fragments");
#endif

			pluginPoint = part_id;
		}

	};

	Part();

	/**
	 * \brief get a specific Fragment
	 * \param index the index of the Fragment starting with 0. 
	 * \return the Fragment with the given index. If index does not exist, return Part::Fragment::nullFragment.
	 */
	virtual Fragment* getFragment(int index) =0;
	//virtual bool makeFragment(std::ostream& outStream, int index) = 0;
	//virtual void makeHtml(std::ostream& html,InlineParts inlineParts = {}) = 0;
	//virtual std::vector<Part*> getAllParts() = 0;
	virtual uint32_t getUniqueIdentifier() = 0;
	/*
	void onRequest(CasRequest& request, Poco::Net::HTTPServerResponse& response)
	{
		response.setContentType("text/html");
		makeHtml(response.send());
	}
	*/

protected:


};

