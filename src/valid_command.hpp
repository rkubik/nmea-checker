#pragma once

#include "basic_command.hpp"
#include "ireader.hpp"

#include <memory>
using namespace std;

class ValidCommand : public BasicCommand
{
public:
    ValidCommand(void);

protected:
    bool execute(void) override;
    
    static bool run(, bool stop_on_error);
private:
    IReader *reader_;
};
