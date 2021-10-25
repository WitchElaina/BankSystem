#ifndef COMMANDTRANSLATOR_H
#define COMMANDTRANSLATOR_H

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

};

#endif // COMMANDTRANSLATOR_H
