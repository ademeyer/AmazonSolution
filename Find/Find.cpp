#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

enum class FileType 
{
    XML, TXT, JPG, MP3, NONE
};

// Class to represent files or directories
class File 
{
public:
    string name;
    int size;
    FileType type;
    bool isDirectory;
    vector<File*> children;

    File(string name, int size, FileType type, bool isDirectory)
        : name(name), size(size), type(type), isDirectory(isDirectory) {}

    ~File() 
    {
        for (File* child : children) 
        {
            delete child;
        }
    }

    void addChild(File* file) 
    {
        children.push_back(file);
    }
};

// Abstract filter class
class Filter 
{
public:
    virtual bool apply(const File* file) const = 0;
    virtual ~Filter() {}
};

// Filter to search files by size
class SearchBySizeFilter : public Filter 
{
    int minSize;
public:
    SearchBySizeFilter(int size) : minSize(size) {}
    bool apply(const File* file) const override 
    {
        return file->size > minSize;
    }
};

// Filter to search files by file type
class SearchByFileType : public Filter 
{
    FileType requiredType;
public:
    SearchByFileType(FileType type) : requiredType(type) {}
    bool apply(const File* file) const override 
    {
        return file->type == requiredType;
    }
};

// Class to find files based on filters
class Finder 
{
public:
    vector<File*> findFiles(const File* directory, const vector<Filter*>& filters) const 
    {
        if (!directory->isDirectory) 
        {
            throw runtime_error("Specified file is not a directory");
        }

        vector<File*> results;
        dfs(directory, filters, results);
        return results;
    }

private:
    void dfs(const File* directory, const vector<Filter*>& filters, vector<File*>& results) const 
    {
        for (const File* file : directory->children) 
        {
            if (file->isDirectory) 
            {
                dfs(file, filters, results);
            }
            else {
                if (applyFilters(file, filters)) 
                {
                    results.push_back(const_cast<File*>(file));
                }
            }
        }
    }

    bool applyFilters(const File* file, const vector<Filter*>& filters) const 
    {
        for (const Filter* filter : filters) 
        {
            if (!filter->apply(file)) 
            {
                return false;
            }
        }
        return true;
    }
};

// Function to print the result of file search
void printResult(const vector<File*>& files) 
{
    for (const File* file : files) 
    {
        cout << "Filename: " << file->name << "\tSize: " << file->size << " bytes\t"
            << (file->isDirectory ? "Directory" : "File") << endl;
    }
}

int main() 
{
    // Setup a simple file system hierarchy
    File root("root", 0, FileType::NONE, true);
    File downloadFolder("Downloads", 0, FileType::NONE, true);
    File letter("loveletter.txt", 20, FileType::TXT, false);
    File xmlFile("schema.xml", 2, FileType::XML, false);
    File picture1("profilepic.jpg", 210, FileType::JPG, false);

    root.addChild(&downloadFolder);
    downloadFolder.addChild(&letter);
    downloadFolder.addChild(&xmlFile);
    downloadFolder.addChild(&picture1);

    // Setup filters
    SearchBySizeFilter sizeFilter(5);  // Files over 5 MB
    SearchByFileType typeFilter(FileType::XML);  // All XML files

    vector<Filter*> filters = { &sizeFilter, &typeFilter };

    Finder finder;

    // Find and print XML files
    auto xmlFiles = finder.findFiles(&root, vector<Filter*>{&typeFilter});
    cout << "XML Files:" << endl;
    printResult(xmlFiles);

    // Find and print files over 5 MB
    auto largeFiles = finder.findFiles(&root, vector<Filter*>{&sizeFilter});
    cout << "Files over 5 MB:" << endl;
    printResult(largeFiles);

    return 0;
}
