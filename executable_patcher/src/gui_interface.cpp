#include "../inc/gui_interface.h"

#define FLTK_STATIC
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>
#include <string>
#include "../inc/patcher.h"

class PatcherApp {
private:
    Fl_Window* window;
    Fl_Input* inputFile;
    Fl_Input* outputFile;
    Fl_Text_Buffer* textBuffer;
    Fl_Output* statusOutput;

    static void input_file_cb(Fl_Widget*, void* app) {
        static_cast<PatcherApp*>(app)->choose_input_file();
    }

    static void output_file_cb(Fl_Widget*, void* app) {
        static_cast<PatcherApp*>(app)->choose_output_file();
    }

    static void patch_cb(Fl_Widget*, void* app) {
        static_cast<PatcherApp*>(app)->perform_patch();
    }

    void choose_input_file() {
        Fl_Native_File_Chooser chooser;
        chooser.title("Select Input File");
        chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);

        if (chooser.show() == 0) {
            inputFile->value(chooser.filename());
        }
    }

    void choose_output_file() {
        Fl_Native_File_Chooser chooser;
        chooser.title("Select Output File");
        chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);

        if (chooser.show() == 0) {
            outputFile->value(chooser.filename());
        }
    }

    void perform_patch() {
        const char* inPath = inputFile->value();
        const char* outPath = outputFile->value();
        const char* content = textBuffer->text();

        if (!inPath || !*inPath) {
            statusOutput->value("Error: No input file specified");
            return;
        }
        if (!outPath || !*outPath) {
            statusOutput->value("Error: No output file specified");
            return;
        }
        if (!content || !*content) {
            statusOutput->value("Error: No content to embed");
            return;
        }

        int result = patch(content, strlen(content), inPath, outPath);

        switch (result) {
        case 0:
            statusOutput->value("Patching...");
            signFile(outPath);
            statusOutput->value("Success! File patched and signed");
            break;
        case 1: statusOutput->value("Error: Cannot open input file"); break;
        case 2: statusOutput->value("Error: Cannot create output file"); break;
        case 3: statusOutput->value("Error: Buffer identifier not found"); break;
        case 4: statusOutput->value("Warning: Buffer limit reached"); break;
        default: statusOutput->value("Unknown error occurred");
        }
    }

public:
    PatcherApp(int argc, char** argv) {
        Fl::scheme("gtk+");

        // Main window
        window = new Fl_Window(650, 500, "Binary Files Patcher");
        window->begin();

        Fl_Box* header = new Fl_Box(20, 10, 560, 30, "BINARY FILES PATCHER");
        header->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
        header->labelfont(FL_BOLD);
        header->labelsize(18);

        // File inputs
        inputFile = new Fl_Input(100, 75, 430, 25, "File to patch:");
        Fl_Button* inputBtn = new Fl_Button(540, 75, 100, 25, "Browse...");
        inputBtn->callback(input_file_cb, this);

        outputFile = new Fl_Input(100, 135, 430, 25, "Patched file:");
        Fl_Button* outputBtn = new Fl_Button(540, 135, 100, 25, "Browse...");
        outputBtn->callback(output_file_cb, this);

        // Текстовый редактор
        textBuffer = new Fl_Text_Buffer();
        Fl_Text_Editor* editor = new Fl_Text_Editor(20, 195, 560, 200);
        editor->buffer(textBuffer);

        // Статус и кнопка
        statusOutput = new Fl_Output(60, 430, 560, 25, "Status:");
        Fl_Button* patchBtn = new Fl_Button(480, 465, 100, 25, "Patch File");
        patchBtn->callback(patch_cb, this);

        window->end();
    }

    int run() {
        window->show();
        return Fl::run();
    }
};

int run_gui(int argc, char** argv) {
    PatcherApp app(argc, argv);
    return app.run();
}