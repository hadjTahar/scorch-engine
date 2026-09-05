#ifndef FONT_H
#define FONT_H

#include <misc/defs.h>
#include <string>

namespace Qx {

class Font
{
public:
    Font():
        pxSize{ 11 },
        familyName{ "Noto Sans" },
        bold{ false },
        italic{ false }
    {

    }
    std::string  familyName;
    bool         bold;
    bool         italic;
    x_real       pxSize;

    // This generates all comparisons automatically!
    auto operator<=>(const Font&) const = default;
    bool operator== (const Font &other) const
    {
        return /*pxSize     == other.pxSize &&*/
               familyName == other.familyName &&
               bold       == other.bold &&
               italic     == other.italic;
    }

    friend std::ostream& operator<<(std::ostream& os, const Font& font) {
        os << "Font(" <<
            font.familyName <<
            (font.bold ? ", bold" : "") <<
            (font.italic ? ", italic" : "") <<
            ")";
        return os;
    }
};

}
#endif // FONT_H
