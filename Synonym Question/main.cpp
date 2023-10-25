#include "SemanticDictionary.h"
using namespace std;


void printMenu()
{
    cout << "1.  Read the semantic dictionary from storage" << endl;
    cout << "2.  Write the semantic dictionary to storage" << endl;
    cout << "3.  Read and process a text file (get smarter!)" << endl;
    cout << "4.  Solve a TOEFL question" << endl;
    cout << "5.  Run automated testing" << endl;
    cout << "6.  Quit" << endl;
    cout << "> ";
}

int main()
{
    //declare SemanticDictionary object
    SemanticDictionary d;

    //declare string for menu choice
    string choice;

    //declare and assign a string for the dictionary file name
    string dictionaryFilename = "SemanticDictionary.txt";

    //output some kind of welcome message
    cout << "Welcome to the program!!!\n";

    //print the menu
    printMenu();
    //input the menu choice
    cin >> choice;

    while (choice != "6")
    {
        if (choice == "1")
        {
            //output that you are reading the dictionary file
            cout << "Reading dictionary from file...\n";

            //construct ifstream object and open the file
            ifstream ifs(dictionaryFilename);
  
            if (!ifs)
            {
                cout << "Dictionary file can't be opened...\n";
            }
            else
            {
                //extract from ifstream object into your dictionary object
                ifs >> d;
                //output that you are done reading
                cout << "Done reading.\n";
            }
        }
        else if (choice == "2")
        {
            //warn the user that this will overwrite the previous file, ask if they want to proceed
            cout << "The previous file will be overwrite. Do you want to proceed? (y or n): ";
            //if proceed
            string answer;
            cin >> answer;
            if (answer == "y")
            {
                //output that you are writing the dictionary to a file
                cout << "Writing dictionary to a file...\n";
                //declare and open ofstream object
                ofstream ofs(dictionaryFilename);
                //insert from the dictionary object into the ofstream object
                ofs << d;
                //output that you are done writing
                cout << "Done writing.\n";
            }
        }
        else if (choice == "3")
        {
            //declare variable for file name
            string userFileName;
            //prompt and input file name
            cout << "Name of the file: ";
            cin >> userFileName;
            //construct ifstream object and open the file
            ifstream ifs(userFileName);

            if (!ifs)
            {
                cout << "The file can't be opened...\n";
            }
            else
            {
                cout << "The file is processing...\n";
                auto start = high_resolution_clock::now(); //code to record time elapsed
                //declare a variable to hold all of the text
                string giantText;
                //loop to read every word in the file.  Concatenate each word onto text, separated by " "
                string word;
                while (ifs >> word) giantText += word + " ";
                vector<vector<string>> sentenceLists = getSentenceLists(giantText);
                for(vector<string> sentenceList : sentenceLists)
                    for(string targetWord : sentenceList) d.processTargetWord(targetWord, sentenceList);

                auto stop = high_resolution_clock::now();  //code to record time elapsed
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << "Done.  Time elapsed: " << duration.count() << " milliseconds" << endl;
            }
        }
        else if (choice == "4")
        {
            //this is a copy and paste of the logic from your old project, starting with "Enter a TOEFL question..."
            cout << "Enter a TOEFL question as <word> <answer> <choice1> <choice2> <choice3>:" << endl;
            string word, answer, choice1, choice2, choice3;
            cin >> word >> answer >> choice1 >> choice2 >> choice3;

            try
            {
                string s = d.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
                cout << "Most similar: " << s << endl;
                cout << "Index: " << d.getSimilarity(word, s) << endl;
                if(s == answer) cout << "Correct answer." << endl;
                else cout << "Incorrect answer." << endl;
            }
            catch(runtime_error& e)
            {
                cout << e.what() << endl;
            }
        }
        else if (choice == "5") {
            ifstream toeflQuestionsFile("toeflQuestions.txt");
            if (!toeflQuestionsFile) {
                cout << "The file can't be opened...\n";
            }
            else {
                ifstream ifs(dictionaryFilename);
                ifs >> d;
                string word, answer, choice1, choice2, choice3, s;
                double total = 0.0;
                double correct = 0.0;
                while (toeflQuestionsFile >> word >> answer >> choice1 >> choice2 >> choice3) {
                    s = d.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
                    if (s == answer) correct++;
                    total++;
                }
                cout << "Done. The program has " << correct / total * 100 << "% of answering TOEFL questions correctly.\n";
            }
        }
        else
        {
            cout << "Invalid menu choice" << endl;
        }

        //print the menu
        //input the menu choice
        printMenu();
        cin >> choice;
    }

    return 0;
}
