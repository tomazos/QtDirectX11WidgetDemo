// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include "InputLayout.h"

InputLayout::InputLayout(Log* pLog)
    : LogWriter(pLog)
    , m_pInputLayout(0)
{}


InputLayout::~InputLayout()
{
    if (m_pInputLayout)
        m_pInputLayout->Release();
}
