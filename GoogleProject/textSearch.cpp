#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>

using namespace std;
enum { BUFFER_SIZE = 65536 };
static int docCount = 0;

std::string execute(std::string const & command)
{
    FILE* f = fopen(command.c_str(), "r");
    if (!f)
    {
        std::cerr << "Could not execute command \"" << command << "\"\n";
        return std::string();
    }
 
    std::vector<char> output;
    char buffer[BUFFER_SIZE];
    std::size_t chars_read;
    while ((chars_read = fread(buffer, sizeof(char), BUFFER_SIZE, f)) > 0)
    {
        output.resize(output.size() + chars_read);
        std::memcpy(&(output[output.size() - chars_read]), buffer, chars_read);
 
        if (chars_read < BUFFER_SIZE)
            break;
    }
 
    fclose(f);
 
    return std::string(std::begin(output), std::end(output));
}

void writeDictionary(string filename, set<string> const & dict)
{
	filename = "dictionaries/" + filename + ".txt";
    FILE* f = fopen(filename.c_str(), "w");
    if (!f)
    {
        std::cerr << "Could not open document \"" << filename << "\"\n";
    }
  	set<string>::iterator it;
  	char* buffer;
  	for(auto it = dict.begin(); it != dict.end(); it++)
  	{
  		string word = *it;
		buffer = new char [word.length()+1];
		std::strcpy (buffer, word.c_str());
		fputs(buffer, f);
		fputs("\n", f);
  	}
  	fclose (f);
}

set<string> parse_lines_for_words(std::string const & output)
{
    regex word_re ("(Mary)+ ");
    //regex dictionary_re ("[A-Za-z]+$");
    regex dictionary_re ("(Mary)+ "); 
    string current;
 
    std::istringstream strm(output);
 	
 	int count = 0;
    std::string line;
    vector<string> lines;
    set<string> wordDictionary;
    while (std::getline(strm, line))
    {
        std::smatch match;
 
        if (std::regex_search(line, match, word_re))
        {
        	count++;
        	// cout<< "Found: " << match[1].str() << endl;
        }
       
    }

 	int state = 0;
 	istringstream stream(output);
 	 while (std::getline(stream, line))
     {
         count++;
         state = 0;
         switch(state)
         {

		         case 0: // split the line into words;
		         {
		         		size_t pos = line.find(" ");
		         		while(pos != string::npos)
		         		{
		         			string word = line.substr(0, pos);
		         			if((*(word.end()-1) > 43 && *(word.end()-1) < 47) || (*(word.end()-1) > 32 && *(word.end()-1) < 35))
	         						word.replace(word.begin(), word.end()-1, "");
	         				if((word[0] > 64 && word[0] < 91) || (word[0] > 96 && word[0] < 123))
         							wordDictionary.insert(word);		         			
		         			// cout<< "word: " << word << endl;
		         			line = line.substr(pos + 1);
		         			// cout<< "line: " << line << endl;
		         			pos = line.find(" ");

		         		}
		         		if(pos == string::npos || line.length() != 0)
		         		{
		         			if((line[0] > 64 && line[0] < 91) || (line[0] > 96 && line[0] < 123))
		         			{		
		         					stop:
		         					if((line[line.length()-1] > 43 && line[line.length()-1] < 47) || (line[line.length()-1] > 32 && line[line.length()-1] < 35))
		         					{
		         							line.erase(line.length()-1, 1);
		         							goto stop;
	         						}
		         					wordDictionary.insert(line);
		         			}

		         		}
		         		

		         		state = 1;
		         }

		         case 1://can re-enable this case if need to check the set/vector
		         {		
		         		startOver:
		         		count = 0;
		         		for(auto it = wordDictionary.begin(); it != wordDictionary.end(); it++){
		         			// cout<< count << ": " << *it << endl;
		         			size_t pos = std::string(*(it)).find_first_of(",.?!-:;)(][_\"\\ \n  \r");
		         			if(pos != -1)
		         			{
		         				set<string>::iterator search;
		         				search = wordDictionary.begin();
		         				// cout<<"\ntrue\n" << endl;
		         				string chop = *it;
		         				search = wordDictionary.find(chop);
		         				wordDictionary.erase(search);
		         				chop = chop.substr(0, pos);
		         				// cout<<"\nnew word: " << chop << endl;
		         				wordDictionary.insert(chop);
		         				goto startOver;
		         			}

		         			count++;
		         		}

		         		state = 2;
		         }

		         case 2: 
		         {
			         	if(state == 2)
			         		continue;
		         }

		 }
     }

    stringstream os; 
  	os << "dictionary" << docCount++;
	writeDictionary(os.str(), wordDictionary);

	return wordDictionary;
}

