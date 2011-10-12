// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

#include "Global.h"

DeclShared(InputLayout)
class InputLayout : public LogWriter
{
public:
    ~InputLayout();

private:
    friend class Device;
    InputLayout(Log*);
    ID3D11InputLayout* m_pInputLayout;
};

#endif // INPUTLAYOUT_H
