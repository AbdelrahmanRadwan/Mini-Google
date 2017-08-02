/*
 * required for cin and cout
 */
#include <iostream>

/*
 * required for ifstream
 */
#include<fstream>

/*
 * required for the string type
 */
#include<string.h>

/*
 * The dirent library is required for listing the files in a given folder. It 
 * is integrated into the g++ compiler. It can also be installed for VC.net.
 */
#include <dirent.h>

/*
 * required for using the vector and the map STL classes.
 */
#include<vector>
#include<map> 

/*
 * if "using namespace std", one would need to add the scope resolution before
 * cin, cout, etc (e.g., std::cin, std::cout)
 */
using namespace std;


/*
 * The ListDir function gets a folder path and fills a vector with all the file
 * names inside this folder. There is no standard C++ code that works on all 
 * operating systems to do this task. One either needs to use a cross platform
 * library (such as Boost), or re-write the function for every intended
 * operating system. In the following function, I use the dirent library, which
 * works on both linux and windows. If you use VC++.net, you will probably need
 * to manually install the library. Ask Google about this. 
 */
int ListDir(const char *path, vector<string>& fileName) 
{
  struct dirent *entry;
  DIR *dp;
 
  dp = opendir(path);
  if (dp == NULL) {
    cout<<"opendir: Path does not exist or could not be read.";
    return -1;
  }
 
  entry = readdir(dp);
  while (entry != NULL)
  {
    fileName.push_back(entry->d_name);
    entry = readdir(dp);
  }
 
  closedir(dp);
  return fileName.size();
}








/*
 * The IsStopWord function helps ignoring the unimportant words from the search
 * index. 
 */
bool IsStopWord(char* word)
{
  if(strlen(word) < 3) 
    return true;
  if(word == "the" || word == "she" || word == "Mrs" || word == "not" ||
     word == "and" || word == "her" || word == "his" || word == "they" ||
     word == "was" || word == "for" || word == "all" || word == "too" ||
     word == "but" || word == "with" || word == "him" || word == "had" )
    return true;
}




/*
 * The AddToIndex function is the main function in the indexing part of our
 * miniGoogle. It gets a word and its position in the dataset, and inserts them
 * in the index. 
 */ 
void AddToIndex(
  char* word, 
  string fileName, 
  int lineNumber, 
  map< string, vector< pair<string, int> > >& index)
{
// try to locate the word in the index
  map< string, vector< pair<string, int> > >::iterator entryReference=
    index.find(word);
    
// if the word is new (never added to the index before), create a new entry.
  if(entryReference == index.end())
  {
    pair<string, int> newEntryLocation= make_pair(fileName, lineNumber);
    vector< pair<string, int> > newEntryLocations;
    newEntryLocations.push_back(newEntryLocation);
    //cerr<<"1";
    index[word]= newEntryLocations;
    //cerr<<"2";
  }
// if the word already exists in the index, add a new location for its list of 
// locations.
  else
  {
    pair<string, int> newEntryLocation= make_pair(fileName, lineNumber);
    //cerr<<"3";
    (*entryReference).second.push_back(newEntryLocation);
    //cerr<<"4";
  }
}















/*
 * The IndexFile function pareses a given file, enumerates all the words in it,
 * and inserts them in the search engine.
 */ 
void IndexFile(
  string pathName, 
  map< string, vector< pair<string, int> > >& index )
{
  ifstream inFile(pathName.c_str(), ifstream::in);
  char line[1000];
  char delimiters[]=" .,!?(){}\"-+&%;<>'";
  char* token;
  int lineNumber=0;
  while(! inFile.eof())
  {
    inFile.getline(line, 1000);
    ++lineNumber;
// Ask Google about the strtok function used for tokenizing strings.    
    token= strtok(line, delimiters);
    while(token != NULL)
    {
      if(! IsStopWord(token))
        AddToIndex(token, pathName, lineNumber, index);
      token= strtok(NULL, delimiters);
    }
  }
  inFile.close();
}




int main() 
{
  int item;
  vector<string> fileName;
  map< string, vector< pair<string, int> > > index;

// the indexing part.  
  int numFiles= ListDir("text/", fileName);

  for (int i=3; i<numFiles; ++i)
  {
    cerr<<endl<<"Started indexing file :"<< fileName[i]<< " number:" <<i ;
    IndexFile("text/" + fileName[i], index);
    cerr<<endl<<"\tFinished indexing file";
  }
  cout<<"\nNumber of entries :" << index.size();
  
 
  return 0;
}