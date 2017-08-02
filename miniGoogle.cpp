using namespace std;
#include<iostream>
#include<vector>
#include<dirent.h>
#include<fstream>
#include<string.h>
#include<map>

int LoadFiles(string path, vector<string>& fileName)
{
  dirent *entry;
  DIR *dp;
 
  dp = opendir(path.c_str());
  if (dp == NULL) {
    cout<<"opendir: Path does not exist or could not be read.";
    return -1;
  }
 
  entry = readdir(dp);
  while (entry != NULL)
  {
    if(entry->d_name[0]!='.')
      fileName.push_back(entry->d_name);
    entry = readdir(dp);
  }
 
  closedir(dp);
  return fileName.size();
}

bool IsStopWord(string token)
{
  if(token.length() < 3)
    return true;
  if(token== "the" || token== "this" || token== "they" ||
    token== "and" ||token== "has" ||token== "have" ||
    token== "their" ||token== "our" ||token== "for" ||
    token== "that" ||token== "can" ||token== "off" ||
    token== "into" ||token== "else" ||token== "could")
    return true;
  return false;
}


void AddToIndex(string token, string pathName, int lineNumber,
  map<string, vector<pair<string, int> > >& index)
{
  map<string, vector<pair<string, int> > >::iterator 
      loc=  index.find(token);
  pair<string, int> location= 
	make_pair<string, int>(pathName, lineNumber);

  if(loc== index.end())
  {
    //token is new
    vector<pair<string, int> > locations;
    locations.push_back(location);
    index[token]= locations;    
  }
  else
  {
    //token already exist
    (*loc).second.push_back(location);
  }
}





void IndexFile(string pathName, 
  map<string, vector<pair<string, int> > >& index )
{
  ifstream inFile(pathName.c_str(), ifstream::in);
  char line[1000];
  char delimiters[]=" ,.;()!+-=/*<>{}[]&%#@?";
  char* token;
  int lineNumber=0;
  while(! inFile.eof() )
  {
    inFile.getline(line,1000);
    ++lineNumber;
    token= strtok(line, delimiters);
    while(token != NULL)
    {
      if(! IsStopWord(token) )
	 AddToIndex(token, pathName, lineNumber, index);
      token= strtok(NULL, delimiters);
    }
  }
  inFile.close();
}

int main()
{
  vector<string> fileNames;
  map<string, vector<pair<string, int> > > index;
  int numFiles= LoadFiles("text/", fileNames);
  cout<< numFiles << " exist in this folder";
  for(int i=0; i< numFiles; ++i)
  {
      string filePath= "text/" + fileNames[i];
      cout<<"\nStart indexing the file: "<< filePath;
      IndexFile(filePath, index);
      cout<<"\nFinished indexing the file: "<< filePath;
  }
  cout<<endl<<endl<<"This index has "<<index.size()<<" entries";
 
  return 0;
}
