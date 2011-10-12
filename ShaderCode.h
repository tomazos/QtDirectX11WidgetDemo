// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#ifndef SHADER_H
#define SHADER_H

#include "Global.h"

DeclShared(ShaderCode);
class ShaderCode : LogWriter
{
public:
    static PShaderCode compile(Log* pLog, const QString& sFilename, const QString& sEntryPoint, const QString& sShaderModel);
    ~ShaderCode();

private:
    friend class Device;

    ShaderCode(Log* pLog);
    bool init(const QString& sFilename, const QString& sEntryPoint, const QString& sShaderModel);

    ID3DBlob* m_pShaderCode;
    ID3DBlob* m_pError;
};

#endif // SHADER_H
