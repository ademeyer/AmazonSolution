/*
Coding - Logical and Maintainable:
Implement Linux find command as an API. The API will support finding files that:

* Files that have a given size requirement.
* Files with a certain naming pattern.

Focus on 2 uses cases at first:

* Find all files over 5 MB somewhere under a directory.
* Find all XML files somewhere under a directory.

The question is:
* Design the classes and/or interfaces.
* Implement the core components.
* Keep in mind that these are just 2 uses cases and that the library should be flexible.
* Write out the code snippets showing how you would use this library.
*/


#include <iostream>
#include <vector>

using namespace std;

enum class FILETYPE
{
    XML = 0,
    TXT,
    JPG,
    MP3,
    NONE,
};

// file class to hold each entity
class File
{
public:
    string name;
    int size;
    FILETYPE type;
    bool isDirectory;
    vector<File*> children;

    File(string Name, int Size, FILETYPE Type, bool isDir) :
        name(Name), size(Size), type(Type), isDirectory(isDir)
    {}

    // clean ups
    ~File()
    {
        for (auto* child : children)
        {
            delete child;
        }
    }

    void addChildren(File* file)
    {
        children.push_back(file);
    }
};

// search filter interface
class Filter
{
public:
    virtual bool apply(const File* file) const = 0;
    virtual ~Filter(){}
};

// implemention of search classes
class SearchBySizeFilter : public Filter
{
    int _size;
public:
    SearchBySizeFilter(const int size) : _size(size){}
    bool apply(const File* file) const override
    {
        return file->size > _size;
    }
};

class SearchByFileType : public Filter
{
    FILETYPE _type;
public:
    SearchByFileType(const FILETYPE type) : _type(type) {}
    bool apply(const File* file) const override
    {
        return file->type == _type;
    }
};

/* Followup Question */
class AndFilter : public Filter
{
    vector<Filter*> filters;
public:
    AndFilter(const vector<Filter*>& Filters) : filters(Filters){}

    bool apply(const File* file) const override
    {
        for (auto& filter : filters)
        {
            if (!filter->apply(file))
            {
                return false;
            }
        }
        return true;
    }
};

class OrFilter : public Filter
{
    vector<Filter*> filters;
public:
    OrFilter(const vector<Filter*>& Filters) : filters(Filters) {}

    bool apply(const File* file) const override
    {
        for (auto& filter : filters)
        {
            if (filter->apply(file))
            {
                return true;
            }
        }
        return false;
    }

};
/* Followup Question */
// Implemention of Find class
class Find
{
    // find recursively using DFS
    void FindWithFilters(const File* Dir, const vector<Filter*>& filters, vector<File*>& output)
    {
        if (Dir->children.empty())
        {
            return;
        }

        for (const auto& file : Dir->children)
        {
            if (file->isDirectory)
            {
                FindWithFilters(file, filters, output);
            }
            else // it is a file
            {
                bool selectFile = true;
                for (const auto& filter : filters)
                {
                    if (!filter->apply(file))
                    {
                        selectFile = false;
                        break;
                    }
                }
                if (selectFile)
                    output.push_back(file);
            }
        }
    }
public:
    vector<File*> FindWithFilters(const File* Dir, const vector<Filter*>& filters)
    {
        if (!Dir->isDirectory)
        {
            throw runtime_error("No such path exists!\n");
        }

        vector<File*> results;
        this->FindWithFilters(Dir, filters, results);
        return results;
    }
};

void printResult(const vector<File*>& files)
{
    for (const auto& file : files)
    {
        // print file name, size, isdir
        cout << "Filename: " << file->name << "\tsize: " << file->size << "byte(s)\tIs" << (file->isDirectory ? "" : "Not") << " directory" << endl;
    }
    cout << endl;
}


int main()
{
    File* root = new File("root", 0, FILETYPE::NONE, true);
    File* DownloadFolder = new File("Downloads", 0, FILETYPE::NONE, true);
    File* letter = new File("loveletter", 20, FILETYPE::TXT, false);
    File* XMLFile = new File("schema", 2, FILETYPE::XML, false);
    File* Picture1 = new File("profilepic", 210, FILETYPE::JPG, false);
    File* Picture2 = new File("Arielpic", 410, FILETYPE::JPG, false);
    File* sysfile = new File("Div", 210, FILETYPE::XML, false);

    DownloadFolder->addChildren(letter);
    DownloadFolder->addChildren(XMLFile);
    DownloadFolder->addChildren(Picture1);
    DownloadFolder->addChildren(Picture2);

    root->addChildren(DownloadFolder);
    root->addChildren(sysfile);

    // create filters
    vector<Filter*> filter1{ (new SearchBySizeFilter(20))};
    vector<Filter*> filter2{ (new SearchByFileType(FILETYPE::XML)) };
    vector<Filter*> filter3{ (new SearchBySizeFilter(20)), (new SearchByFileType(FILETYPE::XML)) };
    
    Find find;
    auto res = find.FindWithFilters(root, filter1);
    printResult(res);

    res = find.FindWithFilters(root, filter2);
    printResult(res);

    res = find.FindWithFilters(root, filter3);
    printResult(res);

    cout << "\n";
}

