#ifndef REDIT_H
#define REDIT_H

#include <QString>

namespace Redit {

void find_text(const QString& plain_text, const QString& text_to_find);

void replace_text(QString& text);

}


#endif // REDIT_H
