#ifndef COMMANDTRANSLATOR_H
#define COMMANDTRANSLATOR_H

#include "withdrawdialog.h"
#include "ui_withdrawdialog.h"

#include <fstream>
using namespace std;

class CommandTranslator
{
public:
    CommandTranslator();

    // check if the index is safety
    bool indexCheck(int num);

    // skip abunai command
    void invalidCommandSkiper(int cmd_index,fstream cmd);

    // GUI withdraw
    void withdrawGUI(string cmd_username,int cmd_index,double cmd_amount,string cmd_desc);

    // GUI deposite
    void depositeGUI(string cmd_username,int cmd_index,double cmd_amount,string cmd_desc);

};

#endif // COMMANDTRANSLATOR_H
