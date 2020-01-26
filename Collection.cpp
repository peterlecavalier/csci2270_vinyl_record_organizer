#include "Collection.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
using namespace std;
#define COUNT 10

Collection::Collection(){
  currFolderName = "";
  genresHead = NULL;
  artistRoot = NULL;
  nameRoot = NULL;
  yearRoot = NULL;
  numListensRoot = NULL;
  ratingRoot = NULL;
  currCounter = 0;
  numRecords = 0;
  numGenres = 0;
}

// Collection::~Collection(){
//   for(unsigned int i = 0; i < records.size(); i++){
//     delRecord(records[i]);
//   }
// }

//----------Tree functions----------
record* addNameHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if((addRec->name > addRoot->name) || (addRec->name == addRoot->name && addRec->artist > addRoot->artist)){
    addRoot->nameRight = addNameHelper(addRoot->nameRight, addRec);
    addRoot->nameRight->nameParent = addRoot;
  }
  if((addRec->name < addRoot->name) || (addRec->name == addRoot->name && addRec->artist < addRoot->artist)){
    addRoot->nameLeft = addNameHelper(addRoot->nameLeft, addRec);
    addRoot->nameLeft->nameParent = addRoot;
  }
  return addRoot;
}
void Collection::addNameTree(record* addRec){
  if(nameRoot == NULL){
    nameRoot = addRec;
  }
  else{
    addNameHelper(nameRoot, addRec);
  }
}

record* addArtistHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if((addRec->artist > addRoot->artist) || (addRec->artist == addRoot->artist && addRec->name > addRoot->name)){
    addRoot->artistRight = addArtistHelper(addRoot->artistRight, addRec);
    addRoot->artistRight->artistParent = addRoot;
  }
  if((addRec->artist < addRoot->artist) || (addRec->artist == addRoot->artist && addRec->name < addRoot->name)){
    addRoot->artistLeft = addArtistHelper(addRoot->artistLeft, addRec);
    addRoot->artistLeft->artistParent = addRoot;
  }
  return addRoot;
}
void Collection::addArtistTree(record* addRec){
  if(artistRoot == NULL){
    artistRoot = addRec;
  }
  else{
    addArtistHelper(artistRoot, addRec);
  }
}

record* addYearHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if((addRec->year > addRoot->year) || (addRec->year == addRoot->year && addRec->artist > addRoot->artist) || (addRec->year == addRoot->year && addRec->artist == addRoot->artist && addRec->name > addRoot->name)){
    addRoot->yearRight = addYearHelper(addRoot->yearRight, addRec);
    addRoot->yearRight->yearParent = addRoot;
  }
  if((addRec->year < addRoot->year) || (addRec->year == addRoot->year && addRec->artist < addRoot->artist) || (addRec->year == addRoot->year && addRec->artist == addRoot->artist && addRec->name < addRoot->name)){
    addRoot->yearLeft = addYearHelper(addRoot->yearLeft, addRec);
    addRoot->yearLeft->yearParent = addRoot;
  }
  return addRoot;
}
void Collection::addYearTree(record* addRec){
  if(yearRoot == NULL){
    yearRoot = addRec;
  }
  else{
    addYearHelper(yearRoot, addRec);
  }
}

record* addNumListensHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if(addRec->numListens > addRoot->numListens || (addRec->numListens == addRoot->numListens && addRec->artist > addRoot->artist) || (addRec->numListens == addRoot->numListens && addRec->artist == addRoot->artist && addRec->name > addRoot->name)){
    addRoot->numListensRight = addNumListensHelper(addRoot->numListensRight, addRec);
    addRoot->numListensRight->numListensParent = addRoot->numListensRight;
  }
  if(addRec->numListens < addRoot->numListens || (addRec->numListens == addRoot->numListens && addRec->artist < addRoot->artist) || (addRec->numListens == addRoot->numListens && addRec->artist == addRoot->artist && addRec->name < addRoot->name)){
    addRoot->numListensLeft = addNumListensHelper(addRoot->numListensLeft, addRec);
    addRoot->numListensLeft->numListensParent = addRoot->numListensLeft;
  }
  return addRoot;
}
void Collection::addNumListensTree(record* addRec){
  if(numListensRoot == NULL){
    numListensRoot = addRec;
  }
  else{
    addNumListensHelper(numListensRoot, addRec);
  }
}

record* addRatingHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if(addRec->rating > addRoot->rating || (addRec->rating == addRoot->rating && addRec->artist > addRoot->artist) || (addRec->rating == addRoot->rating && addRec->artist == addRoot->artist && addRec->name > addRoot->name)){
    addRoot->ratingRight = addRatingHelper(addRoot->ratingRight, addRec);
    addRoot->ratingRight->ratingParent = addRoot->ratingRight;
  }
  if(addRec->rating < addRoot->rating || (addRec->rating == addRoot->rating && addRec->artist < addRoot->artist) || (addRec->rating == addRoot->rating && addRec->artist == addRoot->artist && addRec->name < addRoot->name)){
    addRoot->ratingLeft = addRatingHelper(addRoot->ratingLeft, addRec);
    addRoot->ratingLeft->ratingParent = addRoot->ratingLeft;
  }
  return addRoot;
}
void Collection::addRatingTree(record* addRec){
  if(ratingRoot == NULL){
    ratingRoot = addRec;
  }
  else{
    addRatingHelper(ratingRoot, addRec);
  }
}

