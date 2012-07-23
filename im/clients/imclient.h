#ifndef IMCLIENT_H
#define IMCLIENT_H

#include "../abstractimclient.h"

class ImClient
{
public:
    static AbstractImClient * getImClient(QString clientType);
};

#endif // IMCLIENT_H
