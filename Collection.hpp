#ifndef COLLECTION_HPP
#define COLLECTION_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct record;
struct genre;
struct edgeRecord{
    record *r = NULL;
    int adjListens = 0;
};

struct genre{
  record *root = NULL;
  string genreName = "";
  genre* next = NULL;
  int counter = 0;
};

struct record{
  int recordNumber = 0;
  string name = "";
  string artist = "";
  int year = -1;
  genre* genre = NULL;
  int numListens = 0;
  float rating = -1;
  int counter = 0;
  bool visited = false; //For Dijkstra's with graph
  int distance = 0; //For Djikstra's with graph
  record *prev = NULL; //For Djikstra's with graph
  vector<edgeRecord> adj;

  record *artistLeft = NULL;
  record *artistRight = NULL;
  record *artistParent = NULL;

  record *nameLeft = NULL;
  record *nameRight = NULL;
  record *nameParent = NULL;

  record *yearLeft = NULL;
  record *yearRight = NULL;
  record *yearParent = NULL;

  record *genreLeft = NULL;
  record *genreRight = NULL;
  record *genreParent = NULL;

  record *numListensLeft = NULL;
  record *numListensRight = NULL;
  record *numListensParent = NULL;

  record *ratingLeft = NULL;
  record *ratingRight = NULL;
  record *ratingParent = NULL;
};

class Collection{
  private:
    vector<record*> records;
    string currFolderName;
    genre* genresHead;
    record* artistRoot;
    record* nameRoot;
    record* yearRoot;
    record* numListensRoot;
    record* ratingRoot;
    int currCounter;
    int numRecords;
    int numGenres;
    vector<record*> log;
    queue<record*> listeningQ;
  public:
    Collection();
    // ~Collection();

    //----------Tree functions----------
    void addNameTree(record* addRec);
    void addArtistTree(record* addRec);
    void addYearTree(record* addRec);
    void addNumListensTree(record* addRec);
    void addRatingTree(record* addRec);
    void addGenreTree(record* addRec, genre* addGenre);
    genre* newGenre(string genreName);

    void delNameTree(record* delRec);
    void delArtistTree(record* delRec);
    void delYearTree(record* delRec);
    void delNumListensTree(record* delRec);
    void delRatingTree(record* delRec);
    void delGenreTree(record* delRec);
    void delRecord(record* delRec);

    record* getYearRoot();
    record* getRatingRoot();
    record* getArtistRoot();
    record* getNameRoot();
    record* getNumListensRoot();

    //----------Graph functions----------
    void addEdge(record* r1, record* r2, int num);
    void addRecord(int number, string name, string artist, int year, string genreInp, int numListens, float rating);
    void resetRecordCounters();
    int getCurrCounter();
    record* returnCounterRecord(int recCounter);
    record* returnGenreRoot(int genreCounter);
    bool collectionEmpty();
    int getNumGenres();
    int getNumRecords();
    void setNumRecords(int numRec);
    void setFolderName(string foldName);
    void addToLog(record* addRec);
    void addToQueue(record* addRec);
    void removeFromQueue(int pos);
    void setAllRecordsUnvisited();
    bool antiDijkstra(record* startRec, record* endRec);
    void longestPath(record* checkRec, record* s1Rec);

    //----------File i/o functions----------
    void saveCollection();
    bool loadCollection(string folderName); //Returns true if collection found,
    //false if not.

    //----------Printing functions----------
    void printNameArtist(record *printRec);
    void printYear(record *printRec);
    void printOneGenre(record *printRec);
    void printNumListens(record *printRec);
    void printRating(record *printRec);
    void printYearRange(record *printRec, int low, int high);
    void printMinRating(record *printRec, float minRating);
    void printAllGenres();
    void printFromGenre(record* printRec); //Takes the root of a genre as input
    void printAllByArtist(record *printRec);
    void printAllByName(record *printRec);
    void printAllByYear(record *printRec);
    void printAllByGenre();
    void printAllByNumListens(record *printRec);
    void printAllByRating(record *printRec);
    void printListeningLog();
    int printQueue();
    void printReccInGenre(record* currRec, genre* reccGenre);

    void print2DUtilHelper(record *currNode, int space);
    void print2DUtil( int space);
};

#endif
