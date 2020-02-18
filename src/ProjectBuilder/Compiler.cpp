#include "Compiler.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "log.h"
#include <sstream>
#include <map>
#include "HTMLParser.h"

using namespace std;

inline std::string strToIntList(std::string s) {
    stringstream retVal;
    retVal << "{";
    bool first = true;

    for (char c : s) {
        if (!first)
            retVal << ",";
        else
            first = false;

        retVal << (int) c;

    }

    retVal << "}";
    return retVal.str();
}


Compiler::Compiler(path resourcesPath, path generatedPath) :
        resoucesPath(resourcesPath),
        generatedPath(generatedPath) {

    //system("echo %cd%");

}


void Compiler::actionCompileHTML() {
    compilePath(resoucesPath / "html");

    ofstream ofs((generatedPath / "html.generated.h").string());

    ofs << "// Generated by Project Builder" << endl;
    ofs << "//" << endl;
    ofs << "//" << endl;
    ofs << "// #####################" << endl;
    ofs << "// ##  DO NOT MODIFY  ##" << endl;
    ofs << "// #####################" << endl;
    ofs << "//" << endl;

    for (path p : allGenerated) {

        ofs << "#include \"" << p.lexically_relative(generatedPath).string() << "\"" << endl;
        info << "#include \"" << p.lexically_relative(generatedPath).string() << "\"" << endl;
    }


    ofs.close();
}

void Compiler::actionCompileStatic() {
    compileStatic(resoucesPath / "static");

}


bool Compiler::compilePath(fs::path p) {
    try {

        if (fs::is_regular_file(p)) {
            if (p.extension() == ".html") {

                if (!compileFile(p))
                    return false;
            }
        } else {
            fs::directory_iterator end_itr;

            // cycle through the directory
            for (fs::directory_iterator itr(p); itr != end_itr; ++itr) {
                if (!compilePath(itr->path()))
                    return false;
            }
        }
    }
    catch (std::exception &e) {
        error << "an error ocured: " << e.what();
        return false;
    }
    catch (...) {
        error << "an error ocured";
        return false;
    }
    return true;
}


bool Compiler::compileStatic(path p) {
    try {

        std::stringstream stcInitialStream;
        std::stringstream stcNameStream;

        compileStaticFile(p, stcInitialStream, stcNameStream);


        //open StaticRecouces.h stream (writing stream)
        ofstream ofs((generatedPath / "StaticRecouces.h").string());

        //add notes to file
        ofs << "#pragma once" << endl;
        ofs << "// Generated by Project Builder" << endl;
        ofs << "//" << endl;
        ofs << "//" << endl;
        ofs << "// #####################" << endl;
        ofs << "// ##  DO NOT MODIFY  ##" << endl;
        ofs << "// #####################" << endl;
        ofs << "//" << endl;
        ofs << "#include \"../engine/StaticRecource.h\"\n#include <string>" << endl;


        ofs << endl;


        ofs << "class AllResources \n{\npublic:\nclass AllStatic \n{\npublic:\nAllStatic() \n{\n" << endl;

        ofs << stcInitialStream.str() << endl;

        ofs << "}" << endl;

        ofs << stcNameStream.str() << endl;

        ofs << "};\nAllStatic Static;\n};" << endl;
    }
    catch (std::exception &e) {
        error << "an error ocured: " << e.what();
        return false;
    }
    catch (...) {
        error << "an error ocured";
        return false;
    }

    return true;
}

