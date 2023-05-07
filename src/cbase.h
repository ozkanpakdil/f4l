#ifndef CBASE_H
#define CBASE_H

#include <QScrollArea>

/**this is the class used for scroll jobs
tabletopRightLable
  *@author �zkan pakdil
  */
class CBase:public QScrollArea
{
public:
    CBase (QWidget * parent = 0, const char *name = 0, Qt::WFlags f = 0);
    ~CBase ();
};

#endif
