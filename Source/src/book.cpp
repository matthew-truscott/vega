#include <iostream>
#include <fstream>

#include "book.hpp"
#include "filepath.h"

using namespace text;

Book::Book(project::Global* g, utils::Fun* f, entity::Actor* p)
{
    mG = g;
    mF = f;
    mProtagonist = p;
    if (mG->gVerbose > 0) std::cout << "Book Constructor\n";
    mPage = nullptr;
}

Book::~Book()
{
    if (mG->gVerbose > 0) std::cout << "Book Destructor\n";
}

void Book::read_page(int pageNumber)
{
    // debug
    if (mG->gVerbose > 0) std::cout << "Calling Book::read_page\n";

    // read in JSON file (see nlohmann library)
    std::string filePath = "../../" + mG->json_dir + "/" + filepath::getBookFile(); // fix this to a dynamic name

    if (mG->gVerbose > 0) std::cout << "filepath is " + filePath + "\n";

    json tJson;

    std::ifstream inputFile(filePath);
    if (!inputFile) 
    {
        std::cout << "The file doesn't exist!\n";
        std::cout << "Exiting gracefully...\n"; // handle this in the future
        return;
    }

    inputFile >> tJson;

    if (mG->gVerbose > 0) std::cout << "json allocated\n";

    // clear and regen page object
    if (mPage != nullptr) delete mPage;
    mPage = new Page; // check if dynamic allocation is okay here
    
    // get page number and save to page object
    std::string strPageNumber = std::to_string(pageNumber);

    if (mG->gVerbose > 0) std::cout << "Page number set to " + strPageNumber + "\n";

    // need a nice way to throw exception and handle if the page number is non-existent
    bool existPageNumber = false;
    for (json::iterator it = tJson.begin();
         it != tJson.end();
         ++it)
    {
        // check strings!
        if (it.key() == strPageNumber) 
        {
            existPageNumber = true;
            break;
        }
    }

    if (!existPageNumber)
    {
        if (mG->gVerbose > 0) std::cout << "Page number doesn't exist in file!\n";
        return;
    }

    // read label
    mPage->sLabel = tJson[strPageNumber]["Label"].get<std::string>();
    if (mPage->sLabel.empty())
    {
        if (mG->gVerbose > 0) std::cout << "Label doesn't exist or failed to set\n";
        return;
    }
    if (mG->gVerbose > 0) std::cout << "Label set to: " + mPage->sLabel + "\n";

    // read content
    mPage->sContent = tJson[strPageNumber]["Text"].get<std::string>();
    if (mPage->sContent.empty())
    {
        if (mG->gVerbose > 0) std::cout << "Content doesn't exist or failed to set\n";
        return;
    }
    if (mG->gVerbose > 0) std::cout << "Content set to: " + mPage->sContent + "\n";

    // read parameters
    std::vector<std::string> tVecParam = tJson[strPageNumber]["Parameters"]
            .get<std::vector<std::string>>();
    if (tVecParam.size() != 0) mPage->sVecParam = tVecParam;
    else
    {
        if (mG->gVerbose > 0) std::cout << "No parameters set\n";
    }
    if (mPage->sVecParam.size() > 0 && mG->gVerbose > 0) 
    {
        std::cout << "Paramters set to: ";
        for (std::vector<std::string>::const_iterator i = mPage->sVecParam.begin();
             i != mPage->sVecParam.end();
             ++i)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }

    // read functions
    std::vector<std::string> tVecFunc = tJson[strPageNumber]["Functions"]
            .get<std::vector<std::string>>();
    /*if (tVecFunc.size() != 0)
    {
        for (int i=0; i<tVecFunc.size(); ++i)
        {
            mPage->sVecFunc.push_back(tVecFunc[i]);
        }
    }*/
    if (tVecFunc.size() != 0) mPage->sVecFunc = tVecFunc;
    else
    {
        if (mG->gVerbose > 0) std::cout << "No functions set\n";
    }
    if (mPage->sVecFunc.size() > 0 && mG->gVerbose > 0) 
    {
        std::cout << "Functions set to: ";
        for (std::vector<std::string>::const_iterator i = mPage->sVecFunc.begin();
             i != mPage->sVecFunc.end();
             ++i)
        {
            std::cout << *i << " ";
        }
        std::cout << "\n";
    }

    // read settings
    std::vector<std::string> tVecSetting = tJson[strPageNumber]["Settings"]
            .get<std::vector<std::string>>();
    if (tVecSetting.size() != 0)
    {
        for (std::vector<std::string>::const_iterator i = tVecSetting.begin();
             i != tVecSetting.end();
             ++i)
        {
            size_t tPosOpen = i->find(mG->setting_delimiter_open);
            size_t tPosClose = i->find(mG->setting_delimiter_close);
            size_t tLenOpen = mG->setting_delimiter_open.length();
            size_t tLenClose = mG->setting_delimiter_close.length();

            std::string tLabel = i->substr(0, tPosOpen);
            std::string tOpts = i->substr(tPosOpen+tLenOpen, 
                tPosClose-(tPosOpen+tLenOpen));

            std::vector<std::string> tVecOpt;

            size_t last = 0;
            size_t next = 0;
            while ((next = tOpts.find(mG->setting_delimiter_sep, last)) 
                   != std::string::npos)
            {
                tVecOpt.push_back(tOpts.substr(last, next-last));
                last = next + mG->setting_delimiter_sep.length();
            }
            tVecOpt.push_back(tOpts.substr(last));

            utils::State* tState = new utils::State(tLabel, tVecOpt);
            mPage->sVecState.push_back(tState);
        }
    }

    if (!mPage->sVecState.empty() && mG->gVerbose > 0)
    {
        std::cout << "Settings: \n";
        for (std::vector<utils::State*>::const_iterator i = mPage->sVecState.begin();
             i != mPage->sVecState.end();
             ++i)
        {
            std::cout << "\tLabel: " + (*i)->getname() + "\n";
            std::cout << "\t\tOptions: " + (*i)->list_states() + "\n";
            std::cout << "\t\tCurrent State: " + (*i)->read_state() + "\n";
        }
        std::cout << "\n";
    }

    // read cases
    std::map<std::string, std::string> tMapCase = tJson[strPageNumber]["Cases"]
            .get<std::map<std::string, std::string>>();

    mPage->sCase = new utils::Case(mG, mPage->sVecState, &tMapCase);

    // page read complete!
    if (mG->gVerbose > 0) std::cout << "\nPage Reading Complete!\n\n"; 


}