template <typename T> 
class dictionaries
{
	public:
			dictionaries(){};
			~dictionaries(){};

			void place(T book, T word)
			{
				storage.insert(valuePair(book, word));//Map
				library.insert(book);//set
			}

			void showLibrary()
			{
				int count = 1;
				for(auto it = library.begin(); it != library.end(); it++)
					cout << "[" << count++ <<"] Book Name: " << *it << "\n";//use *it because this is a set iterator
			}

			void printDictionary()
			{
				for(auto it = storage.begin(); it != storage.end(); it++)
					cout << "Book [" << it->first << "]:\t" << it->second << "\n";
			}

			void printDictionary(T book)
			{
				for(auto it = storage.begin(); it != storage.end(); it++)
				{
				 	if(it->first == book)
				 		cout << "Book [" << it->first <<"]:\t" << it->second << "\n";
				 	else if(it->first > book)
				 		break;
				}
			}

			void searchWordInDictionarys(T word)
			{
				int matchesFound = 0;
				for(auto it = storage.begin(); it != storage.end(); it++)
				{
				 	if(it->second == word)
				 	{
				 		cout << "Word found in: " << it->first << "\n";
				 		matchesFound++;
				 	}
				}

				cout << "\n(Word, Matches Found): (" << word <<", " << matchesFound << ").\n\n";
			}

	private:
			typedef multimap<T, T> tMap;
			typedef pair<T, T> valuePair;
			tMap storage;
			set<T> library;
};


int main(int argc, char** argv)
{
	int bookCount=1;
	// for(char** arg = argv + 1; arg != argv + argc; ++arg)
	dictionaries<string> libraryDictionary;
	
	string output = execute("books/MaryHadALittleLamb-mini.txt");
	set<string> marydictionary = parse_lines_for_words(output);	
	for(auto it = marydictionary.begin(); it!= marydictionary.end(); it++)
		libraryDictionary.place("mary had a little lamb", *it);
	bookCount++;

	output = execute("books/Twain-TheAdventuresOfTomSawyer-mini.txt");
	set<string> tomsawyerdictionary = parse_lines_for_words(output);
	for(auto it = tomsawyerdictionary.begin(); it!= tomsawyerdictionary.end(); it++)
		libraryDictionary.place("tom sawyer", *it);
	bookCount++;
	
	output = execute("books/Dickens-OliverTwist-mini.txt");
	set<string> olitwistdictionary = parse_lines_for_words(output);
	for(auto it = olitwistdictionary.begin(); it!= olitwistdictionary.end(); it++)
		libraryDictionary.place("oliver twist", *it);
	bookCount++;

	output = execute("books/Dickens-GreatExpectations-mini.txt");
	set<string> greatextdictionary = parse_lines_for_words(output);
	for(auto it = greatextdictionary.begin(); it!= greatextdictionary.end(); it++)
		libraryDictionary.place("great expectations", *it);
	bookCount++;	

	output = execute("books/Carroll-AliceInWonderland-mini.txt");
	set<string> aliceinwondictionary = parse_lines_for_words(output);
	for(auto it = aliceinwondictionary .begin(); it!= aliceinwondictionary .end(); it++)
		libraryDictionary.place("alice in wonderland", *it);
	bookCount++;

	output = execute("books/Barrie-PeterPan-mini.txt");
	set<string> peterpandictionary = parse_lines_for_words(output);
	for(auto it = peterpandictionary .begin(); it!= peterpandictionary .end(); it++)
		libraryDictionary.place("peter pan", *it);
	bookCount++;

	// libraryDictionary.printDictionary();

	cout<< "\n-------------------------------------\n";
	cout<< "\n-------------------------------------\n\n";
	cout<< "The dictionaries available are:\n\n";
	libraryDictionary.showLibrary();
	cout<< "\n-------------------------------------\n";
	cout<< "\n-------------------------------------\n\n";
	cout<< "User word search:\n\n";
	libraryDictionary.searchWordInDictionarys("Mary");
	cout<< "\n-------------------------------------\n";
	cout<< "\n-------------------------------------\n";	

	return 0;
}
