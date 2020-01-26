#include "Collection.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void menu(){
  cout << endl << "Main Menu" << endl;
  cout << "---------" << endl;
  cout << "1. View your Collection" << endl;
  cout << "2. Add a New Record" << endl;
  cout << "3. Edit a Record" << endl;
  cout << "4. Listening Log" << endl;
  cout << "5. Listening Queue" << endl;
  cout << "6. Recommend Records" << endl;
  cout << "7. Quit" << endl;
  cout << "---------" << endl;
}

int main(int argc, char* argv[]){
  string choice = "";
  string originalString = "";
  int choiceInt = 0;
  float choiceFloat = 0;
  bool validInput = true;
  int mainCounter = 0;

  time_t t = time(NULL);
  tm* timePtr = localtime(&t);
  int currYear = timePtr->tm_year + 1900;

  Collection mainColl;
  bool loaded = mainColl.loadCollection(argv[1]);
  if(loaded == false){
    cout << "Unable to load file." << endl;
    return 0;
    do{
      validInput = true;
      cout << "Would you like to create a new collection? (y/n): ";
      getline(cin, choice);
      if(choice == "Y" || choice == "y"){
        choice = "y";
      }
      else if(choice == "N" || choice == "n"){
        choice = "n";
      }
      else{
        cout << "Please enter 'y' or 'n'. Press enter to continue." << endl;
        cin.ignore();
        validInput = false;
      }
    }while(validInput == false);

    if(choice != "y"){
      cout << "Goodbye!" << endl;
      return 0;
    }
  }
  mainColl.setFolderName(argv[1]);
  cout << endl;
  cout << "                  ooo /// /// ooo" << endl;
  cout << "              o//                 //o" << endl;
  cout << "          o//                         //o" << endl;
  cout << "       o//                               //o" << endl;
  cout << "     o//                                   //o" << endl;
  cout << "   o//                                       //o" << endl;
  cout << "  o//               Welcome to                //o" << endl;
  cout << " o//                                           //o" << endl;
  cout << "o//                    /  /                     //o" << endl;
  cout << "o//                 /        /                  //o" << endl;
  cout << "o//                /          /                 //o" << endl;
  cout << "o//                 /        /                  //o" << endl;
  cout << "o//                    /  /                     //o" << endl;
  cout << " o//                                           //o" << endl;
  cout << "  o//         the Record Collector +!         //o" << endl;
  cout << "   o//                                       //o" << endl;
  cout << "     o//                                   //o" << endl;
  cout << "       o//                               //o" << endl;
  cout << "          o//                         //o" << endl;
  cout << "              o//                 //o" << endl;
  cout << "                  ooo /// /// ooo" << endl << endl;
  cout << "Press enter to continue." << endl;
  cin.ignore();

  do{
    menu();
    cout << "Enter a numeric option: ";
    getline(cin, choice);
    validInput = true;
    if(choice == "1" && !mainColl.collectionEmpty()){
      mainColl.resetRecordCounters();
      do{
        cout << endl << "How would you like to view your collection?" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "1. View all records" << endl;
        cout << "2. View records in a year range" << endl;
        cout << "3. View records greater than a certain rating" << endl;
        cout << "4. View records in a specific genre" << endl << endl;
        cout << "Enter a numeric option: ";
        getline(cin, choice);
        validInput = true;
        if(choice == "1"){
          do{
            cout << endl << "How would you like to view all your records?" << endl;
            cout << "--------------------------------------------" << endl;
            cout << "1. By Artist" << endl;
            cout << "2. By Name" << endl;
            cout << "3. By Year" << endl;
            cout << "4. By Genre" << endl;
            cout << "5. By Number of Listens" << endl;
            cout << "6. By Rating" << endl << endl;
            cout << "Enter a numeric option: ";
            getline(cin, choice);
            validInput = true;
            if(choice == "1"){
              cout << endl;
              mainColl.printAllByArtist(mainColl.getArtistRoot());
            }
            else if(choice == "2"){
              mainColl.printAllByName(mainColl.getNameRoot());
            }
            else if(choice == "3"){
              mainColl.printAllByYear(mainColl.getYearRoot());
            }
            else if(choice == "4"){
              mainColl.printAllByGenre();
            }
            else if(choice == "5"){
              mainColl.printAllByNumListens(mainColl.getNumListensRoot());
            }
            else if(choice == "6"){
              mainColl.printAllByRating(mainColl.getRatingRoot());
            }
            else{
              cout << "Invalid input. Please enter a number between 1-6. Press";
              cout << "enter to continue." << endl;
              cin.ignore();
              validInput = false;
            }
          }while(validInput == false);
        }
        else if(choice == "2"){
          cout << "What year range would you like to view from?" << endl;
          do{
            cout << "Input the earliest year: ";
            validInput = true;
            getline(cin, choice);
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int i = 0; i < choice.length(); i++){
              if(!isdigit(choice[i])){
                validInput = false;
                cout << "Please enter a valid year (no negatives or decimals!)";
                cout << ". Press enter to continue." << endl;
                cin.ignore();
              }
            }
          }while(validInput == false);
          int minYear = stoi(choice);

          do{
            cout << "Input the latest year: ";
            validInput = true;
            getline(cin, choice);
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int j = 0; j < choice.length(); j++){
              if(!isdigit(choice[j])){
                validInput = false;
                cout << "Please enter a valid year (no negatives or decimals!)";
                cout << ". Press enter to continue." << endl;
                cin.ignore();
              }
            }
          }while(validInput == false);
          int maxYear = stoi(choice);
          cout << endl << "All records from " << minYear << "-" << maxYear
          << ":" << endl;
          mainColl.printYearRange(mainColl.getYearRoot(), minYear, maxYear);
        }
        else if(choice == "3"){
          cout << "What is the minimum rating you want to view?" << endl;
          do{
            cout << "Input the minimum rating: ";
            getline(cin, choice);
            validInput = true;
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int k = 0; k < choice.length(); k++){
              if((k == 1 && choice[k] != '.') || (k != 1 && !isdigit(choice[k]))){
                validInput = false;
                cout << "Please enter a valid rating (no negatives!). Press";
                cout << " enter to continue." << endl;
              }
            }
          }while(validInput == false);
          choiceFloat = stof(choice);
          cout << endl << "All records with a minimum rating of " << choiceFloat
          << ":" << endl;
          mainColl.printMinRating(mainColl.getRatingRoot(), choiceFloat);
        }
        else if(choice == "4"){
          cout << endl;
          mainColl.printAllGenres();
          do{
            cout << "Which genre do you want to view from?" << endl;
            cout << "Enter a numeric option: ";
            getline(cin, choice);
            validInput = true;
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int i2 = 0; i2 < choice.length(); i2++){
              if(!(isdigit(choice[i2]))){
                validInput = false;
                break;
              }
            }
            if(validInput == false || stoi(choice) > mainColl.getNumGenres() ||
            stoi(choice) < 1){
              cout << "Please enter a number between 1-" <<
              mainColl.getNumGenres() << ". Press enter to continue." << endl;
              cin.ignore();
              validInput = false;
            }
          }while(validInput == false);
          record* currGenreRoot = mainColl.returnGenreRoot(stoi(choice));
          cout << "Genre: " << currGenreRoot->genre->genreName << endl;
          mainColl.resetRecordCounters();
          mainColl.printFromGenre(currGenreRoot);
        }
        else{
          cout << "Invalid input. Please enter a number between 1-4. Press";
          cout << " Enter to continue." << endl;
          cin.ignore();
          validInput = false;
        }
      }while(validInput == false);
      cout << endl << "What would you like to do?" << endl;
      cout << "-------------------------------------------------" << endl;
      cout << "1. View all details of a specific record" << endl;
      cout << "2. Go to the main menu" << endl << endl;
      do{
        getline(cin, choice);
        validInput = true;
        if(choice == "1"){
          do{
            cout << "Which record? (enter a number from the record list above)"
            << endl;
            getline(cin, choice);
            validInput = true;
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int i3 = 0; i3 < choice.length(); i3++){
              if(!(isdigit(choice[i3]))){
                validInput = false;
                break;
              }
            }
            if(validInput == false || stoi(choice) < 1 || stoi(choice) >
            mainColl.getCurrCounter()){
              cout << "Please enter a number between 1-" <<
              mainColl.getCurrCounter() << ". Press enter to continue." << endl;
              cin.ignore();
              validInput = false;
            }
          }while(validInput == false);
          cout << endl;
          record* currRecordPrint = mainColl.returnCounterRecord(stoi(choice));
          mainColl.printNameArtist(currRecordPrint);
          mainColl.printYear(currRecordPrint);
          mainColl.printOneGenre(currRecordPrint);
          mainColl.printNumListens(currRecordPrint);
          mainColl.printRating(currRecordPrint);
        }
        else if(choice == "2"){
          continue;
        }
        else{
          cout << "Invalid input. Please enter a number between 1-2. Press";
          cout << " Enter to continue." << endl;
          cin.ignore();
          validInput = false;
        }

      }while(validInput == false);
      validInput = false;
    }
    else if(choice == "2"){
      string addName;
      string addArtist;
      string addYear;
      string addGenre;
      string addRating;
      int yearInt;
      float ratingFloat;
      do{
        cout << "What is the name of the record you want to add?" << endl;
        getline(cin, addName);
        validInput = true;
        if(addName == ""){
          validInput = false;
        }
        for(unsigned int index = 0; index < addName.length(); index++){
          if(addName[index] == '%'){
            cout << "Error: You can't have '%' in the name." << endl;
            validInput = false;
          }
        }
      }while(validInput == false);
      do{
        cout << "What is the artist's name for this record?" << endl;
        getline(cin, addArtist);
        validInput = true;
        if(addArtist == ""){
          validInput = false;
        }
        for(unsigned int index1 = 0; index1 < addArtist.length(); index1++){
          if(addArtist[index1] == '%'){
            cout << "Error: You can't have '%' in the name." << endl;
            validInput = false;
          }
        }
      }while(validInput == false);

      do{
        cout << "What year was this record released?" << endl;
        getline(cin, addYear);
        validInput = true;
        for(unsigned int j = 0; j < addYear.length(); j++){
          if(!isdigit(addYear[j])){
            validInput = false;
            break;
          }
        }
        if(validInput == true && stoi(addYear) > currYear){
          validInput = false;
        }
        if(validInput == false){
          cout << "Please enter a valid year." << endl;
          cout << "Note: You can't add a record that hasn't come out yet." << endl;
          cout << "Press enter to continue." << endl;
          cin.ignore();
        }

      }while(validInput == false);
      yearInt = stoi(addYear);
      if(mainColl.getNumGenres() == 0){
        do{
          cout << "Which genre does this record belong to?" << endl;
          cout << "Note: Press enter to set it as Uncategorized." << endl;
          getline(cin, addGenre);
          validInput = true;
          for(unsigned int index2 = 0; index2 < addGenre.length(); index2++){
            if(addGenre[index2] == '%'){
              cout << "Error: You can't have '%' in the genre name." << endl;
              validInput = false;
            }
          }
        }while(validInput == false);
      }
      else{
        mainColl.resetRecordCounters();
        mainColl.printAllGenres();
        int numOfGenres = mainColl.getNumGenres();
        cout << numOfGenres + 1 << ". MAKE NEW GENRE" << endl << endl;
        do{
          cout << "Which genre does this record belong to?" << endl;
          cout << "Note: Press enter to set it as Uncategorized." << endl;
          getline(cin, addGenre);
          validInput = true;
          if(addGenre == ""){
            continue;
          }
          else{
            for(unsigned int index3 = 0; index3 < addGenre.length(); index3++){
              if(!isdigit(addGenre[index3])){
                validInput = false;
                break;
              }
            }
            if(validInput == false || stoi(addGenre) < 1 || stoi(addGenre) > numOfGenres + 1){
              cout << "Error: Please enter a valid number between 1-" << numOfGenres + 1 << endl;
              validInput = false;
            }
          }
        }while(validInput == false);
        if(addGenre != "" && stoi(addGenre) != numOfGenres + 1){
          addGenre = mainColl.returnGenreRoot(stoi(addGenre))->genre->genreName;
        }
        else if(addGenre != "" && stoi(addGenre) == numOfGenres + 1){
          do{
            cout << "What is the name of the new genre?" << endl;
            getline(cin, addGenre);
            for(unsigned int index5 = 0; index5 < addGenre.length(); index5++){
              if(addGenre[index5] == '%'){
                cout << "Error: You can't have '%' in the genre name." << endl;
                validInput = false;
              }
            }
          }while(validInput == false);
        }
      }
      if(addGenre == ""){
        addGenre = "Uncategorized";
      }
      do{
        cout << "What do you rate this album?" << endl;
        cout << "Note: Press enter to leave as unrated." << endl;
        getline(cin, addRating);
        validInput = true;
        if(addRating == ""){
          continue;
        }
        else{
          for(unsigned int index4 = 0; index4 < addRating.length(); index4++){
            if((index4 == 1 && addRating[index4] != '.') || (index4 != 1 && !isdigit(addRating[index4]))){
              validInput = false;
              break;
            }
          }
          if(validInput == false || stof(addRating) < 0 || stof(addRating) > 5){
            cout << "Please enter a valid rating. Rating must be between 0-5." << endl;
            cout << "Press enter to continue." << endl;
            cin.ignore();
            validInput = false;
          }
        }
      }while(validInput == false);
      if(addRating == ""){
        ratingFloat = -1;
      }
      else{
        ratingFloat = stof(addRating);
      }
      do{
        cout << "Are you sure you want to add " << addName << " by " << addArtist << " (You can edit details later from the main menu)? (y/n)" << endl;
        getline(cin, choice);
        validInput = true;
        if(choice == "Y" || choice == "y"){
          mainColl.setNumRecords(mainColl.getNumRecords() + 1);
          mainColl.addRecord(mainColl.getNumRecords(), addName, addArtist, yearInt, addGenre, 0, ratingFloat);
          mainColl.saveCollection();
          cout << addName << " by " << addArtist << " successfully added." << endl;
        }
        else if(choice == "N" || choice == "n"){
          continue;
        }
        else{
          cout << "Please enter 'y' or 'n'. Press enter to continue." << endl;
          cin.ignore();
          validInput = false;
        }
      }while(validInput == false);
      validInput = false;
    }
    else if(choice == "3" && !mainColl.collectionEmpty()){
      mainColl.resetRecordCounters();
      mainColl.printAllByArtist(mainColl.getArtistRoot());
      do{
        cout << "Which record would you like to edit?" << endl;
        getline(cin, choice);
        validInput = true;
        for(unsigned int index6 = 0; index6 < choice.length(); index6++){
          if(!isdigit(choice[index6])){
            validInput = false;
          }
        }
        if(validInput == false || stoi(choice) < 1 || stoi(choice) > mainColl.getNumRecords()){
          cout << "Invalid input! Please enter a number between 1-" << mainColl.getNumRecords() << endl;
          validInput = false;
        }
      }while(validInput == false);
      cout << endl;
      record* currRecordEdit = mainColl.returnCounterRecord(stoi(choice));
      mainColl.printNameArtist(currRecordEdit);
      mainColl.printYear(currRecordEdit);
      mainColl.printOneGenre(currRecordEdit);
      mainColl.printNumListens(currRecordEdit);
      mainColl.printRating(currRecordEdit);
      cout << endl;
      do{
        cout << "Which detail would you like to edit?" << endl;
        cout << "1. Name" << endl;
        cout << "2. Artist" << endl;
        cout << "3. Year" << endl;
        cout << "4. Genre" << endl;
        cout << "5. Rating" << endl;
        cout << "6. Delete Record Entirely" << endl;
        cout << "7. GO BACK TO MAIN MENU" << endl;
        cout << "NOTE: You can edit your listening log from the main menu." << endl;

        getline(cin, choice);
        if(choice == "1"){
          do{
            cout << "New name: ";
            getline(cin, choice);
            validInput = true;
            for(unsigned int index7 = 0; index7 < choice.length(); index7++){
              if(choice[index7] == '%'){
                cout << "Error: Name cannot contain '%'." << endl;
                validInput = false;
              }
            }
          }while(validInput == false);
          do{
            validInput = true;
            cout << "Change '" << currRecordEdit->name << "' to '" << choice << "'? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);
          if(originalString == "y"){
            currRecordEdit->name = choice;
            mainColl.delNameTree(currRecordEdit);
            mainColl.addNameTree(currRecordEdit);
            mainColl.saveCollection();
            cout << "Successfully edited." << endl;
          }
          else{
            validInput = false;
          }
        }
        else if(choice == "2"){
          do{
            cout << "New artist: ";
            getline(cin, choice);
            validInput = true;
            for(unsigned int index8 = 0; index8 < choice.length(); index8++){
              if(choice[index8] == '%'){
                cout << "Error: Artist cannot contain '%'." << endl;
                validInput = false;
              }
            }
          }while(validInput == false);
          do{
            validInput = true;
            cout << "Change '" << currRecordEdit->artist << "' to '" << choice << "'? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);
          if(originalString == "y"){
            currRecordEdit->artist = choice;
            mainColl.delArtistTree(currRecordEdit);
            mainColl.addArtistTree(currRecordEdit);
            mainColl.saveCollection();
            cout << "Successfully edited." << endl;
          }
          else{
            validInput = false;
          }
        }
        else if(choice == "3"){
          do{
            cout << "New year: ";
            getline(cin, choice);
            validInput = true;
            for(unsigned int j = 0; j < choice.length(); j++){
              if(!isdigit(choice[j])){
                validInput = false;
                break;
              }
            }
            if(validInput == true && stoi(choice) > currYear){
              validInput = false;
            }
            if(validInput == false){
              cout << "Please enter a valid year." << endl;
              cout << "Note: You can't have a record that hasn't come out yet." << endl;
              cout << "Press enter to continue." << endl;
              cin.ignore();
            }

          }while(validInput == false);

          do{
            validInput = true;
            cout << "Change " << currRecordEdit->year << " to " << choice << "? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);
          if(originalString == "y"){
            currRecordEdit->year = stoi(choice);
            mainColl.delYearTree(currRecordEdit);
            mainColl.addYearTree(currRecordEdit);
            mainColl.saveCollection();
            cout << "Successfully edited." << endl;
          }
          else{
            validInput = false;
          }
        }
        else if(choice == "4"){
          genre* newEditGenre;
          string editGenre = "";
          mainColl.resetRecordCounters();
          mainColl.printAllGenres();
          int editNumOfGenres = mainColl.getNumGenres();
          cout << editNumOfGenres + 1 << ". MAKE NEW GENRE" << endl << endl;
          do{
            cout << "Which genre does this record belong to?" << endl;
            cout << "Note: Press enter to set it as Uncategorized." << endl;
            getline(cin, editGenre);
            validInput = true;
            if(editGenre == ""){
              continue;
            }
            else{
              for(unsigned int index3 = 0; index3 < editGenre.length(); index3++){
                if(!isdigit(editGenre[index3])){
                  validInput = false;
                  break;
                }
              }
              if(validInput == false || stoi(editGenre) < 1 || stoi(editGenre) > editNumOfGenres + 1){
                cout << "Error: Please enter a valid number between 1-" << editNumOfGenres + 1 << endl;
                validInput = false;
              }
            }
          }while(validInput == false);
          if(editGenre != "" && stoi(editGenre) != editNumOfGenres + 1){ //if not a new genre
            do{
              validInput = true;
              cout << "Change '" << currRecordEdit->genre->genreName << "' to '" << mainColl.returnGenreRoot(stoi(editGenre))->genre->genreName << "'? (y/n)" << endl;
              getline(cin, originalString);
              if(originalString == "Y" || originalString == "y"){
                originalString = "y";
              }
              else if(originalString == "N" || originalString == "n"){
                originalString = "n";
              }
              else{
                cout << "Please enter 'y' or 'n'." << endl;
                validInput = false;
              }
            }while(validInput == false);
            if(originalString == "y"){
              record* editGenreRecord = mainColl.returnGenreRoot(stoi(editGenre));
              mainColl.delGenreTree(currRecordEdit);
              currRecordEdit->genre = editGenreRecord->genre;
              mainColl.addGenreTree(currRecordEdit, editGenreRecord->genre);
              mainColl.saveCollection();
              cout << "Successfully edited." << endl;
            }
            else{
              validInput = false;
            }
          }
          else if(editGenre != "" && stoi(editGenre) == editNumOfGenres + 1){
            do{
              cout << "What is the name of the new genre?" << endl;
              getline(cin, editGenre);
              for(unsigned int index5 = 0; index5 < editGenre.length(); index5++){
                if(editGenre[index5] == '%'){
                  cout << "Error: You can't have '%' in the genre name." << endl;
                  validInput = false;
                }
              }
            }while(validInput == false);

            do{
              validInput = true;
              cout << "Change '" << currRecordEdit->genre->genreName << "' to '" << editGenre << "'? (y/n)" << endl;
              getline(cin, originalString);
              if(originalString == "Y" || originalString == "y"){
                originalString = "y";
              }
              else if(originalString == "N" || originalString == "n"){
                originalString = "n";
              }
              else{
                cout << "Please enter 'y' or 'n'." << endl;
                validInput = false;
              }
            }while(validInput == false);
            if(originalString == "y"){
              mainColl.delGenreTree(currRecordEdit);
              newEditGenre = mainColl.newGenre(editGenre);
              currRecordEdit->genre = newEditGenre;
              mainColl.addGenreTree(currRecordEdit, newEditGenre);
              mainColl.saveCollection();
              cout << "Successfully edited." << endl;
            }
            else{
              validInput = false;
            }
          }
          if(editGenre == ""){ //AHH
            editGenre = "Uncategorized";
          }
        }
        else if(choice == "5"){
          do{
            cout << "New rating: ";
            getline(cin, choice);
            validInput = true;
            if(choice == ""){
              validInput = false;
            }
            for(unsigned int k = 0; k < choice.length(); k++){
              if((k == 1 && choice[k] != '.') || (k != 1 && !isdigit(choice[k]))){
                validInput = false;
                cout << "Please enter a valid rating (no negatives!). Press";
                cout << " enter to continue." << endl;
              }
            }
          }while(validInput == false);

          do{
            validInput = true;
            cout << "Change " << currRecordEdit->rating << " to " << choice << "? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);
          if(originalString == "y"){
            currRecordEdit->rating = stof(choice);
            mainColl.delRatingTree(currRecordEdit);
            mainColl.addRatingTree(currRecordEdit);
            mainColl.saveCollection();
            cout << "Successfully edited." << endl;
          }
          else{
            validInput = false;
          }
        }
        else if(choice == "6"){
          do{
            validInput = true;
            cout << "Are you sure you want to delete '" << currRecordEdit->name << "' from your collection? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);
          if(originalString == "y"){
            mainColl.delRecord(currRecordEdit);
            mainColl.saveCollection();
            cout << "Successfully deleted." << endl;
          }
          else{
            validInput = false;
          }
        }
        else if(choice == "7"){
          continue;
        }
        else{
          cout << "Invalid input. Please enter a number between 1-7!" << endl;
          validInput = false;
        }
      }while(validInput == false);
      validInput = false;

    }
    else if(choice == "4" && !mainColl.collectionEmpty()){
      do{
        cout << "What would you like to do?" << endl;
        cout << "--------------------------" << endl;
        cout << "1. View your listening log" << endl;
        cout << "2. Add to your listening log" << endl << endl;
        cout << "Enter a numeric option:" << endl;
        getline(cin, choice);
        validInput = true;
        if(choice == "1"){
          mainColl.printListeningLog();
          cout << endl << "Press enter to continue." << endl;
          cin.ignore();
        }
        else if(choice == "2"){
          cout << endl;
          mainColl.resetRecordCounters();
          mainColl.printAllByArtist(mainColl.getArtistRoot());
          do{
            cout << endl << "Which record would you like to add?" << endl;
            getline(cin, choice);
            validInput = true;
            for(unsigned int index6 = 0; index6 < choice.length(); index6++){
              if(!isdigit(choice[index6])){
                validInput = false;
              }
            }
            if(validInput == false || stoi(choice) < 1 || stoi(choice) > mainColl.getNumRecords()){
              cout << "Invalid input! Please enter a number between 1-" << mainColl.getNumRecords() << endl;
              validInput = false;
            }
          }while(validInput == false);

          do{
            validInput = true;
            cout << "Add '" << mainColl.returnCounterRecord(stoi(choice))->name << "' to the listening log? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);

          if(originalString == "y"){
            mainColl.addToLog(mainColl.returnCounterRecord(stoi(choice)));
            cout << "Successfully added." << endl;
          }
        }
        else{
          cout << "Invalid input. Please enter a number between 1-2." << endl;
          validInput = false;
        }
      }while(validInput == false);
      validInput = false;
    }
    else if(choice == "5" && !mainColl.collectionEmpty()){
      do{
        cout << "What would you like to do?" << endl;
        cout << "--------------------------" << endl;
        cout << "1. View your listening queue" << endl;
        cout << "2. Add to your listening queue" << endl;
        cout << "3. Remove from the listening queue" << endl << endl;
        cout << "Enter a numeric option:" << endl;
        getline(cin, choice);
        validInput = true;
        if(choice == "1"){
          mainColl.printQueue();
          cout << endl << "Press enter to continue." << endl;
          cin.ignore();
        }
        else if(choice == "2"){
          cout << endl;
          mainColl.resetRecordCounters();
          mainColl.printAllByArtist(mainColl.getArtistRoot());
          do{
            cout << endl << "Which record would you like to add?" << endl;
            getline(cin, choice);
            validInput = true;
            for(unsigned int index6 = 0; index6 < choice.length(); index6++){
              if(!isdigit(choice[index6])){
                validInput = false;
              }
            }
            if(validInput == false || stoi(choice) < 1 || stoi(choice) > mainColl.getNumRecords()){
              cout << "Invalid input! Please enter a number between 1-" << mainColl.getNumRecords() << endl;
              validInput = false;
            }
          }while(validInput == false);

          do{
            validInput = true;
            cout << "Add '" << mainColl.returnCounterRecord(stoi(choice))->name << "' to the listening queue? (y/n)" << endl;
            getline(cin, originalString);
            if(originalString == "Y" || originalString == "y"){
              originalString = "y";
            }
            else if(originalString == "N" || originalString == "n"){
              originalString = "n";
            }
            else{
              cout << "Please enter 'y' or 'n'." << endl;
              validInput = false;
            }
          }while(validInput == false);

          if(originalString == "y"){
            mainColl.addToQueue(mainColl.returnCounterRecord(stoi(choice)));
            mainColl.saveCollection();
            cout << "Successfully added." << endl;
          }
        }
        else if(choice == "3"){
          cout << endl;
          int numInQ = mainColl.printQueue();
          if(numInQ != -1){
            do{
              cout << "Which record would you like to remove from the queue?" << endl;
              getline(cin, choice);
              validInput = true;
              for(unsigned int i = 0; i < choice.length(); i++){
                if(!isdigit(choice[i])){
                  validInput = false;
                }
              }
              if(validInput == false || stoi(choice) < 1 || stoi(choice) > numInQ){
                cout << "Invalid input. Please enter a number between 1-" << numInQ << endl;
                validInput = false;
              }
            }while(validInput == false);
            mainColl.removeFromQueue(stoi(choice));
            mainColl.saveCollection();
            cout << "Successfully removed." << endl;
          }
        }
        else{
          cout << "Invalid input. Please enter a number between 1-3." << endl;
          validInput = false;
        }
      }while(validInput == false);
      validInput = false;
    }
    else if(choice == "6"){
      cout << "How would you like your recommendations to be based?" << endl;
      cout << "----------------------------------------------------" << endl;
      cout << "1. By Genre" << endl;
      cout << "2. By Listening History" << endl << endl;
      do{
        validInput = true;
        getline(cin, choice);
        if(choice == "1"){
          mainColl.resetRecordCounters();
          mainColl.printAllGenres();
          do{
            cout << "Which genre would you like recommendations from?" << endl;
            getline(cin, choice);
            validInput = true;
            for(unsigned int index3 = 0; index3 < choice.length(); index3++){
              if(!isdigit(choice[index3])){
                validInput = false;
                break;
              }
            }
            if(validInput == false || choice == "" || stoi(choice) < 1 || stoi(choice) > mainColl.getNumGenres()){
              cout << "Error: Please enter a valid number between 1-" << mainColl.getNumGenres() << endl;
              validInput = false;
            }
          }while(validInput == false);
          record* reccGenre = mainColl.returnGenreRoot(stoi(choice));
          cout << endl << "We recommend the following" << endl;
          cout << "--------------------------" << endl;
          mainColl.printReccInGenre(mainColl.getNumListensRoot(), reccGenre->genre);
          cout << endl << "Press enter to continue." << endl;
          cin.ignore();
        }
        else if(choice == "2"){
          string rec1Choice = "";
          string rec2Choice = "";
          if(mainColl.getNumRecords() < 3){
            cout << "Sorry, you can't do that unless you have at least 3 records in your collection." << endl;
            validInput = false;
          }
          else{
            mainColl.resetRecordCounters();
            mainColl.printAllByArtist(mainColl.getArtistRoot());
            cout << "Which two records would you like recommendations from?" << endl;
            do{
              cout << "Record 1: ";
              getline(cin, rec1Choice);
              validInput = true;
              for(unsigned int index6 = 0; index6 < rec1Choice.length(); index6++){
                if(!isdigit(rec1Choice[index6])){
                  validInput = false;
                }
              }
              if(validInput == false || rec1Choice == "" || stoi(rec1Choice) < 1 || stoi(rec1Choice) > mainColl.getNumRecords()){
                cout << "Invalid input! Please enter a number between 1-" << mainColl.getNumRecords() << endl;
                validInput = false;
              }
            }while(validInput == false);
            do{
              cout << "Record 2: ";
              getline(cin, rec2Choice);
              validInput = true;
              for(unsigned int index6 = 0; index6 < rec2Choice.length(); index6++){
                if(!isdigit(rec2Choice[index6])){
                  validInput = false;
                }
              }
              if(validInput == false || rec2Choice == "" || stoi(rec2Choice) < 1 || stoi(rec2Choice) > mainColl.getNumRecords()){
                cout << "Invalid input! Please enter a number between 1-" << mainColl.getNumRecords() << endl;
                validInput = false;
              }
              if(rec1Choice == rec2Choice){
                cout << "Invalid input! The records can't be the same." << endl;
                validInput = false;
              }
            }while(validInput == false);
            bool reccCheck = mainColl.antiDijkstra(mainColl.returnCounterRecord(stoi(rec1Choice)), mainColl.returnCounterRecord(stoi(rec2Choice)));
            if(reccCheck == true){
              mainColl.longestPath(mainColl.returnCounterRecord(stoi(rec1Choice)), mainColl.returnCounterRecord(stoi(rec2Choice)));
              cout << "What would you like to do?" << endl;
              cout << "--------------------------" << endl;
              cout << "1. Add every record (in order) to the listening queue" << endl;
              cout << "2. Add one record to the listening queue" << endl;
              cout << "3. Go to the main menu" << endl;
              do{
                validInput = true;
                getline(cin, choice);
                if(choice == "1"){
                  for(unsigned int i = 1; i < mainColl.getCurrCounter() + 1; i++){
                    mainColl.addToQueue(mainColl.returnCounterRecord(i));
                  }
                  cout << "Successfully added to queue." << endl;
                }
                else if(choice == "2"){
                  cout << "Which record would you like to add?" << endl;
                  do{
                    getline(cin, choice);
                    validInput = true;
                    for(unsigned int index6 = 0; index6 < choice.length(); index6++){
                      if(!isdigit(choice[index6])){
                        validInput = false;
                      }
                    }
                    if(validInput == false || choice == "" || stoi(choice) < 1 || stoi(choice) > mainColl.getCurrCounter()){
                      cout << "Invalid input! Please enter a number between 1-" << mainColl.getCurrCounter() << endl;
                      validInput = false;
                    }
                  }while(validInput == false);
                  mainColl.addToQueue(mainColl.returnCounterRecord(stoi(choice)));
                  cout << "Successfully added to queue." << endl;
                }
                else if(choice == "3"){
                  continue;
                }
                else{
                  cout << "Invalid input. Please enter a number between 1-3." << endl;
                  validInput = false;
                }
              }while(validInput == false);
            }
            else{
              cout << "There is no listening linkage between '" << mainColl.returnCounterRecord(stoi(rec1Choice))->name << "' and '" << mainColl.returnCounterRecord(stoi(rec2Choice))->name << "'." << endl;
            }
          }
        }
        else{
          cout << "Invalid input. Please enter a number between 1-2." << endl;
          validInput = false;
        }
      }while(validInput == false);
      validInput = false;
    }
    else if(choice == "7"){
      do{
        validInput = true;
        cout << "Are you sure you want to quit? (y/n)" << endl;
        getline(cin, choice);
        if(choice == "Y" || choice == "y"){
          choice = "y";
        }
        else if(choice == "N" || choice == "n"){
          choice = "n";
        }
        else{
          cout << "Please enter 'y' or 'n'." << endl;
          validInput = false;
        }
      }while(validInput == false);
      if(choice == "y"){
        mainColl.saveCollection();
        cout << "Goodbye!" << endl;
        return 0;
      }
      else{
        validInput = false;
      }
    }
    else if((choice == "1" || choice == "3" || choice == "4" || choice == "5" || choice == "6") && mainColl.collectionEmpty()){
      cout << "Your collection is empty, you can't do that!" << endl;
      cout << "(Add something to your collection!)" << endl;
      cout << "Press enter to continue." << endl;
      cin.ignore();
      validInput = false;
    }
    else{
      cout << "Invalid input. Please enter a number between 1-7. Press enter";
      cout << " to continue." << endl;
      cin.ignore();
      validInput = false;
    }
  }while(validInput == false);

  return 0;
}