void Book::print_page()
{
    if (mPage == nullptr)
    {
        std::cout << "Page not initialized!";
        return;
    }

    std::cout << mPage->sContent << "\n";
}

int Book::check_input(std::string functionInput, std::vector<std::string> paramInput)
{
    // reset stuff
    mFunc.clear();
    mVecParam.clear();

    // exact pattern match against the vector of functions
    for (auto iter = mPage->sVecFunc.begin(); iter != mPage->sVecFunc.end(); ++iter)
    {
        if (iter->compare(functionInput) == 0)
        {       
            mFunc = *iter;
            break;
        }
    }

    // exact pattern match against the vector of parameters
    for (auto iter = mPage->sVecParam.begin(); iter != mPage->sVecParam.end(); ++iter)
    {
        for (auto jter = paramInput.begin(); jter != paramInput.end(); ++jter)
        {
            if (iter->compare(*jter) == 0)
            {
                mVecParam.push_back(*iter);
                break;
            }
        }
    }

    // execute function if valid
    if (mFunc.empty())
    {
        if (mG->gVerbose > 0) std::cout << "Function not in instance.\n";
        return 1;
    }
    else
    {
        // check parameters required in function
        int nArgs = mF->GetNumArg(mFunc);
        if (mG->gVerbose > 0) 
        {
            std::cout << "Function " << mFunc << " narg=" << nArgs << "\n";
        }

        if (nArgs == 0)
        {
            // execute function, no input parameters required
            mF->ExecFunction(mFunc, &mVecParam, mPage, mProtagonist);
        }
    }


    return 0;
}