constexpr unsigned int str2int(const char *str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void Compiler::compileStaticFile(path p, std::iostream &stcInitialStream, std::iostream &stcNameStream, bool writeDataIntoGenerated) {

    if (fs::is_regular_file(p)) {


        //stringstream ss;
        stringstream ssSymbol;

        stcInitialStream << "//" << p.filename().string() << endl;

        

        //ss << "const char ";

        info << p.filename().string();

        for (char c : p.filename().string()) {
            if (c == '.') {
                ssSymbol << "_";
            } else {
                ssSymbol << c;
            }
        }

        if (writeDataIntoGenerated)
        {
            ifstream ifs(p.string(), ios::binary);
            stcInitialStream << ssSymbol.str() << ".data = { ";

            bool isfirst = true;
            char c = ifs.get();
            int counter = 0;

            while (!ifs.eof()) {

                if ((int16_t)c < 0) {
                    stcInitialStream << ((isfirst) ? "" : ",") << (int16_t)c;
                }
                else {
                    stcInitialStream << ((isfirst) ? "" : ",") << "0x" << std::hex << (int16_t)c << std::dec;
                }
                int i = 0;
                c = ifs.get();
                isfirst = false;
                counter++;
            }

            stcInitialStream << " };" << endl;

            stcInitialStream << ssSymbol.str() << ".data_size = " << counter << ";" << endl;

        }
        else
        {
            stcInitialStream << ssSymbol.str() << ".data =  Resource::initializeResourceData(fs::path(\""<< p.filename().string() << "\"));"<<endl;

            stcInitialStream << ssSymbol.str() << ".data_size = " << ssSymbol.str() << ".data.size();" << endl;

        }
        stcInitialStream << ssSymbol.str() << ".content_type = std::string(\"";

        switch (str2int(p.extension().string().c_str())) {
            case str2int(".JPEG"):
            case str2int(".JPG"):
            case str2int(".jpeg"):
            case str2int(".jpg"):
                stcInitialStream << "image/jpg";
                break;
            case str2int(".PNG"):
            case str2int(".png"):
                stcInitialStream << "image/png";
                break;
            case str2int(".css"):
                stcInitialStream << "text/css";
                break;
            default:
                warning << "Static Compiler: " << p.filename().string()
                        << " Unknown File extention. Defaulting to text/plain";
                stcInitialStream << "text/plain";
                break;
        }

        stcInitialStream << "\");" << endl;

        //return ss.str();

        stcNameStream << "Resource " << ssSymbol.str() << ";" << "//" << p.filename().string() << endl;

    } else {
        fs::directory_iterator end_itr;

        stringstream ss;

        // cycle through the directory
        for (fs::directory_iterator itr(p); itr != end_itr; ++itr) {
            compileStaticFile(*itr, stcInitialStream, stcNameStream);
        }

        //return ss.str();
    }

    //return "";
}

void Compiler::htmlNodesToHtmlToken(const HTMLNodeList &nodes, list<htmlToken> &tokens, string &tokenWrite,
                                    std::map<std::string, int> &pluginPoints, int &pluginCount,
                                    std::map<std::string, int> &dataPoints, int &dataCount) {

    for (auto node : nodes) {
        //Handle Part Tags
        if (node.getTagName() == "part") {
            tokenWrite += node.getOpeningTag();

            if (node.hasAttribute("id")) {
                tokens.push_back(htmlToken{htmlTokenType::html, tokenWrite});
                tokenWrite = "";


                tokens.push_back(htmlToken{htmlTokenType::part, node.getAttribute("id")});
                pluginPoints.try_emplace(node.getAttribute("id"), ++pluginCount);
            } else {
                warning << "Part Tag has no id. Ignoring.";
            }

            tokenWrite += node.getClosingTag();

        }
            //Handle Data Tags
        else if (node.getTagName() == "data") {
            tokenWrite += node.getOpeningTag();

            if (node.hasAttribute("id")) {
                tokens.push_back(htmlToken{htmlTokenType::html, tokenWrite});
                tokenWrite = "";


                tokens.push_back(htmlToken{htmlTokenType::data, node.getAttribute("id")});
                dataPoints.try_emplace(node.getAttribute("id"), ++dataCount);
            } else {
                warning << "Data Tag has no id. Ignoring.";
            }

            tokenWrite += node.getClosingTag();
        }
            //Handle Text Nodes
        else if (node.isTextNode()) {
            tokenWrite += node.getText();
        }
            //Handle Empty nodes
        else if (node.isEmpty()) {
            tokenWrite += node.getOpeningTag();
        }
            //Handle All Other Tags
        else {
            tokenWrite += node.getOpeningTag();
            htmlNodesToHtmlToken(node.getChildrenIncludingText(), tokens, tokenWrite, pluginPoints, pluginCount,
                                 dataPoints, dataCount);
            tokenWrite += node.getClosingTag();
        }
    }


}


bool Compiler::compileFile(fs::path sourcePath) {
    //define the Path for the .html.h file (Target)
    path destPath = (generatedPath / sourcePath.lexically_relative(resoucesPath)).string() + ".h";

    //extract the Tecnical Partname
    std::string partName = destPath.filename().string().substr(0, destPath.filename().string().size() - 7);

    std::string className = "Part" + partName;

    //create the target directory if not exist
    if (!fs::is_directory(destPath.parent_path())) {
        fs::create_directories(destPath.parent_path());
    }

    //debug
    info << "Compiling: " << sourcePath << " into " << destPath;
    info << "sourcePath: " << sourcePath << " resoucesPath " << resoucesPath;
    info << "lexically_relative: " << sourcePath.lexically_relative(resoucesPath);
    info << "";

    //input stream of the .html file (source)
    ifstream ifs(sourcePath.string());

    //read .html file into string
    ifs.peek();
    string htmlString = "";
    while (!ifs.eof()) {
        htmlString += ifs.get();
        ifs.peek();
    }

    //close the .html file
    ifs.close();


    HTMLNodeList HTMLPart = HTMLParser::parseHTML(htmlString);


    //list of all tokens of the .html file
    list<htmlToken> tokens;

    //Temporary variable for tokenizing
    string tokenWrite = "";

    //plugin Points
    std::map<std::string, int> pluginPoints;
    int pluginCount = 0;

    //data Points
    std::map<std::string, int> dataPoints;
    int dataCount = 0;

    //Tokenize
    htmlNodesToHtmlToken(HTMLPart, tokens, tokenWrite, pluginPoints, pluginCount, dataPoints, dataCount);

    //create last Token
    tokens.push_back(htmlToken{htmlTokenType::html, tokenWrite});


    //open .html.h stream (writing stream)
    ofstream ofs(destPath.string());

    //add notes to file
    ofs << "// Generated by Project Builder" << endl;
    ofs << "//" << endl;
    ofs << "//" << endl;
    ofs << "// #####################" << endl;
    ofs << "// ##  DO NOT MODIFY  ##" << endl;
    ofs << "// #####################" << endl;
    ofs << "//" << endl;


    ofs << endl;


    ofs << "#pragma once\n#include \"../engine/Part.h\"\n\nclass " << className << " :public Part\n{\npublic:\n";

    ofs << "enum class PartPluginPoints{" << endl;
    for (auto pp : pluginPoints) {
        ofs << pp.first << " = " << pp.second << ((pp!=*(--pluginPoints.end()))?",":"") << endl;
    }
    ofs << "};" << endl;

    ofs << "enum class DataPluginPoints{" << endl;
    for (auto pp : dataPoints) {
        ofs << pp.first << " = " << pp.second << ((pp != *(--dataPoints.end())) ? "," : "") << endl;
    }
    ofs << "};" << endl;

    /*
    for (auto dp : dataPoints) {
        ofs << "static const int " << dp.first << " = " << dp.second << ";" << endl;
    }
    */

    ofs << className << "()\n{\n";

    for (htmlToken token : tokens) {
        ofs << "tokenList.push_back({ ";

        switch (token.type) {
            case htmlTokenType::html:

                ofs << strToIntList(token.text) << ",Token::Type::html,0";

                break;
            case htmlTokenType::part:

                ofs << strToIntList(token.text) << ",Token::Type::part," << pluginPoints.at(token.text);

                break;
            case htmlTokenType::data:

                ofs << strToIntList(token.text) << ",Token::Type::data," << dataPoints.at(token.text);

                break;
            default:
                ofs << "\"\",Token::Type::html,0";
                break;
        }

        ofs << " });" << endl;

    }

    ofs << "}\n"<<className<<" addSubpart("<< className <<"::PartPluginPoints connectionPoint, Part addedPart){\nPart::addSubpart(static_cast<int>(connectionPoint), addedPart);\nreturn *this;\n};"<<endl;

    ofs << "};\n";

    ofs.close();

    allGenerated.push_back(destPath);
    return true;
}