record* addGenreHelper(record* addRoot, record* addRec){
  if(addRoot == NULL){
    return addRec;
  }
  if((addRec->artist > addRoot->artist) || (addRec->artist == addRoot->artist && addRec->name > addRoot->name)){
    addRoot->genreRight = addGenreHelper(addRoot->genreRight, addRec);
    addRoot->genreRight->genreParent = addRoot;
  }
  if((addRec->artist < addRoot->artist) || (addRec->artist == addRoot->artist && addRec->name < addRoot->name)){
    addRoot->genreLeft = addGenreHelper(addRoot->genreLeft, addRec);
    addRoot->genreLeft->genreParent = addRoot;
  }
  return addRoot;
}
void Collection::addGenreTree(record* addRec, genre* addGenre){
  if(addGenre->root == NULL){
    addGenre->root = addRec;
  }
  else{
    addGenreHelper(addGenre->root, addRec);
  }
}

genre* Collection::newGenre(string genreName){
  genre* crawler = genresHead;
  while(crawler != NULL){
    if(genreName == crawler->genreName){
      cout << "This genre already exists in your collection." << endl;
      cout << "Adding record to prexisting genre." << endl;
      return crawler;
    }
    crawler = crawler->next;
  }
  genre* newGenre = new genre;
  numGenres++;
  newGenre->genreName = genreName;
  if(genresHead == NULL){
    genresHead = newGenre;
  }
  else if(genresHead->genreName > genreName){
    newGenre->next = genresHead;
    genresHead = newGenre;
  }
  else{
    genre* travGenre = genresHead;
    while(travGenre->next != NULL && travGenre->next->genreName < genreName){
      travGenre = travGenre->next;
    }
    newGenre->next = travGenre->next;
    travGenre->next = newGenre;
  }
  return newGenre;
}

