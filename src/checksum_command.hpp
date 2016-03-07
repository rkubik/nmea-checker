#pragma once

#include "basic_command.hpp"

class ChecksumCommand : public BasicCommand
{
public:
    ChecksumCommand(void);

protected:
    bool execute(void) override;
};
