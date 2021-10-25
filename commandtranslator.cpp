#include "commandtranslator.h"
#include "config.h"

CommandTranslator::CommandTranslator()
{

}

bool CommandTranslator::indexCheck(int num)
{
    if(num>=DEFAULT_ACCOUNT_INDEX)
        return false;

    else
        return true;
}

void CommandTranslator::invalidCommandSkiper(int cmd_index,fstream cmd)
{
    string cmd_trash;
    if(!indexCheck(cmd_index))
        getline(cmd,cmd_trash);
}