void Collection::delNameTree(record* delRec){
  if(delRec->nameRight == NULL && delRec->nameLeft == NULL){
    if(delRec->nameParent != NULL && delRec->nameParent->nameLeft == delRec){
      delRec->nameParent->nameLeft = NULL;
    }
    else if(delRec->nameParent !=NULL && delRec->nameParent->nameRight == delRec){
      delRec->nameParent->nameRight = NULL;
    }

  }
  else if(delRec->nameRight != NULL && delRec->nameLeft == NULL){
    if(delRec->nameParent != NULL && delRec->nameParent->nameLeft == delRec){
      delRec->nameParent->nameLeft = delRec->nameRight;
    }
    else if(delRec->nameParent !=NULL && delRec->nameParent->nameRight == delRec){
      delRec->nameParent->nameRight = delRec->nameRight;
    }

  }
  else if(delRec->nameRight == NULL && delRec->nameLeft != NULL){
    if(delRec->nameParent != NULL && delRec->nameParent->nameLeft == delRec){
      delRec->nameParent->nameLeft = delRec->nameLeft;
    }
    else if(delRec->nameParent != NULL && delRec->nameParent->nameRight == delRec){
      delRec->nameParent->nameRight = delRec->nameLeft;
    }

  }
  else{
    record* minRight = delRec->nameRight;
    while(minRight->nameLeft != NULL){
      minRight = minRight->nameLeft;
    }

    if(delRec->nameRight == minRight){
      if(delRec->nameParent != NULL){
        if(delRec->nameParent->nameRight == delRec){
          delRec->nameParent->nameRight = minRight;
        }
        else{
          delRec->nameParent->nameLeft = minRight;
        }
        minRight->nameParent = delRec->nameParent;
      }
      else{
        minRight->nameParent = NULL;
      }

      minRight->nameLeft = delRec->nameLeft;
      minRight->nameLeft->nameParent = minRight;

    }
    else{
      minRight->nameParent->nameLeft = minRight->nameRight;
      if(minRight->nameRight != NULL){
        minRight->nameRight->nameParent = minRight->nameParent;
      }
      if(delRec->nameParent != NULL){
        if(delRec->nameParent->nameRight == delRec){
          delRec->nameParent->nameRight = minRight;
        }
        else{
          delRec->nameParent->nameLeft = minRight;
        }
        minRight->nameParent = delRec->nameParent;
      }
      else{
        minRight->nameParent = NULL;
      }
      minRight->nameRight = delRec->nameRight;
      minRight->nameLeft = delRec->nameLeft;
      delRec->nameLeft->nameParent = minRight;
      delRec->nameRight->nameParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->nameParent == NULL){
    nameRoot = delRec;
  }
}

void Collection::delArtistTree(record* delRec){
  if(delRec->artistRight == NULL && delRec->artistLeft == NULL){
    if( delRec->artistParent != NULL && delRec->artistParent->artistLeft == delRec){
      delRec->artistParent->artistLeft = NULL;
    }
    else if(delRec->artistParent !=NULL && delRec->artistParent->artistRight == delRec){
      delRec->artistParent->artistRight = NULL;
    }

  }
  else if(delRec->artistRight != NULL && delRec->artistLeft == NULL){
    if(delRec->artistParent != NULL && delRec->artistParent->artistLeft == delRec){
      delRec->artistParent->artistLeft = delRec->artistRight;
    }
    else if(delRec->artistParent !=NULL && delRec->artistParent->artistRight == delRec){
      delRec->artistParent->artistRight = delRec->artistRight;
    }

  }
  else if(delRec->artistRight == NULL && delRec->artistLeft != NULL){
    if(delRec->artistParent != NULL && delRec->artistParent->artistLeft == delRec){
      delRec->artistParent->artistLeft = delRec->artistLeft;
    }
    else if(delRec->artistParent != NULL && delRec->artistParent->artistRight == delRec){
      delRec->artistParent->artistRight = delRec->artistLeft;
    }

  }
  else{
    record* minRight = delRec->artistRight;
    while(minRight->artistLeft != NULL){
      minRight = minRight->artistLeft;
    }

    if(delRec->artistRight == minRight){
      if(delRec->artistParent != NULL){
        if(delRec->artistParent->artistRight == delRec){
          delRec->artistParent->artistRight = minRight;
        }
        else{
          delRec->artistParent->artistLeft = minRight;
        }
        minRight->artistParent = delRec->artistParent;
      }
      else{
        minRight->artistParent = NULL;
      }

      minRight->artistLeft = delRec->artistLeft;
      minRight->artistLeft->artistParent = minRight;

    }
    else{
      minRight->artistParent->artistLeft = minRight->artistRight;
      if(minRight->artistRight != NULL){
        minRight->artistRight->artistParent = minRight->artistParent;
      }
      if(delRec->artistParent != NULL){
        if(delRec->artistParent->artistRight == delRec){
          delRec->artistParent->artistRight = minRight;
        }
        else{
          delRec->artistParent->artistLeft = minRight;
        }
        minRight->artistParent = delRec->artistParent;
      }
      else{
        minRight->artistParent = NULL;
      }
      minRight->artistRight = delRec->artistRight;
      minRight->artistLeft = delRec->artistLeft;
      delRec->artistLeft->artistParent = minRight;
      delRec->artistRight->artistParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->artistParent == NULL){
    nameRoot = delRec;
  }
}

void Collection::delYearTree(record* delRec){
  if(delRec->yearRight == NULL && delRec->yearLeft == NULL){
    if(delRec->yearParent != NULL && delRec->yearParent->yearLeft == delRec){
      delRec->yearParent->yearLeft = NULL;
    }
    else if(delRec->yearParent !=NULL && delRec->yearParent->yearRight == delRec){
      delRec->yearParent->yearRight = NULL;
    }

  }
  else if(delRec->yearRight != NULL && delRec->yearLeft == NULL){
    if(delRec->yearParent != NULL && delRec->yearParent->yearLeft == delRec){
      delRec->yearParent->yearLeft = delRec->yearRight;
    }
    else if(delRec->yearParent !=NULL && delRec->yearParent->yearRight == delRec){
      delRec->yearParent->yearRight = delRec->yearRight;
    }

  }
  else if(delRec->yearRight == NULL && delRec->yearLeft != NULL){
    if(delRec->yearParent != NULL && delRec->yearParent->yearLeft == delRec){
      delRec->yearParent->yearLeft = delRec->yearLeft;
    }
    else if(delRec->yearParent != NULL && delRec->yearParent->yearRight == delRec){
      delRec->yearParent->yearRight = delRec->yearLeft;
    }

  }
  else{
    record* minRight = delRec->yearRight;
    while(minRight->yearLeft != NULL){
      minRight = minRight->yearLeft;
    }

    if(delRec->yearRight == minRight){
      if(delRec->yearParent != NULL){
        if(delRec->yearParent->yearRight == delRec){
          delRec->yearParent->yearRight = minRight;
        }
        else{
          delRec->yearParent->yearLeft = minRight;
        }
        minRight->yearParent = delRec->yearParent;
      }
      else{
        minRight->yearParent = NULL;
      }

      minRight->yearLeft = delRec->yearLeft;
      minRight->yearLeft->yearParent = minRight;

    }
    else{
      minRight->yearParent->yearLeft = minRight->yearRight;
      if(minRight->yearRight != NULL){
        minRight->yearRight->yearParent = minRight->yearParent;
      }
      if(delRec->yearParent != NULL){
        if(delRec->yearParent->yearRight == delRec){
          delRec->yearParent->yearRight = minRight;
        }
        else{
          delRec->yearParent->yearLeft = minRight;
        }
        minRight->yearParent = delRec->yearParent;
      }
      else{
        minRight->yearParent = NULL;
      }
      minRight->yearRight = delRec->yearRight;
      minRight->yearLeft = delRec->yearLeft;
      delRec->yearLeft->yearParent = minRight;
      delRec->yearRight->yearParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->yearParent == NULL){
    yearRoot = delRec;
  }
}

void Collection::delNumListensTree(record* delRec){
  if(delRec->numListensRight == NULL && delRec->numListensLeft == NULL){
    if(delRec->numListensParent != NULL && delRec->numListensParent->numListensLeft == delRec){
      delRec->numListensParent->numListensLeft = NULL;
    }
    else if(delRec->numListensParent !=NULL && delRec->numListensParent->numListensRight == delRec){
      delRec->numListensParent->numListensRight = NULL;
    }

  }
  else if(delRec->numListensRight != NULL && delRec->numListensLeft == NULL){
    if(delRec->numListensParent != NULL && delRec->numListensParent->numListensLeft == delRec){
      delRec->numListensParent->numListensLeft = delRec->numListensRight;
    }
    else if(delRec->numListensParent != NULL && delRec->numListensParent->numListensRight == delRec){
      delRec->numListensParent->numListensRight = delRec->numListensRight;
    }

  }
  else if(delRec->numListensRight == NULL && delRec->numListensLeft != NULL){
    if(delRec->numListensParent != NULL && delRec->numListensParent->numListensLeft == delRec){
      delRec->numListensParent->numListensLeft = delRec->numListensLeft;
    }
    else if(delRec->numListensParent != NULL && delRec->numListensParent->numListensRight == delRec){
      delRec->numListensParent->numListensRight = delRec->numListensLeft;
    }

  }
  else{
    record* minRight = delRec->numListensRight;
    while(minRight->numListensLeft != NULL){
      minRight = minRight->numListensLeft;
    }

    if(delRec->numListensRight == minRight){
      if(delRec->numListensParent != NULL){
        if(delRec->numListensParent->numListensRight == delRec){
          delRec->numListensParent->numListensRight = minRight;
        }
        else{
          delRec->numListensParent->numListensLeft = minRight;
        }
        minRight->numListensParent = delRec->numListensParent;
      }
      else{
        minRight->numListensParent = NULL;
      }

      minRight->numListensLeft = delRec->numListensLeft;
      minRight->numListensLeft->numListensParent = minRight;

    }
    else{
      minRight->numListensParent->numListensLeft = minRight->numListensRight;
      if(minRight->numListensRight != NULL){
        minRight->numListensRight->numListensParent = minRight->numListensParent;
      }
      if(delRec->numListensParent != NULL){
        if(delRec->numListensParent->numListensRight == delRec){
          delRec->numListensParent->numListensRight = minRight;
        }
        else{
          delRec->numListensParent->numListensLeft = minRight;
        }
        minRight->numListensParent = delRec->numListensParent;
      }
      else{
        minRight->numListensParent = NULL;
      }
      minRight->numListensRight = delRec->numListensRight;
      minRight->numListensLeft = delRec->numListensLeft;
      delRec->numListensLeft->numListensParent = minRight;
      delRec->numListensRight->numListensParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->numListensParent == NULL){
    numListensRoot = delRec;
  }
}

void Collection::delRatingTree(record* delRec){
  if(delRec->ratingRight == NULL && delRec->ratingLeft == NULL){
    if(delRec->ratingParent != NULL && delRec->ratingParent->ratingLeft == delRec){
      delRec->ratingParent->ratingLeft = NULL;
    }
    else if(delRec->ratingParent != NULL && delRec->ratingParent->ratingRight == delRec){
      delRec->ratingParent->ratingRight = NULL;
    }

  }
  else if(delRec->ratingRight != NULL && delRec->ratingLeft == NULL){
    if(delRec->ratingParent != NULL && delRec->ratingParent->ratingLeft == delRec){
      delRec->ratingParent->ratingLeft = delRec->ratingRight;
    }
    else if(delRec->ratingParent != NULL && delRec->ratingParent->ratingRight == delRec){
      delRec->ratingParent->ratingRight = delRec->ratingRight;
    }

  }
  else if(delRec->ratingRight == NULL && delRec->ratingLeft != NULL){
    if(delRec->ratingParent != NULL && delRec->ratingParent->ratingLeft == delRec){
      delRec->ratingParent->ratingLeft = delRec->ratingLeft;
    }
    else if(delRec->ratingParent != NULL && delRec->ratingParent->ratingRight == delRec){
      delRec->ratingParent->ratingRight = delRec->ratingLeft;
    }

  }
  else{
    record* minRight = delRec->ratingRight;
    while(minRight->ratingLeft != NULL){
      minRight = minRight->ratingLeft;
    }

    if(delRec->ratingRight == minRight){
      if(delRec->ratingParent != NULL){
        if(delRec->ratingParent->ratingRight == delRec){
          delRec->ratingParent->ratingRight = minRight;
        }
        else{
          delRec->ratingParent->ratingLeft = minRight;
        }
        minRight->ratingParent = delRec->ratingParent;
      }
      else{
        minRight->ratingParent = NULL;
      }

      minRight->ratingLeft = delRec->ratingLeft;
      minRight->ratingLeft->ratingParent = minRight;

    }
    else{
      minRight->ratingParent->ratingLeft = minRight->ratingRight;
      if(minRight->ratingRight != NULL){
        minRight->ratingRight->ratingParent = minRight->ratingParent;
      }
      if(delRec->ratingParent != NULL){
        if(delRec->ratingParent->ratingRight == delRec){
          delRec->ratingParent->ratingRight = minRight;
        }
        else{
          delRec->ratingParent->ratingLeft = minRight;
        }
        minRight->ratingParent = delRec->ratingParent;
      }
      else{
        minRight->ratingParent = NULL;
      }
      minRight->ratingRight = delRec->ratingRight;
      minRight->ratingLeft = delRec->ratingLeft;
      delRec->ratingLeft->ratingParent = minRight;
      delRec->ratingRight->ratingParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->ratingParent == NULL){
    ratingRoot = delRec;
  }
}

void Collection::delGenreTree(record* delRec){
  if(delRec->genreRight == NULL && delRec->genreLeft == NULL){
    if(delRec->genreParent != NULL && delRec->genreParent->genreLeft == delRec){
      delRec->genreParent->genreLeft = NULL;
    }
    else if(delRec->genreParent != NULL && delRec->genreParent->genreRight == delRec){
      delRec->genreParent->genreRight = NULL;
    }
    else if(delRec == delRec->genre->root){
      if(delRec->genre == genresHead){
        genresHead = genresHead->next;
      }
      else{
        genre* crawler = genresHead;
        while(crawler->next != delRec->genre){
          crawler = crawler->next;
        }
        crawler->next = crawler->next->next;
      }
      delete delRec->genre;
      numGenres--;
    }

  }
  else if(delRec->genreRight != NULL && delRec->genreLeft == NULL){
    if(delRec->genreParent != NULL && delRec->genreParent->genreLeft == delRec){
      delRec->genreParent->genreLeft = delRec->genreRight;
    }
    else if(delRec->genreParent != NULL && delRec->genreParent->genreRight == delRec){
      delRec->genreParent->genreRight = delRec->genreRight;
    }

  }
  else if(delRec->genreRight == NULL && delRec->genreLeft != NULL){
    if(delRec->genreParent != NULL && delRec->genreParent->genreLeft == delRec){
      delRec->genreParent->genreLeft = delRec->genreLeft;
    }
    else if(delRec->genreParent != NULL && delRec->genreParent->genreRight == delRec){
      delRec->genreParent->genreRight = delRec->genreLeft;
    }

  }
  else{
    record* minRight = delRec->genreRight;
    while(minRight->genreLeft != NULL){
      minRight = minRight->genreLeft;
    }

    if(delRec->genreRight == minRight){
      if(delRec->genreParent != NULL){
        if(delRec->genreParent->genreRight == delRec){
          delRec->genreParent->genreRight = minRight;
        }
        else{
          delRec->genreParent->genreLeft = minRight;
        }
        minRight->genreParent = delRec->genreParent;
      }
      else{
        minRight->genreParent = NULL;
      }

      minRight->genreLeft = delRec->genreLeft;
      minRight->genreLeft->genreParent = minRight;

    }
    else{
      minRight->genreParent->genreLeft = minRight->genreRight;
      if(minRight->genreRight != NULL){
        minRight->genreRight->genreParent = minRight->genreParent;
      }
      if(delRec->genreParent != NULL){
        if(delRec->genreParent->genreRight == delRec){
          delRec->genreParent->genreRight = minRight;
        }
        else{
          delRec->genreParent->genreLeft = minRight;
        }
        minRight->genreParent = delRec->genreParent;
      }
      else{
        minRight->genreParent = NULL;
      }
      minRight->genreRight = delRec->genreRight;
      minRight->genreLeft = delRec->genreLeft;
      delRec->genreLeft->genreParent = minRight;
      delRec->genreRight->genreParent = minRight;

    }
    delRec = minRight;
  }
  if(delRec->genreParent == NULL){
    delRec->genre->root = delRec;
  }
}

void Collection::delRecord(record* delRec){
  delNameTree(delRec);
  delArtistTree(delRec);
  delYearTree(delRec);
  delNumListensTree(delRec);
  delRatingTree(delRec);
  delGenreTree(delRec);

  record* currAdjRecord;
  for(unsigned int i = 0; i < delRec->adj.size(); i++){
    currAdjRecord = delRec->adj[i].r;
    for(unsigned int j = 0; j < currAdjRecord->adj.size(); j++){
      if(currAdjRecord->adj[j].r == delRec){
        currAdjRecord->adj.erase(currAdjRecord->adj.begin() + j);
      }
    }
  }

  for(unsigned int i = 0; i < log.size(); i++){
    if(log[i] == delRec){
      log.erase(log.begin() + i);
    }
  }

  queue<record*> tempQ;
  while(!listeningQ.empty()){
    if(listeningQ.front() == delRec){
      listeningQ.pop();
    }
    else{
      tempQ.push(listeningQ.front());
      listeningQ.pop();
    }
  }

  int delRecNum = delRec->recordNumber;
  int recordsPos = -1;
  for(unsigned int i = 0; i < records.size(); i++){
    if(records[i]->recordNumber > delRecNum){
      records[i]->recordNumber--;
    }
    else if(records[i]->recordNumber == delRecNum){
      recordsPos = i;
    }
  }
  numRecords--;
  records.erase(records.begin() + recordsPos);
  delete delRec;
}

record* Collection::getYearRoot(){
  return yearRoot;
}

record* Collection::getRatingRoot(){
  return ratingRoot;
}

record* Collection::getArtistRoot(){
  return artistRoot;
}

record* Collection::getNameRoot(){
  return nameRoot;
}

record* Collection::getNumListensRoot(){
  return numListensRoot;
}

//----------Graph functions----------

void Collection::addEdge(record* r1, record* r2, int num){
  for(unsigned int i = 0; i < r1->adj.size(); i++){
    if(r1->adj[i].r == r2){
      for(unsigned int j = 0; j < r2->adj.size(); j++){
        if(r2->adj[j].r == r1){
          r1->adj[i].adjListens++;
          r2->adj[j].adjListens++;
          return;
        }
      }
    }
  }
  edgeRecord newEdge1;
  newEdge1.r = r2;
  newEdge1.adjListens = num;
  r1->adj.push_back(newEdge1);

  edgeRecord newEdge2;
  newEdge2.r = r1;
  newEdge2.adjListens = num;
  r2->adj.push_back(newEdge2);
}

void Collection::addRecord(int number, string name, string artist, int year, string genreInp, int numListens, float rating){
  record* newRecord = new record;
  newRecord->recordNumber = number;
  newRecord->name = name;
  newRecord->artist = artist;
  newRecord->year = year;
  genre* addGenre;
  genre* crawler;
  crawler = genresHead;
  while(crawler != NULL){ //See if the genre is already there
    if(crawler->genreName == genreInp){
      break;
    }
    crawler = crawler->next;
  }
  if(crawler == NULL){ //If the genre isn't there
    addGenre = newGenre(genreInp);
  }
  else{
    addGenre = crawler;
  }
  newRecord->genre = addGenre;
  newRecord->numListens = numListens;
  newRecord->rating = rating;
  records.push_back(newRecord);
  addNameTree(newRecord);
  addArtistTree(newRecord);
  addYearTree(newRecord);
  addNumListensTree(newRecord);
  addRatingTree(newRecord);
  addGenreTree(newRecord, addGenre);
}

void Collection::resetRecordCounters(){
  currCounter = 0;
  for(unsigned int i = 0; i < records.size(); i++){
    records[i]->counter = 0;
  }
  genre* crawler = genresHead;
  while(crawler != NULL){
    crawler->counter = 0;
    crawler = crawler->next;
  }
}

int Collection::getCurrCounter(){
  return currCounter;
}

record* Collection::returnCounterRecord(int recCounter){
  for(unsigned int i = 0; i < records.size(); i++){
    if(records[i]->counter == recCounter){
      return records[i];
    }
  }
  return NULL;
}

record* Collection::returnGenreRoot(int genreCounter){
  int counter = 1;
  genre* crawler = genresHead;
  while(counter != genreCounter){
    counter++;
    crawler = crawler->next;
  }
  return crawler->root;
}

bool Collection::collectionEmpty(){
  if(records.empty()){
    return true;
  }
  else{
    return false;
  }
}

int Collection::getNumGenres(){
  return numGenres;
}

int Collection::getNumRecords(){
  return numRecords;
}

void Collection::setNumRecords(int numRec){
  numRecords = numRec;
}

void Collection::setFolderName(string foldName){
  currFolderName = foldName;
}

void Collection::addToLog(record* addRec){
  if(!log.empty()){
    addEdge(addRec, log.back(), 1);
  }
  log.push_back(addRec);
}

void Collection::addToQueue(record* addRec){
  listeningQ.push(addRec);
}

void Collection::removeFromQueue(int pos){
  int counter = 1;
  queue<record*> temp;
  while(!listeningQ.empty()){
    if(counter != pos){
      temp.push(listeningQ.front());
    }
    listeningQ.pop();
    counter++;
  }
  while(!temp.empty()){
    listeningQ.push(temp.front());
    temp.pop();
  }
}

void Collection::setAllRecordsUnvisited(){
  for(unsigned int i = 0; i < records.size(); i++){
    records[i]->visited = false;
    records[i]->prev = NULL;
    records[i]->distance = 0;
  }
}

bool Collection::antiDijkstra(record* startRec, record* endRec){
  setAllRecordsUnvisited();
  startRec->visited = true;
  startRec->distance = 0;
  queue<record*> travQ;
  travQ.push(startRec);
  record* currTravRec;
  bool foundTrav = false;
  while(!travQ.empty()){ //Do a Breadth First Search on the graph, make sure the two points are connected.
    currTravRec = travQ.front();
    travQ.pop();
    for(unsigned int i = 0; i < currTravRec->adj.size(); i++){
      if(!currTravRec->adj[i].r->visited){
        currTravRec->adj[i].r->distance = currTravRec->distance + 1;
        if(currTravRec->adj[i].r == endRec){
          foundTrav = true;
          break;
        }
        else{
          currTravRec->adj[i].r->visited = true;
          travQ.push(currTravRec->adj[i].r);
        }
      }
    }
  }

  if(foundTrav == true){
    vector<record*> solvedList;
    setAllRecordsUnvisited();
    startRec->visited = true;
    solvedList.push_back(startRec);
    int minDist = 2147483647;
    int currDist = 0;
    record* solvedRec;
    record* currRec;

    while(!endRec->visited){
      minDist = 2147483647;
      solvedRec = NULL;
      for(unsigned int x = 0; x < solvedList.size(); x++){
        currRec = solvedList[x];
        for(unsigned int y = 0; y < currRec->adj.size(); y++){
          if(!currRec->adj[y].r->visited){
            currDist = currRec->distance - currRec->adj[y].adjListens;
            if(currDist < minDist){
              solvedRec = currRec->adj[y].r;
              minDist = currDist;
              currRec->adj[y].r->prev = currRec;
            }
          }
        }
      }
      solvedRec->distance = minDist;
      solvedRec->visited = true;
      solvedList.push_back(solvedRec);
    }
    return true;
  }
  else{
    return false;
  }
}

void Collection::longestPath(record* startRec, record* endRec){
  record* checkRec = endRec;
  record* s1Rec = startRec;
  vector<record*> path;
  resetRecordCounters();
  path.push_back(checkRec);
  while(checkRec != s1Rec){
    checkRec = checkRec->prev;
    path.push_back(checkRec);
  }

  cout << "Recommendations" << endl;
  cout << "---------------" << endl;

  for(int j = path.size() - 1; j > -1; j--){
    if(path[j] != startRec && path[j] != endRec){
      currCounter++;
      path[j]->counter = currCounter;
      cout << currCounter << ". '" << path[j]->name << "' by " << path[j]->artist << endl;
    }

  }
}

//----------File i/o functions----------
void Collection::saveCollection(){
  resetRecordCounters();
  int time_int = time(NULL); //Set the random number seed based on the current time
  srand(time_int);
  string currFileName = currFolderName + "/collection.csv";
  ofstream saveStream;
  int counter = 0;
  int currRecord = 0;
  record* recordPtr;
  string nameSave;
  string artistSave;

  saveStream.open(currFileName);
  while(counter < numRecords){
    currRecord = rand() % numRecords; //0-63
    recordPtr = records[currRecord];
    nameSave = recordPtr->name;
    artistSave = recordPtr->artist;
    if(recordPtr->counter == 0){
      for(unsigned int i = 0; i < nameSave.length(); i++){
        if(nameSave[i] == ','){
          nameSave[i] = '%';
        }
      }
      for(unsigned int j = 0; j < artistSave.length(); j++){
        if(artistSave[j] == ','){
          artistSave[j] = '%';
        }
      }
      saveStream << recordPtr->recordNumber << "," << nameSave << "," << artistSave << "," << recordPtr->year << "," << recordPtr->genre->genreName << "," << recordPtr->rating << "," << recordPtr->numListens << endl;
      recordPtr->counter = 1;
      counter++;
    }
  }
  saveStream.close();
  currFileName = currFolderName + "/log.csv";
  saveStream.open(currFileName);
  for(unsigned int k = 0; k < log.size(); k++){
    saveStream << log[k]->recordNumber << endl;
  }
  saveStream.close();

  currFileName = currFolderName + "/queue.csv";
  queue<record*> tempQ;
  saveStream.open(currFileName);
  while(!listeningQ.empty()){
    saveStream << listeningQ.front()->recordNumber << endl;
    tempQ.push(listeningQ.front());
    listeningQ.pop();
  }
  saveStream.close();
  while(!tempQ.empty()){
    listeningQ.push(tempQ.front());
    tempQ.pop();
  }
}
bool Collection::loadCollection(string folderName){
  ifstream inStream;
  string currFileName = folderName + "/collection.csv";
  inStream.open(currFileName);
  string line;

  if(inStream.is_open()){
    while(getline(inStream, line)){
      string recNumber;
      string recName;
      string recArtist;
      string recYear;
      string recGenre;
      string recRating;
      string recNumListens;
      stringstream ss(line);

      getline(ss, recNumber, ',');
      getline(ss, recName, ',');
      getline(ss, recArtist, ',');
      getline(ss, recYear, ',');
      getline(ss, recGenre, ',');
      getline(ss, recRating, ',');
      getline(ss, recNumListens);
      for(unsigned int i = 0; i < recName.length(); i++){
        if(recName[i] == '%'){
          recName[i] = ',';
        }
      }
      for(unsigned int j = 0; j < recArtist.length(); j++){
        if(recArtist[j] == '%'){
          recArtist[j] = ',';
        }
      }
      for(unsigned int a = 0; a < recGenre.length(); a++){
        if(recGenre[a] == '%'){
          recGenre[a] = ',';
        }
      }
      int recNumberInt = stoi(recNumber);
      int recYearInt = stoi(recYear);
      float recRatingFloat = stof(recRating);
      int recListensInt = stoi(recNumListens);
      if(numRecords < recNumberInt){
        numRecords = recNumberInt;
      }
      addRecord(recNumberInt, recName, recArtist, recYearInt, recGenre, recListensInt, recRatingFloat);
    }
  }
  else{
    cout << "Collection not found." << endl;
    return false;
  }
  inStream.close();

  currFileName = folderName + "/log.csv";
  inStream.open(currFileName);
  if(inStream.is_open()){
    while(getline(inStream, line)){
      int currNumber = stoi(line);
      for(unsigned int i2 = 0; i2 < records.size(); i2++){
        if(records[i2]->recordNumber == currNumber){
          if(!log.empty() && records[i2] != log.back()){
            addEdge(records[i2], log.back(), 1);
          }
          log.push_back(records[i2]);
          break;
        }
      }
    }
  }
  else{
    cout << "No listening log found - assuming empty" << endl;
  }
  inStream.close();

  currFileName = folderName + "/queue.csv";
  inStream.open(currFileName);
  if(inStream.is_open()){
    while(getline(inStream, line)){
      int currQNumber = stoi(line);
      for(unsigned int i3 = 0; i3 < records.size(); i3++){
        if(records[i3]->recordNumber == currQNumber){
          listeningQ.push(records[i3]);
          break;
        }
      }
    }
  }
  else{
    cout << "No listening queue found - assuming empty" << endl;
  }
  inStream.close();

  return true;
}

//----------Printing functions----------
void Collection::printNameArtist(record *printRec){
  cout << printRec->name << endl;
  cout << "    -by: " << printRec->artist << endl;
}
void Collection::printYear(record *printRec){
  cout << "    -released: " << printRec->year << endl;
}
void Collection::printOneGenre(record *printRec){
  cout << "    -genre: " << printRec->genre->genreName << endl;
}
void Collection::printNumListens(record *printRec){
  cout << "    -number of listens: " << printRec->numListens << endl;
}
void Collection::printRating(record *printRec){
  cout << "    -rating: ";
  if(printRec->rating != -1){
    cout << printRec->rating << endl;
  }
  else{
    cout << "NO RATING" << endl;
  }

}
void Collection::printYearRange(record *printRec, int low, int high){
  if(printRec == NULL){
    return;
  }
  printYearRange(printRec->yearLeft, low, high);
  if(low <= printRec->year && high >= printRec->year){
    currCounter++;
    cout << currCounter << ". ";
    printRec->counter = currCounter;
    printNameArtist(printRec);
    printYear(printRec);
  }
  printYearRange(printRec->yearRight, low, high);
}
void Collection::printMinRating(record *printRec, float minRating){
  if(printRec == NULL){
    return;
  }
  printMinRating(printRec->ratingLeft, minRating);
  if(minRating <= printRec->rating){
    currCounter++;
    cout << currCounter << ". ";
    printRec->counter = currCounter;
    printNameArtist(printRec);
    printRating(printRec);
  }
  printMinRating(printRec->ratingRight, minRating);
}
void Collection::printAllGenres(){
  currCounter = 0;
  genre* crawler = genresHead;
  while(crawler != NULL){
    currCounter++;
    cout << currCounter << ". ";
    crawler->counter = currCounter;
    cout << crawler->genreName << endl;
    crawler = crawler->next;
  }
}
void Collection::printFromGenre(record *printRec){
  if(printRec == NULL){
    return;
  }
  printFromGenre(printRec->genreLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printFromGenre(printRec->genreRight);
}
void Collection::printAllByArtist(record *printRec){
  if(printRec == NULL){
    return;
  }
  printAllByArtist(printRec->artistLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printAllByArtist(printRec->artistRight);
}
void Collection::printAllByName(record *printRec){
  if(printRec == NULL){
    return;
  }
  printAllByName(printRec->nameLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printAllByName(printRec->nameRight);
}
void Collection::printAllByYear(record *printRec){
  if(printRec == NULL){
    return;
  }
  printAllByYear(printRec->yearLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printYear(printRec);
  printAllByYear(printRec->yearRight);
}
void Collection::printAllByGenre(){
  genre* crawler = genresHead;
  while(crawler != NULL){
    cout << crawler->genreName << endl;
    for(unsigned int i = 0; i < crawler->genreName.length(); i++){
      cout << "-";
    }
    cout << endl;
    printFromGenre(crawler->root);
    cout << endl;
    crawler = crawler->next;
  }
}
void Collection::printAllByNumListens(record *printRec){
  if(printRec == NULL){
    return;
  }
  printAllByNumListens(printRec->numListensLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printNumListens(printRec);
  printAllByNumListens(printRec->numListensRight);
}
void Collection::printAllByRating(record *printRec){
  if(printRec == NULL){
    return;
  }
  printAllByRating(printRec->ratingLeft);
  currCounter++;
  cout << currCounter << ". ";
  printRec->counter = currCounter;
  printNameArtist(printRec);
  printRating(printRec);
  printAllByRating(printRec->ratingRight);
}

void Collection::printListeningLog(){
  cout << endl << "LISTENING LOG" << endl;
  cout << "-------------" << endl;
  for(unsigned int i = 0; i < log.size(); i++){
    cout << "'" << log[i]->name << "' by " << log[i]->artist << endl;
  }
}

int Collection::printQueue(){
  if(listeningQ.empty()){
    cout << "Your queue is empty!" << endl;
    return -1;
  }
  else{
    cout << endl << "LISTENING QUEUE" << endl;
    cout << "---------------" << endl;
    queue<record*> temp;
    int counter = 0;
    while(!listeningQ.empty()){
      counter++;
      cout << counter << ". '" << listeningQ.front()->name << "' by " << listeningQ.front()->artist << endl;
      temp.push(listeningQ.front());
      listeningQ.pop();
    }
    while(!temp.empty()){
      listeningQ.push(temp.front());
      temp.pop();
    }
    return counter;
  }
}

void Collection::printReccInGenre(record* currRec, genre* reccGenre){
  if(currRec == NULL){
    return;
  }
  printReccInGenre(currRec->numListensLeft, reccGenre);
  if(currRec->genre == reccGenre){
    printNameArtist(currRec);
    printNumListens(currRec);
  }
  printReccInGenre(currRec->numListensRight, reccGenre);
}

void Collection::print2DUtilHelper(record *currNode, int space)
{
    // Base case
    if (currNode == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->ratingRight, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cout << currNode->name;

    // Process left child
    print2DUtilHelper(currNode->ratingLeft, space);
}

void Collection::print2DUtil( int space)
{
  print2DUtilHelper(ratingRoot, space);
}
