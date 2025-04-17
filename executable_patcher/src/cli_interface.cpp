#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include <climits>
#include "../inc/patcher.h"
#include "../inc/cli_interface.h"

using std::cin;
using std::cout;
using std::endl;

void showHelp() {
    std::cout << "\n=== Help ===\n";
    std::cout << "0 - Show this help message\n";
    std::cout << "1 - Enter text to save\n";
    std::cout << "Q - Quit the program\n";
    std::cout << "============\n\n";
}

bool confirmQuit() {
    std::cout << "Are you sure you want to quit? (Y/N): ";
    char response;
    std::cin >> response;
    std::cin.ignore();

    return (toupper(response) == 'Y');
}


int run_cli()
{
    cout << "\n+-----------------------------------------------------------------+\n" <<
        "|                                                                 |\n" <<
        "|                     BINARY FILES PATCHER                        |\n" <<
        "|                 A simple tool to patch binary files             |\n" <<
        "|      by writing data to the buffer with specified signature     |\n" <<
        "|                      By George Kobrusev                         |\n" <<
        "|                                                                 |\n" <<
        "+-----------------------------------------------------------------+\n";


    char* savedText = new char[10240];
    std::string content;
    int size = 0;
    char choice;
    std::string file_to_patch;
    std::string file_patched;

    showHelp();

    do {

        //system("signtool /?");

        std::cout << "Enter your choice (0-help, 1-enter text, Q-quit): ";
        std::cin >> choice;
        std::cin.ignore();

        switch (toupper(choice)) {
        case '0':
        {
            showHelp();
            break;
        }
        case '1':
        {
            cout << "Enter the path to file to be patched: ";
            cin >> file_to_patch;
            cout << "Enter the path to target file (the one which will be created)";
            cin >> file_patched;

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "\nEnter the content to embed: \n" << std::endl;
            //cin.getline(savedText, 10240);
            std::getline(cin, content);

            int result = patch(content.c_str(), content.length(), file_to_patch, file_patched);

            if (result == 0)
            {
                cout << "\n[OK] : File successfully patched\n\t Applying signature...\n...\n";
                signFile(file_patched);
            }
            else if (result == 1)
            {
                cout << "\n[ERROR] : Cannot open input file\n";
            }
            else if (result == 2)
            {
                cout << "\n[ERROR] : Cannot open output file\n";
            }
            else if (result == 3)
            {
                cout << "\n[MEH] : Couldn't find buffer identifier <st   ...   st>\n";
            }
            else if (result == 4)
            {
                cout << "\n[MEH] : Buffer limit reached. Possible loss of data\n";
            }

            break;
        }
        case 'Q':
        {
            if (confirmQuit()) {
                delete[] savedText;
                return 0;
            }
            break;
        }
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (true);

    return 0;
}