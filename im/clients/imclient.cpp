#include "imclient.h"
#include "pidgin.h"
#include "none.h"

AbstractImClient *ImClient::getImClient(QString clientType)
{
    if ( "pidgin" == clientType ) {
        return new Pidgin();
    } else {
        return new None();
    }
}
