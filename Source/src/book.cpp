#include "book.hpp"
#include <iostream>
#include <fstream>

using namespace text;

Book::Book(project::Global* g)
{
    mG = g;
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
    std::string filePath = "../../" + mG->json_dir + "/" + "test.json"; // fix this to a dynamic name

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
        if (mG -> gVerbose > 0) std::cout << "Page number doesn't exist in file!\n";
        return;
    }

    mPage->sLabel = tJson[strPageNumber]["Label"].get<std::string>();

    if (mPage->sLabel.empty())
    {
        if (mG -> gVerbose > 0) std::cout << "Label doesn't exist or failed to set\n";
        return;
    }

    if (mG -> gVerbose > 0) std::cout << "Label set to " + mPage->sLabel + "\n";
}

void Book::print_page()
{
    if (mPage == nullptr)
    {
        std::cout << "Page not initialized!";
        return;
    }

    std::cout << "Label: " + mPage->sLabel;
}