
#include "mimeTypes.h"

namespace DBProject
{
    namespace MimeTypes {

        struct Mapping
        {
            const char* extension;
            const char* mime_type;
        } mappings[] =
        {
          { "gif", "image/gif" },
          { "htm", "text/html" },
          { "html", "text/html" },
          { "jpg", "image/jpeg" },
          { "png", "image/png" },
          { "plaintext", "text/plain" }
        };

        std::string extension_to_type(const std::string& extension)
        {
            for (Mapping m : mappings)
            {
                if (m.extension == extension)
                {
                    return m.mime_type;
                }
            }

            return "text/plain";
        }

    } // namespace MimeTypes
}
