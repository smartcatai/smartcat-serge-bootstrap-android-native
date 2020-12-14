
common-settings
{
    job
    {
        source_match                            strings\.xml$
        source_process_subdirs                  NO
        normalize_strings                       YES

        # Android provides a built-in fallback mechanism, so there's no need
        # to copy source strings into localization files before they are replaced
        # with the actual translations. So we will keep translations blank, and then
        # remove blank entries completely in the :cleanup-android-xml-file callback (see below)
        leave_untranslated_blank                YES

        parser
        {
            plugin                              parse_android
        }

        # Map certain language codes to Android-specific (Java-specific) ones
        output_lang_rewrite
        {
            id                                  in
            no                                  nb
        }

        callback_plugins
        {
            :cleanup-android-xml-file
            {
                plugin                          replace_strings
                phase                           before_save_localized_file

                data
                {
                    # remove untranslatable strings and collections
                    replace                     `<string\s[^>]+\btranslatable="false"[^>]*>.*?<\/string>`                  `\n` sg
                    replace                     `<string-array\s[^>]+\btranslatable="false"[^>]*>.*?<\/string-array>`      `\n` sg
                    replace                     `<plurals\s[^>]+\btranslatable="false"[^>]*>.*?<\/plurals>`                `\n` sg

                    # remove empty (not translated yet) strings and clean up the file
                    replace                     `\s*<!--.*?-->\s*\n`                                  `\n` sg   # remove comments at the end of lines
                    replace                     `\s*<!--.*?-->\s*`                                      `` sg   # remove all other comments
                    replace                     `\s*<string\s[^>]+><\/string>\s*\n`                   `\n` sg   # remove lines with empty <string> elements
                    replace                     `\s*<item(\s[^>]+)?><\/item>\s*\n`                    `\n` sg   # remove lines with empty <item> elements (with and without attributes)
                    replace                     `\s*<string-array\s[^>]+>\s*<\/string-array>\s*\n`    `\n` sg   # remove lines with empty <string-array> elements
                    replace                     `\s*<plurals\s[^>]+>\s+<\/plurals>\s*\n`              `\n` sg   # remove lines with empty <plurals> elements
                    replace                     `\n{2,}(<\/resources>)`                             `\n$1` sg   # remove extra newlines before the closing tag (for aesthetic reasons)
                }
            }

        }
    }
}
