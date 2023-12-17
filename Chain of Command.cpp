#include <iostream>
#include <string>

using namespace std;

class HelpHandler {
    HelpHandler* successor;
public:
    HelpHandler(HelpHandler* successor = nullptr) : successor(successor) {}

    virtual void showHelp() {
        if (successor != nullptr) {
            successor->showHelp();
        }
        else {
            cout << "No help available." << endl;
        }
    }

    virtual ~HelpHandler() {}
};

class Button : public HelpHandler {
public:
    Button(HelpHandler* successor = nullptr) : HelpHandler(successor) {}

    void click() {
        cout << "Button clicked." << endl;
        showHelp();
    }
};

class TextBox : public HelpHandler {
public:
    TextBox(HelpHandler* successor = nullptr) : HelpHandler(successor) {}

    void setText(const string& text) {
        cout << "Text set: " << text << endl;
    }

    void enter() {
        cout << "Enter key pressed in TextBox." << endl;
        showHelp();
    }
};

class Dialog : public HelpHandler {
public:
    Dialog(HelpHandler* successor = nullptr) : HelpHandler(successor) {}

    void close() {
        cout << "Dialog closed." << endl;
        showHelp();
    }
};

int main() {
    HelpHandler* button = new Button();
    HelpHandler* textBox = new TextBox(button);
    HelpHandler* dialog = new Dialog(textBox);

    cout << "User interacts with the system:" << endl;

    dynamic_cast<Button*>(button)->click();
    dynamic_cast<TextBox*>(textBox)->setText("Hello, Chain of Responsibility!");
    dynamic_cast<TextBox*>(textBox)->enter();
    dynamic_cast<Dialog*>(dialog)->close();

    delete dialog;
    delete textBox;
    delete button;

    return 0;
}